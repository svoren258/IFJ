#include "ial.h"


Ttable * create_table()
{
	Ttable * new_table;
	new_table = malloc(sizeof(Ttable));
	if(new_table == NULL)
		return false;
	return new_table;
}

void find_table_symbol(char *str, Tnode *root, Tnode **pos, Tnode **par)
{
	Tnode *end;

	//nothing in the table so far, no root
	if(root == NULL)
	{
		*par = NULL;
		return;
	}
	
	//the strings mathch
	if( !strcmp(str,root->name) )
	{
		*pos = root;
	}

	//check nodes and find place for the new symbol
	*par = root;
	
	if( strcmp(root->name,str) < 0)
	{
		end = root->childR;
	}
	else
	{
		end = root->childL;
	}

	//binary search
	while(end != NULL)
	{
		//if the strings math
		if( !strcmp(end->name,str) )
		{
			*pos = end;
			return;
		}
		
		//save the node to which new string will be append
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
	*pos = NULL;
}


void insert_table_symbol(char *str, Ttable **table)
{

	Tnode  *par, *pos, *new;
	
	new = malloc(sizeof(Tnode));
	new->name = str;
	new->childR = NULL;
	new->childL = NULL;

	find_table_symbol(str, (*table)->root, &pos, &par);
	if(par == NULL)
	{
		(*table)->root = new;
		return;
	}

	if(pos != NULL)
	{
		fprintf(stderr, "Such string already in the tree!\n");
		return;
	}

	if( strcmp(par->name,new->name) < 0)
	{
		par->childR = new;
		return;
	}
	else 
	{
		par->childL = new;
	}
}

/*destroy table and all its nodes*/
void destroy_table(Ttable **table)
{

}

