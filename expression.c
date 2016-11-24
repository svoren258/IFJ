/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "expression.h"
#include "interpret.h"
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
Ttoken *token, *helper;
tTablePtr globTable;
tTablePtr exprFunc;
tTablePtr exprClass;
tTablePtr funcContext;
tTablePtr classContext;
TFunction *thisFunction;
int TOKENTYPE;

void iStack_push(int val)
{
    iStack->top++;
    iStack->data[iStack->top] = val;
}
void iStack_init()
{
    iStack = malloc(sizeof(TIStack));

    iStack->top = -1;
    iStack_push(OP_DOLAR);
}
//get the priority stack sign
int iStack_top_term()
{
    int b;
    for(int i = iStack->top; i >= 0; i--)
    {
        b = iStack->data[i];
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
        b = iStack->data[i];
        return (b);
    }
    line;
    return SIGN_FAIL;
}

int iStack_pop()
{
    if(iStack->top >= 0)
    {
        int ret = iStack->data[iStack->top];
        iStack->data[iStack->top] = '\0';
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
        b = iStack->data[i];
        if( b != OP_NONTERM )
        return (b);
    }
    return SIGN_FAIL;
}



void printStacks()
{
    #ifdef DEBUG
    printf("-----iStack-----\n");
    int b;
    for(int i = 0; i <= iStack->top; i++)
        {
            
            b = iStack->data[i];
            switch(b)
            {
                case OP_PLUS:
                s("+");
                break;
                
                case OP_MINUS:
                s("-");
                break;
                
                case OP_MUL:
                s("*");
                break;
                
                case OP_DIV:
                s("/");
                break;
                
                case OP_I:
                s("OP_I");
                break;
                
                case OP_NONTERM:
                s("E");
                break;
                
                case R_LESS:
                s("<");
                break;
                
                case OP_DOLAR:
                s("$");
                break;
                
                case OP_COMA:
                s(",");
                break;
                
                case OP_FUNC:
                s("func");
                break;
                
                
                case OP_LESS:
                s("'<'");
                break;
                
                case OP_LEQUAL:
                s("<=");
                break;
                 
                case OP_GREATER:
                s(">");
                break;
                
                case OP_GREQUAL:
                s(">=");
                break;
                
                case OP_EQUAL:
                s("==");
                break;
                
                case OP_NOTEQUAL:
                s("!=");
                break;
                
                
                case OP_LROUND:
                s("(");
                break;
                case OP_RROUND:
                s(")");
                break;
                default:break;
                // SIGN_LESS,//19
                // SIGN_GREATER,//20
                // SIGN_EQUALS,//21
            }
        }
    printf("\n-----/iStack----\n");
    
    printf("-----oStack-----\n");
    
    for(int i = oStack->top; i >= 0; i--)
        {
            TVariable *var = oStack->data[i];
            if(var->type == VARTYPE_INTEGER)
            {
                if(var->value.i)
                printf("%d\n",var->value.i);    
            }
            
            else if(var->type == VARTYPE_DOUBLE)
            {
                if(var->value.d)
                printf("%g\n",var->value.d);
            }
            
            else if(var->type == VARTYPE_STRING)
            {
                if(var->value.s)
                printf("%s\n",var->value.s);    
            }
            
        }
        
    printf("-----/oStack-----\n");
    
    // printf("-----varstack----\n");
    
    // for(int i = varStack->top; i >= 0; i--)
    //     {
    //         token = varStack->data[i];
    //         tok;
    //     }
    // printf("-----/varstack-----\n");    
        #endif
}

void generator(){
    
}

void push_params(int numOfParams)
{

   // TFunction *func;

    
    // TFunction *func;
    // printf("%s\n",exprFunc->name);
    // if((func = get_func_from_table(exprFunc, exprFunc->name))== NULL)
    // {
    //     printf("%s\n",func->name);
    //     line;
    //     ret_error(SYNTAX_ERROR);
    // }
    // else
    // {
    //     for(int i = 0; i < numOfParams; i++)
    //     {
    //         s("LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOL\n");
    //     }
    // }
}

int simple_reduction()
{s("REDUCTION BEGIN\n");
    int params = 0;
    int coma = 0;
    TVariable *var1;
    TVariable *var2;
    TVariable *result;
    if(iStack_top() == OP_I)//ID -> E
    {
        s("TRY REDUCTION ID -> E\n");
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
            {s("TRY REDUCTION (E) -> E\n");
                iStack_pop();
                if(iStack_top() == R_LESS)//(E) -> E
                {
                    iStack_pop();
                    iStack_push(OP_NONTERM);
                }
                else if(iStack_top() == OP_FUNC)//func(par) -> E
                {
                    params = 1;
                    iStack_pop();//func
                    iStack_pop();//<
                    iStack_push(OP_NONTERM);
                }
                else
                {
                    line;ret_error(SYNTAX_ERROR);
                }
            }
            else if(iStack_top() == OP_COMA)//func(par,par,...)
            {//already 1 param counted <- previous pop
            s("TRY REDUCTION func(,,) -> E\n");
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
                        line;
                        ret_error(SYNTAX_ERROR);
                    }
                    iStack_pop();
                }
                if(coma == 1)
                {
                    line;
                    ret_error(SYNTAX_ERROR);
                }
                if(iStack_top() == OP_LROUND)
                    iStack_pop();
                else
                {
                    line;
                    ret_error(SYNTAX_ERROR);
                }
                if(iStack_top() == OP_FUNC)
                {
                    iStack_pop();//func
                    iStack_pop();//< before func
                    //function call
                    push_params(params);
                    
                    
                    iStack_push(OP_NONTERM);
                }
            } else 
            {
                line;
                ret_error(SYNTAX_ERROR);
            }
            
        }
        
        else if(iStack_top() == OP_LROUND)//func() -> E
        {
            s("TRY REDUCTION func() -> E\n");
            iStack_pop();//<
            iStack_pop();//(
            iStack_pop();//func
            iStack_push(OP_NONTERM);
            //func call
        }
        else
        {
            line;
            ret_error(SYNTAX_ERROR);
        }
        printStacks();
    }
        
    if(iStack_top() == OP_NONTERM)//<E op E -> E
    {
        s("TRY REDUCTION <E op E -> E\n");
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
                var1 = stackPop(oStack);
                var2 = stackPop(oStack);
                result = generate_var(0);
                line;
                insert_instruction(thisFunction->list,create_instruction(iStack_top(),var1,var2,result));
                stackPush(oStack,result);
                printf("***REDUCTION COMPARE:E %d E***\n", iStack_pop());//OP
                if(iStack_top() != OP_NONTERM)
                {
                    line;
                    ret_error(SYNTAX_ERROR);
                }
                iStack_pop();//E
                
                if(iStack_top() >= 0 && iStack_top() <= 9)
                {
                    line;
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
  
        
    
    
    if(token->type == TOKEN_INT)
    {
        var->type = VARTYPE_INTEGER;
        var->value.i = atoi(token->data);
    }
        
    else if(token->type == TOKEN_STRING)
    {
        var->type = VARTYPE_STRING;
        var->value.s = token->data;
    }
        
    else if(token->type == TOKEN_DOUBLE)
    {
        var->type = VARTYPE_DOUBLE;
        var->value.d = strtod(token->data,NULL);
    }
    else
    {
        var->type = VARTYPE_NULL;
    }
    return var;
}





int tokenToType(Ttoken *token)
{
    char * TName;
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
            return R_LESS;
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
            token = get_token();
            TVariable *var = NULL;
            TFunction *func = NULL;
            
            //find class by name
            if((exprClass = BSTSearch(globTable->Root, TName)) == NULL)
            {
                exprClass = create_class_table(TName, globTable);
            }
            if(token->type == TOKEN_L_ROUND )
            {//func(..)
                if((func = get_func_from_table(classContext, TName)) == NULL)//this func might be defined in another class later
                {
                    new_function(token->data, classContext);//not gonna use return value from this or???
                }
                func = get_func_from_table(classContext, TName);
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
                        if((func = get_func_from_table(exprClass, TName)) == NULL)//this func might be defined in another class later
                        {
                            new_function(TName, exprClass);//not gonna use return value from this or???
                            line;
                        }
                        unget_token(1);
                        exprFunc = BSTSearch(exprClass->Root, TName);
                        return OP_FUNC;
                    }//class.func()
                    if(( var = get_var_from_table(exprClass, TName)) == NULL)//this var might be defined in another class later
                    {////class.var
                        token->data = TName;
                        var = new_variable( token, exprClass );
                        
                    }////class.var
                    stackPush(oStack, var);
                    
                    unget_token(1);
                    return OP_I;
                }
                else
                {
                    line;
                    ret_error(SYNTAX_ERROR);
                }
            }
            else
            {//var
                
                if(funcContext != NULL){
                if((var = get_var_from_table(funcContext, TName)) == NULL)
                {
                    if((var = get_var_from_table(classContext, TName)) == NULL)
                    {
                        line;
                        ret_error(SEMANTIC_DEF_ERROR);
                    }
                    // printf("%s\n",TName);line;line;
                }}
                stackPush(oStack, var);
                // if(!var)s("*****************************************************\n");
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

    // printf("%s %d \n",token->data, token->type);
    line;
    ret_error(SYNTAX_ERROR);
     return 0;
}

int compare_priority(int stackTop)
{
    // printf("\nINPUT***tok= %s type= %d  itop= %d\n\n",token->data,TOKENTYPE ,iStack_top_term());
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
            printf("BRACKETS:%d\n",brackets);
        }
        if(TOKENTYPE == OP_RROUND){
            brackets--;
            printf("BRACKETS:%d\n",brackets);
        }
        if(brackets < 0){
            printf("BRACKETS:%d RETURN\n",brackets);
            
        }
        // printf("TT:%d  Token:%d\n",TOKENTYPE, token->type);
        // if(TOKENTYPE!=token->type);
        printf("\nINPUT***tok= %s type= %d  itop= %d\n\n",token->data,TOKENTYPE ,iStack_top_term());
        // printf("%c\n",precedence_table[iStack_top_term()][TOKENTYPE]);
        switch(compare_priority(iStack_top_term()))
        {
            case SIGN_LESS:
                
                //id -> E
                printf("LESS: Ttype %d\n",TOKENTYPE);
                if(TOKENTYPE != OP_NONTERM)
                {
                    iStack_push (R_LESS);
                    iStack_push(TOKENTYPE);
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
                if(token->type == TOKEN_INT || token->type == TOKEN_DOUBLE || token->type == TOKEN_STRING)
                {
                    TVariable *var = generate_var(1);
                    stackPush(oStack, var);
                }
            
            break;
            
            case SIGN_GREATER:
            printf("GREATER: Ttype %d\n",TOKENTYPE);
//                if( brackets >= 0 )

                    simple_reduction();
                if(token->type != TOKEN_SEM_CL)
                {
                    if( TOKENTYPE == OP_RROUND && brackets > -1)//add ) to the stack
                    {
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
                        line;
                        ret_error(SYNTAX_ERROR);
                    }
                }
                break;
            
            case SIGN_EQUALS:
            printf("EQUALS Ttype %s\n",token->data);
            iStack_push(TOKENTYPE);//simply add according symbol
            

            break;
            
            default:
            printf("SWITCH DEFAULT TTYPE\n");
                if(iStack->top == 1 && iStack_top() == OP_NONTERM && token->type == TOKEN_SEM_CL)
                {
                    iStack_pop();    
                    insert_instruction(thisFunction->list, create_instruction(INS_ASSIGN,var,stackPop(oStack),NULL));
                    s("***********INS_ASSIGN************\n");
                    break;
                }
            break;
            
            
            
        }
        end++;
        
        
        
        if(( (token->type == TOKEN_SEM_CL) || (brackets==-1) ) && iStack->top == 0)
        {
            s("FINISHED EXPRESSION SUCCESFULLY!!!\n");
            return;//finished expression
        }
        
        if(token->type != TOKEN_SEM_CL )
        {
            if(token->type == TOKEN_R_ROUND && brackets < 0)    
                break;
            token = get_token();
        }
         if(end>70)
         {
             break;
         }
    }
}

void expression(TVariable *var)
{
    printf("**********************EXPRESSION**********************\n");
    oStack = stackInit();
    iStack_init();
    helper = malloc(sizeof(Ttoken));
    thisFunction = get_func_from_table(classContext, funcContext->name);
    
    printf("%s\n",thisFunction->name);

        analysis(var);
        unget_token(1);
        printStacks();

    // }
    printf("********************END EXPRESSION*******************************\n");
    return;
}