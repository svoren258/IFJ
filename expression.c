/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "expression.h"

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
int TOKENTYPE;
int operands = 0,
    operators = 0;

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
        if(  (b != SIGN_LESSER  ) && (b != SIGN_EQUALS) && (b != SIGN_GREATER) && (b != OP_NONTERM))
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

#define DEBUG
#ifdef DEBUG
void printStacks()
{
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
                
                case R_LESSER:
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
                
                
                case OP_LESSER:
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
                // SIGN_LESSER,//19
                // SIGN_GREATER,//20
                // SIGN_EQUALS,//21
            }
        }
    printf("\n-----/iStack----\n");
    
    printf("-----oStack-----\n");
    
    for(int i = oStack->top; i >= 0; i--)
        {
            TVariable *var = oStack->data[i];
            printf("%d\n",var->value.i);
        }
    printf("-----/oStack-----\n");
    
    // printf("-----varstack----\n");
    
    // for(int i = varStack->top; i >= 0; i--)
    //     {
    //         token = varStack->data[i];
    //         tok;
    //     }
    // printf("-----/varstack-----\n");    
        
}
#endif
void generator(){
    
}

int simple_reduction()
{s("REDUCTION BEGIN\n");
    int params = 1;
    int coma = 0;
    if(iStack_top() == OP_I)//ID -> E
    {
        s("TRY REDUCTION ID -> E\n");
        iStack_pop();
        if(iStack_top() == R_LESSER)
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
                if(iStack_top() == R_LESSER)//(E) -> E
                {
                    iStack_pop();
                    iStack_push(OP_NONTERM);
                }
                else if(iStack_top() == OP_FUNC)//func(par) -> E
                {
                    iStack_pop();//func
                    iStack_pop();//<
                    iStack_push(OP_NONTERM);
                }
            }
            else if(iStack_top() == OP_COMA)
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
                if(iStack_top() == OP_LROUND)
                iStack_pop();
                if(iStack_top() == OP_FUNC)
                {
                    iStack_pop();//func
                    iStack_pop();//< before func
                    //function call
                    iStack_push(OP_NONTERM);
                }
            }
            
        }
        
        else if(iStack_top() == OP_LROUND)//func() -> E
        {
            s("TRY REDUCTION func() -> E\n");
            iStack_pop();//<
            iStack_pop();//(
            iStack_pop();//func
            iStack_push(OP_NONTERM);
        }
                // else if (iStack_top() == OP_LROUND)
                // {
                //     iStack_push(OP_NONTERM);
                // }
             
        // else if(iStack_top() == OP_COMA)//func(,,) -> E
        // {
        //     s("TRY REDUCTION func(,,) -> E\n");
        // }
        printStacks();
    }
        
    if(iStack_top() == OP_NONTERM)//<E op E -> E
    {
        s("TRY REDUCTION <E op E -> E\n");
        iStack_pop();//E
        switch(iStack_top())
        {
            
            case OP_PLUS:
            case OP_MINUS:
            case OP_MUL:
            case OP_DIV:
                printf("***REDUCTION:E %d E***\n", iStack_pop());//OP
                iStack_pop();//E
                iStack_pop();//<
                iStack_push(OP_NONTERM);
                printStacks();
                return TRUE;
            case    OP_LESSER:
            case    OP_LEQUAL:
            case    OP_GREATER:
            case    OP_GREQUAL:
            case    OP_EQUAL:
            case    OP_NOTEQUAL:
                printf("***REDUCTION COMPARE:E %d E***\n", iStack_pop());//OP
                iStack_pop();
                iStack_pop();
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
    return var;
}





int tokenToType(Ttoken *token)
{
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
        case TOKEN_LESSER:
            return R_LESSER;
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
            token = get_token();
            if(token->type == TOKEN_L_ROUND )
            {
                unget_token(1);
                return OP_FUNC;
            } 
            else if(token->type == TOKEN_DOT )
            {
                token = get_token();
                if( token->type == TOKEN_ID )
                {
                    token = get_token();
                    if(token->type == TOKEN_L_ROUND)
                    {
                        unget_token(1);
                        return OP_FUNC;
                    }
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
            {
                unget_token(1);
                return OP_I;
            }
            
            
        case TOKEN_INT:
        case TOKEN_DOUBLE:
        case TOKEN_STRING:
        case TOKEN_DOUBLE_E:
        case TOKEN_E:
            return OP_I;
        break;
    }

    tok;    
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
        return SIGN_LESSER; 
    else return SIGN_EQUALS;
}



// int isFunctionCall()
// {
//     if(token->type != TOKEN_ID)
//     {
//         unget_token(1);
//         return FALSE;
        
//     }
        
//     token = get_token();
//     if(token->type != TOKEN_L_ROUND)
//     {
//         unget_token(2);
//         return FALSE;
//     }   
//     unget_token(2);
//     return OP_FUNCTION;
        
// }

// int isFunctionFullNameCall()
// {   
//     if(token->type != TOKEN_ID)
//     {
//         unget_token(1);
//         return FALSE;
//     }
        
    
//     token = get_token();
//     if(token->type != TOKEN_DOT)
//     {
//         unget_token(2);
//         return FALSE;
//     }
        
        
//     token = get_token();
//     if(token->type != TOKEN_ID)
//     {
//         unget_token(3);
//         return FALSE;
//     }
        
        
//     token = get_token();
//     if(token->type != TOKEN_L_ROUND)
//     {
//         unget_token(4);
//         return FALSE;        
//     }

   
    //unget_token(4);
    // return TRUE;
// }

// int isFullNameVar()
// {
//     if(token->type != TOKEN_ID)
//     {
//         unget_token(1);
//         return FALSE;
//     }
        
    
//     token = get_token();
//     if(token->type != TOKEN_DOT)
//     {
//         unget_token(2);
//         return FALSE;
//     }
        
        
//     token = get_token();
//     if(token->type != TOKEN_ID)
//     {
//         unget_token(3);
//         return FALSE;
//     }
        
        
//     token = get_token();
//     if(token->type == TOKEN_L_ROUND)
//     {
//         unget_token(4);
//         return FALSE;        
//     }
//     unget_token(4);
//     return OP_I;
    
// }

void analysis()
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
            case SIGN_LESSER:
                
                //id -> E
                printf("LESSER: Ttype %d\n",TOKENTYPE);
                if(TOKENTYPE != OP_NONTERM)
                {
                    iStack_push (R_LESSER);
                    iStack_push(TOKENTYPE);
                    printStacks();
                }
                
                else
                {//E -> <E+
                        iStack_pop();
                        iStack_push(R_LESSER);
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
                simple_reduction();
                if(token->type != TOKEN_SEM_CL)
                {
                    if( TOKENTYPE == OP_RROUND && brackets != -1)//add ) to the stack
                    {
                        iStack_push(OP_RROUND);
                        printStacks();
                    }
                    else if(iStack_top() == OP_NONTERM && brackets != -1)//E -> <E+
                    {
                        iStack_pop();
                        if(TOKENTYPE != OP_COMA)//if coma, do not insert less sign
                            iStack_push (R_LESSER);
                        iStack_push(OP_NONTERM);
                        iStack_push(TOKENTYPE);
                        printStacks();
                        break;
                    }
                }line;
                break;
            
            case SIGN_EQUALS:
            printf("EQUALS Ttype %s\n",token->data);
            iStack_push(TOKENTYPE);//simply add according symbol
            

            break;
            
            default:
            printf("FAIL TTYPE\n");
                if(iStack->top == 1 && iStack_top() == OP_NONTERM && token->type == TOKEN_SEM_CL)
                {
                    iStack_pop();                    
                    break;
                }
            break;
            
            
            
        }
        end++;
        
        if(token->type != TOKEN_SEM_CL )
        {
            if(token->type == TOKEN_R_ROUND && brackets < 0)    
                break;
            token = get_token();
        }
        //  else if(token->type != TOKEN_R_ROUND || brackets >= 0)
        // {
        //     token = get_token();
        // }
        
        if(( (token->type == TOKEN_SEM_CL) || (brackets==-1) ) && iStack->top == 0)
        {
            s("FINISHED EXPRESSION SUCCESFULLY!!!\n");
            break;//finished expression
        }
        if(end>70)break;
    }
}

void expression(TVariable *var)
{
    printf("***EXPRESSION***\n");
    oStack = stackInit();
    iStack_init();
    helper = malloc(sizeof(Ttoken));
    // if(isFunctionCall())
    //     line;
    // else if(isFunctionFullNameCall())
    // {
    //     line;
    // }
    // else
    // {
        analysis();
        unget_token(1);
        printStacks();

    // }
    printf("***END EXPRESSION***\n");
    return;
}