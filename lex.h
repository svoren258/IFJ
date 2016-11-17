#include "defs.h"
#include "error.h"

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

Ttoken *getToken();
TBuffer *extendBuffer(TBuffer*, char);
int isKeyword(TBuffer*);


//char *printToken();
//stavy automatu


typedef enum
{
KEYWORD_BOOLEAN,//0
KEYWORD_BREAK,
KEYWORD_CLASS,
KEYWORD_CONTINUE,
KEYWORD_DO,
KEYWORD_DOUBLE,
KEYWORD_ELSE,
KEYWORD_FALSE,
KEYWORD_FOR,
KEYWORD_IF,
KEYWORD_INT,//10
KEYWORD_RETURN,
KEYWORD_STRING,
KEYWORD_STATIC,
KEYWORD_TRUE,
KEYWORD_VOID,
KEYWORD_WHILE,
STATE_INIT,			//1 počáteční stav
STATE_END,			//2 koncový stav
STATE_PLUS,			//3
STATE_MINUS,	//20
STATE_MUL,			//5
STATE_DIV,			//6
STATE_INC,//7
STATE_DEC,//8
STATE_ASSIGN,			//9
STATE_EQUALS,		
STATE_GREATER,		//7
STATE_LESSER,			//8
STATE_GR_EQ,			//9
STATE_LE_EQ,		//30
STATE_EXCL_MARK,		//11
STATE_NOT_EQ,			//12
STATE_DOT,			//13
STATE_SEM_CL,			//14
STATE_COLON,			//15
STATE_QUOTE,			
STATE_OR,			//17
STATE_LOGIC_OR,			//18
STATE_AND,			//19
STATE_LOGIC_AND,	//40
STATE_L_ROUND,		//21
STATE_R_ROUND,		//22
STATE_L_SQUARE,		//23
STATE_R_SQUARE,		//24
STATE_L_CURLY,		//25
STATE_R_CURLY,		
STATE_DEC_E,		//27
STATE_LINE_COM,		//28
STATE_BEGIN_COM,		//29
STATE_END_COM,		//50
STATE_ID,			//31
STATE_STRING,			//32
STATE_INT,			//33
STATE_FUT_DOUBLE,		//34
STATE_DOUBLE,		//35
STATE_COMMA,		//40
TOKEN_PLUS,				//37 +
TOKEN_MINUS,			//38 -
TOKEN_MUL,				//39 *
TOKEN_DIV,				//60 /
TOKEN_INC,
TOKEN_DEC,
TOKEN_MOD,				//41 %
TOKEN_ASSIGN,			//42 =
TOKEN_EQUALS,			//43 ==
TOKEN_GREATER,			//50 >
TOKEN_LESSER,			//45 <
TOKEN_GR_EQ,			//46 >=
TOKEN_LE_EQ,			//47 <=
TOKEN_EXCL_MARK,		//48 !
TOKEN_NOT_EQ,			//49 !=
TOKEN_DOT,				//50 .
TOKEN_SEM_CL,			//51 ;
TOKEN_COLON,			//52 :
TOKEN_QUOTE,			//53 "
TOKEN_OR,				//60 |
TOKEN_LOGIC_OR,			//55 ||
TOKEN_AND,				//56 &
TOKEN_LOGIC_AND,		//57 &&
TOKEN_L_ROUND,			//58 (
TOKEN_R_ROUND,			//59 )
TOKEN_L_SQUARE,			//60 [
TOKEN_R_SQUARE,			//61 ]
TOKEN_L_CURLY,			//62 {
TOKEN_R_CURLY,			//63 }
TOKEN_E,				//70 [0-9e0-9]
TOKEN_DEC_E,			//65 [0-9.0-9e0-9]
TOKEN_LINE_COM,			//66 //
TOKEN_BEGIN_COM,		//67 /*
TOKEN_END_COM,			//68 */
TOKEN_ID,				//75 [a-Z0-9]
TOKEN_STRING,			//70 string
TOKEN_INT,				//71 integer

TOKEN_DOUBLE,			//72 double
TOKEN_COMMA,			//73 ,
TOKEN_EOF,
}tState;




//prototyp funkce
int get_token(Ttoken *token);
#endif
