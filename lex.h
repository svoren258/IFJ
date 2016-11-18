/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "defs.h"
#include "error.h"
#include "stack.h"

#ifndef LexDefs
#define LexDefs

extern char *keywords[];

typedef struct{
	char* data;
	int used;
	int capacity;
}TBuffer;

//struktura pro token
typedef struct{
	char* data;
	int type;
}Ttoken;

Ttoken *getTokenFromStack();
Ttoken *getToken();
TBuffer *extendBuffer(TBuffer*, char);
int isKeyword(TBuffer*);
void lexFinish();
void ungetToken(Ttoken*);


//char *printToken();
//stavy automatu


typedef enum
{
KEYWORD_BOOLEAN,		//0
KEYWORD_BREAK,			//1
KEYWORD_CLASS,			//2
KEYWORD_CONTINUE,			//3
KEYWORD_DO,			//4
KEYWORD_DOUBLE,			//5
KEYWORD_ELSE,			//6
KEYWORD_FALSE,			//7
KEYWORD_FOR,			//8
KEYWORD_IF,			//9
KEYWORD_INT,//10
KEYWORD_RETURN,			//11
KEYWORD_STRING,			//12
KEYWORD_STATIC,			//13
KEYWORD_TRUE,			//14
KEYWORD_VOID,			//15
KEYWORD_WHILE,			//16
STATE_INIT,			//17
STATE_END,			//18 koncový stav
STATE_PLUS,			//19
STATE_MINUS,	//20
STATE_MUL,			//21
STATE_DIV,			//22
STATE_INC,//23
STATE_DEC,//24
STATE_ASSIGN,			//25
STATE_EQUALS,		//26
STATE_GREATER,		//27
STATE_LESSER,			//28
STATE_GR_EQ,			//29
STATE_LE_EQ,		//30
STATE_EXCL_MARK,		//31
STATE_NOT_EQ,			//32
STATE_DOT,			//33
STATE_SEM_CL,			//34
STATE_COLON,			//35
STATE_QUOTE,			//36
STATE_OR,			//37
STATE_LOGIC_OR,			//38
STATE_AND,			//39
STATE_LOGIC_AND,	//40
STATE_L_ROUND,		//41
STATE_R_ROUND,		//42
STATE_L_SQUARE,		//43
STATE_R_SQUARE,		//44
STATE_L_CURLY,		//45
STATE_R_CURLY,		//46
STATE_DEC_E,		//47
STATE_LINE_COM,		//48
STATE_BEGIN_COM,		//49
STATE_END_COM,		//50
STATE_ID,			//51
STATE_STRING_DOUBLE,			//52
STATE_INT,			//53
STATE_FUT_DOUBLE,		//54
STATE_DOUBLE,		//55
STATE_COMMA,		//56
TOKEN_PLUS,				//57 +
TOKEN_MINUS,			//58 -
TOKEN_MUL,				//59 *
TOKEN_DIV,				//60 /
TOKEN_INC,//61
TOKEN_DEC,//62
TOKEN_MOD,	 			//63 %
TOKEN_ASSIGN,			//64 =
TOKEN_EQUALS,			//65 ==
TOKEN_GREATER,			//66 >
TOKEN_LESSER,			//67 <
TOKEN_GR_EQ,			//68 >=
TOKEN_LE_EQ,			//69 <=
TOKEN_EXCL_MARK,		//70 !
TOKEN_NOT_EQ,			//71 !=
TOKEN_DOT,				//72 .
TOKEN_SEM_CL,			//73 ;
TOKEN_COLON,			//74 :
TOKEN_QUOTE,			//75 "
TOKEN_OR,				//76 |
TOKEN_LOGIC_OR,			//77 ||
TOKEN_AND,				//78 &
TOKEN_LOGIC_AND,		//79 &&
TOKEN_L_ROUND,			//80 (
TOKEN_R_ROUND,			//81 )
TOKEN_L_SQUARE,			//82 [
TOKEN_R_SQUARE,			//83 ]
TOKEN_L_CURLY,			//84 {
TOKEN_R_CURLY,			//85 }
TOKEN_E,				//86 [0-9e0-9]
TOKEN_DOUBLE_E,			//87 [0-9.0-9e0-9]
TOKEN_LINE_COM,			//88 //
TOKEN_BEGIN_COM,		//89 /*
TOKEN_END_COM,			//90 */
TOKEN_ID,				//91 [a-Z0-9]
TOKEN_STRING,			//92 string
TOKEN_INT,				//93 integer

TOKEN_DOUBLE,			//94 double
TOKEN_COMMA,			//95 ,
TOKEN_EOF,				//96
STATE_STRING_SINGLE,	//97
STATE_E,				//98
TOKEN_DEC_E,
STATE_ASCII_DOUBLE,
STATE_ASCII_SINGLE,
TOKEN_TYPE,
}tState;




//prototyp funkce
int get_token(Ttoken *token);
#endif
