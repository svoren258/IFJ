/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ14        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include "ial.h"



int main(){
	
	Ttable *keywords;
	keywords = create_table();	

	Ttable *functions;
	functions = create_table();
	insert_table_symbol("abc",&keywords);
	insert_table_symbol("def",&keywords);
	insert_table_symbol("ghj",&keywords);
	 // printf("%s\n",table->root->childR->name);

	free(keywords->root->childR->childR);
	free(keywords->root->childR);
	free(keywords->root);
	free(keywords);
	free(functions);
	//printf("%s\n",keywords->root->childR->childR->name);

	return 1;
}
