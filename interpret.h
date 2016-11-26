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
#include "parser.h"

int interpret();
enum{
    INS_ADD,    // "+"0
    INS_SUB,    // "-"1
    INS_MUL,    // "*"2
    INS_DIV,    // "/"3
      
    INS_CMP_LESS,//<4
    INS_CMP_LEQUAL,//<=5
    INS_CMP_GREATER,//>6
    INS_CMP_GREQUAL,//>=7
    
    INS_CMP_EQUAL,//==8
    INS_CMP_NOTEQUAL,//!=9
    INS_JCMP,    //jump if true10
    INS_JNCMP,     //jump if false11
    INS_JMP,    //jump12
    INS_CMP,    //if the var tested has value 1 it's true13
    INS_ASSIGN, // "=" assign value to the variable14
    INS_LABEL,//15
    INS_RET,//16
    INS_PUSH_VAR,//17
    INS_CALL,//18
    INS_PUSH_TABLE,//19
};

#endif