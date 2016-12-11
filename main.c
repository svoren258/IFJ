/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#include <stdio.h>
//#include "defs.h"
#include "ial.h"
#include "lex.h"
#include "parser.h"
#include "interpret.h"
#include <unistd.h>

Ttoken *token;
FILE *file;
TBuffer * buffer;
TStack* varStack;
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		//fprintf(stderr, "Wrong number of arguments! Use 1\n");
		ret_error(INTERNAL_ERROR);
	}
	
	file = fopen(argv[1], "r");
	
	if(!file)
	{ 
		//fprintf(stderr, "nejde otevrit soubor %s\n",argv[1]);
		ret_error(INTERNAL_ERROR);
	}

	lexStart();
    parse();
    // TVariable *var = NULL;
    // expression(var);
    // interpret();
    
    
    finish_expression();
    lexFinish();
	return 0;
}