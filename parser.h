
/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
/*Syntactic analysis*/
#include "defs.h"
#include "ial.h"
#include "lex.h"

#include "error.h"
#include "expression.h"

#ifndef ParserDefs
#define ParserDefs

TFunction *new_function(Ttoken *token);
TVariable *new_variable(Ttoken *token);
void store_function(/*stack*/TFunction *f, tTablePtr *table);
void store_variable(/*stack*/TVariable *v, tTablePtr *table);
tTablePtr create_class_table(char*);

/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/



void parse();
#endif