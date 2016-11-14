#include "defs.h"

#ifndef LexDefs
#define LexDefs

extern char *keywords[];


//stavy automatu
typedef enum
{
KEYWORDS,		// klíčová slova
INIT,			// počáteční stav
END,			// koncový stav
PLUS,			// +
MINUS,			// -
MUL,			// *
DIV,			// /
MOD,			// %
EQUATE,			// =
EQUALS,			// ==
GREATER,		// >
LESSER,			// <
GR_EQ,			// >=
LE_EQ,			// <=
EXPL,			// !
N_EQ,			// !=
DOT,			// .
SEM_CL,			// ;
COLON,			// :
QUOTE,			// "
OR_A,			// |
OR_B,			// ||
AND_A,			// &
AND_B,			// &&
LB,				// (
PB,				// )
LSB,			// [
PSB,			// ]
LDB,			// {
PDB,			// }
N_DEC,			// [0-9]
N_DEC_E,		// [0-9e0-9]
DEC,			// [0-9.0-9]
DEC_E,			// [0-9.0-9e0-9]
COM,			// //
B_COM_A,		// /*
B_COM_B,		// */
ID,				// [a-Z0-9]
STRNG,			// string
INTGR,			// integer
DBLE			// double
}tState;


//struktura pro token
typedef struct token{
	char* data;
	tState type;
}Ttoken;


//prototyp funkce
Ttoken *get_token();
#endif
