#include "lex.h"


Ttoken *token;

char *keywords[] ={"boolean","break","class","continue","do","double","else","false","for","if","int","return",
	"String","static","true","void","while"};


void lex_init(){
	token = malloc(sizeof(Ttoken));



}

Ttoken *get_token(){
	token->name = "if";
	token->type = TOKEN_IF;	
	return token;
}
