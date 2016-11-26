/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "interpret.h"

TList *globalInitList;
tTablePtr globTable;
TListItem ins;
TVariable *var1,*var2,*result;

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

void math()
{
                var1 = ins->add1;
                var2 = ins->add2;
                result = ins->add3;
                int op = ins->operation;
                ins = ins->next;
                if((var1 == NULL) || (var2 == NULL) || (result == NULL))                
                    ret_error(SEMANTIC_DEF_ERROR);
                if(var1->type == VARTYPE_BOOLEAN || var2->type == VARTYPE_BOOLEAN)
                    ret_error(SEMANTIC_TYPE_ERROR);
                if(var1->type == VARTYPE_STRING || var2->type == VARTYPE_STRING)
                { 
                    printf("STRING CONCATENATION\n");
                }
                result->defined = 1;
                
                switch(op)
                {
                case INS_ADD:
                    if(var1->type == VARTYPE_DOUBLE || var2->type == VARTYPE_DOUBLE)
                    {
                        result->type = VARTYPE_DOUBLE;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.d + var2->value.d;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.d = var1->value.d + var2->value.i;
                        if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.i + var2->value.d;
                        printf("\tADD RESULT:%g\t\n",result->value.d);
                        break;
                    }
                    else if(var1->type == VARTYPE_INTEGER && var2->type == VARTYPE_INTEGER)
                    {   
                        result->type = VARTYPE_INTEGER;
                        result->value.i = var1->value.i + var2->value.i;
                        printf("\tADD RESULT:%d\t\n",result->value.i);
                        break;
                    }
                    else
                    {
                        line;
                        ret_error(SEMANTIC_DEF_ERROR);
                    }
                    break;
                case INS_SUB:
                    if(var1->type == VARTYPE_DOUBLE || var2->type == VARTYPE_DOUBLE)
                    {
                        result->type = VARTYPE_DOUBLE;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.d - var2->value.d;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.d = var1->value.d - var2->value.i;
                        if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.i - var2->value.d;
                        printf("\tSUB RESULT:%g\t\n",result->value.d);
                        break;
                    }
                    else if(var1->type == VARTYPE_INTEGER && var2->type == VARTYPE_INTEGER)
                    {   
                        result->type = VARTYPE_INTEGER;
                        result->value.i = var1->value.i - var2->value.i;
                        printf("\tSUB RESULT:%d\t\n",result->value.i);
                        break;
                    }
                    else
                    {
                        line;
                        ret_error(SEMANTIC_DEF_ERROR);
                    }
                    break;
                case INS_MUL:
                    if(var1->type == VARTYPE_DOUBLE || var2->type == VARTYPE_DOUBLE)
                    {
                        result->type = VARTYPE_DOUBLE;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.d * var2->value.d;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.d = var1->value.d * var2->value.i;
                        if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.i * var2->value.d;
                        printf("\tMUL RESULT:%g\t\n",result->value.d);
                        break;
                    }
                    else if(var1->type == VARTYPE_INTEGER && var2->type == VARTYPE_INTEGER)
                    {   
                        result->type = VARTYPE_INTEGER;
                        result->value.i = var1->value.i * var2->value.i;
                        printf("\tMUL RESULT:%d\t\n",result->value.i);
                        break;
                    }
                    else
                    {
                        line;
                        ret_error(SEMANTIC_DEF_ERROR);
                    }
                    break;
                case INS_DIV:
                    if(var1->type == VARTYPE_DOUBLE || var2->type == VARTYPE_DOUBLE)
                    {
                        result->type = VARTYPE_DOUBLE;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.d / var2->value.d;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.d = var1->value.d / var2->value.i;
                        if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.i / var2->value.d;
                        printf("\tDIV RESULT:%g\t\n",result->value.d);
                        break;
                    }
                    else if(var1->type == VARTYPE_INTEGER && var2->type == VARTYPE_INTEGER)
                    {   
                        result->type = VARTYPE_INTEGER;
                        result->value.i = var1->value.i / var2->value.i;
                        printf("\tDIV RESULT:%d\t\n",result->value.i);
                        break;
                    }
                    else
                    {
                        line;
                        ret_error(SEMANTIC_DEF_ERROR);
                    }

                case INS_CMP_LESS:
                    if((var1->type == VARTYPE_INTEGER|| var1->type == VARTYPE_DOUBLE) &&(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE))
                    {
                        result->type = VARTYPE_BOOLEAN;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.d < var2->value.d;
                        else if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.d < var2->value.i;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.i < var2->value.d;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_INTEGER)
                            {result->value.b = var1->value.i < var2->value.i;line;printf("%d %d\n",var1->value.i , var2->value.i);}
                        printf("\tCOMPARE:%d\t\n",result->value.b);
                        break;
                    }
                case INS_CMP_LEQUAL:
                case INS_CMP_GREATER:
                case INS_CMP_GREQUAL:
                case INS_CMP_EQUAL:
                case INS_CMP_NOTEQUAL:
                    default:printf("DEFAULT\n");
                    break;
                }
}

int interpret()
{
    
    ins = globalInitList->First;
    // tTablePtr ifj = BSTSearch(globTable, "ifj");
    // TFunction *func = get_func_from_table(ifj->Root,"find");
    
    TFunction * func;
    // tTablePtr pclass = BSTSearch(globTable, "Game");
    
    // tTablePtr pfunc = BSTSearch(pclass->Root, "play");
    // printf("%s\n",pfunc->name);
    
    
    
    // ins = func->list->First;
    printf("\n\n***INTERPRET BEGINING***\n\n");  
    while(ins)
    {
        translate_listitem(ins);
        printf(" %d\n",ins->operation);
        switch(ins->operation)
        {
            case INS_ADD:
            case INS_SUB:
            case INS_MUL:
            case INS_DIV:
            case INS_CMP:
            case INS_CMP_LESS:
            case INS_CMP_LEQUAL:
            case INS_CMP_GREATER:
            case INS_CMP_GREQUAL:
            case INS_CMP_EQUAL:
            case INS_CMP_NOTEQUAL:
            {
                math();
                continue;
            }
            
            case INS_ASSIGN:
                ins = ins->next;
                if(var1->type == VARTYPE_INTEGER)
                {
                    if(var2->type == VARTYPE_STRING || var2->type == VARTYPE_BOOLEAN)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);    
                    }
                    
                    var1->value.i = var2->value.i ? var2->value.i : var2->value.d;
                    continue;
                }
                else if(var1->type == VARTYPE_DOUBLE)
                {
                    if(var2->type == VARTYPE_STRING || var2->type == VARTYPE_BOOLEAN)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);    
                    }
                    var1->value.d = var2->value.i ? var2->value.i : var2->value.d;
                    continue;
                }
                else if(var1->type == VARTYPE_STRING)
                {
                    if(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE || var2->type == VARTYPE_BOOLEAN)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);    
                    }
                    var1->value.s = var2->value.s;
                    continue;
                }printf("assigned\n");
            
            case INS_JMP:
            {
                ins = ins->add3;
                continue;
            }
            
            case INS_JCMP:
            {
                printf("JCMP\n");
                ins = ins->add3;
                continue;
            }
            
            case INS_CALL:
            {
                func = ins->add1;
                if(!strcmp(func->className, "ifj16"))
                {
                    ins = ins->next;
                    printf("ifj16 func: %s\n",func->name);
                    continue;
                }
                
                // ins = func->list->First->next->next;
                // printf("%d\n",ins->operation);
                printf("FUNC CALL: %s\n",func->name);
                printf("CLASS: %s\n",func->className);
                //printf("%d\n",ins->next->next->operation);
                ins = func->list->First;
               
                continue;
            }
            
        }
        
        
        ins = ins->next;
    }
      
    return 1;
}