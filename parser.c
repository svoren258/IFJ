/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#include "parser.h"
#include "expression.h"
#include "interpret.h"

TList *globalInitList;
tTablePtr funcContext = NULL;
tTablePtr classContext;
tTablePtr globTable;//v nej su tabulky tried | v kazdej tabulke triedy su jej funkcie a glob premenne.
Ttoken *token;//globalna premenna struktury token - do nej sa priradzuje vysledok get_token();
TStack *gStack;//zasobnik, pravdepodobne na prehladu o tom, ktora funkcia sa prave spracuvava

tTablePtr create_class_table(char *name, tTablePtr destTable)//navratova hodnota - uzol stromu
{
    tTablePtr classTable;
    tTablePtr node = BSTSearch(destTable, name);
    if (node == NULL) {
        //vytvorenie pointera
        TClass *class = malloc(sizeof(TClass));
        if (class == NULL) {
            ret_error(INTERNAL_ERROR);
        }
        BSTInit(&classTable);//inicializacia(uzol = NULL)
        BSTInsert(&destTable, &classTable, name);//pridanie uzlu do tabulky a nastavenie atributu - name
        classTable = BSTSearch(destTable, name);
        classTable->type = NODE_TYPE_CLASS;
        classTable->name = name;
        class->numOfVars = 0;
        class->defined = 0;
        class->stack = stackInit();
        classTable->data.c = class;
        return classTable;
    }
    return node;//vrati uzol tabulky triedy
}

TVariable *get_var_from_table(tTablePtr Table, char *name) {
    tTablePtr tree = BSTSearch(Table->Root, name);
    if (tree)
        return tree->data.v;

    return NULL;
}

TFunction *get_func_from_table(tTablePtr Table, char *name) {
    tTablePtr tree = BSTSearch(Table->Root, name);
    if (tree)
        return tree->data.f;

    return NULL;
}

TClass *get_class_from_table(tTablePtr Table, char *name) {
    tTablePtr tree = BSTSearch(Table, name);
    if (tree)
        return tree->data.c;
    return NULL;
}

void parser_init() {

    gStack = stackInit();

    BSTInit(&globTable);

    BSTInsert(&globTable, &globTable, "GlobTable");
    /*keywords to globtable*/

    //vytvorenie uzlov pre vstavane funkcie v tabulke vstavanych funkcii
    tTablePtr ifj16Table = create_class_table("ifj16", globTable);
    ifj16Table->data.c->defined = 1;

    TFunction *readInt = new_function("readInt", ifj16Table);
    readInt->numOfParams = 0;
    readInt->params[0] = FUNCTYPE_INT;
    readInt->defined = 1;

    TFunction *readDouble = new_function("readDouble", ifj16Table);
    readDouble->numOfParams = 0;
    readDouble->params[0] = FUNCTYPE_DOUBLE;
    readDouble->defined = 1;

    TFunction *readString = new_function("readString", ifj16Table);
    readString->numOfParams = 0;
    readString->params[0] = FUNCTYPE_STRING;
    readString->defined = 1;

    TFunction *print = new_function("print", ifj16Table);
    print->numOfParams = 0;
    print->params[0] = FUNCTYPE_VOID;
    print->defined = 1;

    TFunction *length = new_function("length", ifj16Table);
    length->numOfParams = 1;
    length->params[0] = FUNCTYPE_INT;
    length->params[1] = VARTYPE_STRING;
    length->defined = 1;

    TFunction *substr = new_function("substr", ifj16Table);
    substr->numOfParams = 3;
    substr->params[0] = FUNCTYPE_STRING;
    substr->params[1] = VARTYPE_STRING;
    substr->params[2] = VARTYPE_INTEGER;
    substr->params[3] = VARTYPE_INTEGER;
    substr->defined = 1;

    TFunction *compare = new_function("compare", ifj16Table);
    compare->numOfParams = 2;
    compare->params[0] = FUNCTYPE_INT;
    compare->params[1] = VARTYPE_STRING;
    compare->params[2] = VARTYPE_STRING;
    compare->defined = 1;

    TFunction *find = new_function("find", ifj16Table);
    find->numOfParams = 2;
    find->params[0] = FUNCTYPE_INT;
    find->params[1] = VARTYPE_STRING;
    find->params[2] = VARTYPE_STRING;
    find->defined = 1;

    TFunction *sort = new_function("sort", ifj16Table);
    sort->numOfParams = 1;
    sort->params[0] = FUNCTYPE_STRING;
    sort->params[1] = VARTYPE_STRING;
    sort->defined = 1;

    globalInitList = InitList(&globalInitList);
    InsertFirst(globalInitList, INS_LABEL, NULL, NULL, NULL);
}

void parser_finish() {
    BSTDispose(&globTable);
}

TFunction *new_function(char *tokenName, tTablePtr table) {    /*allocate the space for a new function*/

    TFunction *f;
    f = malloc(sizeof(TFunction));
    if (f == NULL) {
        ret_error(INTERNAL_ERROR);
    }

    tTablePtr loc_table;
    if (table->Root == NULL) {
        BSTRootNode(&table, &loc_table, tokenName);
    } else {
        BSTInit(&loc_table);
        BSTInsert(&table->Root, &loc_table, tokenName);
    }
    loc_table->type = NODE_TYPE_FUNCTION;

    TList *list;
    list = InitList(&list);
    InsertFirst(list, INS_LABEL, NULL, NULL, NULL);

    /*assign the table to the function*/
    f->list = list;
    f->stack = stackInit();
    f->numOfVars = 0;
    f->numOfParams = 0;
    f->defined = 0;
    f->name = tokenName;
    f->params[0] = FUNCTYPE_NULL;
    f->className = table->name;

    loc_table->data.f = f;

    return f;
}

TVariable *new_variable(Ttoken *token, tTablePtr table) {
    TVariable *v;
    v = malloc(sizeof(TVariable));
    if (v == NULL) {
        ret_error(INTERNAL_ERROR);
    }
    tTablePtr new_var;
    if (table->Root == NULL) {
        BSTRootNode(&table, &new_var, token->data);
    } else {
        BSTInit(&new_var);
        BSTInsert(&table->Root, &new_var, token->data);
    }

    new_var->type = NODE_TYPE_VARIABLE;

    v->declared = 0;
    v->fullNameCall = 0;
    v->name = token->data;
    v->className = NULL;
    v->type = VARTYPE_NULL;
    if (table->type == NODE_TYPE_CLASS) {
        v->className = table->name;
    } else if (table->type == NODE_TYPE_FUNCTION) {
        v->className = table->data.f->className;
    }
    new_var->data.v = v;
    return v;
}


/*--------------------automat-----------------------*/
void starter() {
    token = get_token();
    if (token->type != KEYWORD_CLASS) {
        ret_error(SYNTAX_ERROR);
    }
    while (token->type == KEYWORD_CLASS) {
        if (token->type == KEYWORD_CLASS) {
            token = get_token();
            if (token->type != TOKEN_ID) {
                ret_error(SYNTAX_ERROR);
            }
            char *className = token->data;

            tTablePtr classTable = create_class_table(className, globTable);
            classContext = classTable;
            funcContext = NULL;
            if (classTable->data.c->defined == 1) { line;
                ret_error(SEMANTIC_DEF_ERROR);
            }
            classTable->data.c->defined = 1;

            token = get_token();
            if (token->type != TOKEN_L_CURLY) {
                ret_error(SYNTAX_ERROR);
            }
            token = get_token();
            while (token->type == KEYWORD_STATIC) {
                token = get_token();
                Declaration(classTable, token);
                token = get_token();
            }
            if (token->type != TOKEN_R_CURLY) {
                ret_error(SYNTAX_ERROR);
            }
            token = get_token();
        } else {
            ret_error(SYNTAX_ERROR);
        }
    }
    if (token->type != TOKEN_EOF) {
        ret_error(SYNTAX_ERROR);
    } else {
        tTablePtr node = BSTSearch(globTable, "Main");
        if (node == NULL) { line;
            ret_error(SEMANTIC_DEF_ERROR);
        } else {
            node = BSTSearch(node->Root, "run");
            if (node == NULL) { line;
                ret_error(SEMANTIC_DEF_ERROR);
            }
            else{
                TListItem run = create_instruction(INS_CALL, node->data.f, NULL, NULL);
                insert_instruction(globalInitList, run);
            }
        }
    }
}

void Declaration(tTablePtr table, Ttoken *token) {
    Ttoken *tokenID;
    tTablePtr node = NULL;
    char *type = NULL;


    if ((token->type != TOKEN_TYPE) && ((token->type != KEYWORD_BOOLEAN) && (token->type != KEYWORD_VOID))) {
        ret_error(SYNTAX_ERROR);
    }
    if ((token->type == KEYWORD_BOOLEAN) || (token->type == KEYWORD_VOID)) {
        type = token->data;
        token = get_token();
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }
        tokenID = token;

        node = BSTSearch(table->Root, tokenID->data);
        if (node != NULL) {
            if (node->data.f->defined == 1) { line;
                ret_error(SEMANTIC_DEF_ERROR);
            }
        }
        token = get_token();
        if (token->type != TOKEN_L_ROUND) {
            ret_error(SYNTAX_ERROR);
        }
        TFunction *f = funcDef(table, tokenID, type);
        f->declared = 1;
        f->defined = 1;
    } else {
        type = token->data;   //typ premennej resp funkcie
        token = get_token();
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }

        tokenID = token;

        node = BSTSearch(table->Root, tokenID->data);

        if ((node != NULL) && (node->type == NODE_TYPE_FUNCTION)) {
            if (node->data.f->defined == 1) { line;
                ret_error(SEMANTIC_DEF_ERROR);
            }
        } else if ((node != NULL) && (node->type == NODE_TYPE_VARIABLE)) {
            if (node->data.v->declared == 1) { line;
                ret_error(SEMANTIC_DEF_ERROR);
            }
        }
        token = get_token();
        if (token->type != TOKEN_L_ROUND) {
            unget_token(1);
            TVariable *v = variableDecl(table, tokenID, type);
            v->declared = 1;
            v->position = table->data.c->numOfVars;
            table->data.c->numOfVars++;
        } else {
            TFunction *f = funcDef(table, tokenID, type);
            f->declared = 1;
            f->defined = 1;
        }
    }
}

TVariable *variableDecl(tTablePtr table, Ttoken *tokenID, char *type) {
    TVariable *var;
    tTablePtr node = NULL;
    node = BSTSearch(table->Root, tokenID->data);

    if (node == NULL) {
        var = new_variable(tokenID, table);
        if (!type) {
            var->type = VARTYPE_NULL;
        } else {
            if (!(strcmp(type, "int"))) {
                var->type = VARTYPE_INTEGER;
            } else if (!(strcmp(type, "double"))) {
                var->type = VARTYPE_DOUBLE;
            } else if (!(strcmp(type, "String"))) {
                var->type = VARTYPE_STRING;
            }
        }
    } else {
        var = node->data.v;
    }

    if (var->declared != 1) {
        if (table->type == NODE_TYPE_CLASS) {
            stackPush(table->data.c->stack, var);
        } else if (table->type == NODE_TYPE_FUNCTION) {
            stackPush(table->data.f->stack, var);
        }
    }

    token = get_token();
    if (token->type == TOKEN_ASSIGN) {
        expression(var);
        var->defined = 1;
        token = get_token();
        if (token->type != TOKEN_SEM_CL) {
            ret_error(SYNTAX_ERROR);
        }

    } else if (token->type != TOKEN_SEM_CL) { line;
        ret_error(SEMANTIC_DEF_ERROR);
    }
    node = BSTSearch(table->Root, tokenID->data);
    node->data.v = var;
    return var;
}

TFunction *funcDef(tTablePtr table, Ttoken *tokenID, char *funcType) {
    TFunction *f;
    TVariable *v;
    TVariable *param;
    Ttoken *token_varID;
    tTablePtr node;
    classContext = table;
    int paramsCount = 0;

    node = BSTSearch(table->Root, tokenID->data);
    if (node == NULL) {
        f = new_function(tokenID->data, table);
    } else {
        f = node->data.f;
    }

    f->numOfVars = 0;

    if (!(strcmp(funcType, "int"))) {
        f->params[paramsCount] = FUNCTYPE_INT;
    } else if (!(strcmp(funcType, "double"))) {
        f->params[paramsCount] = FUNCTYPE_DOUBLE;
    } else if (!(strcmp(funcType, "String"))) {
        f->params[paramsCount] = FUNCTYPE_STRING;
    } else if (!(strcmp(funcType, "void"))) {
        f->params[paramsCount] = FUNCTYPE_VOID;
    } else if (!(strcmp(funcType, "boolean"))) {
        f->params[paramsCount] = FUNCTYPE_BOOLEAN;
    } else {
        f->params[paramsCount] = FUNCTYPE_NULL;
    }

    tTablePtr fTable = BSTSearch(table->Root, tokenID->data);
    if (fTable != NULL && fTable->type == NODE_TYPE_FUNCTION) {
        funcContext = fTable;
    }

    token = get_token();

    while (token->type != TOKEN_R_ROUND) {
        if (token->type == TOKEN_COLON) {
            token = get_token();
        }
        paramsCount++;
        param = params(fTable, token, paramsCount);
        stackPush(f->stack, param);
        token = get_token();
        if ((token->type != TOKEN_COLON) && (token->type != TOKEN_R_ROUND)) {
            ret_error(SYNTAX_ERROR);
        }
    }

    f->numOfParams = paramsCount;
    f->numOfVars += f->numOfParams;

    token = get_token();
    if (token->type != TOKEN_L_CURLY) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();

    while (token->type != TOKEN_R_CURLY) {
        switch (token->type) {  //volanie funkcii alebo priradovanie hodnot do premennych
            case TOKEN_TYPE: {
                //deklaracie a definicie lokalnych premennych
                char *type = token->data;
                token = get_token();
                if (token->type != TOKEN_ID) {
                    ret_error(SYNTAX_ERROR);
                }

                token_varID = token;

                if ((BSTSearch(fTable->Root, token_varID->data))) { line;
                    ret_error(SEMANTIC_DEF_ERROR);
                }

                v = variableDecl(fTable, token_varID, type);

                v->declared = 1;
                v->position = f->numOfVars;
                f->numOfVars++;
                break;
            }
            case TOKEN_ID: {
                token_varID = token;
                node = NULL;
                token = get_token();
                if (token->type == TOKEN_DOT) {
                    char *className = token_varID->data;
                    tTablePtr tableOfClass;
                    if ((strcmp(className, "ifj16"))) {
                        tableOfClass = create_class_table(className, globTable);
                    } else {
                        tableOfClass = create_class_table("ifj16", globTable);
                    }
                    token = get_token();
                    if (token->type != TOKEN_ID) {
                        ret_error(SYNTAX_ERROR);
                    }
                    token_varID = token;

                    token = get_token();
                    if (token->type == TOKEN_ASSIGN) {
                        unget_token(1);
                        variableDecl(tableOfClass, token_varID, NULL);
                    } else if (token->type == TOKEN_L_ROUND) {
                        node = BSTSearch(tableOfClass->Root, token_varID->data);
                        if ((node == NULL) && (strcmp(className, "ifj16"))) {
                            TFunction *f = new_function(token_varID->data, tableOfClass);
                            f->declared = 1;
                            unget_token(4);
                            expression(NULL);
                        } else {
                            unget_token(4);
                            expression(NULL);
                        }
                        token = get_token();
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    } else {
                        ret_error(SYNTAX_ERROR);
                    }
                } else {
                    unget_token(1);
                    node = BSTSearch(fTable->Root,
                                     token_varID->data);   //neexistuje staticka premmenna s nazvom token->data v danej triede
                    if (node == NULL) {
                        node = BSTSearch(table->Root, token_varID->data);
                        if (node == NULL) {
                            token = get_token();
                            if (token->type == TOKEN_ASSIGN) {
                                unget_token(1);
                                v = variableDecl(table, token_varID, NULL);
                            } else if (token->type == TOKEN_L_ROUND) {
                                unget_token(2);
                                expression(NULL);
                                token = get_token();
                                if (token->type != TOKEN_SEM_CL) {
                                    ret_error(SYNTAX_ERROR);
                                }
                            }
                        } else {
                            token = get_token();
                            if (token->type == TOKEN_ASSIGN) {
                                unget_token(1);
                                variableDecl(table, token_varID, NULL);
                                unget_token(1);
                                token = get_token();
                                if (token->type != TOKEN_SEM_CL) {
                                    ret_error(SYNTAX_ERROR);
                                }
                            } else if (token->type == TOKEN_L_ROUND) {
                                unget_token(2);

                                expression(NULL);
                                token = get_token();
                                if (token->type != TOKEN_SEM_CL) {
                                    ret_error(SYNTAX_ERROR);
                                }
                            } else {
                                ret_error(SYNTAX_ERROR);
                            }
                        }

                    } else {
                        token = get_token();
                        if (token->type == TOKEN_ASSIGN) {
                            unget_token(1);
                            variableDecl(fTable, token_varID, NULL);
                            unget_token(1);
                            token = get_token();
                            if (token->type != TOKEN_SEM_CL) {
                                ret_error(SYNTAX_ERROR);
                            }
                        } else if (token->type == TOKEN_L_ROUND) {
                            unget_token(2);

                            expression(NULL);
                            token = get_token();
                            if (token->type != TOKEN_SEM_CL) {
                                ret_error(SYNTAX_ERROR);
                            }
                        } else {
                            ret_error(SYNTAX_ERROR);
                        }
                    }
                }
                break;
            }
            case KEYWORD_IF: {
                ifelse_statement(fTable);
                break;
            }
            case KEYWORD_WHILE: {
                while_statement(fTable);
                break;
            }
            case KEYWORD_RETURN: {
                return_statement(fTable);
                break;
            }
            default: {
                ret_error(SYNTAX_ERROR);
            }
        }
        token = get_token();
    }

    TListItem retItem = create_instruction(INS_RET, NULL, NULL, NULL);
    insert_instruction(f->list, retItem);

    node = BSTSearch(table->Root, tokenID->data);

    node->data.f = f;

    funcContext = NULL;
    return f;
}

TVariable *params(tTablePtr fTable, Ttoken *token, int numOfParam) { //spracovanie parametrov funkcie
    tTablePtr table = fTable;
    tTablePtr node = NULL;
    TFunction *f = table->data.f;
    TVariable *var;
    if (token->type != TOKEN_TYPE) { tok;line;
        ret_error(SEMANTIC_DEF_ERROR);
    }
    char *type = token->data;

    Ttoken *tokenID = get_token();
    if (tokenID->type != TOKEN_ID) {
        ret_error(SYNTAX_ERROR);
    }

    node = BSTSearch(table->Root, tokenID->data);
    if (node == NULL) {
        var = new_variable(tokenID, table);
    } else { line;
        ret_error(SEMANTIC_DEF_ERROR);
    }
    if (!(strcmp(type, "int"))) {
        var->type = VARTYPE_INTEGER;
        f->params[numOfParam] = VARTYPE_INTEGER;
    } else if (!(strcmp(type, "double"))) {
        var->type = VARTYPE_DOUBLE;
        f->params[numOfParam] = VARTYPE_DOUBLE;
    } else if (!(strcmp(type, "String"))) {
        var->type = VARTYPE_STRING;
        f->params[numOfParam] = VARTYPE_STRING;
    } else {
        var->type = VARTYPE_NULL;
    }

    var->declared = 1;
    var->position = numOfParam - 1;
    node = BSTSearch(table->Root, tokenID->data);
    node->data.v = var;
    return var;
}

void ifelse_statement(tTablePtr table) {
    TVariable *var = malloc(sizeof(TVariable));
    if (var == NULL) {
        ret_error(INTERNAL_ERROR);
    }
    var->name = NULL;
    var->type = 0;
    TListItem endIf = create_instruction(INS_LABEL, NULL, NULL, NULL);
    TListItem endElse = create_instruction(INS_LABEL, NULL, NULL, NULL);
    TListItem cmp = create_instruction(INS_JCMP, var, NULL, endIf);
    TListItem jmp = create_instruction(INS_JMP, NULL, NULL, endElse);

    token = get_token();
    if (token->type != TOKEN_L_ROUND) {
        ret_error(SYNTAX_ERROR);
    }

    expression(var);

    token = get_token();
    if (token->type != TOKEN_R_ROUND) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    if (token->type != TOKEN_L_CURLY) {
        ret_error(SYNTAX_ERROR);
    }

    insert_instruction(table->data.f->list, cmp);

    token = get_token();

    block_body(token);

    insert_instruction(table->data.f->list, jmp);

    token = get_token();
    if (token->type != KEYWORD_ELSE) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    if (token->type != TOKEN_L_CURLY) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();

    insert_instruction(table->data.f->list, endIf);

    block_body(token);

    insert_instruction(table->data.f->list, endElse);
}

void while_statement(tTablePtr table) {
    TVariable *var = malloc(sizeof(TVariable));
    if (var == NULL) {
        ret_error(INTERNAL_ERROR);
    }
    var->name = NULL;

    TListItem startWhile = create_instruction(INS_LABEL, NULL, NULL, NULL);
    TListItem endWhile = create_instruction(INS_LABEL, NULL, NULL, NULL);
    TListItem cmp = create_instruction(INS_JCMP, var, NULL, endWhile);
    TListItem jmp = create_instruction(INS_JMP, NULL, NULL, startWhile);

    token = get_token();
    if (token->type != TOKEN_L_ROUND) {
        ret_error(SYNTAX_ERROR);
    }
    //must jump before the compare instruction in order to work properly
    insert_instruction(table->data.f->list, startWhile);

    expression(var);

    token = get_token();
    if (token->type != TOKEN_R_ROUND) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    if (token->type != TOKEN_L_CURLY) {
        ret_error(SYNTAX_ERROR);
    }

    insert_instruction(table->data.f->list, cmp);

    token = get_token();

    block_body(token);

    insert_instruction(table->data.f->list, jmp);

    insert_instruction(table->data.f->list, endWhile);

}

void return_statement(tTablePtr table) {
    TListItem retItem;
    token = get_token();
    if (table->data.f->params[0] == FUNCTYPE_VOID) {
        retItem = create_instruction(INS_RET, NULL, NULL, NULL);
        if (token->type != TOKEN_SEM_CL) {
            ret_error(SEMANTIC_TYPE_ERROR);
        }
    } else {
        TVariable *ret = malloc(sizeof(TVariable));
        if (ret == NULL) {
            ret_error(INTERNAL_ERROR);
        }
        ret->name = NULL;
        ret->type = VARTYPE_NULL;
        unget_token(1);
        retItem = create_instruction(INS_RET, ret, NULL, NULL);
        expression(ret);
        token = get_token();
        if (token->type != TOKEN_SEM_CL) { line;
            ret_error(SYNTAX_ERROR);
        }
    }
    insert_instruction(table->data.f->list, retItem);
}

void block_body(Ttoken *token) {
    tTablePtr node;
    Ttoken *token_varID;
    while (token->type != TOKEN_R_CURLY) {
        switch (token->type) {
            case TOKEN_ID: {
                token_varID = token;
                token = get_token();
                if (token->type == TOKEN_DOT) {
                    char *className = token_varID->data;
                    tTablePtr tableOfClass;
                    if ((strcmp(className, "ifj16"))) {
                        tableOfClass = create_class_table(className, globTable);
                    } else {
                        tableOfClass = create_class_table("ifj16", globTable);
                    }
                    token = get_token();
                    if (token->type != TOKEN_ID) {
                        ret_error(SYNTAX_ERROR);
                    }
                    token_varID = token;

                    token = get_token();
                    if (token->type == TOKEN_ASSIGN) {
                        unget_token(1);
                        variableDecl(tableOfClass, token_varID, NULL);
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    } else if (token->type == TOKEN_L_ROUND) {
                        node = BSTSearch(tableOfClass->Root, token_varID->data);

                        if ((node == NULL) && (strcmp(className, "ifj16"))) {
                            TFunction *f = new_function(token_varID->data, tableOfClass);
                            f->declared = 1;
                            unget_token(4);
                            expression(NULL);
                            token = get_token();
                            if (token->type != TOKEN_SEM_CL) {
                                ret_error(SYNTAX_ERROR);
                            }
                        } else {
                            unget_token(4);
                            expression(NULL);
                            token = get_token();
                        }
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    } else {
                        ret_error(SYNTAX_ERROR);
                    }
                } else {
                    unget_token(1);
                    node = BSTSearch(funcContext->Root,
                                     token_varID->data);   //neexistuje staticka premmenna s nazvom token->data v danej triede
                    if (node == NULL) {
                        node = BSTSearch(classContext->Root, token_varID->data);
                        if (node == NULL) {
                            token = get_token();
                            if (token->type == TOKEN_ASSIGN) {
                                variableDecl(classContext, token_varID, NULL);
                            } else if (token->type == TOKEN_L_ROUND) {
                                unget_token(2);
                                expression(NULL);
                                token = get_token();
                                if (token->type != TOKEN_SEM_CL) {
                                    ret_error(SYNTAX_ERROR);
                                }
                            }
                        } else {
                            token = get_token();
                            if (token->type == TOKEN_ASSIGN) {
                                unget_token(1);
                                variableDecl(classContext, token_varID, NULL);
                                unget_token(1);
                                token = get_token();
                                if (token->type != TOKEN_SEM_CL) {
                                    ret_error(SYNTAX_ERROR);
                                }
                            } else if (token->type == TOKEN_L_ROUND) {
                                unget_token(2);
                                expression(NULL);
                                token = get_token();
                                if (token->type != TOKEN_SEM_CL) {
                                    ret_error(SYNTAX_ERROR);
                                    token = get_token();
                                    if (token->type == TOKEN_ASSIGN) {
                                        unget_token(1);
                                        variableDecl(funcContext, token_varID, NULL);
                                        unget_token(1);
                                        token = get_token();
                                        if (token->type != TOKEN_SEM_CL) {
                                            ret_error(SYNTAX_ERROR);
                                        }
                                    } else if (token->type == TOKEN_L_ROUND) {
                                        TFunction *f = new_function(token_varID->data, classContext);
                                        f->defined = 1;
                                        unget_token(2);
                                        expression(NULL);
                                        token = get_token();
                                        if (token->type != TOKEN_SEM_CL) {
                                            ret_error(SYNTAX_ERROR);
                                        }
                                    } else {
                                        ret_error(SYNTAX_ERROR);
                                    }
                                }
                            } else {
                                ret_error(SYNTAX_ERROR);
                            }
                        }
                    } else {
                        token = get_token();
                        if (token->type == TOKEN_ASSIGN) {
                            unget_token(1);
                            variableDecl(funcContext, token_varID, NULL);
                            unget_token(1);
                            token = get_token();
                            if (token->type != TOKEN_SEM_CL) {
                                ret_error(SYNTAX_ERROR);
                            }
                        } else if (token->type == TOKEN_L_ROUND) {
                            unget_token(2);
                            expression(NULL);
                            token = get_token();
                            if (token->type != TOKEN_SEM_CL) {
                                ret_error(SYNTAX_ERROR);
                            }
                        } else {
                            ret_error(SYNTAX_ERROR);
                        }
                    }
                }
                break;
            }
            case KEYWORD_IF: {
                ifelse_statement(funcContext);
                break;
            }
            case KEYWORD_WHILE: {
                while_statement(funcContext);
                break;
            }
            case KEYWORD_RETURN: {
                return_statement(funcContext);
                break;
            }
            default:
                ret_error(SYNTAX_ERROR);
        }
        token = get_token();
    }
}
/*--------------------/automat-----------------------*/

void parse() {
    parser_init();
    starter();
    interpret();
    parser_finish();
}