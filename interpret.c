/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "interpret.h"

TList *globalInitList;

int interpret()
{
    int i = 0;
    TListItem ins;
    ins = globalInitList->First;
    
    
    
    while(ins)
    { 
        printf("interpret %d\n",ins->operation);
        i++;
        printf("%d\n",i);
        ins = ins->next;
    }
    printf("\n\n***INTERPRET BEGINING***\n\n");    
    return 1;
}