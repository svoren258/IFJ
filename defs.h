#ifndef Ttypes
#define Ttypes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include "ial.h" 

#define db() printf("debug \n");
#define TRUE 1

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
	int somestuff;
	char * someotherstuff;
	tTablePtr table;
};

struct new_var 
{
	char *name;
	int type;
	union{
		int i;
		double d;
		char *c;
	}value;
	
};

// struct node 
// {
// 	char *name;
// 	int type;
// 	union{
// 		TFunction *f;
// 		TVariable v;
// 	}data;
// 	struct node *Lchild;
// 	struct node *Rchild;
// };

// struct table 
// {
// 	struct node *root;
// };
#endif
