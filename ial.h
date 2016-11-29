/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#ifndef ial_h
#define ial_h
//#include "defs.h"
#include "builtin.h"


#define TRUE 1
#define FALSE 0

enum{
	NODE_TYPE_CLASS,
	NODE_TYPE_FUNCTION,
	NODE_TYPE_VARIABLE,
};


typedef struct tTable *tTablePtr;
struct tTable {
	char *name;
	int type;
    int defined;

	union
	{
		struct new_func *f;
		struct new_var *v;
		struct new_class *c;
	}data;			                                                      /* klíč */
	struct tTable * LPtr;                                    /* levý podstrom */
	struct tTable * RPtr;
	struct tTable * Root;
	/* pravý podstrom */
};

/* prototypy funkcí */
char* sort(TVariable* s);
int find(TVariable* s,TVariable* search);
void BSTCopy (tTablePtr Root);
void BSTInit   (tTablePtr *);
tTablePtr BSTSearch (tTablePtr RootPtr, char*);//
void BSTInsert (tTablePtr *, tTablePtr *, char* key);//(Table, new node, name of the node)
void BSTDelete (tTablePtr *, char* key);
void BSTDispose(tTablePtr *);
void BSTRootNode(tTablePtr *RootPtr, tTablePtr *new, char *K);
void merge(char* s, char* left, int l_length, char* right, int r_length);
void sorting(char* s, int length);
TStack * copyStack(TStack*);

#endif
