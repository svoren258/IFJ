#include "parser.h"

Ttable* globTable;
Ttable* locTable;
Ttoken *token;

void parser_init(){
	globTable = create_table();	
	locTable = create_table();	
	/*keywords*/

	int i = 0;
	while(keywords[i])
	{	
		//printf("%s\n",keywords[i]);
		token->name = keywords[i];
		TVariable *v = new_variable(token);
		store_variable(v);
		
		i++;
	}
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
	v->name = token->name;
	return v;

}
void store_function(/*stack*/TFunction *f){
	insert_table_symbol(f,NULL,&globTable);
}
void store_variable(/*stack*/TVariable *v){
	insert_table_symbol(NULL,v,&globTable);
}


/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/

void parse(){
	parser_init();
	token = get_token();
	

	destroy_table(&locTable);
	destroy_table(&globTable);
}