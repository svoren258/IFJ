#include "parser.h"
#include "error.h"

Ttable* globTable;
Ttoken *token;

void keywords_init()
{
	int i = 0;
	while(keywords[i])
	{	
		token->name = keywords[i];
		TVariable *v = new_variable(token);
		v->type = TYPE_KEYWORD;
		store_variable(v, globTable);
		i++;
	}

}

void parser_init()
{
	globTable = create_table();	
	
	/*keywords*/
	keywords_init();
	
}

TFunction *new_function(Ttoken *token)
{	/*allocate the space for a new function*/
	TFunction *f;
	f = malloc(sizeof(TFunction));

	/*create local symbol table*/
	Ttable *table;
	table = malloc(sizeof(Ttable));

	/*assign the table to the function*/
	f->type = RET_INT;
	f->table = table;
	f->name = token->name;
	return f;
}

TVariable *new_variable(Ttoken *token)
{	
	TVariable *v;
	v = malloc(sizeof(TVariable));
	
	v->name = token->name;
	return v;

}
void store_function(/*stack*/TFunction *f)
{
	insert_table_symbol(f,NULL,&globTable);
}
void store_variable(/*stack*/TVariable *v, Ttable *table)
{
	insert_table_symbol(NULL, v, &table);
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
	token = get_token();
	token->name = "count";

	TFunction *f;
	f = new_function(token);

	token->name = "a";
	token->type = TYPE_INT;

	TVariable *v;
	v = new_variable(token);
	store_variable(v,f->table);

	token->name = "b";
	token->type = TYPE_INT;
	
	v = new_variable(token);

	store_variable(v, f->table);
	store_function(f);

	//printf("%s\n",f->table->root->name);
	
	destroy_table(&globTable);
}