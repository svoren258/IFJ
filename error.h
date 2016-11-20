/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#ifndef PROJEKT_IFJ_ERROR_H
#define PROJEKT_IFJ_ERROR_H
#include "defs.h"
#include "lex.h"
void ret_error(int error);

enum error_values{
    LEX_ERROR = 1,
    SYNTAX_ERROR = 2,
    SEMANTIC_DEF_ERROR = 3,
    SEMANTIC_TYPE_ERROR = 4,
    //FILE_ERROR = 5,
    SEMANTIC_OTHER_ERROR = 6,
    INPUT_READ_ERROR = 7,
    UNINIT_VAR_ERROR = 8,
    ZERO_DIV_ERROR = 9,
    OTHER_RUNTIME_ERROR = 10,
    INTERNAL_ERROR = 99
};

#endif //PROJEKT_IFJ_ERROR_H
