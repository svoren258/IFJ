/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "defs.h"
#include "lex.h"
#include "parser.h"
// #include "stack.h"

// #include "ial.h"

#define TABLESIZE 17
extern char  predence_table[TABLESIZE][TABLESIZE];

typedef struct{
    int data[1000];
    int top;
}TIStack;


void expression(TVariable *var);
TVariable *generateVar();
int isFunctionCall();
int isFunctionFullNameCall();
int isFullNameVar();



enum{
   
    
    OP_PLUS,//0
    OP_MINUS,//1
    OP_MUL,//2
    OP_DIV,//3

    OP_LESS,//4
    OP_LEQUAL,//5
    OP_GREATER,//6
    OP_GREQUAL,//7
    
    OP_EQUAL,//8
    OP_NOTEQUAL,//9
    
    OP_LROUND,//10
    OP_RROUND,//11
    OP_FUNC,//12
    OP_I,//13
    OP_COMA,//14
    OP_DOLAR,//15
    
    OP_NONTERM,//16
    R_LESS,
    SIGN_LESS,//17
    SIGN_GREATER,//18
    SIGN_EQUALS,//19
    SIGN_FAIL,//20
};


#endif