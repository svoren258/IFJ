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
TStack *localStack, *globalStack, *returnStack;
TFunction *function;

TStack *functionNodesStack;
tTablePtr functionNode, classNode;



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

int is_everything_defined(tTablePtr *RootPtr)
{   
    // printf("name %s type %d\n",(*RootPtr)->name,(*RootPtr)->type);
    
        if(*RootPtr)
        {
//          printf("name %s type %d\n",(*RootPtr)->name,(*RootPtr)->type);
            
            if(!is_everything_defined(&(*RootPtr)->RPtr))
                return FALSE;
            if(!is_everything_defined(&(*RootPtr)->LPtr))
                return FALSE;
                


            if((*RootPtr)->Root)
            {
                if(!is_everything_defined(&(*RootPtr)->Root))
                    return FALSE;
            }

            if((*RootPtr)->type == NODE_TYPE_VARIABLE)
            {
                if((*RootPtr)->data.v->defined == 0)
                    return FALSE;
                    // printf("VAriable ok\n");
            }
        
            else if((*RootPtr)->type == NODE_TYPE_FUNCTION)
            {
                if((*RootPtr)->data.f->defined == 0)
                    return FALSE;
                    // printf("func ok %d\n",(*RootPtr)->data.f->defined);
            }
            
            else if((*RootPtr)->type == NODE_TYPE_CLASS)
            {
                //  if((*RootPtr)->data.c->defined == 0)
                if((*RootPtr)->data.c->defined == 0)
                    return FALSE;
                    // printf("class ok\n");
                
            }
        

        }
        return TRUE;
}


TVariable *get_variable(TVariable *findVar)
{
    
    // printf("Find var: %s\n",findVar->name);
    TVariable *var;//stack to be returned
    TStack *topStack;//for local variables
    if(localStack->top>=0)
    topStack = stackTop(localStack);
    if(functionNodesStack->top >= 0)
    functionNode = stackTop(functionNodesStack);//for getting positions of the variables in the stack
    
    // #ifdef DEBUG
    // printf("\n\nFIND var:%s",findVar->name);
    // printf("\nFunction call: %s stacktop:%d\n",functionNode->name,functionNodesStack->top);
    // for(int i = 0; i < topStack->top; i++){
    //     TVariable *var1 = topStack->data[i];
    //     printf("%d var:%s pos:%d type:%d\n",i, var1->name,var1->position,var1->type);
    // }
    // #endif
    
    
    //First look for the return variable
    if(!strcmp(findVar->name, "return"))
    {
        for(int i = returnStack->top; i >= 0; i--)
        {
            var = returnStack->data[i];
            if(!strcmp(var->name, "return"))
            {
                stackPop(returnStack);
                return var;//returns basically the last return variable
            }
            
        }
    }
    
   if(functionNode)
    {
        //Looking for a local variable
        var = get_var_from_table(functionNode,findVar->name);//get the variable structure
        if(var)
        {
            // printf(" first %s\n",var->name);
            var = topStack->data[var->position];//fidn variable on the position
        }
        if(var)
        {
            return var;//return the variable
        } 
    }
    
    // printf("first?\n");
        
    //Looking for a global variable
    tTablePtr  fullClassIdentifier = BSTSearch(globTable, findVar->className);//node of the class
    if(!fullClassIdentifier)
    {
        ret_error(10);
    }
    
    //Looking for a global variable outside the current class
    var = get_var_from_table(fullClassIdentifier,findVar->name);//variable structure
    topStack = fullClassIdentifier->data.c->stack;//find in the global stack
    
    if(var != NULL)
        var = topStack->data[var->position];
    
    if(var != NULL)
        return var;

    //This should never happen    
    return NULL;
}

void math()
{
    var1 = ins->add1;
    if(var1->name)var1 = get_variable(var1);
    var2 = ins->add2;
    if(var2->name)var2 = get_variable(var2);
    
    result = ins->add3;
    int op = ins->operation;
    ins = ins->next;
    // if(var1->name)printf("VAR1: %s\n",var1->name);
    // if(var2->name)printf("VAR1: %s\n",var2->name);
    // if(result->name)printf("VAR1: %s\n",result->name);
    if((var1 == NULL) || (var2 == NULL) || (result == NULL))  
    {
        line;
        ret_error(UNINIT_VAR_ERROR);
    }
    if( var1->defined == 0 || var2->defined == 0)
    {
        line;
        ret_error(UNINIT_VAR_ERROR);
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
            if(!result->value.s)ret_error(INTERNAL_ERROR);
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
            ret_error(SEMANTIC_TYPE_ERROR);
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
            // printf("%s %d %s %d\n",var1->name, var1->type, var2->name, var2->type);
            line;
            ret_error(SEMANTIC_TYPE_ERROR);
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
            ret_error(SEMANTIC_TYPE_ERROR);
        }
        break;
    case INS_DIV:
    if(var2->value.d == 0 || var2->value.i == 0)
                ret_error(ZERO_DIV_ERROR);
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
            ret_error(SEMANTIC_TYPE_ERROR);
        }

    case INS_CMP_LESS:
        if((var1->type == VARTYPE_INTEGER|| var1->type == VARTYPE_DOUBLE) &&(var2->type == VARTYPE_INTEGER || var2->type == VARTYPE_DOUBLE))
        {//printf("\t%g %d\n",var1->value.d, var2->value.i);
            result->type = VARTYPE_BOOLEAN;
            if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_DOUBLE)
                result->value.b = var1->value.d < var2->value.d;
            else if(var1->type == VARTYPE_DOUBLE     && var2->type == VARTYPE_INTEGER)
            {
                result->value.b = var1->value.d < var2->value.i;
                // printf("computed:%d\n",result->value.b);
            }
            else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_DOUBLE)
                result->value.b = var1->value.i < var2->value.d;
            else if(var1->type == VARTYPE_INTEGER    && var2->type == VARTYPE_INTEGER)
                {result->value.b = var1->value.i < var2->value.i;
            // printf("\tCOMPARE:%d\t\n",result->value.b);
            break;
        }
        else
        {
            ret_error(SEMANTIC_TYPE_ERROR);
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
        else
        {
            ret_error(SEMANTIC_TYPE_ERROR);
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
        else
        {
            ret_error(SEMANTIC_TYPE_ERROR);
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
        else
        {
            ret_error(SEMANTIC_TYPE_ERROR);
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
        else
        {
            ret_error(SEMANTIC_TYPE_ERROR);
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
        else
        {
            ret_error(SEMANTIC_TYPE_ERROR);
        }
        default:line;ret_error(SEMANTIC_TYPE_ERROR);
        break;
        }
    }
}

int interpret()
{
    #ifdef DEBUG
    printf("\n\n\t***INTERPRET BEGINING***\n\n");  
    #endif
    ins = globalInitList->First;
    functionNode = NULL;
    
    localStack = stackInit();
    globalStack = stackInit();
    returnStack = stackInit();
    functionNodesStack = stackInit();
    // tTablePtr ifj = BSTSearch(globTable, "ifj");
    // TFunction *func = get_func_from_table(ifj->Root,"find");
    
    tTablePtr globStack = BSTSearch(globTable, "Main");
    classNode = globStack;
    
    stackPush(globalStack, globStack->data.c->stack);

    tTablePtr runFuncNode = BSTSearch(globStack->Root, "run");
    TStack *runStack = runFuncNode->data.f->stack;
    TList * list = runFuncNode->data.f->list;
    
    TListItem  LItem = create_instruction(INS_LABEL,NULL,NULL,NULL);
    insert_instruction(list, LItem);
    stackPush(runStack, LItem);
    
    
    

    
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
                
                if(!ins->add1 || !ins->add2)ret_error(SEMANTIC_DEF_ERROR);
                var1 = ins->add1;
                if(var1->name)
                {
                    #ifdef DEBUG
                    // printf("varname1: %s\n",var1->name);
                    #endif
                    var1 = get_variable(var1);
                    // #ifdef DEBUG
                    // printf("varname1: %s %d\n",var1->name,var1->type);
                    // #endif
                }
                
                
                var2 = ins->add2;
                if(var2->name)
                {
                    #ifdef DEBUG
                    // printf("varname2: %s\n",var2->name);
                    #endif
                    var2 = get_variable(var2);
                    #ifdef DEBUG
                    // printf("varname2: %s\n",var2->name);
                    // printf("return %d\n",var2->value.i);
                    #endif
                }
                if(!var1 || !var2)ret_error(SEMANTIC_DEF_ERROR);
                if( var2->defined == 0)
                {
                    line;
                    ret_error(UNINIT_VAR_ERROR);
                }
                
                
                var1->defined = 1;
                ins = ins->next;
                if(var1->type == VARTYPE_NULL)
                {
                    var1->type = var2->type;
                }
                if(var1->type == VARTYPE_INTEGER)
                {
                    // printf("to%s assign %d\n",var1->name, var2->value.i);
                    if(var2->type == VARTYPE_STRING || var2->type == VARTYPE_BOOLEAN)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);    
                    }
                    var1->value.i = (var2->type == VARTYPE_INTEGER) ? var2->value.i : var2->value.d;
                    continue;
                }
                else if(var1->type == VARTYPE_DOUBLE)
                {
                    if(var2->type == VARTYPE_STRING || var2->type == VARTYPE_BOOLEAN)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);    
                    }
                    var1->value.d = (var2->type == VARTYPE_INTEGER) ? var2->value.i : var2->value.d;
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
                ret_error(UNINIT_VAR_ERROR);
            
            case INS_JMP:
            {
                ins = ins->add3;
                continue;
            }
            
            case INS_JCMP:
            {   
                var1 = ins->add1;
                // printf("\tJCMP:%d\n",var1->value.b);
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
                TVariable *result = ins->add3;
                // if(ins->add3)
                // {
                //     result = ins->add3;   
                // }
                //  printf("\t%s %s call\n",func->name,func->className);
                
                if(!strcmp(func->className,"Main") && !strcmp(func->name,"run"))
                {//printf("LOOOL\n");
                    tTablePtr globStack = BSTSearch(globTable, "Main");
                    tTablePtr runFuncNode = BSTSearch(globStack->Root, "run");
                    TStack *runStack = runFuncNode->data.f->stack;
                    stackPush(functionNodesStack, runFuncNode);
                    stackPush(localStack, runStack);
                    functionNode = stackTop(functionNodesStack);
                }
                
                
                if(strcmp(func->className, "ifj16"))
                {
                    
                    classNode = BSTSearch(globTable, func->className);
                    functionNode = BSTSearch(classNode->Root, func->name);
                    stackPush(functionNodesStack, functionNode);
                    TStack *globStack = classNode->data.c->stack;
                    stackPush(globalStack, globStack);
                    
                    //push return var and next instr
                    TListItem returnIns = ins->add2;//next instruction
                    
                    TStack *topStack = stackTop(localStack);
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
                        if(!var)ret_error(SEMANTIC_DEF_ERROR);
                        if(var->defined == 0)ret_error(UNINIT_VAR_ERROR);
                        if(var->name)
                        {
                            var = get_variable(var);
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
                        // if(var->type == VARTYPE_DOUBLE)printf("\nNUM:%g\n",var->value.d);
                        // printf("VARTYPE: %d\n",var->type);4
                        print(var);
                    }
                    if(!strcmp(func->name, "length"))
                    {
                        TVariable *var = stackTop(stack);
                        if(!var)ret_error(SEMANTIC_DEF_ERROR);
                        if(var->defined == 0)ret_error(UNINIT_VAR_ERROR);
                        if(var->name)
                        {
                            var = get_variable(var);
                        }
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var->type != VARTYPE_STRING)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        
                        if(result)
                        {
                            int lth = length(var->value.s);
                            result->type = VARTYPE_INTEGER;
                            result->value.i = lth;
                            result->defined = 1;
                            stackPush(returnStack, result);
                        }
                        
                    }
                    if(!strcmp(func->name, "compare"))
                    {
                        TVariable *var1 = stackPop(stack);
                        TVariable *var2 = stackTop(stack);
                        if(!var1 || !var2)ret_error(SEMANTIC_DEF_ERROR);
                        if(var1->defined == 0 || var2->defined == 0)ret_error(UNINIT_VAR_ERROR);
                        if(var1->name)
                        {
                            var1 = get_variable(var1);
                        }
                        if(var2->name)
                        {
                            var2 = get_variable(var2);
                        }
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var1->type != VARTYPE_STRING || var2->type != VARTYPE_STRING)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        
                        if(result)
                        {
                            int lth = compare(var1->value.s,var2->value.s);
                            result->type = VARTYPE_INTEGER;
                            result->value.i = lth;
                            result->defined = 1;
                            stackPush(returnStack, result);
                        }
                        
                    }
                    if(!strcmp(func->name, "substr"))
                    {
                        TVariable *var0 = stackPop(stack);
                        TVariable *var1 = stackPop(stack);
                        TVariable *var2 = stackTop(stack);
                        if(!var0 || !var1 || !var2)ret_error(SEMANTIC_DEF_ERROR);
                        if(var0->defined == 0 || var1->defined == 0 || var2->defined == 0)ret_error(UNINIT_VAR_ERROR);
                        if(var0->name)
                        {
                            var0 = get_variable(var0);
                        }
                        if(var1->name)
                        {
                            var1 = get_variable(var1);
                        }
                        if(var2->name)
                        {
                            var2 = get_variable(var2);
                        }
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var0->type != VARTYPE_STRING || var1->type != VARTYPE_INTEGER || var2->type != VARTYPE_INTEGER )
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        
                        if(result)
                        {
                            result->type = VARTYPE_STRING;
                            result->value.s = malloc(sizeof(char)*100);
                            if(!result->value.s)ret_error(INTERNAL_ERROR);
                            result->value.s = strcpy(result->value.s, substr(var0->value.s, var1->value.i,var2->value.i));
                            result->defined = 1;
                            stackPush(returnStack, result);
                        }
                        
                    }
                    if(!strcmp(func->name, "find"))
                    {
                        TVariable *var0 = stackPop(stack);
                        TVariable *var1 = stackPop(stack);
                        if(!var0 || !var1)ret_error(SEMANTIC_DEF_ERROR);
                        if(var0->defined == 0 || var1->defined == 0)ret_error(UNINIT_VAR_ERROR);
                        if(var0->name)
                        {
                            var0 = get_variable(var0);
                        }
                        if(var1->name)
                        {
                            var1 = get_variable(var1);
                        }
                       
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var0->type != VARTYPE_STRING || var1->type != VARTYPE_STRING  )
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        
                        if(result)
                        {
                            result->type = VARTYPE_INTEGER;
                            result->value.i = find(var0, var1);
                            result->defined = 1;
                            stackPush(returnStack, result);
                        }
                        
                    }
                    if(!strcmp(func->name, "sort"))
                    {
                        TVariable *var = stackTop(stack);
                        if(!var)ret_error(SEMANTIC_DEF_ERROR);
                        if(var->defined == 0)ret_error(UNINIT_VAR_ERROR);
                        if(var->name)
                        {
                            var = get_variable(var);
                        }
                        if(stack->top != 0)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        if(var->type != VARTYPE_STRING)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        
                        if(result)
                        {
                            result->type = VARTYPE_STRING;
                            result->value.s = malloc(sizeof(char)*300);
                            if(!result->value.s)ret_error(INTERNAL_ERROR);
                            result->value.s = strcpy(result->value.s, sort(var));
                            result->defined = 1;
                            stackPush(returnStack, result);
                        }
                        
                    }
                    if(!strcmp(func->name, "readDouble"))
                    {
                        if(result)
                        {
                            double lth = readDouble();
                            if(lth == -1)ret_error(INPUT_READ_ERROR);
                            result->defined = 1;
                            result->type = VARTYPE_DOUBLE;
                            result->value.d = lth;
                            stackPush(returnStack, result);
                        }
                    }
                    if(!strcmp(func->name, "readInt"))
                    {
                        if(result)
                        {
                            int lth = readInt();
                            if(lth == -1)ret_error(INPUT_READ_ERROR);
                            result->type = VARTYPE_INTEGER;
                            result->defined = 1;
                            result->value.i = lth;
                            stackPush(returnStack, result);
                        }
                    }
                    if(!strcmp(func->name, "readString"))
                    {
                        if(result)
                        {
                            result->type = VARTYPE_STRING;
                            result->value.s = malloc(sizeof(char)*300);
                            if(!result->value.s)ret_error(INTERNAL_ERROR);
                            result->value.s = strcpy(result->value.s, readString());
                            result->defined = 1;
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
                    for(int i=0; i <= paramStack->top; i++)
                    {
                        stackPush(locStack,paramStack->data[i]);
                        
                    }
                }
                else
                {
                    
                    // printf("***LOCSTACK***\n");
                    for(int i=0; i <= locStack->top; i++)
                    {
                        TVariable *src = paramStack->data[paramStack->top - i];
                        TVariable *dest = locStack->data[i];
                        // printf("%d\n",src->defined);
                        // printf("%d %d\n",src->type, dest->type);
                        if(locStack->top != paramStack->top)
                            ret_error(SEMANTIC_TYPE_ERROR);
                        if(src->defined == 0)
                            ret_error(UNINIT_VAR_ERROR);
                        if(src->type != dest->type)
                        {
                            line;
                            ret_error(SEMANTIC_TYPE_ERROR);
                        }
                        
                        char *name = dest->name;
                        dest = src;
                        dest->position = i;
                        
                        locStack->data[i] = dest;
                        // printf("%d\n",dest->defined);
                        
                        dest->name = name;
                    }
                }
                
                stackPush(localStack, locStack);
                
                ins = ins->next;
                continue;
            }
            
            case INS_RET:
            {
                TStack * topStack = stackTop(localStack);
                TFunction *currFunc = functionNode->data.f;
                // printf("%s\n",currFunc->name);
                TListItem instr = stackPop(topStack);
                TVariable *result = ins->add1;
                
                
                if(result)
                {
                    // printf("%d %d\n",currFunc->params[0],result->type);
                    if(currFunc->params[0] != result->type)
                    {
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);
                    }
                    result->name = malloc(sizeof(char)* 100);
                    if(!result->name)
                    {
                        line;
                        ret_error(INTERNAL_ERROR);
                    }
                    strcpy(result->name, "return");
                    stackPush(returnStack,result);
                } else {
                    if(currFunc->params[0] != FUNCTYPE_VOID)
                    {
                        // printf("%d\n",currFunc->params[0]);
                        line;
                        ret_error(SEMANTIC_TYPE_ERROR);
                    }
                }

                ins = instr;
                
                stackPop(functionNodesStack);
                stackPop(localStack);
                stackPop(globalStack);
                
                continue;
            }
            
            case INS_LABEL:
            {
                ins = ins->next;
                continue;
            }
            default:
            printf("End of switch of interpreter\n");exit(1);
            break;
            
        }
        
        
        ins = ins->next;
    }
      
      
      
    if(!is_everything_defined(&globTable))
    {
        line;
        ret_error(SEMANTIC_DEF_ERROR);
    }
        
//     ins = globalInitList->First;
//     TListItem nextIns;
    
//     while(ins)
//  {
//      nextIns = ins->next;
//      free(ins);
//      if(nextIns)
//          ins = nextIns;
//      else
//          break;
//  }
    return 1;
}