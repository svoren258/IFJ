/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "list.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

// TListItem insertInstruction(TList* list, int operation, void* ad1, void* ad2, void* ad3)
// {
// 	TElem * ins;
// 	ins = PostInsert( list, operation, ad1, ad2, ad3);
// 	return ins;
// }

TList * InitList () {

	TList * list;
	list = malloc(sizeof(TList));

	//initialize the empty list
	list->First = NULL;
	list->Act = NULL;
	return list;
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DisposeList (TList *L) {
	//exit if the list is empty
	if(!L->First)
		return;

	//keep deleting the first until the list is empty
	while(L->First)
		DeleteFirst(L);
	
	//set the list to the default config
	L->Act = NULL;
	L->First = NULL;
	/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/
	

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void InsertFirst (TList *L, int operation, void* ad1, void *ad2, void *ad3) {
	
	//create a pointer
	struct TElem * first;
	
	//alloc space for the data
	if((first = malloc(sizeof(struct TElem))) == NULL)
	{//allocation unsuccessful
		Error();
		return;
	}

	
	//set the data
	first->operation = operation;
	first->add1 = ad1;
	first->add2 = ad2;
	first->add3 = ad3;
	first->next = L->First;

	L->First = first;
	
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
    

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void First (TList *L) {
	//set activity to the first item
	L->Act = L->First;
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

// void CopyFirst (TList *L, int *val) {
// 	//if the list has no active nor first item, EXIT
// 	if(!L->First && !L->Act)
// 	{
// 		Error();
// 		return;
// 	}
// 	//assign data to the val variable
// 	*val = L->First->data;
// /*
// ** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
// ** Pokud je seznam L prázdný, volá funkci Error().
// **/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
// }

void DeleteFirst (TList *L) {
	//create a helper variable that will be used to free the space
	TListItem ptr = L->First;
	if(ptr)
	{
		//if first item of a list exists, let's delete it and change activity, based on its current state
		L->First = ptr->next;
		L->Act == ptr ? L->Act = NULL : (L->Act = L->Act);
		free(ptr);
		ptr = L->First;
	}
	if(ptr)
	{
		//if the next item in the list exists, make it the first one.
		L->First = ptr;
	}
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
	

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}	

// void PostDelete (TList *L) {
// 	//if no active item exists, or the item after the current one does not exists, EXIT
// 	if(!L->Act || !L->Act->next)
// 		return;
// 	//create helper variable to free space
// 	TListItem del;
// 	del = L->Act->next;

// 	//redirect pointer of the current active item to the next one
// 	L->Act->next = L->Act->next->next;
// 	free(del);
// /* 
// ** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
// ** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
// ** nic se neděje.
// **/

	
	
//  // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
// }

void insert_instruction(TList *L, TListItem new)
{
	if(!L->Act)
		return;
		
	// new->operation = op;
	// new->add1 = add1;
	// new->add2 = add2;
	// new->add3 = add3;
	new->next = L->Act->next;
	L->Act->next = new;
}


TListItem create_instruction(int op, void * add1, void * add2, void * add3)
{
		
	struct TElem *new = NULL;
	if((new = malloc(sizeof(struct TElem))) == NULL)
	{
		//unsuccessful malloc, exit function
		Error();
		ret_error(INTERNAL_ERROR);
		return NULL;
	}
	
	new->operation = op;
	new->add1 = add1;
	new->add2 = add2;
	new->add3 = add3;

	return new;
}
TListItem PostInsert (TList *L, int op, void *add1, void *add2, void *add3) {
	//if no active item exists EXIT
	

	//create a helper variable to free the space
	struct TElem *new = NULL;
	if((new = malloc(sizeof(struct TElem))) == NULL)
	{
		//unsuccessful malloc, exit function
		Error();
		ret_error(INTERNAL_ERROR);
		return NULL;
	}
	//malloc successful, assign data
	new->operation = op;
	new->add1 = add1;
	new->add2 = add2;
	new->add3 = add3;
	new->next = L->Act->next;
	L->Act->next = new;
	return new;

/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Copy (TList *L, int *val) {
	//if no active item, exit function
	if(!L->Act)
	{
		Error();
		return;
	}

	//copy data from active item to the val variable
	*val = L->Act->data;
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Actualize (TList *L, int val) {
	//set data to the active item, if no active item, exit function!
	if(!L->Act)
		return;
	L->Act->data = val;
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Succ (TList *L) {
	//if active item exists, set activity to the next one(if it exists)
	if(!L->Act)
		return;
	TListItem act;
	act = L->Act;
	L->Act = act->next;
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int Active (TList *L) {		
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
	//acivity test of an item
return L->Act ? TRUE : FALSE;
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}
