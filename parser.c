/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#include "parser.h"

#include "expression.h"
//#include "defs.h"
#include "interpret.h"

TList *globalInitList;
tTablePtr funcContext;
tTablePtr classContext;
tTablePtr globTable;//v nej su tabulky tried | v kazdej tabulke triedy su jej funkcie a glob premenne.
tTablePtr builtInTable; //tabulka s vstavanymi funkciami
Ttoken *token;//globalna premenna struktury token - do nej sa priradzuje vysledok get_token();
TStack *gStack;//zasobnik, pravdepodobne na prehladu o tom, ktora funkcia sa prave spracuvava

tTablePtr create_class_table(char *name, tTablePtr destTable)//navratova hodnota - uzol stromu
{
    printf("som v create_class_table\n");
    tTablePtr classTable;
    tTablePtr node = BSTSearch(destTable, name);
    if (node == NULL) {
        printf("vytvaram novu tabulku\n");
        //vytvorenie pointera
        TClass *class = malloc(sizeof(TClass));
        BSTInit(&classTable);//inicializacia(uzol = NULL)
        BSTInsert(&destTable, &classTable, name);//pridanie uzlu do tabulky a nastavenie atributu - name
        classTable = BSTSearch(destTable, name);
        classTable->type = NODE_TYPE_CLASS;
        classTable->name = name;
        class->numOfVars = 0;
        class->stack = stackInit();
        classTable->data.c = class;
        return classTable;
    }
    printf("vraciam uzol uz vytvorenej tabulky\n");
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

void parser_init() {

    gStack = stackInit();

    BSTInit(&globTable);

    BSTInsert(&globTable, &globTable, "GlobTable");
    /*keywords to globtable*/
    // keywords_init();

    BSTInit(&builtInTable);

    BSTInsert(&builtInTable, &builtInTable, "ifj16");

    //vytvorenie uzlov pre vstavane funkcie v tabulke vstavanych funkcii
    TFunction *readInt = new_function("readInt", builtInTable);
    readInt->numOfParams = 0;
    readInt->params[0] = FUNCTYPE_INT;

    TFunction *readDouble = new_function("readDouble", builtInTable);
    readDouble->numOfParams = 0;
    readDouble->params[0] = FUNCTYPE_DOUBLE;

    TFunction *readString = new_function("readString", builtInTable);
    readString->numOfParams = 0;
    readString->params[0] = FUNCTYPE_STRING;

    TFunction *print = new_function("print", builtInTable);
    print->numOfParams = 0;
    print->params[0] = FUNCTYPE_VOID;
    print->defined = 1;

    TFunction *length = new_function("length", builtInTable);
    length->numOfParams = 1;
    length->params[0] = FUNCTYPE_INT;
    length->params[1] = VARTYPE_STRING;
    length->defined = 1;

    TFunction *substr = new_function("substr", builtInTable);
    substr->numOfParams = 3;
    substr->params[0] = FUNCTYPE_STRING;
    substr->params[1] = VARTYPE_STRING;
    substr->params[2] = VARTYPE_INTEGER;
    substr->params[3] = VARTYPE_INTEGER;
    substr->defined = 1;

    TFunction *compare = new_function("compare", builtInTable);
    compare->numOfParams = 2;
    compare->params[0] = FUNCTYPE_INT;
    compare->params[1] = VARTYPE_STRING;
    compare->params[2] = VARTYPE_STRING;
    compare->defined = 1;

    TFunction *find = new_function("find", builtInTable);
    find->numOfParams = 2;
    find->params[0] = FUNCTYPE_INT;
    find->params[1] = VARTYPE_STRING;
    find->params[2] = VARTYPE_STRING;
    find->defined = 1;

    TFunction *sort = new_function("sort", builtInTable);
    sort->numOfParams = 1;
    sort->params[0] = FUNCTYPE_STRING;
    sort->params[1] = VARTYPE_STRING;
    sort->defined = 1;

    globalInitList = InitList(&globalInitList);
    InsertFirst(globalInitList, INS_LABEL, NULL, NULL, NULL);

}


void parser_finish() {
    BSTDispose(&globTable);
    BSTDispose(&builtInTable);

}

TFunction *new_function(char *tokenName, tTablePtr table) {    /*allocate the space for a new function*/
    //upravit prvy paramenter na char*
    printf("som v new_function\n");

    TFunction *f;
    f = malloc(sizeof(TFunction));

    tTablePtr loc_table;
    if (table->Root == NULL) {
        BSTRootNode(&table, &loc_table, tokenName);
    } else {
        printf("pridavam fuknciu do Rootu\n");
        BSTInit(&loc_table);
        BSTInsert(&table->Root, &loc_table, tokenName);
    }
    loc_table->type = NODE_TYPE_FUNCTION;


//    TStack *stack = stackInit();
    printf("som pred listom\n");
//    if ((strcmp(table->name, "ifj16"))) {
    TList *list;
    list = InitList(&list);
    InsertFirst(list, INS_LABEL, NULL, NULL, NULL);
    f->list = list;
//    }

    f->stack = stackInit();
    /*assign the table to the function*/
    f->defined = 0;
    f->name = tokenName;
    f->params[0] = FUNCTYPE_NULL;
    f->className = table->name;


    loc_table->data.f = f;

    return f;
}

TVariable *new_variable(Ttoken *token, tTablePtr table) {
    printf("som v new_variable\n");
    printf("som v tabulke %s\n", table->name);
    printf("tokendata: %s\n", token->data);

    TVariable *v;
    v = malloc(sizeof(TVariable));
    tTablePtr new_var;
    if (table->Root == NULL) {
        printf("idem vytvarat novy root\n");
        BSTRootNode(&table, &new_var, token->data);
        printf("presiel som cez BSTRootNode\n");
    } else {
        BSTInit(&new_var);
        BSTInsert(&table->Root, &new_var, token->data);
    }
    new_var->type = NODE_TYPE_VARIABLE;

    //new_var->name = token->data;
    //BSTInit(&new_var);
    //BSTInsert(&table, &new_var, token->data);

    v->declared = 0;
    v->name = token->data;
    v->type = VARTYPE_NULL;
    if (table->type == NODE_TYPE_CLASS) {
        v->className = table->name;
    } else if (table->type == NODE_TYPE_FUNCTION) {
        printf("som v ife v tabulke funkcie\n");
        v->className = table->data.f->className;
    }
    
    new_var->data.v = v;

    return v;

}

//void store_function(/*stack*/TFunction *f, tTablePtr table) {
//    tTablePtr new_func;
//    BSTInit(&new_func);
//
//    BSTInsert(&table, &new_func, f->name);
//    stackPush(gStack, f);
//}
//
//void store_variable(/*stack*/TVariable *v, tTablePtr table) {
//
//    tTablePtr node;
//    node = BSTSearch(table, v->name);
//    if (node == NULL) {
//        tTablePtr new_var;
//        BSTInit(&new_var);
//        BSTInsert(&table, &new_var, v->name);
//        new_var->data.v = v;
//    } else {
//        tTablePtr node = BSTSearch(table, v->name);
//        node->data.v = v;
//    }
//
//}


/*--------------------automat-----------------------*/
void starter() {
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    while (token->type == KEYWORD_CLASS) {
        printf("som vo while class\n");
        if (token->type == KEYWORD_CLASS) {
            token = get_token();
            printf("nacitany token: %s\n", token->data);
            if (token->type != TOKEN_ID) {
                ret_error(SYNTAX_ERROR);
            }

            tTablePtr table = create_class_table(token->data, globTable);
            classContext = table;
            funcContext = NULL;
            tTablePtr node = BSTSearch(globTable, token->data);
            if (node->defined == 1) {
                ret_error(SEMANTIC_DEF_ERROR);
            }
            node->defined = 1;

            token = get_token();
            printf("nacitany token: %s\n", token->data);
            if (token->type != TOKEN_L_CURLY) {
                ret_error(SYNTAX_ERROR);
            }
            printf("tablename: %s\n", table->name);
            token = get_token();
            printf("nacitany token: %s\n", token->data);
            while (token->type == KEYWORD_STATIC) {
                printf("som vo while v starteri\n");
                token = get_token();
                printf("nacitany token: %s\n", token->data);
                printf("tablename: %s\n", table->name);
                Declaration(table, token);
                token = get_token();
                printf("nacitany token: %s\n", token->data);
            }
            if (token->type != TOKEN_R_CURLY) {
                ret_error(SYNTAX_ERROR);
            }
            token = get_token();
            printf("nacitany token: %s\n", token->data);
        } else {
            ret_error(SYNTAX_ERROR);
        }
    }
    if (token->type == TOKEN_EOF) {
        printf("koniec programu\n");
        ret_error(0);
    }
    //dosli sme na koniec programu
}

void Declaration(tTablePtr table, Ttoken *token) {
    printf("som v Declaration\n");
    Ttoken *tokenID;
    tTablePtr node = NULL;
    char *type = NULL;
    //int staticVars = table->data.c->numOfVars;

    if ((token->type != TOKEN_TYPE) && ((token->type != KEYWORD_BOOLEAN) && (token->type != KEYWORD_VOID))) {  //TOKEN_TYPE <= int, string, double; TOKEN_BOOL plati len pre funkciu
        ret_error(SYNTAX_ERROR);
    }
    if ((token->type == KEYWORD_BOOLEAN) || (token->type == KEYWORD_VOID)) {
        printf("som vo vetve VOID\n");
        type = token->data;
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }
        tokenID = token;

        printf("tablename: %s\n", table->name);

        node = BSTSearch(table->Root, tokenID->data);

        printf("som za BSTSearch\n");
        if (node != NULL) {
            printf("som v ife\n");
            if (node->data.f->defined == 1) {
                ret_error(SEMANTIC_DEF_ERROR);
            }
        }
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_L_ROUND) {
            ret_error(SYNTAX_ERROR);
        }
        printf("typ funkcie: %s\n", type);
        TFunction *f = funcDef(table, tokenID, type);
        //node = BSTSearch(table, tokenID->data);
        //node->defined = 1;
        f->defined = 1;
        printf("function %s is defined\n", f->name);
    } else {
        type = token->data;   //typ premennej resp funkcie
        printf("typ tokenu: %s\n", type);
        printf("som v else vetve\n");
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }

        tokenID = token;

        printf("tablename: %s\n", table->name);

        node = BSTSearch(table->Root, tokenID->data);

        if ((node != NULL) && (node->type == NODE_TYPE_FUNCTION)) {
            if (node->data.f->defined == 1) {
                ret_error(SEMANTIC_DEF_ERROR);
            }
        } else if ((node != NULL) && (node->type == NODE_TYPE_VARIABLE)) {
            if (node->data.v->declared == 1) {
                ret_error(SEMANTIC_DEF_ERROR);
            }
        }

        printf("som za ifom\n");
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_L_ROUND) {
            unget_token(1);
            TVariable *v = variableDecl(table, tokenID, type);
            v->declared = 1;
            v->position = table->data.c->numOfVars;
            table->data.c->numOfVars++;
            printf("var %s is declared\n", v->name);
        } else {
            TFunction *f = funcDef(table, tokenID, type);
            f->declared = 1;
            f->defined = 1;
            printf("function %s is defined\n", f->name);
            //node = BSTSearch(table, tokenID->data);
            //node->defined = 1;
        }
    }
}

TVariable *variableDecl(tTablePtr table, Ttoken *tokenID, char *type) {
    printf("som vo variableDecl\n");

    TVariable *var;
    tTablePtr node = NULL;
    printf("tokenID: %s\n", tokenID->data);
    node = BSTSearch(table->Root, tokenID->data);

    printf("som za BSTSearch\n");
    printf("nazov tabulky: %s\n", table->name);
    if (node == NULL) {
        printf("som v ife\n");
        var = new_variable(tokenID, table);
        printf("som za new_var\n");
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
        printf("varname: %s\n", var->name);
    }

    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type == TOKEN_ASSIGN) {

        printf("som v assign\n");
        expression(var);

        printf("som za expr\n");
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_SEM_CL) {
            ret_error(SYNTAX_ERROR);
        }

    } else if (token->type != TOKEN_SEM_CL) {
        ret_error(SEMANTIC_DEF_ERROR);
    }

    //store_variable(var, &table);

    printf("tablename: %s\n", table->name);
    printf("tokenID: %s\n", tokenID->data);
    node = BSTSearch(table->Root, tokenID->data);
    //printf("som za BSTSearch\n");
    node->data.v = var;
    //node->type = NODE_TYPE_VARIABLE;
    printf("nacitany token pred koncom variableDecl: %s\n", token->data);

    if(table->type == NODE_TYPE_CLASS){
        TListItem pushVar = create_instruction(INS_PUSH_VAR, var, table->data.c->stack, NULL);
        insert_instruction(globalInitList, pushVar);
    }
    else if(table->type == NODE_TYPE_FUNCTION){
        TListItem pushVar = create_instruction(INS_PUSH_VAR, var, table->data.f->stack, NULL);
        insert_instruction(table->data.f->list, pushVar);
    }

    return var;
}


TFunction *funcDef(tTablePtr table, Ttoken *tokenID, char *funcType) {
    printf("som vo funcDef\n");
    TFunction *f;
    TVariable *v;
    Ttoken *token_varID;
    tTablePtr node;
    int paramsCount = 0;

    //char *type = NULL;
    printf("tablename: %s\n", table->name);
    printf("tokenID: %s\n", tokenID->data);
    node = BSTSearch(table->Root, tokenID->data);
    if (node == NULL) {
        f = new_function(tokenID->data, table);
    } else {
        f = node->data.f;
        //printf("nazov funkcie: %s\n", f->name);
    }

    f->numOfVars = 0;

    printf("som za new_func\n");
    //stackPush(gStack, f);
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


    printf("typ funkcie: %d\n", f->params[paramsCount]);
    //f = stackTop(gStack);

    tTablePtr fTable = BSTSearch(table->Root, tokenID->data);
    classContext = table;
    funcContext = fTable;
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    while (token->type != TOKEN_R_ROUND) {
        paramsCount++;
        params(fTable, token, paramsCount);
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if ((token->type != TOKEN_COLON) && (token->type != TOKEN_R_ROUND)) {
            ret_error(SYNTAX_ERROR);
        }
    }

    f->numOfParams = paramsCount;
    printf("pocet parametrov: %d\n", f->numOfParams);

    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type != TOKEN_L_CURLY) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    printf("som pred switchom\n");


    while (token->type != TOKEN_R_CURLY) {
        printf("som vo while\n");
        switch (token->type) {  //volanie funkcii alebo priradovanie hodnot do premennych
            case TOKEN_TYPE: {
                //deklaracie a definicie lokalnych premennych
                printf("som v switchi case token_type\n");
                char *type = token->data;

                token = get_token();
                printf("nacitany token: %s\n", token->data);
                if (token->type != TOKEN_ID) {
                    ret_error(SYNTAX_ERROR);
                }

                token_varID = token;

                printf("tablename: %s\n", fTable->name);

                printf("tokenID: %s\n", token_varID->data);
                if ((BSTSearch(fTable->Root, token_varID->data))) {
                    ret_error(SEMANTIC_DEF_ERROR);
                }

                v = variableDecl(fTable, token_varID, type);
                printf("som za variableDecl v token_type\n");
                v->declared = 1;
                v->position = f->numOfVars;
                f->numOfVars++;

                //token = get_token();
                //printf("nacitany token: %s\n", token->data);
                break;
            }
            case TOKEN_ID: {
                printf("som v switchi case token_id\n");
                token_varID = token;
                node = NULL;
                token = get_token();
                printf("nacitany token: %s\n", token->data);
                if (token->type == TOKEN_DOT) {
                    char *className = token_varID->data;
                    tTablePtr tableOfClass;
                    if (!(strcmp(className, "ifj16"))) {
                        tableOfClass = create_class_table(className, builtInTable);
                        //tableOfClass->type = NODE_TYPE_CLASS;
                        printf("som v builtInTable\n");
                    } else {
                        tableOfClass = create_class_table(className, globTable);
                        //tableOfClass->type = NODE_TYPE_CLASS;
                        printf("som v classTable\n");
                    }
                    token = get_token();
                    printf("nacitany token: %s\n", token->data);
                    if (token->type != TOKEN_ID) {
                        ret_error(SYNTAX_ERROR);
                    }
                    token_varID = token;

                    token = get_token();
                    printf("nacitany token: %s\n", token->data);
                    if (token->type == TOKEN_ASSIGN) {
                        unget_token(1);
                        printf("tablename: %s\n", tableOfClass->name);
                        printf("token_varID: %s\n", token_varID->data);
                        printf("som pred variableDecl\n");
                        variableDecl(tableOfClass, token_varID, NULL);
                        printf("som za variableDecl a nacitany token je: %s\n", token->data);
                        //unget_token(1);
                        //token = get_token();
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    } else if (token->type == TOKEN_L_ROUND) {
                        printf("som vo vetve func\n");
                        printf("nazov hladanej funkcie: %s\n", token_varID->data);
                        printf("nazov tabulky: %s\n", tableOfClass->name);
                        node = BSTSearch(tableOfClass->Root, token_varID->data);
                        printf("som za BSTSearch\n");

                        if ((node == NULL) && (!(strcmp(tableOfClass->name, builtInTable->name)))) {
                            ret_error(SEMANTIC_DEF_ERROR);
                        } else if ((node == NULL) && (strcmp(tableOfClass->name, builtInTable->name))) {
                            printf("nacitany token: %s\n", token->data);
                            TFunction *f = new_function(token_varID->data, tableOfClass);
                            printf("function name: %s\n", f->name);
                            f->declared = 1;
                            //node = BSTSearch(tableOfClass->Root, token_varID->data);
                            //node->data.f = f;
                            //node->type = NODE_TYPE_FUNCTION;

                            unget_token(4);

                            expression(NULL);

                        } else {
                            unget_token(4);

                            expression(NULL);
                            printf("som za expr\n");

                        }
                        token = get_token();
                        printf("nacitany token: %s\n", token->data);
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    } else {
                        ret_error(SYNTAX_ERROR);
                    }

                } else {

                    printf("nacitany token pred unget: %s\n", token->data);
                    unget_token(1);

                    //printf("nacitany token za unget: %s\n", token->data);
                    printf("tablename: %s\n", fTable->name);
                    printf("token_varID: %s\n", token_varID->data);
                    node = BSTSearch(fTable->Root,
                                     token_varID->data);   //neexistuje staticka premmenna s nazvom token->data v danej triede
                    if (node == NULL) {

                        node = BSTSearch(table->Root, token_varID->data);
                        if (node == NULL) {

                            ret_error(SEMANTIC_DEF_ERROR);

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
                                //token = get_token();
                                if (token->type != TOKEN_SEM_CL) {
                                    ret_error(SYNTAX_ERROR);
                                }
                            } else {
                                ret_error(SYNTAX_ERROR);
                            }
                        }
                    } else {
                        printf("som v else\n");
                        token = get_token();
                        printf("nacitany token: %s\n", token->data);
                        if (token->type == TOKEN_ASSIGN) {
                            printf("som v assign\n");
                            unget_token(1);
                            variableDecl(fTable, token_varID, NULL);
                            printf("som za variableDecl a nacitany token je: %s\n", token->data);
                            unget_token(1);
                            token = get_token();
                            if (token->type != TOKEN_SEM_CL) {
                                ret_error(SYNTAX_ERROR);
                            }
                        } else if (token->type == TOKEN_L_ROUND) {
                            unget_token(2);

                            expression(NULL);
                            token = get_token();
                            printf("nacitany token: %s\n", token->data);
                            if (token->type != TOKEN_SEM_CL) {
                                ret_error(SYNTAX_ERROR);
                            }
                        } else {
                            ret_error(SYNTAX_ERROR);
                        }
                    }
                }
                printf("som pred breakom a mam token %s\n", token->data);

                break;
            }
            case KEYWORD_IF: {
                printf("nacitany token v caseIF: %s\n", token->data);
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
            default:
                ret_error(SYNTAX_ERROR);
        }
        token = get_token();
        printf("nacitany token: %s\n", token->data);
    }
    printf("som za whileom\n");

    //store_function(f, &table);
    printf("nazov tabulky: %s\n", table->name);
    printf("nazov funkcie: %s\n", tokenID->data);
    node = BSTSearch(table->Root, tokenID->data);
    //printf("som za BSTSearch\n");
    node->data.f = f;
    //node->type = NODE_TYPE_FUNCTION;
    //node->defined = 1;
    //stackPop(gStack);
    return f;
    //...
}

void params(tTablePtr fTable, Ttoken *token, int numOfParam) { //spracovanie parametrov funkcie
    printf("som v params\n");
    tTablePtr table = fTable;
    tTablePtr node = NULL;
    TFunction *f = table->data.f;
    TVariable *var;
    if (token->type != TOKEN_TYPE) {
        ret_error(SEMANTIC_DEF_ERROR);
    }
    //char *type = token->data;
    if (!(strcmp(token->data, "int"))) {
        f->params[numOfParam] = VARTYPE_INTEGER;
    } else if (!(strcmp(token->data, "double"))) {
        f->params[numOfParam] = VARTYPE_DOUBLE;
    } else if (!(strcmp(token->data, "String"))) {
        f->params[numOfParam] = VARTYPE_STRING;
    } else {
        f->params[numOfParam] = VARTYPE_NULL;
    }

    Ttoken *tokenID = get_token();
    printf("tokenID: %s\n", tokenID->data);
    if (tokenID->type != TOKEN_ID) {
        ret_error(SYNTAX_ERROR);
    }
    printf("tablename: %s\n", table->name);

    node = BSTSearch(table->Root, tokenID->data);
    if (node == NULL) {
        var = new_variable(tokenID, table);
    } else {
        ret_error(SEMANTIC_DEF_ERROR);
        //var = node->data.v;
    }
    var->declared = 1;
    //store_variable(var, &table);
    node = BSTSearch(table->Root, tokenID->data);
    node->data.v = var;
    //node->type = NODE_TYPE_VARIABLE;

    printf("koncim params\n");

}

void ifelse_statement(tTablePtr table) {
    printf("som v if_statement\n");

    TVariable *var = malloc(sizeof(TVariable));

    TListItem endIf = create_instruction(INS_LABEL, NULL, NULL, NULL);
    TListItem endElse = create_instruction(INS_LABEL, NULL, NULL, NULL);
    TListItem cmp = create_instruction(INS_JCMP, var, NULL, endIf);
    TListItem jmp = create_instruction(INS_JMP, NULL, NULL, endElse);

    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type != TOKEN_L_ROUND) {
        ret_error(SYNTAX_ERROR);
    }
    printf("som v ife pred expr\n");
    expression(var);
    printf("som v ife za expr\n");


    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type != TOKEN_R_ROUND) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type != TOKEN_L_CURLY) {
        ret_error(SYNTAX_ERROR);
    }

    insert_instruction(table->data.f->list, cmp);

    token = get_token();
    printf("nacitany token: %s\n", token->data);

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
    printf("som vo while_statement\n");
    TVariable *var = malloc(sizeof(TVariable));

    TListItem startWhile = create_instruction(INS_LABEL, NULL, NULL, NULL);
    TListItem endWhile = create_instruction(INS_LABEL, NULL, NULL, NULL);
    TListItem cmp = create_instruction(INS_JCMP, var, NULL, endWhile);
    TListItem jmp = create_instruction(INS_JMP, NULL, NULL, startWhile);

    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type != TOKEN_L_ROUND) {
        ret_error(SYNTAX_ERROR);
    }
    printf("som pred expr vo while_statement\n");
    expression(var);
    printf("som za expr vo while_statement\n");
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type != TOKEN_R_ROUND) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type != TOKEN_L_CURLY) {
        ret_error(SYNTAX_ERROR);
    }

    insert_instruction(table->data.f->list, startWhile);

    insert_instruction(table->data.f->list, cmp);

    token = get_token();
    printf("nacitany token: %s\n", token->data);

    block_body(token);

    insert_instruction(table->data.f->list, jmp);

    insert_instruction(table->data.f->list, endWhile);

}

void return_statement(tTablePtr table) {
    printf("som v return_statement\n");

    TListItem retItem;
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (table->data.f->params[0] == FUNCTYPE_VOID) {
        retItem = create_instruction(INS_RET, NULL, NULL, NULL);
        if (token->type != TOKEN_SEM_CL) {
            ret_error(SYNTAX_ERROR);
        }

    } else {
        TVariable *ret = malloc(sizeof(TVariable));
        retItem = create_instruction(INS_RET, ret, NULL, NULL);
        expression(ret);
        token = get_token();
        if (token->type != TOKEN_SEM_CL) {
            ret_error(SYNTAX_ERROR);
        }
    }

    insert_instruction(table->data.f->list, retItem);

}

void block_body(Ttoken *token) {
    tTablePtr node;
    Ttoken *token_varID;
    while (token->type != TOKEN_R_CURLY) {
        printf("som vo while\n");
        switch (token->type) {

            case TOKEN_ID: {
                printf("som v switchi case token_id\n");

                token_varID = token;
                token = get_token();
                printf("nacitany token: %s\n", token->data);
                if (token->type == TOKEN_DOT) {
                    char *className = token_varID->data;
                    tTablePtr tableOfClass;
                    if (!(strcmp(className, "ifj16"))) {
                        tableOfClass = create_class_table(className, builtInTable);
                        //tableOfClass->type = NODE_TYPE_CLASS;
                        printf("som v builtInTable\n");
                    } else {
                        tableOfClass = create_class_table(className, globTable);
                        //tableOfClass->type = NODE_TYPE_CLASS;
                        printf("som v classTable\n");
                    }
                    token = get_token();
                    printf("nacitany token: %s\n", token->data);
                    if (token->type != TOKEN_ID) {
                        ret_error(SYNTAX_ERROR);
                    }
                    token_varID = token;

                    token = get_token();
                    printf("nacitany token: %s\n", token->data);
                    if (token->type == TOKEN_ASSIGN) {
                        unget_token(1);
                        printf("tablename: %s\n", tableOfClass->name);
                        printf("token_varID: %s\n", token_varID->data);
                        printf("som pred variableDecl\n");
                        variableDecl(tableOfClass, token_varID, NULL);
                        printf("som za variableDecl a nacitany token je: %s\n", token->data);
                        //unget_token(1);
                        //token = get_token();
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    } else if (token->type == TOKEN_L_ROUND) {
                        printf("som vo vetve func\n");
                        printf("nazov hladanej funkcie: %s\n", token_varID->data);
                        printf("nazov tabulky: %s\n", tableOfClass->name);
                        node = BSTSearch(tableOfClass->Root, token_varID->data);
                        printf("som za BSTSearch\n");

                        if ((node == NULL) && (!(strcmp(tableOfClass->name, builtInTable->name)))) {
                            ret_error(SEMANTIC_DEF_ERROR);
                        } else if ((node == NULL) && (strcmp(tableOfClass->name, builtInTable->name))) {
                            printf("nacitany token: %s\n", token->data);
                            TFunction *f = new_function(token_varID->data, tableOfClass);
                            printf("function name: %s\n", f->name);
                            f->declared = 1;
                            //node = BSTSearch(tableOfClass->Root, token_varID->data);
                            //node->data.f = f;
                            //node->type = NODE_TYPE_FUNCTION;

                            unget_token(4);

                            expression(NULL);
                            token = get_token();
                            if (token->type != TOKEN_SEM_CL) {
                                ret_error(SYNTAX_ERROR);
                            }
                        } else {
                            unget_token(4);

                            expression(NULL);
                            printf("som za expr\n");
                            token = get_token();
                        }

                        printf("nacitany token: %s\n", token->data);
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    } else {
                        ret_error(SYNTAX_ERROR);
                    }

                } else {

                    printf("nacitany token pred unget: %s\n", token->data);
                    unget_token(1);

                    //printf("nacitany token za unget: %s\n", token->data);

                    printf("token_varID: %s\n", token_varID->data);
                    node = BSTSearch(funcContext->Root, token_varID->data);   //neexistuje staticka premmenna s nazvom token->data v danej triede
                    if (node == NULL) {

                        node = BSTSearch(classContext->Root, token_varID->data);
                        if (node == NULL) {

                            ret_error(SEMANTIC_DEF_ERROR);

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
                                        printf("function name: %s\n", f->name);
                                        f->defined = 1;
                                        //node = BSTSearch(table->Root, tokenID->data);
                                        //node->data.f = f;
                                        //node->type = NODE_TYPE_FUNCTION;
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
                        printf("som v else\n");
                        token = get_token();
                        printf("nacitany token: %s\n", token->data);
                        if (token->type == TOKEN_ASSIGN) {
                            printf("som v assign\n");
                            unget_token(1);
                            variableDecl(funcContext, token_varID, NULL);
                            printf("som za variableDecl a nacitany token je: %s\n", token->data);
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
                printf("som pred breakom a mam token %s\n", token->data);
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
        printf("nacitany token: %s\n", token->data);
    }
}


/*--------------------/automat-----------------------*/

void parse() {

    parser_init();
    starter();
    parser_finish();
}