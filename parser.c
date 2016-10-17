#include "parser.h"

Ttable* globTable;
Ttable* locTable;
Ttoken *token;

void parser_init(){
	globTable = create_table();	
	locTable = create_table();	
	
	printf("%s\n",keywords[1]);
}

TFunction *new_function(Ttoken *token){
	TFunction *f;
	f = malloc(sizeof(TFunction));
	f->name = token->name;
	return f;
}

TVariable *new_variable(Ttoken *token){
	TVariable *v;
	v = malloc(sizeof(TVariable));
	
	return v;

}
void store_function(/*stack*/TFunction *f){
	insert_table_symbol(f,NULL,&globTable);
}
void store_variable(/*stack*/TVariable *v){

}


/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/

void parse(){
	parser_init();
	token = get_token();
	TFunction *f;
	
	f = new_function(token);
	store_function(f);


	
	f = new_function(token);
	store_function(f);

	token->name = " LOL";
	
	f = new_function(token);
	store_function(f);


	destroy_table(&locTable);
	destroy_table(&globTable);
}