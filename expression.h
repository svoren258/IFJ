/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "defs.h"
#include "lex.h"


#include "stack.h"

#ifndef EXPRESSION_H
#define EXPRESSION_H

extern char  predence_table[12][12];

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
void expression(Ttoken *token, TVariable *var);

#endif