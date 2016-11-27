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
    printf("FIND %s\n",name);
    TStack *topStack;
    // tTablePtr varNode;
    // tTablePtr classNode;
    // tTablePtr funcNode;
    TVariable *var;
    
    topStack = stackTop(localStack);
    
    // varNode = BSTSearch(functionTable->Root, name);
    var = get_var_from_table(functionNode,name);//varNode->data.v;
    if(var)
    {
        printf("%d\n",topStack->top);
        var = topStack->data[var->position];
        printf("%s %d\n",var->name,var->position);
    }
    
    // printf("%s\n",var->name);
    
    
    
    if(var != NULL)
    {
        printf("FOUND VARIABLE %s def:%d type:%d\n",var->name, var->defined, var->type);
        return var;
    }
        
   
    topStack = stackTop(globalStack);
     
    var = get_var_from_table(classNode,name);//varNode->data.v;line;
    
        
    var = topStack->data[var->position];
    
    
    if(var != NULL)
        return var;
    else
    {
        line;
        ret_error(SEMANTIC_DEF_ERROR);
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
                    if(var1->name)printf("%s def:%d 2\n",var1->name,var1->defined);
                    if(var2->name)printf("%s def:%d 1\n",var2->name,var2->defined);
                    line;
                    ret_error(SEMANTIC_DEF_ERROR);
                }
                if(var1->type == VARTYPE_BOOLEAN || var2->type == VARTYPE_BOOLEAN)
                {
                    line;
                    ret_error(SEMANTIC_TYPE_ERROR);
                }
                    
                    
                    
                result->defined = 1;
                if(var1->type == VARTYPE_STRING || var2->type == VARTYPE_STRING)
                { 
                    if(var1->type == VARTYPE_INTEGER)
                    {
                        char buffer[100];
                        snprintf(buffer, 10, "%d", var1->value.i);    
                        var1->value.s = buffer;
                        
                    }
                    else if(var1->type == VARTYPE_DOUBLE)
                    {
                        char buffer[100];
                        snprintf(buffer, 10, "%f", var1->value.d);    
                        var1->value.s = buffer;
                    }
                    else if(var1->type == VARTYPE_BOOLEAN)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);
                    }
                        
                        
                    if(var2->type == VARTYPE_INTEGER)
                    {
                        char buffer[100];
                        snprintf(buffer, 10, "%d", var2->value.i);    
                        var2->value.s = buffer;
                    }
                    else if(var2->type == VARTYPE_DOUBLE)
                    {
                        char buffer[100];
                        snprintf(buffer, 10, "%f", var2->value.d);    
                        var2->value.s = buffer;
                    }    
                    else if(var2->type == VARTYPE_BOOLEAN)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);
                    }
                        
                    result->type = VARTYPE_STRING;
                    // printf("%s %s\n",var1->value.s, var2->value.s);
                    
                    strncat(var1->value.s, var2->value.s, 100);
                    result->value.s = var1->value.s;
                    //strncpy(result->value.s, var1->value.s, 100);line;
                    return;
                }
                
                
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
                            {result->value.b = var1->value.i < var2->value.i;
                        printf("\tCOMPARE:%d\t\n",result->value.b);
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
                        printf("\tCOMPARE:%d\t\n",result->value.b);
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
                        printf("\tCOMPARE:%d\t\n",result->value.b);
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
                        printf("\tCOMPARE:%d\t\n",result->value.b);
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
                        printf("\tCOMPARE:%d\t\n",result->value.b);
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
                        printf("\tCOMPARE:%d\t\n",result->value.b);
                        break;
                    }
                    default:printf("DEFAULT MATH INS\n");
                    break;
                }
                }
}

int interpret()
{
    printf("\n\n***INTERPRET BEGINING***\n\n");  
    ins = globalInitList->First;
    
    localStack = stackInit();
    globalStack = stackInit();
    // tTablePtr ifj = BSTSearch(globTable, "ifj");
    // TFunction *func = get_func_from_table(ifj->Root,"find");
    
    tTablePtr globStack = BSTSearch(globTable, "Main");
    classNode = globStack;
    
    stackPush(globalStack, globStack->data.c->stack);

    tTablePtr runFunc = BSTSearch(globStack->Root, "run");
    TStack *runStack = runFunc->data.f->stack;
    
    stackPush(localStack, runStack);
    functionNode = runFunc;
    
    
    TFunction * func;
    // tTablePtr pclass = BSTSearch(globTable, "Game");
    
    // tTablePtr pfunc = BSTSearch(pclass->Root, "play");
    // printf("%s\n",pfunc->name);
    
    
    
    // ins = func->list->First;
    
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
                var1 = ins->add1;
                if(var1->name)
                var1 = get_variable(var1->name);
                
                var2 = ins->add2;
                if(var2->name)
                var2 = get_variable(var2->name);
                
                var1->defined = 1;
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
                
                printf("JCMP\n");
                if(var1->type != VARTYPE_BOOLEAN)
                {
                    line;
                    ret_error(SEMANTIC_TYPE_ERROR);
                }
                    
                if(var1->value.b == 1)
                    ins = ins->add3;
                else
                    ins = ins->next;
                continue;
            }
            
            case INS_CALL:
            {
                
                func = ins->add1;
                function = func;
                
                printf("\t%s call\n",func->name);
                
                if(strcmp(func->className, "ifj16"))
                {
                    
                    classNode = BSTSearch(globTable, func->className);
                    functionNode = BSTSearch(classNode->Root, func->name);
                    TStack *globStack = classNode->data.c->stack;
                    stackPush(globalStack, globStack);
                }
                
                
                
                if(!strcmp(func->className, "ifj16"))
                {
                    TStack *stack = stackTop(localStack);
                    if(!strcmp(func->name,"print"))
                    {
                        
                        TVariable *var = stackTop(stack);
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
                        stackPop(localStack);
                        // printf("%d\n",localStack->top);
                    }
                    
                    ins = ins->next;
                    // printf("ifj16 func: %s\n",func->name);
                    continue;
                }
                
                
                
                
                
                
                
                
                // ins = func->list->First->next->next;
                // printf("%d\n",ins->operation);
                // printf("FUNC CALL: %s\n",func->name);
                // printf("CLASS: %s\n",func->className);
                // printf("stack: %d\n", func->stack->top);
                //printf("%d\n",ins->next->next->operation);
                ins = func->list->First;
               
                continue;
            }
            
            case INS_PUSH_TABLE:
            {
                TStack *locStack = ins->add2;//odkaz na zasobnik funkcie(origin zasobnik z parsera)
                TStack *paramStack = ins->add1;//zasobnik parametrov, ktory sa do zasobniku funkcie nakopiruje
                
                for(int i=0; i <= paramStack->top; i++)
                {
                    TVariable *dest = locStack->data[i];
                    TVariable *src  = paramStack->data[i];
                    dest->value = src->value;
                    dest->type = src->type;
                }
                if(locStack->top <0)
                {
                    for(int i=0; i <= paramStack->top; i++)
                    {
                        stackPush(locStack,paramStack->data[i]);
                        
                        
                    }
                }
                
                
                tTablePtr helo = BSTSearch(globTable, "Game");
                helo = BSTSearch(helo->Root, "hello");
                TFunction *func = helo->data.f;//funkcia hello z Game
                printf("***params top%d %d\n",func->numOfParams,func->stack->top);//obsahuje len 1 premennu na zasobniku, mali by byt 2
                printf("\t\tparamstack top:%d locstack:%d\n",paramStack->top,locStack->top);
                //  TVariable *var = stackTop(paramStack);
                  TVariable *var1 = stackTop(locStack);
                  stackPop(locStack);
                  printf("*****var on helo stack:%s %d\n",var1->name,var1->type);
                //   printf("%s",var->name);
                /**************************************************/
                //COPY STACK FOR BY VALUE FUNCTIONS NO BY REFRENCE  
                /****************************************************/
                stackPush(localStack, locStack);
                
                ins = ins->next;
                continue;
            }
            
            
        }
        
        
        ins = ins->next;
    }
      
    return 1;
}