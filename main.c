/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
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
Ttoken *token;
FILE *file;
TBuffer * buffer;


int main(int argc, char **argv)
{
	if(argc != 2) return EXIT_FAILURE;
	
	file = fopen(argv[1], "r");

	if(!file)
	{ 
		fprintf(stderr, "nejde otevrit soubor %s\n",argv[1]);
		return EXIT_FAILURE; 
	}
	
	token = getToken();
	while(token->type != TOKEN_EOF)
	{
		printf("%s %d\n ",token->data, token->type);
		token = getToken();
	}
	
// parse();
lexFinish();
	return 0;
}