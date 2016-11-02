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

#define TRUE 1
#define FALSE 0
typedef char * string;
typedef struct table Ttable;
typedef struct node Tnode;
typedef struct new_func TFunction;
typedef struct new_var TVariable;

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

struct new_func
{
	char *params;
	char *name;
	int type;
	int defined;
	tStack *stack;
	
	tTablePtr table;
};

struct new_var 
{
	char *name;
	int type;
	int inicialized;
	union{
		int i;
		double d;
		char *c;
	}value;
	
};


#endif
