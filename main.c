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
	
	
	Ttable * keywords_table;
	keywords_table = malloc(sizeof(Ttable));
	keywords_table->name = "Keywords";
	
	insert("abc",&keywords_table);
	insert("def",&keywords_table);
	insert("ghj",&keywords_table);
	// printf("%s\n",keywords_table->root->name);
	 // printf("%s\n",keywords_table->root->childR->name);
	printf("%s\n",keywords_table->root->childR->childR->name);

	return 1;
}
