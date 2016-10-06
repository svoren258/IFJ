#include "ial.h"




void find(char *str, Tnode *root, Tnode *pos, Tnode **par){
	Tnode *end;

	//nothing in the table so far, no root
	if(root == NULL)
	{
		printf("No root\n");
		*par = NULL;
		return;
	}
	
	//the new symbol is identic with the only one existing
	if( !strcmp(str,root->name) )
	{
		printf("Found!! %s\n", root->name);
		*pos = *root;
	}

	//check nodes and find place for the new symbol
	*par = root;
	//printf("%s\n",*par->name);
	if( strcmp(root->name,str) < 0)
	{
		end = root->childR;
	}
	else
	{
		end = root->childL;
	}

	while(end != NULL)
	{

		if( !strcmp(end->name,str) )
		{
			*par = end;
			return;
		}
		*par = end;
		if( strcmp(end->name,str) < 0)
		{
			*par = end;
			end = end->childR;
		}
		else
		{	
			*par = end;
			end = end->childL;
		}
	}
	pos = NULL;
}


void insert(char *str, Ttable **table){
	//printf("%s\n",(*table)->root->name);

	Tnode  *par, *pos, *new;
	
	new = malloc(sizeof(Tnode));
	new->name = str;
	new->childR = NULL;
	new->childL = NULL;

	find(str, (*table)->root, pos, &par);
	if(par == NULL)
	{
		(*table)->root = new;
		return;
	}

	if( strcmp(par->name,new->name) < 0)
	{
		printf("parrent: %s\n",par->name);
		par->childR = new;
		return;
	}
	else 
	{
		par->childL = new;
		printf("%s\n",new->name);
	}

}

