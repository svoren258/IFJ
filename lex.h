#include "defs.h"

#ifndef LexDefs
#define LexDefs
enum tokens {
	TOKEN_IF = 0,
	TOKEN_ELSE,

};

extern char *keywords[];


typedef struct token{
	char* name;
	int type;
}Ttoken;



typedef enum
{
PLUS,
MINUS,
MUL,
DIV,
MOD,
EQUATE,
EQUALS,
GREATER,
LESSER,
GR_EQ,
LE_EQ,
EXPL,
N_EQ,
DOT,
SEM_CL,
COLON,
QUOTE,
OR_A,
OR_B,
AND_A,
AND_B,
LB,
PB,
LSB,
PSB,
LDB,
PDB,
N_DEC,
N_DEC_E,
DEC,
DEC_E,
COM,
B_COM,
}tState;

void lex_finish();
void lex_init();
Ttoken *get_token();
#endif
