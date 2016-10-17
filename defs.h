#ifndef Ttypes
#define Ttypes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#define debug() printf("debug \n");


typedef char * string;
typedef struct table Ttable;
typedef struct node Tnode;
typedef struct new_func TFunction;
typedef struct new_var TVariable;


struct new_func {
	char *name;
	int type;
	int somestuff;
	char * someotherstuff;
};

struct new_var {
	char *name;
	int type;
	union{
		int i;
		double d;
		char *c;
	}value;
	
};

struct node {
	char *name;
	int type;
	union{
		TFunction f;
		TVariable v;
	}data;
	struct node *Lchild;
	struct node *Rchild;
};

struct table {
	struct node *root;
};
#endif
