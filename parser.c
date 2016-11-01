#include "parser.h"
#include "error.h"

tTablePtr globTable;
Ttoken *token;
tStack *gStack;

void keywords_init()
{
	int i = 0;
	while(keywords[i])
	{	
		
		 token->name = keywords[i];
		 TVariable *v = new_variable(token);
		 v->type = TYPE_KEYWORD;
		
		 store_variable(v, &globTable);
		 i++;
	}

}

void parser_init()
{
	
	gStack = stackInit();
	
	BSTInit(&globTable);
	BSTInsert(&globTable, &globTable, "GlobTable");

	/*keywords to globtable*/
	keywords_init();
	
}

void parser_finish()
{
	BSTDispose(&globTable);
	
}

TFunction *new_function(Ttoken *token)
{	/*allocate the space for a new function*/
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

TVariable *new_variable(Ttoken *token)
{	
	TVariable *v;
	v = malloc(sizeof(TVariable));
	
	v->inicialized = FALSE;
	v->name = token->name;
	return v;

}
void store_function(/*stack*/TFunction *f, tTablePtr *table)
{
	tTablePtr new_func;
	BSTInit(&new_func);

	BSTInsert(table, &new_func, f->name);
	stackPush(gStack, f);
}
void store_variable(/*stack*/TVariable *v, tTablePtr *table)
{
	
	if( BSTExists(*table, v->name) )
	{
		ret_error(SYNTAX_ERROR);
	}
		
	tTablePtr new_var;
	BSTInit(&new_var);

	BSTInsert(table, &new_var, v->name);
	new_var->data.v = v;
	
	
}


/*--------------------automat-----------------------*/
void starter(){
    Ttoken *token = get_token();
    if(token->type == TOKEN_CLASS){
        token = get_token();
        if(token->type == TOKEN_MAIN){
            token = get_token();
            if(token->type == L_BRACKET){
                token = get_token();
                if(token->type == TOKEN_STATIC) {
                    globalDecl(token);
                }

                void globalDecl(Ttoken token) {
                    while (token->type == TOKEN_STATIC) { //deklaracie globalnych premennych
                        token = get_token();
                        declare(globTable, token);
                    }
                }

                void declare(Ttable table, Ttoken token) {
                    if(token->type == TOKEN_INT || token->type == TOKEN_STRING ||
                        token->type == TOKEN_DOUBLE) {
                        token = get_token();
                        if (token->type == TOKEN_ID) {
                            if (search_Id(globTable, token)) {

                            }
                            else {
                                add_Id(globTable, token);
                            }
                            token = get_token();
                            if (token->type == L_ROUND_BRACKET) {
                                token = get_token();
                                params(token);
                            }
                            if (token->type == TOKEN_SEMICOLON) {
                                token = get_token();
                            }
                        }
                    }
                    if(token->type == TOKEN_VOID){
                        token = get_token();
                        if(token->type == TOKEN_RUN){
                            token = get_token();
                            if(token->type == L_ROUND_BRACKET) {
                                token = get_token();
                                if (token->type == R_ROUND_BRACKET) {
                                    func_definition();
                                }
                            }
                        }
                        else {
                            if(token->type == TOKEN_ID){
                                token = get_token();
                                if(token->type == L_ROUND_BRACKET){
                                    token = get_token();
                                }
                                params(token);
                             }

                        }
                    }

                }

            void params(Ttoken token){
                while(token->type != R_ROUND_BRACKET){
                    token = get_token();
                    if (token->type == TOKEN_INT || token->type == TOKEN_STRING ||
                        token->type == TOKEN_DOUBLE) {
                        token = get_token();
                        if (token->type == TOKEN_ID) {
                            if (search_Id(localTable, token)) {
                                continue;
                            }
                            else {
                                add_Id(localTable, token);
                            }
                            token = get_token();
                            if(token->type == TOKEN_COLON){
                                continue;
                            }
                        }
                    }
                    else{
                        ret_error(SEMANTIC_TYPE_ERROR);
                    }
                }
            }
            void func_definition(){
                token = get_token();
                if(token->type == TOKEN_INT || token->type == TOKEN_DOUBLE || token->type == TOKEN_STRING){
                    declare(localTable, token);
                }
                if(token->type == TOKEN_ID){
                    token = get_token();
                    if(token->type == TOKEN_ASSIGN){

                    }
                }

            }
            void assign(){

            }

                }
            }
        }
    }

/*--------------------/automat-----------------------*/

void parse()
{
	parser_init();


	parser_finish();

}