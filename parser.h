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
void keywords_init();

/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/



void parse();
#endif