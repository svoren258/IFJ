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
// #include "stack.h"
#include "error.h"
// #include "ial.h"


extern char  predence_table[12][12];


void expression(TVariable *var);
TVariable *generateVar();
int isFunctionCall();
int isFunctionFullNameCall();

enum{
    OP_PLUS,
    OP_MINUS,
    OP_MUL,
    OP_DIVISION,
    
    OP_LESSER,
    OP_LEQUAL,
    OP_GREATER,
    OP_GREQUAL,
    
    OP_EQUAL,
    OP_NOTEQUAL,
    
    OP_LBRACKET,
    OP_RBRACKET,
};


#endif