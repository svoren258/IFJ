/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#ifndef PROJEKT_IFJ_BUILTIN_H
#define PROJEKT_IFJ_BUILTIN_H

#include "defs.h"

char* readString();
int readInt();
double readDouble();
void print(TVariable* var);
int length(char* s);
char* substr(char* s,int i,int n);
int compare(char* s1,char* s2);
void sorting(char* s, int length);
void merge(char*s,char*left,int l_length,char*right,int r_length);

#endif //PROJEKT_IFJ_BUILTIN_H


