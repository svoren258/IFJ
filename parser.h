/*Syntactic analysis*/
#include "ial.h"
#include "lex.h"
#include "defs.h"

#ifndef ParserDefs
#define ParserDefs

TFunction *new_function(Ttoken *token);
TVariable *new_variable(Ttoken *token);
void store_function(/*stack*/TFunction *f);
void store_variable(/*stack*/TVariable *v);


/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/



void parse();
#endif