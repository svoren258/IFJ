/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ14        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#define debug() printf("debug \n");

struct node {
	char *name;
	struct node *childL;
	struct node *childR;
};

struct table {
	struct node *root;
};

typedef struct table Ttable;
typedef struct node Tnode;

/*creates new symbols table implemented by a binary tree*/
Ttable *create_table();

/*Find string(str) in a binary tree with root(root). If found save to (pos) else save parrent(par) to which new node should be added*/
void find_table_symbol(char *str, Tnode *root, Tnode **pos, Tnode **par);

/*Insert string into table(binary tree)*/
void insert_table_symbol(char *str, Ttable **table);