#include "parser.h"

tTablePtr globTable;
Ttoken *token;

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
	
	
	BSTInit(&globTable);
	BSTInsert(&globTable, "GlobTable");

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

	/*create local symbol table*/
	struct tTable *table;
	table = malloc(sizeof(struct 	tTable));

	/*assign the table to the function*/
	f->type = RET_INT;
	f->table = table;
	f->name = token->name;
	return f;
}

TVariable *new_variable(Ttoken *token)
{	
	TVariable *v;
	v = malloc(sizeof(TVariable));
	
	v->name = token->name;
	return v;

}
void store_function(/*stack*/TFunction *f, tTablePtr *table)
{
	//BSTInsert(globTable,f);
}
void store_variable(/*stack*/TVariable *v, tTablePtr *table)
{

	tTablePtr new_var;
	BSTInit(&new_var);
	
	
	BSTInsert(table, v->name);
	new_var->data.v = v;

}


/*--------------------automat-----------------------*/




/*--------------------/automat-----------------------*/

void parse()
{
	parser_init();

	parser_finish();

}