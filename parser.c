#include "parser.h"

tTablePtr globTable;
Ttoken *token;
TStack *gStack;

// void keywords_init()
// {
// 	int i = 0;
// 	while(keywords[i])
// 	{	
		
// 		 token->data = keywords[i];
// 		 TVariable *v = new_variable(token);
// 		 v->type = TYPE_KEYWORD;
		
// 		 store_variable(v, &globTable);
// 		 i++;
// 	}

// }

void parser_init()
{
	
	gStack = stackInit();
	
	BSTInit(&globTable);
	
	BSTInsert(&globTable, &globTable, "GlobTable");
	
	/*keywords to globtable*/
	// keywords_init();
	
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

	TStack *stack = stackInit();
	
	f->stack = stack;
	/*assign the table to the function*/
	f->defined = FALSE;
	f->type = RET_INT;
	f->table = loc_table;
	f->name = token->data;
	return f;
}

TVariable *new_variable(Ttoken *token)
{	
	TVariable *v;
	v = malloc(sizeof(TVariable));
	
	v->inicialized = FALSE;
	v->name = token->data;
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
	
	if( BSTSearch(*table, v->name) )
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
	
	token = getToken();
	
	TVariable *var;
	var = new_variable(token);
	
	expression(token,var);
	parser_finish();

}