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

void InitList (tList *L) {

	//initialize the empty list
	L->First = NULL;
	L->Act = NULL;
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DisposeList (tList *L) {
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

void InsertFirst (tList *L, int val) {
	
	//create a pointer
	struct tElem *first ;
	
	//alloc space for the data
	if((first = malloc(sizeof(struct tElem))) == NULL)
	{//allocation unsuccessful
		Error();
		return;
	}

	
	//set the data
	first->data = val;
	first->ptr = L->First;
	L->First = first;
	
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
    

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void First (tList *L) {
	//set activity to the first item
	L->Act = L->First;
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	

 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void CopyFirst (tList *L, int *val) {
	//if the list has no active nor first item, EXIT
	if(!L->First && !L->Act)
	{
		Error();
		return;
	}
	//assign data to the val variable
	*val = L->First->data;
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DeleteFirst (tList *L) {
	//create a helper variable that will be used to free the space
	tElemPtr ptr = L->First;
	if(ptr)
	{
		//if first item of a list exists, let's delete it and change activity, based on its current state
		L->First = ptr->ptr;
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

void PostDelete (tList *L) {
	//if no active item exists, or the item after the current one does not exists, EXIT
	if(!L->Act || !L->Act->ptr)
		return;
	//create helper variable to free space
	tElemPtr del;
	del = L->Act->ptr;

	//redirect pointer of the current active item to the next one
	L->Act->ptr = L->Act->ptr->ptr;
	free(del);
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void PostInsert (tList *L, int op, void *add1, void *add2, void *add3) {
	//if no active item exists EXIT
	if(!L->Act)
		return;

	//create a helper variable to free the space
	struct tElem *new = NULL;
	if((new = malloc(sizeof(struct tElem))) == NULL)
	{
		//unsuccessful malloc, exit function
		Error();
		return;
	}
	//malloc successful, assign data
	new->operation = op;
	new->add1 = add1;
	new->add2 = add2;
	new->add3 = add3;
	new->ptr = L->Act->ptr;
	L->Act->ptr = new;

/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Copy (tList *L, int *val) {
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

void Actualize (tList *L, int val) {
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

void Succ (tList *L) {
	//if active item exists, set activity to the next one(if it exists)
	if(!L->Act)
		return;
	tElemPtr act;
	act = L->Act;
	L->Act = act->ptr;
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
	
	
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int Active (tList *L) {		
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
	//acivity test of an item
return L->Act ? TRUE : FALSE;
 // solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}
