#ifndef TTokens
#define TTokens
enum tokens {
	TOKEN_IF = 0,
	TOKEN_ELSE,

};

typedef struct token{
	char* name;
	int type;
}Ttoken;


void lex_init();
Ttoken *get_token();
#endif