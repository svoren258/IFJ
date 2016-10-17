/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ14        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "defs.h"

/*creates new symbols table implemented by a binary tree*/
Ttable *create_table();

/*frees all the memory allocated for the tree and all its nodes*/
void destroy_table();

/*Find string(str) in a binary tree with root(root). If found save to (pos) else save parrent(par) to which new node should be added*/
void find_table_symbol(char *str, Tnode *root, Tnode **pos, Tnode **par);

/*Insert string into table(binary tree)*/
void insert_table_symbol(TFunction *f, TVariable *v, Ttable **table);

/*Destroys all nodes within a table*/
void destroy_tree(Tnode *root);

/*Destroys the symbol table*/
void destroy_table(Ttable **table);