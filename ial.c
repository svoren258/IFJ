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

    int size_s = strlen(str);
    int size_search = strlen(search_str);
    printf("size_s: %d\n", size_s);
    printf("size_search: %d\n", size_search);
    if(size_s < size_search)
        return -1;

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
    for (int l = 0; l < size_search; ++l) {
        printf("%d\n", prefix_t[l+1]);
    }

    int i = 0;
    int j = 0;
    while (i<size_s && j<size_search) {
        if (str[i] == search_str[j]) {
            match = TRUE;
            printf("if true\n");
            j++;
            i++;
        }
        else {
            if(j == 0)
                i++;
            match = FALSE;
            j = prefix_t[j + 1];
        }
    }

        if(match == TRUE) {
            free(prefix_t);
            return i-size_search;
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
		(*new)->Root = NULL;
		(*RootPtr)->Root = (*new);

		return;
	}


}




void BSTInsert (tTablePtr* RootPtr, tTablePtr* new, char *K)	{
	
	
	//printf("INSERT INTO %s\n",K);


	if( !(*RootPtr) )
	{
		(*new) = malloc(sizeof(struct tTable));
		(*new)->type = NODE_TYPE_NULL;
		(*new)->defined = 0;
		(*new)->name = K;
		(*new)->LPtr = NULL;
		(*new)->RPtr = NULL;
		(*new)->Root = NULL;
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


void BSTDispose (tTablePtr *RootPtr) {	
		if(*RootPtr)
		{
			
			BSTDispose(&(*RootPtr)->RPtr);
			BSTDispose(&(*RootPtr)->LPtr);

			if((*RootPtr)->Root)
			{
				BSTDispose(&(*RootPtr)->Root);
			}

			if((*RootPtr)->type == NODE_TYPE_VARIABLE)
			{
				free((*RootPtr)->data.v);
			}
		
			else if((*RootPtr)->type == NODE_TYPE_FUNCTION)
			{
				free((*RootPtr)->data.f);
			}
			
			else if((*RootPtr)->type == NODE_TYPE_CLASS)
			{
				free((*RootPtr)->data.c);
			}
		
			if((*RootPtr))
			{
				// printf("Delete %s\n",(*RootPtr)->name);
				free(*RootPtr);
				(*RootPtr) = NULL;	
			}
		}
}

void freeVar(TVariable *var)
{
}

void freeFunc(TFunction *func)
{
}

void freeClass(TClass *cls)
{
}

TStack* copyStack(TStack* oldStack)
{
	TStack * newStack = stackInit();
	
	for(int i = 0; i <= oldStack->top; i++)
	{
		TVariable *var = oldStack->data[i];
		TVariable *newVar = malloc(sizeof(TVariable));
		newVar->name = NULL;
		newVar->className = NULL;
		if(var->className)
		{
			newVar->className = malloc(sizeof(char)*100);
			newVar->className = strcpy(newVar->className, var->className);
		}
		if(var->name)
		{
			newVar->name =		malloc(sizeof(char)*100);
			newVar->name =		strcpy(newVar->name,var->name);
		}
		newVar->value = 	var->value;
		newVar->type =		var->type;
		newVar->position =	var->position;
		newVar->constant =	var->constant;
		newVar->defined =	var->defined;
		newVar->declared =	var->declared;

		stackPush(newStack, newVar);
	}
	// printf("oldstack\n");
	// for(int i = 0; i <= oldStack->top ; i++)
	// {
	// 	TVariable *var = oldStack->data[i];
	// 	printf("name:%s type:%d position:%d\n",var->name, var->type, var->position);
	// }
	// printf("newstack\n");
	// for(int i = 0; i <= newStack->top ; i++)
	// {
	// 	TVariable *var = newStack->data[i];
	// 	printf("name:%s type:%d position:%d\n",var->name, var->type, var->position);
	// }
	return newStack;
}
