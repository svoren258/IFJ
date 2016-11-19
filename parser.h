
/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
/*Syntactic analysis*/
#include "ial.h"
#include "lex.h"
#include "defs.h"
#include "error.h"
#include "expression.h"

#ifndef ParserDefs
#define ParserDefs

TFunction *new_function(Ttoken *token);
TVariable *new_variable(Ttoken *token);
void store_function(/*stack*/TFunction *f, tTablePtr *table);
void store_variable(/*stack*/TVariable *v, tTablePtr *table);
tTablePtr create_class_table(char*);
void starter();
void Declaration(tTablePtr table, Ttoken *token);
TVariable *variableDecl(tTablePtr table, Ttoken *tokenID, char *type);
TFunction *funcDef(tTablePtr table, Ttoken *tokenID, char *funcType);
void params(TFunction *f, Ttoken *token, int numOfParam);

/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/



void parse();
#endif