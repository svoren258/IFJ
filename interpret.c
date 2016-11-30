/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "interpret.h"
//#include "defs.h"


TList *globalInitList;
tTablePtr globTable;
TListItem ins;
TVariable *var1,*var2,*result;
TStack *localStack, *globalStack;
TFunction *function;

TStack *functionNodesStack;
tTablePtr functionNode;
tTablePtr classNode;


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

TVariable *get_variable(char *name)
{
    
   
    // tTablePtr varNode;
    // tTablePtr classNode;
    // tTablePtr funcNode;
    TVariable *var;
    TStack *topStack = stackTop(localStack);
    functionNode = stackTop(functionNodesStack);
    // varNode = BSTSearch(functionTable->Root, name);
    #ifdef DEBUG
    printf("\n\nFIND var:%s",name);
    printf("\nFunction call: %s stacktop:%d\n",functionNode->name,functionNodesStack->top);
    for(int i = 0; i < topStack->top; i++){
        TVariable *var1 = topStack->data[i];
        printf("%d var:%s pos:%d\n",i, var1->name,var1->position);
    }
    #endif
    
    
   
    
    
    var = get_var_from_table(functionNode,name);//varNode->data.v;
    if(var)
    {
        // printf("%d\n",topStack->top);
        // printf("var %s found on %d position\n",var->name,var->position);
        var = topStack->data[var->position];
        // printf("%s %d\n",var->name,var->position);
    }
    
    
    
    // printf("%s\n",var->name);
    
    
    
    if(var != NULL)
    {
        // printf("FOUND VARIABLE %s def:%d type:%d\n",var->name, var->defined, var->type);
        return var;
    }
        
   
    topStack = stackTop(globalStack);
     
    var = get_var_from_table(classNode,name);//varNode->data.v;line;
    
    if(var != NULL)
    var = topStack->data[var->position];
    
    
    if(var != NULL)
        return var;
    
     if(!strcmp(name, "return"))
    {
        for(int i = 0; i <= topStack->top; i++)
        {
            var = topStack->data[i];
            if(!strcmp(var->name, "return"))
            {
                stackPop(topStack);
                return var;    
            }
            
        }
    }
    
    
    return NULL;
}

void math()
{
                var1 = ins->add1;
                if(var1->name)var1 = get_variable(var1->name);
                var2 = ins->add2;
                if(var2->name)var2 = get_variable(var2->name);
                
                result = ins->add3;
                int op = ins->operation;
                ins = ins->next;
                // if(var1->name)printf("VAR1: %s\n",var1->name);
                // if(var2->name)printf("VAR1: %s\n",var2->name);
                // if(result->name)printf("VAR1: %s\n",result->name);
                if((var1 == NULL) || (var2 == NULL) || (result == NULL))  
                {
                    line;
                    ret_error(SEMANTIC_DEF_ERROR);
                }
                if(var1->defined == 0 || var2->defined == 0)
                {
                    
                    line;
                    ret_error(SEMANTIC_DEF_ERROR);
                }
                if(var1->type == VARTYPE_BOOLEAN || var2->type == VARTYPE_BOOLEAN)
                {
                    line;
                    ret_error(SEMANTIC_TYPE_ERROR);
                }
                    
                    
                    
                result->defined = 1;
                
                
                
                switch(op)
                {
                case INS_ADD:
                
                    if(var1->type == VARTYPE_STRING || var2->type == VARTYPE_STRING)
                    { 
                        char buffer1[100],buffer2[100];
                        
                        if(var1->type == VARTYPE_INTEGER)
                        {
                            snprintf(buffer1, 10, "%d", var1->value.i);    
                        }
                        else if(var1->type == VARTYPE_DOUBLE)
                        {
                            snprintf(buffer1, 10, "%f", var1->value.d);    
                        }
                        else if(var1->type == VARTYPE_STRING)
                        {
                            strcpy(buffer1,var1->value.s);//buffer1 = var1->value.s;
                        }
                        else if(var1->type == VARTYPE_BOOLEAN)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                            
                        if(var2->type == VARTYPE_INTEGER)
                        {
                            snprintf(buffer2, 10, "%d", var2->value.i);    
                        }
                        else if(var2->type == VARTYPE_DOUBLE)
                        {
                            snprintf(buffer2, 10, "%f", var2->value.d);    
                        }    
                        else if(var2->type == VARTYPE_STRING)
                        {
                            strcpy(buffer2, var2->value.s);
                        }
                        else if(var2->type == VARTYPE_BOOLEAN)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        
                        result->type = VARTYPE_STRING;
                        result->value.s = malloc(sizeof(char)*(300));
                        strcpy(result->value.s, buffer1);
                        strcat(result->value.s, buffer2);
                        return;
                    }
                
                    if(var1->type == VARTYPE_DOUBLE || var2->type == VARTYPE_DOUBLE)
                    {
                        result->type = VARTYPE_DOUBLE;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.d + var2->value.d;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.d = var1->value.d + var2->value.i;
                        if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.d = var1->value.i + var2->value.d;
                        // printf("\tADD RESULT:%g\t\n",result->value.d);
                        break;
                    }
                    else if(var1->type == VARTYPE_INTEGER && var2->type == VARTYPE_INTEGER)
                    {   
                        result->type = VARTYPE_INTEGER;
                        result->value.i = var1->value.i + var2->value.i;
                        // printf("\tADD RESULT:%d\t\n",result->value.i);
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
                        // printf("\tSUB RESULT:%g\t\n",result->value.d);
                        break;
                    }
                    else if(var1->type == VARTYPE_INTEGER && var2->type == VARTYPE_INTEGER)
                    {   
                        result->type = VARTYPE_INTEGER;
                        result->value.i = var1->value.i - var2->value.i;
                        // printf("\tSUB RESULT:%d\t\n",result->value.i);
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
                        // printf("\tMUL RESULT:%g\t\n",result->value.d);
                        break;
                    }
                    else if(var1->type == VARTYPE_INTEGER && var2->type == VARTYPE_INTEGER)
                    {   
                        result->type = VARTYPE_INTEGER;
                        result->value.i = var1->value.i * var2->value.i;
                        // printf("\tMUL RESULT:%d\t\n",result->value.i);
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
                        // printf("\tDIV RESULT:%g\t\n",result->value.d);
                        break;
                    }
                    else if(var1->type == VARTYPE_INTEGER && var2->type == VARTYPE_INTEGER)
                    {   
                        result->type = VARTYPE_INTEGER;
                        result->value.i = var1->value.i / var2->value.i;
                        // printf("\tDIV RESULT:%d\t\n",result->value.i);
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
                            {result->value.b = var1->value.i < var2->value.i;
                        // printf("\tCOMPARE:%d\t\n",result->value.b);
                        break;
                    }
                case INS_CMP_LEQUAL:
                    if((var1->type == VARTYPE_INTEGER|| var1->type == VARTYPE_DOUBLE) &&(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE))
                    {
                        result->type = VARTYPE_BOOLEAN;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.d <= var2->value.d;
                        else if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.d <= var2->value.i;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.i <= var2->value.d;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.i <= var2->value.i;
                        // printf("\tCOMPARE:%d\t\n",result->value.b);
                        break;
                    }
                case INS_CMP_GREATER:
                    if((var1->type == VARTYPE_INTEGER|| var1->type == VARTYPE_DOUBLE) &&(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE))
                    {
                        result->type = VARTYPE_BOOLEAN;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.d > var2->value.d;
                        else if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.d > var2->value.i;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.i > var2->value.d;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.i > var2->value.i;
                        // printf("\tCOMPARE:%d\t\n",result->value.b);
                        break;
                    }
                case INS_CMP_GREQUAL:
                    if((var1->type == VARTYPE_INTEGER|| var1->type == VARTYPE_DOUBLE) &&(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE))
                    {
                        result->type = VARTYPE_BOOLEAN;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.d >= var2->value.d;
                        else if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.d >= var2->value.i;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.i >= var2->value.d;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.i >= var2->value.i;
                        // printf("\tCOMPARE:%d\t\n",result->value.b);
                        break;
                    }
                case INS_CMP_EQUAL:
                    if((var1->type == VARTYPE_INTEGER|| var1->type == VARTYPE_DOUBLE) &&(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE))
                    {
                        result->type = VARTYPE_BOOLEAN;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.d == var2->value.d;
                        else if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.d == var2->value.i;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.i == var2->value.d;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.i == var2->value.i;
                        // printf("\tCOMPARE:%d\t\n",result->value.b);
                        break;
                    }
                case INS_CMP_NOTEQUAL:
                    if((var1->type == VARTYPE_INTEGER|| var1->type == VARTYPE_DOUBLE) &&(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE))
                    {
                        result->type = VARTYPE_BOOLEAN;
                        if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.d != var2->value.d;
                        else if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.d != var2->value.i;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                            result->value.b = var1->value.i != var2->value.d;
                        else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_INTEGER)
                            result->value.b = var1->value.i != var2->value.i;
                        // printf("\tCOMPARE:%d\t\n",result->value.b);
                        break;
                    }
                    default:line;ret_error(SEMANTIC_TYPE_ERROR);
                    break;
                }
                }
}

int interpret()
{
    printf("\n\n\t***INTERPRET BEGINING***\n\n");  
    ins = globalInitList->First;
    
    localStack = stackInit();
    globalStack = stackInit();
    functionNodesStack = stackInit();
    // tTablePtr ifj = BSTSearch(globTable, "ifj");
    // TFunction *func = get_func_from_table(ifj->Root,"find");
    
    tTablePtr globStack = BSTSearch(globTable, "Main");
    classNode = globStack;
    
    stackPush(globalStack, globStack->data.c->stack);

    tTablePtr runFuncNode = BSTSearch(globStack->Root, "run");
    TStack *runStack = runFuncNode->data.f->stack;
    TList * list = runFuncNode->data.f->list;
    
    TListItem  LItem= create_instruction(INS_LABEL,NULL,NULL,NULL);
    insert_instruction(list, LItem);
    stackPush(runStack, LItem);
    
    
    stackPush(functionNodesStack, runFuncNode);
    stackPush(localStack, runStack);
    functionNode = stackTop(functionNodesStack);
    

    
    TFunction * func;

    
    // ins = func->list->First;
    
    while(ins)
    {
        #ifdef DEBUG
         translate_listitem(ins);
         printf(" %d\n",ins->operation);
         #endif
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
                
            
                var1 = ins->add1;
                if(var1->name)
                {
                    #ifdef DEBUG
                    printf("varname1: %s\n",var1->name);
                    #endif
                    var1 = get_variable(var1->name);
                    #ifdef DEBUG
                    // printf("varname1: %s\n",var1->name);
                    #endif
                }
                
                
                var2 = ins->add2;
                if(var2->name)
                {
                    #ifdef DEBUG
                    printf("varname2: %s\n",var2->name);
                    #endif
                    var2 = get_variable(var2->name);
                    #ifdef DEBUG
                    // printf("varname2: %s\n",var2->name);
                    // printf("return %d\n",var2->value.i);
                    #endif
                }
                
                if(var1 == NULL || var2 == NULL)
                {
                    line;
                    ret_error(SEMANTIC_DEF_ERROR);
                }
                
                
                var1->defined = 1;
                ins = ins->next;
                if(var1->type == VARTYPE_NULL)
                {
                    var1->type = var2->type;
                }
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
                        printf("%s %d", var1->name, var1->type);
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);    
                    }
                    var1->value.s = var2->value.s;
                    continue;
                }
                else if(var1->type == VARTYPE_BOOLEAN)
                {
                    if(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE || var2->type == VARTYPE_DOUBLE)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);    
                    }
                    var1->value.b = var2->value.b;
                    continue;
                }
                line;
                ret_error(SEMANTIC_DEF_ERROR);
            
            case INS_JMP:
            {
                ins = ins->add3;
                continue;
            }
            
            case INS_JCMP:
            {   
                var1 = ins->add1;
                // printf("\n\nJCMP:%d\n",var1->value.b);
                // printf("JCMP\n");
                if(var1->type != VARTYPE_BOOLEAN)
                {
                    line;
                    ret_error(SEMANTIC_TYPE_ERROR);
                }
                    
                if(var1->value.b == 0)
                    ins = ins->add3;
                else
                    ins = ins->next;
                continue;
            }
            
            case INS_CALL:
            {   
                // ins = ins->next;
                // continue;
                
                func = ins->add1;
                function = func;
                TVariable *result;
                if(ins->add3)
                {
                    result = ins->add3;   
                }
                // printf("\t%s call\n",func->name);
                
                if(strcmp(func->className, "ifj16"))
                {
                    
                    classNode = BSTSearch(globTable, func->className);
                    functionNode = BSTSearch(classNode->Root, func->name);
                    stackPush(functionNodesStack, functionNode);
                    TStack *globStack = classNode->data.c->stack;
                    stackPush(globalStack, globStack);
                    
                    //push return var and next instr
                    TListItem returnIns = ins->add2;//next instruction
                    
                    // TVariable *var = ins->add3;//save return value here
                    // if(var)printf("RETURN VAR%s\n",var->name);
                    
                    TStack *topStack = stackTop(localStack);
                    // printf("RETURN INS:%d\n",returnIns->operation);
                    // printf("Stack size : %d\n",topStack->top);
                    // stackPush(topStack,var);
                    stackPush(topStack,returnIns);
                }
                
                
                
                if(!strcmp(func->className, "ifj16"))
                {
                    TStack *stack = stackTop(localStack);
                    stackPop(localStack);
                    if(!strcmp(func->name,"print"))
                    {
                        TVariable *var = stackTop(stack);
                        if(var->name)
                        {
                            var = get_variable(var->name);
                        }
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var->type == 0)
                        {
                            line;
                            ret_error(SEMANTIC_DEF_ERROR);
                        }
                        print(var);
                    }
                    if(!strcmp(func->name, "length"))
                    {
                        TVariable *var = stackTop(stack);
                        
                        if(var->name)
                        {
                            var = get_variable(var->name);
                        }
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var->type != VARTYPE_STRING)
                        {
                            line;
                            ret_error(SEMANTIC_DEF_ERROR);
                        }
                        
                        if(result)
                        {
                            int lth = length(var->value.s);
                            result->type = VARTYPE_INTEGER;
                            result->value.i = lth;
                            TStack * returnStack = stackTop(globalStack);
                            stackPush(returnStack, result);
                        }
                        
                    }
                    if(!strcmp(func->name, "compare"))
                    {
                        TVariable *var1 = stackPop(stack);
                        TVariable *var2 = stackTop(stack);
                        
                        if(var1->name)
                        {
                            var1 = get_variable(var1->name);
                        }
                        if(var2->name)
                        {
                            var2 = get_variable(var2->name);
                        }
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var1->type != VARTYPE_STRING || var2->type != VARTYPE_STRING)
                        {
                            line;
                            ret_error(SEMANTIC_DEF_ERROR);
                        }
                        
                        if(result)
                        {
                            int lth = compare(var1->value.s,var2->value.s);
                            result->type = VARTYPE_INTEGER;
                            result->value.i = lth;
                            TStack * returnStack = stackTop(globalStack);
                            stackPush(returnStack, result);
                        }
                        
                    }
                    if(!strcmp(func->name, "substr"))
                    {
                        TVariable *var0 = stackPop(stack);
                        TVariable *var1 = stackPop(stack);
                        TVariable *var2 = stackTop(stack);
                        
                        if(var0->name)
                        {
                            var0 = get_variable(var0->name);
                        }
                        if(var1->name)
                        {
                            var1 = get_variable(var1->name);
                        }
                        if(var2->name)
                        {
                            var2 = get_variable(var2->name);
                        }
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var0->type != VARTYPE_STRING || var1->type != VARTYPE_INTEGER || var2->type != VARTYPE_INTEGER )
                        {
                            line;
                            ret_error(SEMANTIC_DEF_ERROR);
                        }
                        
                        if(result)
                        {
                            //char* lth = substr(var0->value.i, var1->value.i,var2->value.s);
                            result->type = VARTYPE_STRING;
                            result->value.s = malloc(sizeof(char)*100);
                            result->value.s = strcpy(result->value.s, substr(var0->value.s, var1->value.i,var2->value.i));
                            TStack * returnStack = stackTop(globalStack);
                            stackPush(returnStack, result);
                        }
                        
                    }
                    if(!strcmp(func->name, "readDouble"))
                    {
                        if(result)
                        {
                            double lth = readDouble();
                            result->type = VARTYPE_DOUBLE;
                            result->value.d = lth;
                            TStack * returnStack = stackTop(globalStack);
                            stackPush(returnStack, result);
                        }
                    }
                    if(!strcmp(func->name, "readInt"))
                    {
                        if(result)
                        {
                            int lth = readInt();
                            result->type = VARTYPE_INTEGER;
                            result->value.i = lth;
                            TStack * returnStack = stackTop(globalStack);
                            stackPush(returnStack, result);
                        }
                    }
                    if(!strcmp(func->name, "readString"))
                    {
                        if(result)
                        {
                            result->type = VARTYPE_STRING;
                            result->value.s = malloc(sizeof(char)*300);
                            result->value.s = strcpy(result->value.s, readString());
                            TStack * returnStack = stackTop(globalStack);
                            stackPush(returnStack, result);
                        }
                    }
                    
                    stackPop(stack);
                    /***end***/
                    
                    ins = ins->next;
                    // printf("ifj16 func: %s\n",func->name);
                    continue;
                }
                ins = func->list->First;
               
                continue;
            }
            
            case INS_PUSH_TABLE:
            {
                TStack *locStack = copyStack(ins->add2);//odkaz na zasobnik funkcie(origin zasobnik z parsera)
                TStack *paramStack = copyStack(ins->add1);//zasobnik parametrov, ktory sa do zasobniku funkcie nakopiruje
                
                
                if(locStack->top <0)
                {
                    // printf("***LOCSTACK***\n");
                    for(int i=0; i <= paramStack->top; i++)
                    {
                        // TVariable *var = paramStack->data[i];printf("%s\n",var->value.s);
                        stackPush(locStack,paramStack->data[i]);
                        // TVariable *var = locStack->data[i];
                        // if(var->type==VARTYPE_STRING)printf("%s \t\tdef:%d ",var->value.s, var->defined);
                        // if(var->type==VARTYPE_DOUBLE)printf("%g \t\tdef:%d ",var->value.d, var->defined);
                        // if(var->type==VARTYPE_INTEGER)printf("%d \t\tdef:%d ",var->value.i, var->defined);
                        // printf("Vartype: %d\n",var->type);
                        
                    }
                    // printf("***END LOCSTACK***\n");
                }
                else
                {
                    
                    // printf("***LOCSTACK***\n");
                    for(int i=0; i <= paramStack->top; i++)
                    {
                        TVariable *src = paramStack->data[paramStack->top - i];
                        TVariable *dest = locStack->data[i];
                        // printf("%d\n",src->defined);
                        char *name = dest->name;
                        dest = src;
                        dest->position = i;
                        
                        locStack->data[i] = dest;
                        // printf("%d\n",dest->defined);
                        
                        dest->name = name;
                        
                        // TVariable *var = locStack->data[i];
                        // if(var->type==VARTYPE_STRING)printf("%d|%s \t\tdef:%d ",i,var->value.s, var->defined);
                        // if(var->type==VARTYPE_DOUBLE)printf("%d|%g \t\tdef:%d ",i,var->value.d, var->defined);
                        // if(var->type==VARTYPE_INTEGER)printf("%d|%d \t\tdef:%d ",i,var->value.i, var->defined);
                        // printf("Vartype: %d\n",var->type);
                        
                        
                    }
                    // printf("paramStack\n");
                    // for(int i = 0; i < paramStack->top; i++)
                    // {
                    //     TVariable * var = paramStack->data[i];
                    //     printf("%d var:%s pos:%d\n",i, var->name, var->position);
                    // }
                    // printf("locStack\n");
                    // for(int i = 0; i < locStack->top; i++)
                    // {
                    //     TVariable * var = locStack->data[i];
                    //     printf("%d var:%s pos:%d\n",i, var->name, var->position);
                    // }
                    
                    // printf("***END LOCSTACK***\n");
                }
                
                //   printf("%s",var->name);
                /**************************************************/
                //COPY STACK FOR BY VALUE FUNCTIONS NO BY REFRENCE  
                /****************************************************/
                stackPush(localStack, locStack);
                
                ins = ins->next;
                continue;
            }
            
            case INS_RET:
            {
                //   ins = ins->next;
                // continue;
                
                TStack * topStack = stackTop(localStack);
                // printf("Stack size : %d\n",topStack->top);
                TListItem instr = stackPop(topStack);
                TVariable *result = ins->add1;
                
                
                if(result)
                {
                    result->name = malloc(sizeof(char)* 100);
                    strcpy(result->name, "return");
                    topStack = stackTop(globalStack);
                    stackPush(topStack,result);
                }
                
                
                // printf("REAL RETURN INS%d\n",instr->operation);
                // TListItem nextIns = create_instruction(INS_JMP, instr, NULL, NULL);
                ins = instr;
                
                stackPop(functionNodesStack);
                stackPop(localStack);
                
                continue;
            }
            default:
            break;
            
        }
        
        
        ins = ins->next;
    }
      
    return 1;
}