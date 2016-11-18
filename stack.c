/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/


#include "stack.h"


int solved;

void stackError ( int error_code ){
/*   ----------
** Vytiskne upozornění, že došlo k chybě při práci se zásobníkem.
**
** TUTO FUNKCI, PROSÍME, NEUPRAVUJTE!
*/
	static const char* SERR_STRINGS[MAX_SERR+1] = {"Unknown error","Stack error: INIT","Stack error: PUSH","Stack error: TOP"};
	if ( error_code <= 0 || error_code > MAX_SERR )
		error_code = 0;
	printf ( "%s\n", SERR_STRINGS[error_code] );
	//err_flag = 1;
}

TStack* stackInit () {
	//if stack does not exist, exit function
	TStack * s;
	s =  malloc(sizeof(TStack*));
	
	
	if(!s)
	{
		stackError(SERR_INIT);
		return NULL;
	}
	//set the stack top to starting position
	s->capacity = 10;
	s->data = malloc(sizeof(void*) * s->capacity);
	s->top = -1;
	return s;

}

int stackEmpty ( const TStack* s ) {

	//returns true if the stack is empty
	return ( s->top == -1) ? TRUE : FALSE;

}



void *stackTop ( const TStack* s) {
	//if stack is empty, exit function
	if(stackEmpty(s))
	{
		stackError(SERR_TOP);
		return NULL;
	}
	//return data from the top of the stack
	return s->data[s->top];
}


void stackPop ( TStack* s ) {
	//if the stack exists, delete element from the top of it
	if(!stackEmpty(s))
	{
		s->data[s->top] = '\0';
		s->top--;
	}

}


void stackPush ( TStack* s, void *data ) {
	//if stack is full, exit function

	
	s->top++;
	if(s->top > s->capacity)
	{
		s->data = realloc(s->data, sizeof(void *) * s->capacity * 2);
		s->capacity = s->capacity * 2;
	}

	s->data[s->top] = data;
	
}
