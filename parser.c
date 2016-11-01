#include "parser.h"

tTablePtr globTable;
Ttoken *token;
tStack *gStack;

void keywords_init()
{
	int i = 0;
	while(keywords[i])
	{	
		
		 token->name = keywords[i];
		 TVariable *v = new_variable(token);
		 v->type = TYPE_KEYWORD;
		
		 store_variable(v, &globTable);
		 i++;
	}

}

void parser_init()
{
	
	gStack = stackInit();
	
	BSTInit(&globTable);
	BSTInsert(&globTable, &globTable, "GlobTable");

	/*keywords to globtable*/
	keywords_init();
	
}

void parser_finish()
{
	BSTDispose(&globTable);
	
}

TFunction *new_function(Ttoken *token)
{	/*allocate the space for a new function*/
	TFunction *f;
	f = malloc(sizeof(TFunction));

	tTablePtr loc_table;
	BSTInit(&loc_table);

	tStack *stack = stackInit();
	
	f->stack = stack;
	/*assign the table to the function*/
	f->defined = FALSE;
	f->type = RET_INT;
	f->table = loc_table;
	f->name = token->name;
	return f;
}

TVariable *new_variable(Ttoken *token)
{	
	TVariable *v;
	v = malloc(sizeof(TVariable));
	
	v->inicialized = FALSE;
	v->name = token->name;
	return v;

}
void store_function(/*stack*/TFunction *f, tTablePtr *table)
{
	tTablePtr new_func;
	BSTInit(&new_func);

	BSTInsert(table, &new_func, f->name);
	stackPush(gStack, f);
}
void store_variable(/*stack*/TVariable *v, tTablePtr *table)
{
	
	if( BSTExists(*table, v->name) )
	{
		ret_error(SYNTAX_ERROR);
	}
		
	tTablePtr new_var;
	BSTInit(&new_var);

	BSTInsert(table, &new_var, v->name);
	new_var->data.v = v;
	
	
}


/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/

void parse()
{
	parser_init();


	parser_finish();

}