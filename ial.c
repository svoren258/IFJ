/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "ial.h"

// tTablePtr BSTPrepare (tTablePtr new_node){
	
// 	new_node = malloc(sizeof(struct tTable));
// 	if(new_node)
// 		return new_node;
// }

void BSTInit (tTablePtr *RootPtr) {

	(*RootPtr) = NULL;	
}	



tTablePtr BSTSearch (tTablePtr RootPtr, char *node)	{
	printf("som v BSTSearch\n");

	if( (RootPtr == NULL) || (node == NULL)  )
		return NULL;

	if( !strcmp(node, RootPtr->name) )
	{
		return RootPtr;
	}

	if( strcmp(node, RootPtr->name) < 0)
		if(BSTSearch(RootPtr->LPtr, node))
			return BSTSearch(RootPtr->LPtr, node);

	if( strcmp(node, RootPtr->name) > 0)
		if(BSTSearch(RootPtr->RPtr, node))
			return BSTSearch(RootPtr->RPtr, node);

	return NULL;
} 

void BSTRootNode(tTablePtr *RootPtr, tTablePtr *new, char *K){

	BSTInit(new);

	if( !(*new) )
	{
		(*new) = malloc(sizeof(struct tTable));
		(*new)->name = K;
		(*new)->LPtr = NULL;
		(*new)->RPtr = NULL;
		(*RootPtr)->Root = (*new);

		return;
	}


}




void BSTInsert (tTablePtr* RootPtr, tTablePtr* new, char *K)	{
	
	
	//printf("INSERT INTO %s\n",K);


	if( !(*RootPtr) )
	{
		(*new) = malloc(sizeof(struct tTable));
		(*new)->name = K;
		(*new)->LPtr = NULL;
		(*new)->RPtr = NULL;
		(*RootPtr) = (*new);

		return;
	}

	
	
	if( !strcmp(K, (*RootPtr)->name) )
	{
		printf("%s already exists\n",K);
		return;
	}

	if( strcmp(K, (*RootPtr)->name) < 0 )
		BSTInsert(&(*RootPtr)->LPtr, &(*new), K);
	
	if( strcmp(K, (*RootPtr)->name) > 0 )
		BSTInsert(&(*RootPtr)->RPtr, &(*new), K);
	
}

void ReplaceByRightmost (tTablePtr PtrReplaced, tTablePtr *RootPtr) {

	if( !(*RootPtr) )
		return;
	
	if((*RootPtr)->RPtr)
	{
		ReplaceByRightmost( PtrReplaced, &(*RootPtr)->RPtr);
	}
	else 
	{
	
		PtrReplaced->name = (*RootPtr)->name;
		PtrReplaced->data = (*RootPtr)->data;
		tTablePtr del = (*RootPtr);
		(*RootPtr) = (*RootPtr)->LPtr;
		
		free(del);

	}


	
}

void BSTDelete (tTablePtr *RootPtr, char* K) 		{


	if(! (*RootPtr) )
		return;

	if( strcmp(K, (*RootPtr)->name) < 0 )
	{
		BSTDelete(&(*RootPtr)->LPtr, K);
	}

	if( strcmp(K, (*RootPtr)->name) > 0 )
	{
		BSTDelete(&(*RootPtr)->RPtr, K);
	}

	if( !strcmp(K, (*RootPtr)->name) )
	{
		
		tTablePtr del = *RootPtr;

		if( (*RootPtr)->LPtr && (*RootPtr)->RPtr )
		{
			ReplaceByRightmost( (*RootPtr), &(*RootPtr)->LPtr );
		}
		else if( (*RootPtr)->LPtr )
		{
			(*RootPtr) = (*RootPtr)->LPtr;
		}
		else if( (*RootPtr)->RPtr )
		{
			(*RootPtr) = (*RootPtr)->RPtr;

		}
		if( !(*RootPtr)->LPtr && !(*RootPtr)->RPtr)  
		{
			(*RootPtr) = (*RootPtr)->LPtr;
			free(del);
		}
	}



} 

void BSTDispose (tTablePtr *RootPtr) {	

		if(*RootPtr)
		{
			
			
			BSTDispose(&(*RootPtr)->RPtr);
			BSTDispose(&(*RootPtr)->LPtr);

			if((*RootPtr)->data.v)
			{
				TVariable *freeVar;
				freeVar = (*RootPtr)->data.v;
				free(freeVar);
			}
	
			if((*RootPtr))
			{
				//printf("Delete %s\n",(*RootPtr)->name);
				free(*RootPtr);
				(*RootPtr) = NULL;	
			}
			

			
		}
}