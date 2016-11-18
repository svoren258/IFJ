/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#ifndef Ttypes
#define Ttypes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include "ial.h" 
#include "stack.h"
#include "error.h"

#define dbl printf("Left debug\n")
#define dbr printf("Right debug\n")
#define line printf("***LINE: %d***\n",__LINE__)
#define TRUE 1
#define FALSE 0
#define MAX_PARAMS_COUNT 100

typedef char * string;
typedef struct table Ttable;
typedef struct node Tnode;


typedef enum
{
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_KEYWORD,
	TYPE_VOID
}Ttype;

enum
{
	RET_INT,
	RET_FLOAT,
	RET_STRING
};

typedef struct new_func TFunction;
struct new_func
{
	char params[MAX_PARAMS_COUNT];
	char *className;
	char *name;
	int type;
	int defined;
	int declared;
	TStack *stack;
	
	tTablePtr table;
};

typedef struct new_var TVariable;
struct new_var 
{
	char *className;
	char *name;
	int type;
	int defined;
	int declared;
	union{
		int i;
		double d;
		char *c;
	}value;
	
};


#endif
