#include "ial.h"

// tTablePtr BSTPrepare (tTablePtr new_node){
	
// 	new_node = malloc(sizeof(struct tTable));
// 	if(new_node)
// 		return new_node;
// }

void BSTInit (tTablePtr *RootPtr) {

	(*RootPtr) = NULL;	
}	



int BSTExists (tTablePtr RootPtr, tTablePtr node)	{

	if( !RootPtr || !node  )
		return FALSE;

	if( !strcmp(node->name, RootPtr->name) )
	{
		return TRUE;
	}

	if( strcmp(node->name, RootPtr->name) < 0)
		if(BSTExists(RootPtr->LPtr, node))
			return TRUE;

	if( strcmp(node->name, RootPtr->name) > 0)
		if(BSTExists(RootPtr->RPtr, node))
			return TRUE;

	return FALSE;
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
			
			printf("TOBE DELETED %s\n",(*RootPtr)->name);
			BSTDispose(&(*RootPtr)->RPtr);
			BSTDispose(&(*RootPtr)->LPtr);

			if((*RootPtr)->data.v)
			{
				TVariable *freeVar;
				freeVar = (*RootPtr)->data.v;
				free(freeVar);
			}
	
			//printf("%s deleted\n",(*RootPtr)->name);
			free(*RootPtr);
			(*RootPtr) = NULL;

			
		}
}