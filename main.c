/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ14        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#include <stdio.h>
#include "ial.h"
#include "lex.h"
#include "parser.h"
#include "defs.h"

//#define FILE_ERROR 5

int main(int argc, char** argv){

//	FILE *f;
//	if (argc == 1)
//	{
//		printf("Missing input file\n");
//		return FILE_ERROR;
//	}
//	if ((f = fopen(argv[1], "r")) == NULL)
//	{
//		printf("Error while opening file\n");
//		return FILE_ERROR;
//	}

	lex_init();

	parse();

	lex_finish();
//	fclose(f);
	return 0;
}
