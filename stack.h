/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "defs.h"

#ifndef _STACK_H_
#define _STACK_H_




#define MAX_STACK 20
extern int STACK_SIZE; 
/* 
 * Hodnota MAX_STACK udává skutečnou velikost statického pole pro uložení
 * hodnot zásobníku. Při implementaci operací nad ADT zásobník však
 * předpokládejte, že velikost tohoto pole je pouze STACK_SIZE. Umožní to
 * jednoduše měnit velikost zásobníku v průběhu testování. Při implementaci
 * tedy hodnotu MAX_STACK vůbec nepoužívejte. 
 */

extern int solved;                      /* Indikuje, zda byla operace řešena. */
extern int err_flag;                   /* Indikuje, zda operace volala chybu. */

                                        /* Chybové kódy pro funkci stackError */
#define MAX_SERR    3                                   /* počet možných chyb */
#define SERR_INIT   1                                  /* chyba při stackInit */
#define SERR_PUSH   2                                  /* chyba při stackPush */
#define SERR_TOP    3                                   /* chyba při stackTop */

                             /* ADT zásobník implementovaný ve statickém poli */
typedef struct {
    int capacity;
	void** data;                             /* pole pro uložení hodnot */
	int top;                                /* index prvku na vrcholu zásobníku */
} TStack;

                                  /* Hlavičky funkcí pro práci se zásobníkem. */
void stackError ( int error_code );
TStack* stackInit ();
int stackEmpty ( const TStack* s );
void* stackTop ( const TStack* s);
void stackPop ( TStack* s );
void stackPush ( TStack* s, void*);

#endif
