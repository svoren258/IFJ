/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#ifndef INTERPRET_H
#define INTERPRET_H


#include "defs.h"
#include "list.h"


int interpret(TList *list);
enum{
    INS_ADD,    // "+"
    INS_SUB,    // "-"
    INS_MUL,    // "*"
    INS_DIV,    // "/"
      
    INS_CMP_LESS,//<
    INS_CMP_LEQUAL,//<=
    INS_CMP_GREATER,//>
    INS_CMP_GREQUAL,//>=
    
    INS_CMP_EQUAL,//==
    INS_CMP_NOTEQUAL,//!=
    INS_JCMP,    //jump if true
    INS_JNCMP,     //jump if false
    INS_JMP,    //jump
    INS_CMP,    //if the var tested has value 1 it's true
    INS_ASSIGN, // "=" assign value to the variable
    INS_LABEL,
    INS_RET,
    INS_PUSH_VAR,
};

#endif