#include "lex.h"


Ttoken *token;

char *keywords[] ={"boolean","break","class","continue","do","double","else","false","for","if","int","return",
	"String","static","true","void","while"};


void lex_init(){
	token = malloc(sizeof(Ttoken));
}

void lex_finish()
{
	free(token);
	
}

Ttoken *get_token(){

	return token;
}
