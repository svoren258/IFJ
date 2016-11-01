#include "list.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
	//init the linked list to default config
	L->First = NULL;
	L->Act = NULL;
	L->Last = NULL;
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
    
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDisposeList (tDLList *L) {

	//while there is a first item, keep deleting it
	while(L->First)
	{
		//create a helper variable to free the space
		tDLElemPtr delete;
		delete = L->First;
		//set first item of the list based on the pointer from the item that is to be deleted
		L->First = delete->rptr;

		free(delete);

	}
	//after list is emptied, set it to the default config
	L->First = NULL;
	L->Last = NULL;
	L->Act = NULL;

/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertFirst (tDLList *L, int val) {
	//create space for a new item
	struct tDLElem * first;
	first = malloc(sizeof(struct tDLElem));
	//if unsuccessful malloc, exit the function
	if(!first)
	{
		DLError();
		return;
	}
	//assign data to the item
	first->data = val;
	first->lptr = NULL;
	first->rptr = NULL;
	//if there are more than 0 items in the list, lets link them with the new one, otherwise set First and Last pointer to the new one
	if(L->First)
	{
		first->rptr = L->First;
		L->First->lptr = first;
		L->First = first;
	} else {
		L->First = first;
		L->Last = first;
	}
	
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertLast(tDLList *L, int val) {
	//create space for the new item
	struct tDLElem * last;
	last = malloc(sizeof(struct tDLElem));
	//if malloc was not successful exit function
	if(!last)
	{
		DLError();
		return;
	}
	//assign data to the new item
	last->data = val;
	last->rptr = NULL;
	last->lptr = NULL;
	//if the list has some items, link them with the new one, otherwise set first and last pointers of the list to the new item
	if(L->Last)
	{
		last->lptr = L->Last;
		L->Last->rptr = last;
		L->Last = last;
	} else {
		L->First = last;
		L->Last = last;
	}
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLFirst (tDLList *L) {
	//set activity to the first item of the list
	L->Act = L->First;
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLLast (tDLList *L) {
	//set activity to the last item of the list
	L->Act = L->Last;
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyFirst (tDLList *L, int *val) {
	//exit function if the list does not exist
	if(!L)
	{
		DLError();
		return;
	}
	//save data from the first item to the val variable
	*val = L->First->data;
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyLast (tDLList *L, int *val) {
	//exit function if the list does not exist
	if(!L)
	{
		DLError();
		return;
	}
	//save data from the last item to the val variable
	*val = L->Last->data;
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDeleteFirst (tDLList *L) {
	//exit function if the list does not exist
	if(!L)
		return;
	//set activity to null, if the item that is to be deleted is active
	if(L->Act == L->First)
		L->Act = NULL;

	//create helper variable to free the space
	tDLElemPtr first;
	first = L->First;
	
	//if there is an item after the current one, set pointer of the first item of the list to the next one
	if(first->rptr)
	{
		L->First = first->rptr;
		L->First->lptr = NULL;
	}
	//if there is an item after the next item, lets link it to the first item
	if(first->rptr->rptr)
		L->First->rptr = first->rptr->rptr;


	//free the space
	free(first);

/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}	

void DLDeleteLast (tDLList *L) {
	//exit if the list does not exist
	if(!L)
		return;

	//set activity to null if the item to be deleted is active
	if(L->Act == L->Last)
		L->Act = NULL;

	//create a helper variable
	tDLElemPtr last;
	last = L->Last;
	
	//if there is an item before the one to be deleted, set the pointer of the last item of the list to it.
	if(last->lptr)
	{
		L->Last = last->lptr;
		L->Last->rptr = NULL;
	}
	//if there is an item before the previous one, set the pointer of the last one to it.
	if(last->lptr->lptr)
	{
		L->Last->lptr = last->lptr->lptr;
	}
	
	//free the space
	free(last);

/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostDelete (tDLList *L) {
	//exit if the list has no active item, or if the active is the last item in the list
	if(!L->Act || L->Act == L->Last)
		return;
	
	//create a helper variable to free the space
	tDLElemPtr next;
	next = L->Act->rptr;

	//if there is an item after the one to be deleted, set the right pointer of the current one to it, else make it null
	if(next->rptr)
	{
		L->Act->rptr = next->rptr;
		next->rptr->lptr = L->Act;
	} else {
		L->Act->rptr = NULL;
		L->Last = L->Act;
	}

	//free the space
	free(next);
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
	
		
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreDelete (tDLList *L) {
	//exit if the list has no active item or the active item is the first in the list
	if(!L->Act || L->Act == L->First)
		return;

	//create a helper variable
	tDLElemPtr prev;
	prev = L->Act->lptr;

	//if there is an item before the previous one, lets link the current one to it, else make it null
	if(prev->lptr)
	{
		L->Act->lptr = prev->lptr;
		prev->lptr->rptr = L->Act;
	} else {
		L->Act->lptr = NULL;
		L->First = L->Act;
	}
	
	//free the space
	free(prev);

/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	
			
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostInsert (tDLList *L, int val) {
	//exit if the list has no active item
	if(!L->Act)
		return;

	//create a new item
	tDLElemPtr new;
	new = (tDLElemPtr)malloc(sizeof(tDLElemPtr));

	//if the malloc was unsuccessful exit the function
	if(!new)
	{
		DLError();
		return;
	}

	//if the active item has a next item, lets link the new one with it, else set the right poitner to null
	if(L->Act->rptr)
		new->rptr = L->Act->rptr;
	else
		new->rptr = NULL;

	//the new item will be linked with the active one
	new->lptr = L->Act;
	L->Act->rptr = new;
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreInsert (tDLList *L, int val) {
	//exit if the list has no active item
	if(!L->Act)
		return;

	//create a new item
	tDLElemPtr new;
	new = (tDLElemPtr)malloc(sizeof(tDLElemPtr));

	//exit if the malloc was unsuccessful
	if(!new)
	{
		DLError();
		return;
	}

	//if the active item has a previous item lets link it with the new one
	if(L->Act->lptr)
		new->lptr = L->Act->lptr;
	else
		new->lptr = NULL;

	//link the new item with the active item
	new->rptr = L->Act;
	L->Act->lptr = new;
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopy (tDLList *L, int *val) {
	//exit if the list has no active item
	if(!L->Act)
	{
		DLError();
		return;
	}

	//save data of the active item to the val variable
	*val = L->Act->data;
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
		
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLActualize (tDLList *L, int val) {
	//exit if the list has no active item
	if(!L->Act)
		return;

	//set data to the active item
	L->Act->data = val;
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLSucc (tDLList *L) {
	//exit if the list has no active item
	if(!L->Act)
		return;

	//set activity to the next item if there is some
	if(L->Act->rptr)
		L->Act = L->Act->rptr;
	//otherwise delete activity of the list
	else
		L->Act = NULL;
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}


void DLPred (tDLList *L) {
	//exit if the list has no active item
	if(!L->Act)
		return;

	//set activity to the previous item if there is some
	if(L->Act->lptr)
		L->Act = L->Act->lptr;
	//otherwise activity of the list is deleted
	else
		L->Act = NULL;
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int DLActive (tDLList *L) {

/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
	//if the list has an active item, returns true
	return (L->Act) ? 1 : 0;
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}