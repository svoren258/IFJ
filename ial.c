/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#include "ial.h"
//#include "builtin.h"
//#include "defs.h"
// tTablePtr BSTPrepare (tTablePtr new_node){
	
// 	new_node = malloc(sizeof(struct tTable));
// 	if(new_node)
// 		return new_node;
// }

int find(TVariable* s, TVariable* search){
    char* str = s->value.s;
    char* search_str = search->value.s;

    int size_s = length(str);
    int size_search = length(search_str);
    if(size_search == 0)
        return 0;
    bool match = FALSE;
    int* prefix_t = malloc((size_search+1)* sizeof(int));

    prefix_t[0] = -1;
    for (int k = 0; k < size_search; ++k) {
        prefix_t[k+1] = prefix_t[k] + 1;
        while((prefix_t[k+1] > 0) && (search_str[k] != search_str[prefix_t[k+1]-1])) {
            prefix_t[k+1] = prefix_t[prefix_t[k+1]-1]+1;
        }
    }

    for (int i = 0; i < size_s; ++i) {
        for (int j = 0; j < size_search; ++j) {
            if(str[i+j] == search_str[j])
                match = TRUE;
            else{
                match = FALSE;
                break;
            }
        }
        if(match == TRUE) {
            free(prefix_t);
            return i;
        }
    }
    free(prefix_t);
    return -1;
}

char* sort(TVariable* s){
    char* str = s->value.s;

    int lngth = length(str);
    sorting(str, lngth);

    return str;
}

void sorting(char* s, int length){

    if(length <= 1)
        return;


    int mid = length/2;
    char* left = (char*) malloc(mid);
    for (int i = 0; i < mid; ++i) {
        left[i] = s[i];
    }

    char* right = (char*) malloc(length-mid);
    for (int j = mid; j < length; ++j) {
        right[j-mid] = s[j];
    }

    sorting(left, mid);
    sorting(right, length-mid);
    merge(s, left, mid, right, length-mid);
    free(left);
    free(right);

}
void merge(char* s, char* left, int l_length, char* right, int r_length){
    int i = 0;
    int j = 0;

    while((i < l_length) && (j < r_length)){
        if(left[i] < right[j]){
            s[i+j] = left[i];
            i++;
        }
        else{
            s[i+j] = right[j];
            j++;
        }
    }
    if (i < l_length){
        while (i < l_length) {
            s[i + j] = left[i];
            i++;
        }
    }
    else {
        while (j < r_length) {
            s[i + j] = right[j];
            j++;
        }
    }
}

void BSTInit (tTablePtr *RootPtr) {

	(*RootPtr) = NULL;	
}	



tTablePtr BSTSearch (tTablePtr RootPtr, char *node)	{
	//printf("som v BSTSearch\n");

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
		printf("%s already exists %s %d\n",K, __FILE__, __LINE__);
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
void BSTCopy (tTablePtr Root)//copy from Root to dest all nodes
{
	if(Root)
	printf("%s\n",Root->name);
	
	BSTCopy(Root->RPtr);
	BSTCopy(Root->LPtr);
	
	if(Root)
	{
		line;
	printf("copy; %s positiion:%d\n",Root->name,Root->data.v->position);
		// BSTInsert(dest,Root, (*Root)->name);
	}
	
}

void BSTDispose (tTablePtr *RootPtr) {	
		if(*RootPtr)
		{
			// if((*RootPtr)->Root)
			// 	BSTDispose(&(*RootPtr));
			
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
				// printf("Delete %s\n",(*RootPtr)->name);
				free(*RootPtr);
				(*RootPtr) = NULL;	
			}
			

			
		}
}
