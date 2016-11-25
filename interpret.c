/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "interpret.h"

TList *globalInitList;
void translate_listitem(TListItem ins)
{
    switch(ins->operation)
        {
            case INS_ADD:
            printf("INS_ADD ");
            break;
            
            case INS_SUB:
            printf("INS_SUB ");
            break;
            
            case INS_MUL:
            printf("INS_MUL ");
            break;
            
            case INS_DIV:
            printf("INS_DIV ");
            break;
            
            case INS_CMP_LESS:
            printf("INS_CMP_LESS ");
            break;
            
            case INS_CMP_LEQUAL:
            printf("INS_CMP_LEQUAL ");
            break;
            
            case INS_CMP_GREATER:
            printf("INS_CMP_GREATER ");
            break;
            
            case INS_CMP_GREQUAL:
            printf("INS_CMP_GREQUAL ");
            break;
            
            case INS_CMP_EQUAL:
            printf("INS_CMP_EQUAL ");
            break;
            
            case INS_CMP_NOTEQUAL:
            printf("INS_CMP_NOTEQUAL ");
            break;
            
            case INS_JCMP:
            printf("INS_JCMP ");
            break;
            
            case INS_JNCMP:
            printf("INS_JNCMP ");
            break;
            
            case INS_JMP:
            printf("INS_JMP ");
            break;
            
            case INS_CMP:
            printf("INS_CMP ");
            break;
            
            case INS_ASSIGN:
            printf("INS_ASSIGN ");
            break;
            
            case INS_LABEL:
            printf("INS_LABEL ");
            break;
            
            case INS_RET:
            printf("INS_RET ");
            break;
            
            case INS_PUSH_VAR:
            printf("INS_PUSH_VAR ");
            break;
            
            case INS_CALL:
            printf("INS_CALL ");
            break;
            
            case INS_PUSH_TABLE:
            printf("INS_PUSH_TABLE ");
            break;
            
            default:
            printf("other\n");
            break;
        }
}


int interpret()
{
    TListItem ins;
    ins = globalInitList->First;
    
    
    printf("\n\n***INTERPRET BEGINING***\n\n");  
    while(ins)
    {
        switch(ins->operation)
        {
            case INS_JMP:
            {
                ins = ins->add3;
            }
        }
        translate_listitem(ins);
        printf(" %d\n",ins->operation);
        ins = ins->next;
    }
      
    return 1;
}