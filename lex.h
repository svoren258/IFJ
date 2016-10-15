enum tokens {
	TOKEN_IF = 0,
	TOKEN_ELSE,

};

typedef struct token{
	char* data;
	int type;
}Ttoken;


void lex_init();
Ttoken *get_token();