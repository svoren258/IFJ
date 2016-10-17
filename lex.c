#include "lex.h"
#include "ial.h"

Ttoken *token;


char keywords[17][10]={"boolean","break","class","continue","do","double","else","false","for","if","int","return",
	"String","static","true","void","while"};

void lex_init(){
	token = malloc(sizeof(Ttoken));
}

Ttoken *get_token(){
	token->name = "if";
	token->type = TOKEN_IF;	
	return token;
}
int main(){


}
