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
    if (token->data != class) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    if (token->type != TOKEN_ID) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    if (token->type != L_BRACKET) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    if (token->type == TOKEN_STATIC) {
        //glob premenna
        //glob funkcia
        token = get_token();
        Declaration(globTable, token);
    } else if (token->type == TOKEN_TYPE) {

        //f->type = token->data;
        //lokal premenna
        //lokal funkcia
        Declaration(locTable, token);
    } else {
        ret_error(SYNTAX_ERROR);
    }
}

void Declaration(Ttable *table,Ttoken *token) {

    if (token->type != TOKEN_TYPE) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    if (token->type != TOKEN_ID) {
        ret_error(SYNTAX_ERROR);
    }

    Ttoken *tokenID = token;

    token = get_token();
    if (token->type != TOKEN_LROUND_BRACKET) {
        variableDecl(table, tokenID);
    }
    funcDecl(tokenID);
}

void variableDecl(Ttable *table, Ttoken *tokenID) {
    TVariable *var;
    var = new_variable(tokenID);

    if ((BSTExists(table, tokenID->data))) {
        ret_error(SEMANTIC_DEF_ERROR);
    }



    Ttoken *token = get_token();
    if (token->type == TOKEN_ASSIGN) {
        assign_val(table, tokenID);
    } else if (token->type == TOKEN_SEMICOLON) {
        store_variable(var, globTable);
    } else {
        ret_error(SEMANTIC_DEF_ERROR);
    }
}

void assign_val(Ttable *table, Ttoken *tokenID) { ///prvy argument nie je isty
    Ttoken *token = get_token();
    if(token->type != TOKEN_INT || token->type != TOKEN_DOUBLE || token->type != TOKEN_STRING || token->type != TOKEN_ID{
        ret_error(SYNTAX_ERROR);
    }
//    if(token->type == TOKEN_ID){
//        if(!(BSTExists(table, token->data))){
//            ret_error(SEMANTIC_DEF_ERROR);
//        }
//    }
    expression(tokenID);
}

void funcDecl(Ttoken *tokenID) {
    TFunction *f;
    f = new_function(tokenID);
    Ttoken *token = get_token();
    while (token->type != TOKEN_RROUND_BRACKET) {
        params(f->table, token);
        token = get_token();
        if (token->type != TOKEN_COLON || token->type != TOKEN_RROUND_BRACKET) {
            ret_error(SYNTAX_ERROR);
        }
    }
    token = get_token();
    if(token->type != TOKEN_L_BRACKET){
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    while(token->type == TOKEN_TYPE){
//        if(token->type != TOKEN_TYPE){
//            ret_error(SYNTAX_ERROR);
//        }
        token = get_token();
        if(token->type != TOKEN_ID){
            ret_error(SYNTAX_ERROR);
        }
        variableDecl(f->table, token);
        token = get_token();
    }

    switch (token->type){
        case TOKEN_ID:
            Ttoken *tokenID = token;
            if(!(BSTExists(f->table, token->data)) || !(BSTExists(globTable, token->data))){
                ret_error(SEMANTIC_DEF_ERROR);
            }
            token = get_token();
           if(token->type == TOKEN_ASSIGN){
                expression(tokenID);
            }
            else if(token->type == TOKEN_LROUND_BRACKET){
                token = get_token();
                while(token->type == TOKEN_ID) {
                    if (!(BSTExists(f->table, token->data))) {
                        ret_error(SEMANTIC_DEF_ERROR);
                    }
                    token = get_token();
                    if (token->type != TOKEN_COLON) {
                        break;
                    }
                    token = get_token();
                }

                if(token->type != TOKEN_RROUND_BRACKET) {
                    ret_error(SYNTAX_ERROR);
                }
                token = get_token();
                if(token->type != TOKEN_SEMICOLON){
                    ret_error(SYNTAX_ERROR);
                }
            }
            else{
                ret_error(SYNTAX_ERROR);
            }
            token = get_token();

        case TOKEN_IF:

        case TOKEN_FOR:

        //...
    }
    
}

void params(Ttable *table, Ttoken *tokenType) { //spracovanie parametrov funkcie
    TVariable *var;
    if (tokenType->type != TOKEN_TYPE) {
        ret_error(SEMANTIC_DEF_ERROR);
    }
    Ttoken *token = get_token();
    var = new_variable(token);
    if (token->type != TOKEN_ID) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    if ((BSTExists(table, token->data))) {
        ret_error(SEMANTIC_DEF_ERROR);
    }
    store_variable(var, table);
}


/*--------------------/automat-----------------------*/

void parse() {
    parser_init();


    parser_finish();

}