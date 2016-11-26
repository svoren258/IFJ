/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
/*Syntactic analysis*/
#ifndef ParserDefs
#define ParserDefs

#include "defs.h"
#include "ial.h"
#include "lex.h"
#include "expression.h"


//#include "interpret.h"
// #include "list.h"


//#include "error.h"
//#include "list.h"
//#include "stack.h"

TClass *get_class_from_table(tTablePtr Table, char *name);
TFunction *get_func_from_table(tTablePtr Table, char* name);
TVariable *get_var_from_table(tTablePtr Table, char* name);

TFunction *new_function(char *tokenName, tTablePtr table);
TVariable *new_variable(Ttoken *token, tTablePtr table);
void store_function(/*stack*/TFunction *f, tTablePtr table);
void store_variable(/*stack*/TVariable *v, tTablePtr table);
tTablePtr create_class_table(char *name, tTablePtr destTable);
void starter();
void Declaration(tTablePtr table, Ttoken *token);
TVariable *variableDecl(tTablePtr table, Ttoken *tokenID, char *type);
TFunction *funcDef(tTablePtr table, Ttoken *tokenID, char *funcType);
void params(tTablePtr fTable, Ttoken *token, int numOfParam);
void ifelse_statement(tTablePtr table);
void block_body(Ttoken *token);
void while_statement(tTablePtr table);
void return_statement(tTablePtr table);

/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/



void parse();
#endif