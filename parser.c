#include "ial.h"

void parse(){

Ttable *keywords;
	keywords = create_table();	

	string words[5];
	words[0] = "IF";
	words[1] = "THEN";
	words[2] = "ELSE";
	words[3] = "VOID";
	words[4] = "MAIN";

	for(int i=0; i<5; i++)	
	insert_table_symbol(words[i],&keywords);
	



	destroy_table(&keywords);
}