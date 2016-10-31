/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ14        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "defs.h"

#define TRUE 1
#define FALSE 0
#define dbl printf("Left debug\n")
#define dbr printf("Right debug\n")

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
int BSTSearch (tTablePtr RootPtr, tTablePtr node);
void BSTInsert (tTablePtr *, char*);
void BSTDelete (tTablePtr *, char*);
void BSTDispose(tTablePtr *);
//tTable BSTPrepare ();

#endif