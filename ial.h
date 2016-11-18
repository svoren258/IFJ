/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "defs.h"

#define TRUE 1
#define FALSE 0


#ifndef ialh
#define ialh
typedef struct tTable {
	char *name;
	union
	{
		struct new_func *f;
		struct new_var *v;
	}data;			                                                      /* klíč */
	struct tTable * LPtr;                                    /* levý podstrom */
	struct tTable * RPtr;                                   /* pravý podstrom */
} *tTablePtr;

/* prototypy funkcí */

void BSTInit   (tTablePtr *);
tTablePtr BSTSearch (tTablePtr RootPtr, char*);
//int BSTExists (tTablePtr RootPtr, char* node);
void BSTInsert (tTablePtr *, tTablePtr *, char* key);
void BSTDelete (tTablePtr *, char* key);
void BSTDispose(tTablePtr *);

#endif