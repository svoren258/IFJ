#include "parser.h"
#include "error.h"

tTablePtr globTable;
Ttoken *token;
tStack *gStack;

void keywords_init() {
    int i = 0;
    while (keywords[i]) {

        token->name = keywords[i];
        TVariable *v = new_variable(token);
        v->type = TYPE_KEYWORD;

        store_variable(v, &globTable);
        i++;
    }

}

void parser_init() {

    gStack = stackInit();

    BSTInit(&globTable);
    BSTInsert(&globTable, &globTable, "GlobTable");

    /*keywords to globtable*/
    keywords_init();

}

void parser_finish() {
    BSTDispose(&globTable);

}

TFunction *new_function(Ttoken *token) {    /*allocate the space for a new function*/
    TFunction *f;
    f = malloc(sizeof(TFunction));

    tTablePtr loc_table;
    BSTInit(&loc_table);

    tStack *stack = stackInit();

    f->stack = stack;
    /*assign the table to the function*/
    f->defined = FALSE;
    f->type = RET_INT;
    f->table = loc_table;
    f->name = token->name;
    return f;
}

TVariable *new_variable(Ttoken *token) {
    TVariable *v;
    v = malloc(sizeof(TVariable));

    v->inicialized = FALSE;
    v->name = token->name;
    return v;

}

void store_function(/*stack*/TFunction *f, tTablePtr *table) {
    tTablePtr new_func;
    BSTInit(&new_func);

    BSTInsert(table, &new_func, f->name);
    stackPush(gStack, f);
}

void store_variable(/*stack*/TVariable *v, tTablePtr *table) {

    if (BSTExists(*table, v->name)) {
        ret_error(SYNTAX_ERROR);
    }

    tTablePtr new_var;
    BSTInit(&new_var);

    BSTInsert(table, &new_var, v->name);
    new_var->data.v = v;


}


/*--------------------automat-----------------------*/
void starter() {
    Ttoken token = get_token();
    while (token->data == class) {  //token->type == TOKEN_CLASS

        token = get_token();
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }
        if (BSTSearch(classTable, token.data)) {
            ret_error(SEMANTIC_DEF_ERROR);
        }
        Ttable *table = create_class_table(token.data);
        token = get_token();
        if (token->type != L_BRACKET) {
            ret_error(SYNTAX_ERROR);
        }
        token = get_token();
        while (token->type == TOKEN_STATIC) {
            token = get_token();
            Declaration(table, token);
            token = get_token();

//        } else if (token->data == class) {
//            token = get_token();
//            if (token.type != TOKEN_ID) {
//                ret_error(SYNTAX_ERROR);
//            }
//            if (BSTExists(classTable, token.data) {
//                ret_error(SEMANTIC_DEF_ERROR);
//            }
//            table = create_class_table(token.data);
//        } else {
//            ret_error(SYNTAX_ERROR);
//        }
        }
        if (token->type != R_BRACKET) {
            ret_error(SYNTAX_ERROR);
        }
        token = get_token();
    }
//        if (token->data == TOKEN_EOF){
//            ret_error(0);
//        }
    //dosli sme na koniec programu
}


void Declaration(tTable *table, Ttoken *token) {
    Ttoken *tokenID;
    tTablePtr node;
    char *type;
    if ((token->type != TOKEN_TYPE) && ((token->type != TOKEN_BOOL) || (token->type !=
                                                                        TOKEN_VOID))) {  //TOKEN_TYPE <= int, string, double; TOKEN_BOOL plati len pre funkciu
        ret_error(SYNTAX_ERROR);
    }
    if ((token->type == TOKEN_BOOL) || (token->type == TOKEN_VOID)) {
        type = token->data;
        token = get_token();
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }
        tokenID = token;
        node = BSTSearch(table, tokenID);
        if (node != NULL) {
            if (node->declared == 1) {
                ret_error(SEMANTIC_DEF_ERROR);
            }
        }
        token = get_token();
        if (token->type != TOKEN_LROUND_BRACKET) {
            ret_error(SYNTAX_ERROR);
        }
        funcDef(table, tokenID, type);
        node->declared = 1;
    } else {
        type = token->data;   //typ premennej resp funkcie

        token = get_token();
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }

        tokenID = token;
        node = BSTSearch(table, tokenID);
        if (node != NULL) {
            if (node->declared == 1) {
                ret_error(SEMANTIC_DEF_ERROR);
            }
        }

        token = get_token();
        if (token->type != TOKEN_LROUND_BRACKET) {
            variableDecl(table, tokenID, type);
            node->declared = 1;
        }
        funcDef(table, tokenID, type);
        node->declared = 1;
    }
}

void variableDecl(tTable *table, Ttoken *tokenID, char *type) {
    TVariable *var;
    var = new_variable(tokenID);
    var->type = type;

    Ttoken *token = get_token();
    if (token->type == TOKEN_ASSIGN) {
        expression(&var, tokenID);
        token = get_token();
        if (token->type != TOKEN_SEMICOLON) {
            ret_error(SYNTAX_ERROR);
        }

    } else if (token->type != TOKEN_SEMICOLON) {
        ret_error(SEMANTIC_DEF_ERROR);
    }
    store_variable(var, &table);
}


void funcDef(tTable *table, TToken *tokenID, char *type) {
    TFunction *f;
    f = new_function(tokenID);
    f->type = type;


    Ttoken *token = get_token();
    while (token->type != TOKEN_RROUND_BRACKET) {
        params(f, token);
        //f->paramcount++;

        token = get_token();
        if ((token->type != TOKEN_COLON) && (token->type != TOKEN_RROUND_BRACKET)) {
            ret_error(SYNTAX_ERROR);
        }
    }

    token = get_token();
    if (token->type != TOKEN_L_BRACKET) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    while (token->type == TOKEN_TYPE) { //deklaracie a definicie lokalnych premennych
        char *type = token->data;
        token = get_token();

        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }
        Ttoken *tokenID = token;
        if((BSTSearch(f->table, tokenID->data))){
            ret_error(SEMANTIC_DEF_ERROR);
        }
        variableDecl(f->table, tokenID, type);
        token = get_token();
    }

    switch (token->type) {
        case TOKEN_ID:
            char *type = NULL;
            Ttoken *tokenID = token;
            tTablePtr node;
            node = BSTSearch(f->table, token->data);   //neexistuje staticka premmenna s nazvom token->data v danej triede
            if (node == NULL) {
                node = BSTSearch(table, token->data);
                if (node == NULL) {
                    node->declared = 0;

                    Ttoken *token = get_token();
                    if (token->type != TOKEN_ASSING) {
                        funcCall(f, table, tokenID, type);
                    }
                    variableDecl(f->table, tokenID, type);
                }
                else{
                    token = get_token();
                    if (token->type == TOKEN_ASSIGN) {
                        TVariable *var = node->data.v;
                        token = get_token();
                        expression(&var, tokenID);
                        token = get_token();
                        if (token->type != TOKEN_SEMICOLON) {
                            ret_error(SYNTAX_ERROR);
                        }
                    } else if (token->type == TOKEN_LROUND_BRACKET) {
                        //TFunction *f = node->data.f;
                        token = get_token();
                        if (token->type != TOKEN_ID) {
                            ret_error(SYNTAX_ERROR);
                        }
                        tokenID = token;
                        funcCall(f, table, tokenID, type);
                }
            } else {

                token = get_token();
                if (token->type == TOKEN_ASSIGN) {
                    TVariable *var = node->data.v;
                    token = get_token();
                    expression(&var, tokenID);
                    token = get_token();
                    if (token->type != TOKEN_SEMICOLON) {
                        ret_error(SYNTAX_ERROR);
                    }
                } else if (token->type == TOKEN_LROUND_BRACKET) {
                    //TFunction *f = node->data.f;
                    token = get_token();
                    if (token->type != TOKEN_ID) {
                        ret_error(SYNTAX_ERROR);
                    }
                    tokenID = token;
                    funcCall(f, table, tokenID, type);
                }
            } else {
        ret_error(SYNTAX_ERROR);
    }

            break;

        case TOKEN_IF:
            if_statement(token);
            break;
        case TOKEN_FOR:
            for_statement();
            break;
        case TOKEN_WHILE:
            while_statement();
            break;
        case TOKEN_BREAK:
            //vytvori instrukciu break
            break;
        case TOKEN_CONTINUE:
            //vytvori instrukciu continue
            break;
        case TOKEN_DO:
            do_statement();
            break;
        case TOKEN_ELSE:
            else_statement();
            break;
        case TOKEN_RETURN:
            //vytvori instrukciu return
            break;
    }
    //store_function();
    //...


}


void funcCall(TFunction *f, Ttable *table, Ttoken *tokenID, char *type) {
    tTablePtr node;
    while (tokenID->type == TOKEN_ID) {
        node = BSTSearch(table, tokenID->data);
        if (node == NULL) {
                node->declared = 0;
                char *type = NULL;
                variableDecl(f->table, tokenID, type);
            }
        }
        Ttoken *token = get_token();
        if (token->type != TOKEN_COLON) {
            break;
        }
        token = get_token();
    }
    if (token->type != TOKEN_RROUND_BRACKET) {
        ret_error(SYNTAX_ERROR);
    }

    token = get_token();
    if (token->type != TOKEN_SEMICOLON) {
        ret_error(SYNTAX_ERROR);
    }
}


    void params(TFunction *f, Ttoken *token) { //spracovanie parametrov funkcie

        Ttable *table = f->table;
        TVariable *var;
        if (token->type != TOKEN_TYPE) {
            ret_error(SEMANTIC_DEF_ERROR);
        }
        char *type = token->data;
        var->type = type;
        Ttoken *token = get_token();
        var = new_variable(token);
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }

        store_variable(var, &table);

    }

    void if_statement(Ttoken *token) {
        TVariable *var;
        var = new_variable(token);
        token = get_token();
        if (token->type != TOKEN_LROUND_BRACKET) {
            ret_error(SYNTAX_ERROR);
        }
        expression(&var, token);

        TInstruction *label;
        label->operation = ins_lab;
        label->add1 = NULL;
        label->add2 = NULL;
        label->add3 = NULL;

        create_ins(ins_jmp, var, NULL, label);
        create_ins(ins_lab, NULL, NULL, NULL);


    }


/*--------------------/automat-----------------------*/

    void parse() {
        parser_init();


        parser_finish();

    }