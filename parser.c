#include "ial.h"


void init(){

}

void parse(){

	Ttable* globalSTable;
	globalSTable = create_table();	

	insert_table_symbol("test", &globalSTable);
	insert_table_symbol("string", &globalSTable);


	destroy_table(&globalSTable);
}