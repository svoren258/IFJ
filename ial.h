/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#ifndef ial_h
#define ial_h
#include "defs.h"


#define TRUE 1
#define FALSE 0

enum{
	NODE_TYPE_CLASS,
	NODE_TYPE_FUNCTION,
	NODE_TYPE_VARIABLE,
};
typedef struct tTable *tTablePtr;
struct tTable {
	int type;
	char *name;
	char *type;
	union
	{
		struct new_func *f;
		struct new_var *v;
	}data;			                                                      /* klíč */
	struct tTable * LPtr;                                    /* levý podstrom */
	struct tTable * RPtr;                                   /* pravý podstrom */
};

/* prototypy funkcí */

void BSTInit   (tTablePtr *);
tTablePtr BSTSearch (tTablePtr RootPtr, char *node);
void BSTInsert (tTablePtr *, tTablePtr *, char* key);
void BSTDelete (tTablePtr *, char* key);
void BSTDispose(tTablePtr *);

#endif