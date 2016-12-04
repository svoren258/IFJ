/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#ifndef defs_h
#define defs_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

//#include "ial.h"
#include "list.h"
#include "stack.h"
#include "error.h"

#include "lex.h"

 //#define DEBUG

#ifdef DEBUG
#define dbl printf("Left debug\n")
#define dbr printf("Right debug\n")
#define line printf("***FILE: %s  LINE: %d***\n",__FILE__, __LINE__)
#define tok printf("%s\n",token->data)
#define pint(toprint) printf("CONTROL %d\n",toprint)
#define s(toprint) printf("%s ",toprint)
#define p(toprint) printf("%s \n",toprint)
#define ks printf("KDE SOM?!?!\n")
#endif



#ifndef DEBUG
#define pint(toprint) ;
#define line ;
#define tok ;
#define s(toprint) ;
#endif

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

typedef struct new_class TClass;
struct new_class
{
	int numOfVars;
	int defined;
	TStack *stack;
};



typedef struct new_func TFunction;
struct new_func
{
	int params[MAX_PARAMS_COUNT];
	char *className;
	char *name;
	int defined;
    int declared;
	int numOfParams;
	int numOfVars;
	TStack *stack;
	TList *list;
	//struct tTable *table;
};

enum{
    FUNCTYPE_NULL,
    FUNCTYPE_INT,
    FUNCTYPE_DOUBLE,
    FUNCTYPE_STRING,
    FUNCTYPE_BOOLEAN,
    FUNCTYPE_VOID,
};

enum{
	VARTYPE_NULL,
	VARTYPE_INTEGER,
	VARTYPE_DOUBLE,
	VARTYPE_STRING,
	VARTYPE_BOOLEAN,
};

typedef struct new_var TVariable;
struct new_var 
{
	char *className;
	char *name;
	int type;
	int position;
	int constant;
	int defined;
	int declared;
	union{
		int i;
		double d;
		char *s;
		int b;
	}value;
};




#endif
