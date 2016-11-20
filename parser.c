/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#include "parser.h"
#include "error.h"
#include "list.h"
#include "stack.h"
tTablePtr context;
tTablePtr globTable;//v nej su tabulky tried | v kazdej tabulke triedy su jej funkcie a glob premenne.
Ttoken *token;//globalna premenna struktury token - do nej sa priradzuje vysledok get_token();
TStack *gStack;//zasobnik, pravdepodobne na prehladu o tom, ktora funkcia sa prave spracuvava

tTablePtr create_class_table(char* name)//navratova hodnota - uzol stromu
{
    printf("som v create_class_table\n");
    tTablePtr classTable;
    tTablePtr node = BSTSearch(globTable, name);
    if(node == NULL){
        //vytvorenie pointera
        BSTInit(&classTable);//inicializacia(uzol = NULL)
        BSTInsert(&globTable, &classTable, name);//pridanie uzlu do tabulky a nastavenie atributu - name
        classTable = BSTSearch(globTable, name);

        return classTable;
    }
    return node;//vrati uzol tabulky triedy
}

void parser_init()
{
	
	gStack = stackInit();
	
	BSTInit(&globTable);
	
	BSTInsert(&globTable, &globTable, "GlobTable");
	
	/*keywords to globtable*/
	// keywords_init();
	
}

void parser_finish() {
    BSTDispose(&globTable);

}

TFunction *new_function(Ttoken *token, tTablePtr table)
{	/*allocate the space for a new function*/
	TFunction *f;
	f = malloc(sizeof(TFunction));

	tTablePtr loc_table;
	BSTInit(&loc_table);
    BSTInsert(&table, &loc_table, token->data);
	TStack *stack = stackInit();
	
	f->stack = stack;
	/*assign the table to the function*/
	f->defined = 0;
	f->table = loc_table;
	f->name = token->data;
	return f;
}

TVariable *new_variable(Ttoken *token)
{	
	TVariable *v;
	v = malloc(sizeof(TVariable));
	v->declared = 0;
    v->name = token->data;
    v->type = VARIABLE_NULL;
	return v;

}

void store_function(/*stack*/TFunction *f, tTablePtr *table) {
    tTablePtr new_func;
    BSTInit(&new_func);

    BSTInsert(table, &new_func, f->name);
    stackPush(gStack, f);
}
void store_variable(/*stack*/TVariable *v, tTablePtr *table)
{

	if(!( BSTSearch(*table, v->name)))
	{
        tTablePtr new_var;
        BSTInit(&new_var);
        BSTInsert(table, &new_var, v->name);
        new_var->data.v = v;
	}
    else{
        tTablePtr node = BSTSearch(*table, v->name);
        node->data.v = v;
    }

}


/*--------------------automat-----------------------*/
void starter() {
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    printf("nacitany token ma cislo: %d\n", token->type);
    if (token->type == KEYWORD_CLASS) {

        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }

        tTablePtr table = create_class_table(token->data);

        tTablePtr node = BSTSearch(globTable, token->data);


        node->type = "class"; // => table->type = "class"; ???

        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_L_CURLY) {
            ret_error(SYNTAX_ERROR);
        }
        printf("tablename: %s\n", table->name);
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        while (token->type == KEYWORD_STATIC) {
            printf("som vo while\n");
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
    }
    else{
        ret_error(SYNTAX_ERROR);
    }

//        if (token->data == TOKEN_EOF){
//            ret_error(0);
//        }
    //dosli sme na koniec programu
}

void Declaration(tTablePtr table, Ttoken *token) {
    printf("som v Declaration\n");
    Ttoken *tokenID;
    tTablePtr node = NULL;
    char *type = NULL;
    printf("cislo tokenu: %d\n", token->type);
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
        node = BSTSearch(table, tokenID->data);
        if (node != NULL) {

            if (node->data.f->defined == 1) {
                ret_error(SEMANTIC_DEF_ERROR);
            }
        }
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_L_ROUND) {
            ret_error(SYNTAX_ERROR);
        }
        TFunction *f = funcDef(table, tokenID, type);
        f->defined = 1;
    } else {
        type = token->data;   //typ premennej resp funkcie
        printf("som v else vetve\n");
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }

        tokenID = token;

        printf("tablename: %s\n", table->name);

        node = BSTSearch(table, tokenID->data);

        if (node != NULL) {
            printf("som v ife\n");
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
            printf("var is declared\n");
        }
        else{
            TFunction *f = funcDef(table, tokenID, type);
            f->defined = 1;
        }
    }
}

TVariable *variableDecl(tTablePtr table, Ttoken *tokenID, char *type) {
    printf("som vo variableDecl\n");

    TVariable *var;
    tTablePtr node = NULL;

    node = BSTSearch(table, tokenID->data);
    printf("som za BSTSearch\n");
    if(node == NULL){
        printf("som v ife\n");
        var = new_variable(tokenID);
        printf("som za new_var\n");
        var->type = type;
    }
    else{
        var = node->data.v;

        printf("varname: %s\n", var->name);
    }

    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type == TOKEN_ASSIGN) {
        context = table;
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
    printf("som pred store\n");
    store_variable(var, &table);
    printf("som za store\n");
    printf("tablename: %s\n", table->name);
    printf("tokenID: %s\n", tokenID->data);
    node = BSTSearch(table, tokenID->data);
    printf("som za BSTSearch\n");
    node->type = "variable";

    return var;
}


TFunction *funcDef(tTablePtr table, Ttoken *tokenID, char *funcType) {
    printf("som vo funcDef\n");
    TFunction *f;
    TVariable *v;
    Ttoken *token_varID;
    tTablePtr node = NULL;
    int paramsCount = 0;
    //char *type = NULL;
    f = new_function(tokenID, table);
    printf("som za new_func\n");
    //stackPush(gStack, f);

    f->params[paramsCount] = funcType;
    printf("typ funkcie: %s\n", f->params[paramsCount]);
    //f = stackTop(gStack);

    token = get_token();
    printf("nacitany token: %s\n", token->data);
    while (token->type != TOKEN_R_ROUND) {
        paramsCount++;
        params(f, token, paramsCount);
        token = get_token();
        if ((token->type != TOKEN_COLON) && (token->type != TOKEN_R_ROUND)) {
            ret_error(SYNTAX_ERROR);
        }
    }

    f->numOfParams = paramsCount;

    token = get_token();
    printf("nacitany token: %s\n", token->data);
    if (token->type != TOKEN_L_CURLY) {
        ret_error(SYNTAX_ERROR);
    }
    token = get_token();
    printf("nacitany token: %s\n", token->data);
    while (token->type == TOKEN_TYPE) { //deklaracie a definicie lokalnych premennych
        printf("som vo while\n");
        char *type = token->data;
        token = get_token();
        printf("nacitany token: %s\n", token->data);
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }
        token_varID = token;
        printf("tablename: %s\n", f->table->name);
        printf("tokenID: %s\n", token_varID->data);
        if((BSTSearch(f->table, token_varID->data))){
            ret_error(SEMANTIC_DEF_ERROR);
        }

        v = variableDecl(f->table, token_varID, type);
        printf("som za variableDecl\n");
        v->declared = 1;

        token = get_token();
        printf("nacitany token: %s\n", token->data);
    }
    printf("som za whileom a pred switchom\n");

    switch (token->type) {  //volanie funkcii alebo priradovanie hodnot do premennych
        case TOKEN_ID:
            printf("som v switchi case token_id\n");
            token_varID = token;

            node = NULL;
            token = get_token();
            printf("nacitany token: %s\n", token->data);
            if(token->type == TOKEN_DOT) {
                char *className = token_varID->data;
                tTablePtr tableOfClass = create_class_table(className);
                token = get_token();
                if (token->type != TOKEN_ID) {
                    ret_error(SYNTAX_ERROR);
                }
                //tokenID = token;
                //node = BSTSearch(tableOfClass, tokenID->data);
                //if(node == NULL){
                token = get_token();
                if (token->type == TOKEN_ASSIGN) {
                    unget_token(1);
                    variableDecl(tableOfClass, token_varID, NULL);
                    //unget_token(1);
                    //token = get_token();
                    if (token->type != TOKEN_SEM_CL) {
                        ret_error(SYNTAX_ERROR);
                    }
                }
                else if (token->type == TOKEN_L_ROUND) {
                    unget_token(2);
                    context = tableOfClass;
                    expression(NULL);
                    unget_token(1);
                    if (token->type != TOKEN_SEM_CL) {
                        ret_error(SYNTAX_ERROR);
                    }
                }
                else {
                    ret_error(SYNTAX_ERROR);
                }
            }
            unget_token(1);
            printf("tablename: %s\n", f->table->name);
            printf("tokenID: %s\n", token_varID->data);
            node = BSTSearch(f->table, token_varID->data);   //neexistuje staticka premmenna s nazvom token->data v danej triede
            if (node == NULL) {

                node = BSTSearch(table, token_varID->data);
                if (node == NULL) {

                    token = get_token();

                    if(token->type == TOKEN_ASSIGN){
                        unget_token(1);
                        variableDecl(f->table, token_varID, NULL);
                        unget_token(1);
                        token = get_token();
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    }
                    else if (token->type == TOKEN_L_ROUND) {
                        unget_token(2);
                        context = f->table;
                        expression(NULL);
                        unget_token(1);

                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    }
                    else{
                        ret_error(SYNTAX_ERROR);
                    }
                }
                else {
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
                        context = table;
                        expression(NULL);
                        unget_token(1);
                        token = get_token();
                        if (token->type != TOKEN_SEM_CL) {
                            ret_error(SYNTAX_ERROR);
                        }
                    }
                    else{
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
                    variableDecl(f->table, token_varID, NULL);
                    unget_token(1);
                    printf("som za variableDecl\n");
                    token = get_token();
                    if (token->type != TOKEN_SEM_CL) {
                        ret_error(SYNTAX_ERROR);
                    }
                } else if (token->type == TOKEN_L_ROUND) {
                    unget_token(2);
                    context = f->table;
                    expression(NULL);
                    unget_token(1);
                    token = get_token();
                    if (token->type != TOKEN_SEM_CL) {
                        ret_error(SYNTAX_ERROR);
                    }
                }
                else{
                    ret_error(SYNTAX_ERROR);
                }
            }
            break;


//        case KEYWORD_IF:
//            if_statement(token);
//            break;
//        case KEYWORD_FOR:
//            for_statement();
//            break;
//        case KEYWORD_WHILE:
//            while_statement();
//            break;
//        case KEYWORD_BREAK:
//            //vytvori instrukciu break
//            break;
//        case KEYWORD_CONTINUE:
//            //vytvori instrukciu continue
//            break;
//        case KEYWORD_DO:
//            do_statement();
//            break;
//        case KEYWORD_ELSE:
//            else_statement();
//            break;
//        case KEYWORD_RETURN:
//            //vytvori instrukciu return
//            break;

    }
    store_function(f, &table);

    node = BSTSearch(table, tokenID->data);
    node->type = "function";
    //stackPop(gStack);
    return f;
    //...


}

    void params(TFunction *f, Ttoken *token, int numOfParam) { //spracovanie parametrov funkcie

        tTablePtr table = f->table;
        tTablePtr node = NULL;
        TVariable *var;
        if (token->type != TOKEN_TYPE) {
            ret_error(SEMANTIC_DEF_ERROR);
        }
        //char *type = token->data;
        f->params[numOfParam] = token->data;
        //var->type = type;
        Ttoken *tokenID = get_token();
        var = new_variable(tokenID);
        if (token->type != TOKEN_ID) {
            ret_error(SYNTAX_ERROR);
        }

        store_variable(var, &table);
        node = BSTSearch(table, tokenID->data);
        node->type = "variable";
        var->declared = 1;

    }

//    void if_statement(Ttoken *token) {
//        TVariable *var;
//        var = new_variable(token);
//        token = get_token();
//        if (token->type != TOKEN_L_ROUND) {
//            ret_error(SYNTAX_ERROR);
//        }
//        expression(&(*var));
//
//
//        TElem *label;
//        label->operation = ins_lab;
//        label->add1 = NULL;
//        label->add2 = NULL;
//        label->add3 = NULL;
//
//        insertInstruction();
//        //create_ins(ins_jmp, var, NULL, label);
//        //create_ins(ins_lab, NULL, NULL, NULL);
//    }


/*--------------------/automat-----------------------*/

void parse()
{

	parser_init();
    starter();
	parser_finish();
}