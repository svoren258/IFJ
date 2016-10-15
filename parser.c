#include "ial.h"
#include "lex.h"


Ttable* globTable;
Ttable* locTable;

void parser_init(){

	globTable = create_table();	
	locTable = create_table();	
}

/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/

void parse(){


	Ttoken *token = get_token();

	insert_table_symbol("test", &globalSTable);
	insert_table_symbol("string", &globalSTable);


	destroy_table(&globalSTable);
}