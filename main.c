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
<<<<<<< HEAD
Ttoken *token;
=======
        Ttoken *token;
>>>>>>> b25c97f85c5efe64daa722381154a3ea06a735a2
FILE *file;
TBuffer * buffer;


int main(int argc, char **argv)
{
<<<<<<< HEAD
	if(argc != 2) return EXIT_FAILURE;
	
	file = fopen(argv[1], "r");

	if(!file)
	{ 
		fprintf(stderr, "nejde otevrit soubor %s\n",argv[1]);
		return EXIT_FAILURE; 
	}
	
	// token = getToken();
	// while(token->type != TOKEN_EOF)
	// {
	// 	printf("%s \t <%d>\n",token->data, token->type);
	// 	token = getToken();
	// }
	
parse();
lexFinish();
	return 0;
}
=======
    if(argc != 2) return EXIT_FAILURE;

    file = fopen(argv[1], "r");

    if(!file)
    {
        fprintf(stderr, "nejde otevrit soubor %s\n",argv[1]);
        return EXIT_FAILURE;
    }

    // token = getToken();
    // while(token->type != TOKEN_EOF)
    // {
    // 	printf("%s\n",token->data);
    // 	token = getToken();
    // }
    parse();

    lexFinish();
    return 0;
}
>>>>>>> b25c97f85c5efe64daa722381154a3ea06a735a2
