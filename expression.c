/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "expression.h"
#include "interpret.h"
//#include "defs.h"
tTablePtr globTable;

char precedence_table[TABLESIZE][TABLESIZE] =
{/*st\in +   -   *   /   <  <=   >  >=  ==  !=   (   ) func  i   ,   $*/
/* + */{'>','>','<','<','>','>','>','>','>','>','<','>','<','<','<','>'},//0
/* - */{'>','>','<','<','>','>','>','>','>','>','<','>','<','<','<','>'},//1
/* * */{'>','>','>','>','>','>','>','>','>','>','<','>','<','<','<','>'},//2
/* / */{'>','>','>','>','>','>','>','>','>','>','<','>','<','<','<','>'},//3
/* < */{'<','<','<','<','$','$','$','$','$','$','<','>','<','<','<','>'},//4
/*<= */{'<','<','<','<','$','$','$','$','$','$','<','>','<','<','<','>'},//5
/* > */{'<','<','<','<','$','$','$','$','$','$','<','>','<','<','<','>'},//6
/*>= */{'<','<','<','<','$','$','$','$','$','$','<','>','<','<','<','>'},//7
/*== */{'<','<','<','<','$','$','$','$','$','$','<','>','<','<','<','>'},//8
/*!= */{'<','<','<','<','$','$','$','$','$','$','<','>','<','<','<','>'},//9
/* ( */{'<','<','<','<','<','<','<','<','<','<','<','=','<','<','=','$'},//10
/* ) */{'>','>','>','>','>','>','>','>','>','>','$','>','$','$','>','>'},//11
/*fun*/{'$','$','$','$','$','$','$','$','$','$','=','$','$','$','$','$'},//12
/* i */{'>','>','>','>','>','>','>','>','>','>','$','>','>','$','>','>'},//13
/* , */{'<','<','<','<','<','<','<','<','<','<','<','=','<','<',',','$'},//14
/* $ */{'<','<','<','<','<','<','<','<','<','<','<','$','<','<','<','$'},//15

    
};

TStack *oStack;
TIStack * iStack;
TStack *varStack;
Ttoken *token, *helper;
tTablePtr globTable;
tTablePtr exprFunc;
tTablePtr exprClass;
tTablePtr funcContext;
tTablePtr classContext;
TFunction *thisFunction;
TFunction *functionCall;
TList *globalInitList;
TList * list;
tTablePtr functionCallTable;
int TOKENTYPE;

double literal_double(char* s){
    char* str = malloc(sizeof(char));
    if(!str)ret_error(INTERNAL_ERROR);
    str[0] = '\0';
    int i;
    for (i = 0; s[i] != 'e' && s[i] != 'E'  ; ++i) {
        str =  realloc(str, sizeof(char)*(i+1)*8);
        if(!str)ret_error(INTERNAL_ERROR);
        str[i] = s[i];
        str[i+1] = '\0';
    }
 
    double result = atof(str);
    int sign = 0;
 
    if(s[i+1] == '-') {
        sign = 1;
        i++;
    } else if(s[i+1] == '+')
        i++;
 
    char* str2 = malloc(sizeof(char));
    if(!str2)ret_error(INTERNAL_ERROR);
    int in = 0;
 
    for (int j = i+1; s[j] != '\0'; ++j) {
        str2 = (char*) realloc(str2, sizeof(char)*(in+1)*8);
        if(!str)ret_error(INTERNAL_ERROR);
        str2[in] = s[j];
        str2[in+1] = '\0';
        in++;
    }
    int exponent = atoi(str2);
    double number = 1;
 
    for (int k = 0; k < exponent; ++k) {
        number = number * 10;
    }
    
    if(sign == 1)
        number = 1/number;
    result = result * number;
    free(str);
    free(str2);
 
    return result;
 
}
 

void iStack_push(int val)
{
    TIData* newdata  = malloc(sizeof(TIData));
    if(!newdata)ret_error(INTERNAL_ERROR);
    iStack->top++;
    iStack->data[iStack->top] = newdata;
    iStack->data[iStack->top]->data = val;
}
void iStack_init()
{
    
    iStack = malloc(sizeof(TIStack));
    if(!iStack)ret_error(INTERNAL_ERROR);

    iStack->top = -1;
    iStack_push(OP_DOLAR);
}
//get the priority stack sign
int iStack_top_term()
{
    int b;
    for(int i = iStack->top; i >= 0; i--)
    {
        b = iStack->data[i]->data;
        if(  (b != SIGN_LESS  ) && (b != SIGN_EQUALS) && (b != SIGN_GREATER) && (b != OP_NONTERM))
        return (b);
    }
    
    return OP_DOLAR;
}

//get the top of the stack
int iStack_top()
{
    int b;
    for(int i = iStack->top; i >= 0; i--)
    {
        b = iStack->data[i]->data;
        return (b);
    }
    //line;
    return SIGN_FAIL;
}

int iStack_pop()
{
    if(iStack->top >= 0)
    {
        int ret = iStack->data[iStack->top]->data;
        TIData *data = iStack->data[iStack->top];
        free(data);
        // iStack->data[iStack->top] = '\0';
        iStack->top--;
        return ret;
    }
        
    return OP_DOLAR;
}

int iStack_get_sign()
{
    int b;
    for(int i = iStack->top; i >= 0; i--)
    {
        b = iStack->data[i]->data;
        if( b != OP_NONTERM )
        return (b);
    }
    return SIGN_FAIL;
}


void print_list()
{
    #ifdef DEBUG
    // TListItem ins;
    // if(thisFunction)
    // {
    //     ins = thisFunction->list->First;
    //     //printf("Function list\n");
    // }
     
    // else
    // {
    //     ins = globalInitList->First;
    //     //printf("class list\n");
    // }
    // if(thisFunction)return;
    // insert_instruction(list,create_instruction(INS_LABEL,NULL,NULL,NULL));
    // //printf("*******************************THE WHOLE FUNCTION LIST******************************\n");
    // // while(ins)
    // // {
    // //     //printf("%d\n",ins->operation);
    // //     ins = ins->next;
    // // }
    // //printf("********************************END FUNCTION LIST**********************************\n");
    #endif
}

void printStacks()
{
    // #ifdef DEBUG
    // //printf("-----iStack-----\n");
    // int b;
    // for(int i = 0; i <= iStack->top; i++)
    //     {
            
    //         b = iStack->data[i]->data;
    //         switch(b)
    //         {
    //             case OP_PLUS:
    //             //s("+");
    //             break;
                
    //             case OP_MINUS:
    //             //s("-");
    //             break;
                
    //             case OP_MUL:
    //             //s("*");
    //             break;
                
    //             case OP_DIV:
    //             //s("/");
    //             break;
                
    //             case OP_I:
    //             //s("OP_I");
    //             break;
                
    //             case OP_NONTERM:
    //             //s("E");
    //             break;
                
    //             case R_LESS:
    //             //s("<");
    //             break;
                
    //             case OP_DOLAR:
    //             //s("$");
    //             break;
                
    //             case OP_COMA:
    //             //s(",");
    //             break;
                
    //             case OP_FUNC:
    //             //s("func");
    //             break;
                
                
    //             case OP_LESS:
    //             //s("'<'");
    //             break;
                
    //             case OP_LEQUAL:
    //             //s("<=");
    //             break;
                 
    //             case OP_GREATER:
    //             //s(">");
    //             break;
                
    //             case OP_GREQUAL:
    //             //s(">=");
    //             break;
                
    //             case OP_EQUAL:
    //             //s("==");
    //             break;
                
    //             case OP_NOTEQUAL:
    //             //s("!=");
    //             break;
                
                
    //             case OP_LROUND:
    //             //s("(");
    //             break;
    //             case OP_RROUND:
    //             //s(")");
    //             break;
    //             default:break;
    //             // SIGN_LESS,//19
    //             // SIGN_GREATER,//20
    //             // SIGN_EQUALS,//21
    //         }
    //     }
    // //printf("\n-----/iStack----\n");
    
    // //printf("-----oStack-----\n");
    
    // for(int i = oStack->top; i >= 0; i--)
    //     {
    //         TVariable *var = oStack->data[i];
    //         if(var->type == VARTYPE_INTEGER)
    //         {
    //             if(var->name)
    //             //printf("varname:%s \n",var->name);
    //             if(var->value.i)
    //             //printf("%d INT\n",var->value.i);    
    //         }
            
    //         else if(var->type == VARTYPE_DOUBLE)
    //         {
    //             if(var->name)
    //             //printf("varname:%s \n",var->name);
    //             if(var->value.d)
    //             //printf("%g DOUBLE\n",var->value.d);
    //         }
            
    //         else if(var->type == VARTYPE_STRING)
    //         {
    //             if(var->name)
    //             //printf("varname:%s \n",var->name);
    //             if(var->value.s)
    //             //printf("%s string\n",var->value.s);    
    //         }
    //         else
    //         {
    //             if(var->name)
    //             //printf("varname:%s \n",var->name);
    //             //printf("anonym otop %d\n",oStack->top);
    //         }
            
    //     }
        
    // //printf("-----/oStack-----\n");
    
    // // //printf("-----varstack----\n");
    
    // // for(int i = varStack->top; i >= 0; i--)
    // //     {
    // //         token = varStack->data[i];
    // //         tok;
    // //     }
    // // //printf("-----/varstack-----\n");    
    //     #endif
}


TStack * push_params(int numOfParams)
{
    TStack *paramStack;
    paramStack = stackInit();
    // //printf("function:%s \n",exprFunc->name);
    // //printf("function:%s  in class: %s\n",exprFunc->name, exprClass->name);
    // functionCall = iStack->data[iStack->top]->ptr;
    // TVariable *result = stackPop(oStack);
    if(!functionCall)
    {//line;
        // //printf("%s\n",functionCall->name);
        //line;
        ret_error(SYNTAX_ERROR);
    }
    else
    {
        printStacks();
        for(int i = 0; i < numOfParams; i++)
        {
            // TVariable *var = stackTop(oStack);
            // printf("%s\n",var->name);
            stackPush(paramStack, stackPop(oStack));
        }
        // //printf("********************\n******************\n****************\n");
        // //printf("Params: %d\n",paramStack->top);
        // //printf("%s\n",functionCall->name);
    }
    // stackPush(oStack, result);
    // //printf("I am here %s\n", functionCall->name);
    return paramStack;
}

int simple_reduction(TVariable *var)
{////s("REDUCTION BEGIN\n");
    int params = 0;
    int coma = 0;
    TVariable *var1;
    TVariable *var2;
    TVariable *result;
    if(iStack_top() == OP_I)//ID -> E
    {
        ////s("TRY REDUCTION ID -> E\n");
        iStack_pop();
        if(iStack_top() == R_LESS)
        {
            iStack_pop();
            iStack_push(OP_NONTERM);
        }
        printStacks();
    } 
    
    
    if(iStack_top() == OP_RROUND)
    {
        
        iStack_pop();
        if(iStack_top() == OP_NONTERM)//(E) -> E
        {
            iStack_pop();
            if(iStack_top() == OP_LROUND)
            {
                iStack_pop();
                if(iStack_top() == R_LESS)//(E) -> E
                {////s("TRY REDUCTION (E) -> E\n");
                    iStack_pop();
                    iStack_push(OP_NONTERM);
                }
                else if(iStack_top() == OP_FUNC)//func(par) -> E
                {////s("TRY REDUCTION func(par) -> E\n");
                    params = 1;
                    
                    
                    iStack_pop();//func
                    iStack_pop();//< before func
                    //function call
                    
                    
                    if(var)
                    {
                        result = generate_var(0);
                        result->name = "return";    
                        //printf("\t\t\tLOL\n");
                    }
                    
                    TListItem lab = create_instruction(INS_LABEL, NULL,NULL,NULL);
                    insert_instruction(list,create_instruction(INS_PUSH_TABLE, push_params(params), functionCall->stack, NULL));
                    insert_instruction(list,create_instruction(INS_CALL, functionCall, lab, result));
                    insert_instruction(list,lab);
                    if(var)stackPush(oStack, result);
                    iStack_push(OP_NONTERM);
                }
                else
                {
                    //line;ret_error(SYNTAX_ERROR);
                }
            }
            else if(iStack_top() == OP_COMA)//func(par,par,...)
            {//already 1 param counted <- previous pop
            ////s("TRY REDUCTION func(,,) -> E\n");
                params = 1;
                while(iStack_top() != OP_LROUND)
                {
                    if(iStack_top() == OP_COMA && coma == 0)
                    {
                        coma = 1;
                    }
                    else if(iStack_top() == OP_NONTERM && coma == 1)
                    {
                        params++;
                        coma = 0;
                    }
                    else
                    {
                        //line;
                        ret_error(SYNTAX_ERROR);
                    }
                    iStack_pop();
                }
                if(coma == 1)
                {
                    //line;
                    ret_error(SYNTAX_ERROR);
                }
                if(iStack_top() == OP_LROUND)
                    iStack_pop();
                else
                {
                    //line;
                    ret_error(SYNTAX_ERROR);
                }
                if(iStack_top() == OP_FUNC)
                {
                    iStack_pop();//func
                    iStack_pop();//< before func
                    //function call
                    
                    
                    if(var)
                    {
                        result = generate_var(0);
                        result->name = "return";    
                    }
                    
                    TListItem lab = create_instruction(INS_LABEL, NULL,NULL,NULL);//line;
                    insert_instruction(list,create_instruction(INS_PUSH_TABLE, push_params(params), functionCall->stack, NULL));
                    insert_instruction(list,create_instruction(INS_CALL, functionCall, lab, result));
                    insert_instruction(list,lab);
                    if(var)stackPush(oStack, result);
                    iStack_push(OP_NONTERM);
                }
            } 
            else 
            {
                //line;
                ret_error(SYNTAX_ERROR);
            }
            
        }
        
        else if(iStack_top() == OP_LROUND)//func() -> E
        {
            // printStacks();
            ////s("TRY REDUCTION func() -> E\n");
            iStack_pop();// "("
            iStack_pop();//func
            iStack_pop();//< before func
            //function call
            // printStacks();exit(1);
            
            // //printf("\t\t\tSTACK TOP%d\n",functionCall->stack->top);
            if(var)
            {
                result = generate_var(0);
                result->name = "return";    
            }
            
            TListItem lab = create_instruction(INS_LABEL, NULL,NULL,NULL);
            insert_instruction(list,create_instruction(INS_PUSH_TABLE, push_params(0), functionCall->stack, NULL));
            insert_instruction(list,create_instruction(INS_CALL, functionCall, lab, result));
            insert_instruction(list,lab);
            if(var)stackPush(oStack, result);
            iStack_push(OP_NONTERM);
            //func call
        }
        else
        {
            //line;
            ret_error(SYNTAX_ERROR);
        }
        printStacks();
    }
        
    if(iStack_top() == OP_NONTERM)//<E op E -> E
    {
        iStack_pop();//E
        switch(iStack_top())
        {
            
            case    OP_PLUS:
            case    OP_MINUS:
            case    OP_MUL:
            case    OP_DIV:
            case    OP_LESS:
            case    OP_LEQUAL:
            case    OP_GREATER:
            case    OP_GREQUAL:
            case    OP_EQUAL:
            case    OP_NOTEQUAL:
                var2 = stackPop(oStack);
                var1 = stackPop(oStack);
                result = generate_var(0);
                TListItem ins = create_instruction(iStack_top(),var1,var2,result);
                insert_instruction(list,ins);
                stackPush(oStack,result);
                // //printf("***********REDUCTION :E %d E***********\n", iStack_top());//OP
                iStack_pop();
                if(iStack_top() != OP_NONTERM)
                {
                    //line;
                    ret_error(SYNTAX_ERROR);
                }
                iStack_pop();//E
                
                if(iStack_top() >= 0 && iStack_top() <= 9)
                {
                    //line;
                    ret_error(SYNTAX_ERROR);
                }
                iStack_pop();//<
                iStack_push(OP_NONTERM);
                printStacks();
                return TRUE;
            default:
                iStack_push(OP_NONTERM);
                return FALSE;
        }
        
    }
    return FALSE;
}

TVariable *generate_var(int assign)
{
    TVariable *var;
    var = malloc(sizeof(TVariable));
    if(!var)ret_error(INTERNAL_ERROR);
    stackPush(varStack, var);
    var->name = NULL;
    var->className = NULL;
    var->declared = 1;
    var->defined = 0;
    var->type = VARTYPE_NULL;
    
    if(assign == 1)
    {
        var->defined = 1;
        if(token->type == TOKEN_INT || token->type == TOKEN_E)
        {
            var->type = VARTYPE_INTEGER;
            var->value.i = atoi(token->data);
            if( token->type ==  TOKEN_E)
            {
                var->type = VARTYPE_DOUBLE;
                var->value.d = literal_double(token->data);
                return var;
            }
        }
            
        else if(token->type == TOKEN_STRING)
        {
            var->type = VARTYPE_STRING;
            var->value.s = token->data;
        }
            
        else if(token->type == TOKEN_DOUBLE || token->type ==  TOKEN_DOUBLE_E )
        {
            if( token->type ==  TOKEN_DOUBLE_E)
            {
                
                var->type = VARTYPE_DOUBLE;
                var->value.d = literal_double(token->data);
                return var;
            }
            var->type = VARTYPE_DOUBLE;
            var->value.d = strtod(token->data,NULL);
            
        }
    }
    return var;
}





int tokenToType(Ttoken *token)
{
    char * TName;
    char * CName;
    // if(isFunctionCall())return OP_FUNCTION;
    // if(isFunctionFullNameCall())return OP_FUNCTION;
    // if(isFullNameVar())return OP_I;
    switch(token->type)
    {
        case TOKEN_PLUS: 
            return OP_PLUS;
        case TOKEN_MINUS:
            return OP_MINUS;
        case TOKEN_MUL:
            return OP_MUL;
        case TOKEN_DIV:
            return OP_DIV;
        case TOKEN_GREATER:
            return OP_GREATER;
        case TOKEN_LESS:
            return OP_LESS;
        case TOKEN_GR_EQ:
            return OP_GREQUAL;
        case TOKEN_LE_EQ:
            return OP_LEQUAL;
        case TOKEN_NOT_EQ:
            return OP_NOTEQUAL;
        case TOKEN_EQUALS:
            return OP_EQUAL;
        case TOKEN_COLON:
            return OP_COMA;
        case TOKEN_SEM_CL:
            return OP_DOLAR;
        case TOKEN_L_ROUND:
            return OP_LROUND;
        case TOKEN_R_ROUND:
            return OP_RROUND;
        case TOKEN_ID:
            
            TName = token->data;
            CName = token->data;
            token = get_token();
            TVariable *var = NULL;
            
            //find class by name
            
            if(token->type == TOKEN_L_ROUND )
            {//func(..)
                if((functionCall = get_func_from_table(classContext, TName)) == NULL)//this func might be defined in another class later
                {
                    functionCall = new_function(TName, classContext);//not gonna use return value from this or???
                }
                //printf("%s\n",functionCall->name);
                functionCall = get_func_from_table(classContext, TName);
                functionCallTable = BSTSearch(classContext->Root, TName);
                //printf("%s\n",functionCall->name);
                unget_token(1);
                return OP_FUNC;
            } //func(..)
            else if(token->type == TOKEN_DOT )
            {
                token = get_token();
                if( token->type == TOKEN_ID )
                {
                    TName = token->data;
                    token = get_token();
                    if(token->type == TOKEN_L_ROUND)
                    {//class.func()
                        if((exprClass = BSTSearch(globTable->Root, CName)) == NULL)
                        {
                            exprClass = create_class_table(CName, globTable);
                        }
                        if((functionCall = get_func_from_table(exprClass, TName)) == NULL)//this func might be defined in another class later
                        {
                            functionCall = new_function(TName, exprClass);//not gonna use return value from this or???
                            //line;
                        }
                        functionCallTable = BSTSearch(exprClass->Root, TName);
                       // //printf("%s\n",functionCallTable->name);
                        unget_token(1);
                        exprFunc = BSTSearch(exprClass->Root, TName);
                        ////printf("class:%s func:%s\n",exprClass->name,exprFunc->name);
                        // //printf("%s\n",exprFunc->name);exit(1);
                        return OP_FUNC;
                    }//class.func()
                    
                    ////class.var
                    if((exprClass = BSTSearch(globTable->Root, CName)) == NULL)
                    {
                        exprClass = create_class_table(CName, globTable);
                    }
                    if(( var = get_var_from_table(exprClass, TName)) == NULL)//this var might be defined in another class later
                    {
                        
                        token->data = TName;
                        var = new_variable( token, exprClass );
                        
                    }////class.var
                    stackPush(oStack, var);
                    
                    unget_token(1);
                    return OP_I;
                }
                else
                {
                    //line;
                    ret_error(SYNTAX_ERROR);
                }
            }
            else
            {//var
                // exprClass = NULL;
                if(funcContext != NULL){
                if((var = get_var_from_table(funcContext, TName)) == NULL)
                {
                    if((var = get_var_from_table(classContext, TName)) == NULL)
                    {
                        //line;
                        ret_error(SEMANTIC_DEF_ERROR);
                    }
                    // //printf("%s\n",TName);//line;//line;
                }}
                stackPush(oStack, var);
                // if(!var)//s("*****************************************************\n");
                unget_token(1);
                return OP_I;
            }//var
            
            
        case TOKEN_INT:
        case TOKEN_DOUBLE:
        case TOKEN_STRING:
        case TOKEN_DOUBLE_E:
        case TOKEN_E:
            return OP_I;
        break;
    }

    //printf("%s %d \n",token->data, token->type);
    //line;
    ret_error(SYNTAX_ERROR);
     return 0;
}

int compare_priority(int stackTop)
{
    // //printf("\nINPUT***tok= %s type= %d  itop= %d\n\n",token->data,TOKENTYPE ,iStack_top_term());
    if( precedence_table[ stackTop ][ TOKENTYPE ] == '$' )
    {
        return SIGN_FAIL;
    }
    
    if( precedence_table[ stackTop ][ TOKENTYPE ] == '>' )
        return SIGN_GREATER;
    else if( precedence_table[ stackTop ][ TOKENTYPE ] == '<' )
        return SIGN_LESS; 
    else return SIGN_EQUALS;
}

void analysis(TVariable *var)
{
    // int helper;
    int end = 0;
    int brackets = 0;
    token = get_token();
    while( 1 )
    {
        helper = token;
        TOKENTYPE = tokenToType(token);
        token = helper;
        if(TOKENTYPE == OP_LROUND){
            brackets++;
            ////printf("BRACKETS:%d\n",brackets);
        }
        if(TOKENTYPE == OP_RROUND){
            brackets--;
           // //printf("BRACKETS:%d\n",brackets);
        }
        if(brackets < 0){
           // //printf("BRACKETS:%d RETURN\n",brackets);
            
        }
       
        // //printf("TT:%d  Token:%d\n",TOKENTYPE, token->type);
        // if(TOKENTYPE!=token->type);
        // //printf("\nINPUT***tok= %s type= %d  itop= %d\n\n",token->data,TOKENTYPE ,iStack_top_term());
        // //printf("%c\n",precedence_table[iStack_top_term()][TOKENTYPE]);
        switch(compare_priority(iStack_top_term()))
        {
            case SIGN_LESS:
                
                //id -> E
                // //printf("LESS: Ttype %d\n",TOKENTYPE);
                if(TOKENTYPE != OP_NONTERM)
                {
                    
                    iStack_push (R_LESS);
                    iStack_push(TOKENTYPE);
                    if(TOKENTYPE == OP_FUNC)
                    {
                        iStack->data[iStack->top]->ptr = functionCall;
                        // exit(1);
                    }
                        
                    printStacks();
                    
                }
                
                else
                {//E -> <E+
                        iStack_pop();
                        iStack_push(R_LESS);
                        iStack_push(OP_NONTERM);
                        iStack_push(TOKENTYPE);
                }
                //
                if(token->type == TOKEN_INT || token->type == TOKEN_DOUBLE || token->type == TOKEN_STRING || token->type == TOKEN_E || token->type == TOKEN_DOUBLE_E)
                {
                    // printf("%d\n",token->type);
                    // tok;
                    TVariable *var = generate_var(1);
                    stackPush(oStack, var);
                }
            
            break;
            
            case SIGN_GREATER:
         //   //printf("GREATER: Ttype %d\n",TOKENTYPE);
//                if( brackets >= 0 )

                    simple_reduction(var);
                if(token->type != TOKEN_SEM_CL)
                {
                    if( TOKENTYPE == OP_RROUND && brackets == -1 && iStack->top == 1)
                    {
                        iStack_pop();
                        if(var)
                        {
                            #ifdef DEBUG
                            //printf("*************ASSIGN*************\n");
                            #endif
                            insert_instruction(list, create_instruction(INS_ASSIGN,var,stackPop(oStack),NULL));
                        }
                        
                        break;

                    }
                    
                    if( TOKENTYPE == OP_RROUND && brackets > -1)//add ) to the stack
                    {//line;
                        iStack_push(OP_RROUND);
                        printStacks();
                    }
                    else if(iStack_top() == OP_NONTERM && brackets > -1)//E -> <E+
                    {
                        iStack_pop();
                        if(TOKENTYPE != OP_COMA)//if coma, do not insert less sign
                            iStack_push (R_LESS);
                        iStack_push(OP_NONTERM);
                        iStack_push(TOKENTYPE);
                        printStacks();
                        break;
                    }
                    else if(iStack_top() == OP_NONTERM && brackets == -1)
                    {
                        iStack_pop();
                    }
                    else
                    {
                        //line;
                        ret_error(SYNTAX_ERROR);
                    }
                }
                break;
            
            case SIGN_EQUALS:
          //  //printf("EQUALS Ttype %s\n",token->data);
            iStack_push(TOKENTYPE);//simply add according symbol
            

            break;
            
            default:
           // //printf("SWITCH DEFAULT TTYPE\n");
                if(iStack->top == 1 && iStack_top() == OP_NONTERM && token->type == TOKEN_SEM_CL)
                {
                    iStack_pop();    
                    if(var)
                    {
                        #ifdef DEBUG
                        //printf("*************ASSIGN*************\n");
                        #endif
                        insert_instruction(list, create_instruction(INS_ASSIGN,var,stackPop(oStack),NULL));
                    }
                    
                    print_list();
                    
                    break;
                }
            break;
            
            
            
        }
        end++;
        
        
        
        if(( (token->type == TOKEN_SEM_CL) || (brackets==-1) ) && iStack->top == 0)
        {
            //s("FINISHED EXPRESSION SUCCESFULLY!!!\n");
            return;//finished expression
        }
        
        if(token->type != TOKEN_SEM_CL )
        {
            if(token->type == TOKEN_R_ROUND && brackets < 0)    
                break;
            token = get_token();
        }
         if(end>100)
         {
             ret_error(SYNTAX_ERROR);
             break;
         }
    }
}


void finish_expression()
{
    for(int i = 0; i<=varStack->top; i++)
    {
        TVariable *var= varStack->data[i];
        free(var);
    }
    for(int i = 0; i<=iStack->top; i++)
    {
        TIData *var= iStack->data[i];
        free(var);
    }
    free(iStack);
    free(varStack);
}

void expression(TVariable *var)
{
    // //printf("**********************EXPRESSION**********************\n");

    thisFunction = NULL;
    if(!oStack)oStack = stackInit();
    if(!varStack)varStack = stackInit();
    iStack_init();
    if(!helper)helper = malloc(sizeof(Ttoken));
    if(!helper)ret_error(INTERNAL_ERROR);
    // printf("begin\n");
    if(funcContext)thisFunction = get_func_from_table(classContext, funcContext->name);
    
    if(thisFunction == NULL)
    {
        list = globalInitList;
    }
        
    else
    {
        list = thisFunction->list;
    }
    // //printf("%s\n",thisFunction->name);

    analysis(var);
    unget_token(1);
    printStacks();
    
    // for(int i = 0; i<=iStack->top; i++)
    // {
    //     TIData *var= iStack->data[i];
    //     free(var);
    // }
    // if(iStack)free(iStack);
    // free(helper);
    // printf("end\n");
    // }
    // //printf("********************END EXPRESSION*******************************\n");
    return;
}
