/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
#include "expression.h"
#include "list.h"
#include "defs.h"
#include "error.h"

tTablePtr globTable;

char precedence_table[TABLESIZE][TABLESIZE] =
{/*st\in +   -   *   /   <  <=   >  >=  ==  !=   (   ) func  i   ,   $*/
/* + */{'>','>','<','<','>','>','>','>','>','>','<','>','<','<','<','>'},//0
/* - */{'>','>','<','<','>','>','>','>','>','>','<','>','<','<','<','>'},//1
/* * */{'>','>','>','>','>','>','>','>','>','>','<','>','<','<','<','>'},//2
/* / */{'>','>','>','>','>','>','>','>','>','>','<','>','<','<','<','>'},//3
/* < */{'<','<','<','<','>','<','<','<','>','>','<','>','<','<','<','>'},//4
/*<= */{'<','<','<','<','<','>','<','<','>','>','<','>','<','<','<','>'},//5
/* > */{'<','<','<','<','<','<','>','<','>','>','<','>','<','<','<','>'},//6
/*>= */{'<','<','<','<','<','<','<','>','>','>','<','>','<','<','<','>'},//7
/*== */{'<','<','<','<','<','<','<','<','>','<','<','>','<','<','<','>'},//8
/*!= */{'<','<','<','<','<','<','<','<','<','<','<','>','<','<','<','>'},//9
/* ( */{'<','<','<','<','<','<','<','<','<','<','=','=','<','<','=','$'},//10
/* ) */{'>','>','>','>','>','>','>','>','>','>','$','>','$','$','>','>'},//11
/*fun*/{'$','$','$','$','$','$','$','$','$','$','=','$','$','$','$','$'},//12
/* i */{'>','>','>','>','>','>','>','>','>','>','$','>','>','$','>','>'},//13
/* , */{'<','<','<','<','<','<','<','<','<','<','<','=','<','<',',','$'},//14
/* $ */{'<','<','<','<','<','<','<','<','<','<','<','$','<','<','<','$'},//15

    
};

TStack *oStack;
TIStack * iStack;
Ttoken *token;
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
                
                case OP_LESSER:
                s("<");
                break;
                
                case OP_DOLAR:
                s("$");
                break;
                
                default:break;
                
                // OP_MINUS,//1
                // OP_MUL,//2
                // OP_DIVISION,//3
            
                // OP_LESSER,//4
                // OP_LEQUAL,//5
                // OP_GREATER,//6
                // OP_GREQUAL,//7
                
                // OP_EQUAL,//8
                // OP_NOTEQUAL,//9
                
                // OP_LBRACKET,//10
                // OP_RBRACKET,//11
                // OP_FUNCTION,//12
                // OP_I,//13
                // OP_COMA,//14
                // OP_DOLAR,//15
                
                // OP_LROUND,//16
                // OP_RROUND,//17
                // OP_NONTERM,//18
                
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
{
    if(iStack_top() == OP_NONTERM)
    {
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
    if(isFunctionCall())return OP_FUNCTION;
    if(isFunctionFullNameCall())return OP_FUNCTION;
    if(isFullNameVar())return OP_I;
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
            return OP_LESSER;
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
        case TOKEN_INT:
        case TOKEN_DOUBLE:
        case TOKEN_STRING:
        case TOKEN_DOUBLE_E:
        case TOKEN_E:
        case TOKEN_ID:
            return OP_I;
        break;
    }
    
    line;
    ret_error(SYNTAX_ERROR);
     return 0;
}

int compare_priority(int stackTop, Ttoken * token)
{
    // if(iStack->top < 0)
        // return SIGN_DOLAR;
//   printf("%c\n", precedence_table[ tokenToType(stackTop(opStack)) ][ tokenToType(token) ] );
    if( precedence_table[ stackTop ][ tokenToType(token) ] == '$' )
    {
        printStacks();
        pint(stackTop);
        pint(tokenToType(token));
        return SIGN_FAIL;
    }
    
    if( precedence_table[ stackTop ][ tokenToType(token) ] == '>' )
        return SIGN_GREATER;
    else if( precedence_table[ stackTop ][ tokenToType(token) ] == '<' )
        return SIGN_LESSER; 
    else return SIGN_EQUALS;
}



int isFunctionCall()
{
    if(token->type != TOKEN_ID)
    {
        unget_token(1);
        return FALSE;
        
    }
        
    token = get_token();
    if(token->type != TOKEN_L_ROUND)
    {
        unget_token(2);
        return FALSE;
    }   
    unget_token(2);
    return OP_FUNCTION;
        
}

int isFunctionFullNameCall()
{   
    if(token->type != TOKEN_ID)
    {
        unget_token(1);
        return FALSE;
    }
        
    
    token = get_token();
    if(token->type != TOKEN_DOT)
    {
        unget_token(2);
        return FALSE;
    }
        
        
    token = get_token();
    if(token->type != TOKEN_ID)
    {
        unget_token(3);
        return FALSE;
    }
        
        
    token = get_token();
    if(token->type != TOKEN_L_ROUND)
    {
        unget_token(4);
        return FALSE;        
    }

   
    unget_token(4);
    return OP_FUNCTION;
}

int isFullNameVar()
{
    if(token->type != TOKEN_ID)
    {
        unget_token(1);
        return FALSE;
    }
        
    
    token = get_token();
    if(token->type != TOKEN_DOT)
    {
        unget_token(2);
        return FALSE;
    }
        
        
    token = get_token();
    if(token->type != TOKEN_ID)
    {
        unget_token(3);
        return FALSE;
    }
        
        
    token = get_token();
    if(token->type == TOKEN_L_ROUND)
    {
        unget_token(4);
        return FALSE;        
    }
    unget_token(4);
    return OP_I;
    
}

void analysis()
{
    // int helper;
    int end = 0;
    token = get_token();
    while( 1 )
    {
        
        // printStacks();
        printf("\ntok= %s  itop= %d\n\n",token->data, iStack_top_term());
        switch(compare_priority(iStack_top_term(), token))
        {
            case SIGN_LESSER:
                printf("Ttype %d\n",tokenToType(token));
                //id -> E
                
                if(tokenToType(token) != OP_NONTERM)
                {
                    iStack_push(OP_LESSER);
                    iStack_push(tokenToType(token));
                }
                
                else// if(iStack_top() == OP_NONTERM)
                {//E -> <E+
                        iStack_pop();
                        iStack_push(OP_LESSER);
                        iStack_push(OP_NONTERM);
                        iStack_push(tokenToType(token));
                }
                //
                if(token->type == TOKEN_INT || token->type == TOKEN_DOUBLE || token->type == TOKEN_STRING)
                {
                    TVariable *var = generate_var(1);
                    stackPush(oStack, var);
                }
                printStacks();
            
            break;
            
            case SIGN_GREATER:
                //ID -> E
                if(iStack_top() == OP_I)
                {
                    iStack_pop();
                    if(iStack_top() == OP_LESSER)
                    {
                        iStack_pop();
                        iStack_push(OP_NONTERM);
                    }
                } 
                //newly created E op E
                    simple_reduction();
                    
                if(token->type != TOKEN_SEM_CL)//E -> <E+
                {
                    if(iStack_top() == OP_NONTERM)
                    {
                        // return;
                        iStack_pop();
                        iStack_push(OP_LESSER);
                        iStack_push(OP_NONTERM);
                        iStack_push(tokenToType(token));
                        line;
                        break;
                    }
                    // helper = iStack_pop();
                    // iStack_push(OP_LESSER);//(<+
                    // iStack_push(tokenToType(token));
                }
                printStacks();
                break;
            
            case SIGN_EQUALS:
            line;
            iStack_push(tokenToType(token));
            break;
            
            default:
                if(iStack->top == 1 && iStack_top() == OP_NONTERM)
                {
                    iStack_pop();                    
                    line;
                    return;
                }
            
            
            
            
        }
        end++;
        if(iStack->top == -1)
        break;
        
        if(token->type != TOKEN_SEM_CL)
        {
            token = get_token();
            
        }
        
        
        if(end>10)break;
    }
}

void expression(TVariable *var)
{
    printf("***EXPRESSION***\n");
    oStack = stackInit();
    iStack_init();
    
    // if(isFunctionCall())
    //     line;
    // else if(isFunctionFullNameCall())
    // {
    //     line;
    // }
    // else
    // {
        analysis();
        printStacks();

    // }
    printf("***END EXPRESSION***\n");
    
}