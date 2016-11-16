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
Ttoken *token;
FILE *file;


int main(int argc, char **argv)
{
// 	if(argc != 2) return EXIT_FAILURE;
	
// 	file = fopen(argv[1], "r");
	
	
// 	if(!file)
// 	{ 
// 		fprintf(stderr, "nejde otevrit soubor %s\n",argv[1]);
// 		return EXIT_FAILURE; 
// 	}
	
token = malloc(sizeof(Ttoken));

// 	get_token(&token);
// 	while (token.type != END ){
		
// 		printf("%s\n",printToken());
// 		get_token(&token);
//	}
//lex_init();

parse();

//lex_finish();
	return 0;
}