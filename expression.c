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

char precedence_table[12][12] =
{/*st\in +   -   *   /   <  <=   >  >=  ==  !=   (   )  */
/* + */{'>','>','<','<','>','>','>','>','>','>','>','<'},
/* - */{'>','>','<','<','>','>','>','>','>','>','>','<'},
/* * */{'>','>','>','>','>','>','>','>','>','>','>','<'},
/* / */{'>','>','>','>','>','>','>','>','>','>','>','<'},
/* < */{'<','<','<','<','>','<','<','<','>','>','>','<'},
/*<= */{'<','<','<','<','<','>','<','<','>','>','>','<'},
/* > */{'<','<','<','<','<','<','>','<','>','>','>','<'},
/*>= */{'<','<','<','<','<','<','<','>','>','>','>','<'},
/*== */{'<','<','<','<','<','<','<','<','>','<','>','<'},
/*!= */{'<','<','<','<','<','<','<','<','<','#','>','<'},
/* ( */{'#','#','#','#','#','#','#','#','#','#','<','<'},
/* ) */{'>','>','>','>','>','>','>','>','>','>','#','>'}

    
};

TStack *postfixStack, *opStack, *varStack;
Ttoken *token;
int operands = 0,
    operators = 0;



#define DEBUG
#ifdef DEBUG
void printStacks(){
    printf("-----Postfix-----\n");
    
    for(int i = postfixStack->top; i >= 0; i--)
        {
            token = postfixStack->data[i];
            tok;
        }
    printf("-----/postfix----\n");
    
    printf("-----opStack-----\n");
    
    for(int i = opStack->top; i >= 0; i--)
        {
            token = opStack->data[i];
            tok;
        }
    printf("-----/opstack-----\n");
    
    printf("-----varstack----\n");
    
    for(int i = varStack->top; i >= 0; i--)
        {
            token = varStack->data[i];
            tok;
        }
    printf("-----/varstack-----\n");    
        
}
#endif
void generator(){
    
}

TVariable *generateVar()
{
    TVariable *newVar;
    newVar = malloc(sizeof(TVariable));
    stackPush(varStack, newVar);
    return newVar;
}

int tokenToType(Ttoken *token)
{
    switch(token->type)
    {
        case TOKEN_PLUS: 
            return OP_PLUS;
        case TOKEN_MINUS:
            return OP_MINUS;
        case TOKEN_MUL:
            return OP_MUL;
        case TOKEN_DIV:
            return OP_DIVISION;
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
        default:
            break;
    }
   
    return 42;
}

// Ttoken *storeToken()
// {
//     Ttoken * token_store;
//     token_store = malloc(sizeof(Ttoken));

//     if(!token_store)
//         ret_error(INTERNAL_ERROR);
    
//     token_store->data = token->data;
//     token_store->type = token->type;
            
        
//     return token_store;
// }

//returns true if current Token has bigger priority than the top of the opStack
int hasBiggerPrio()
{
    if(stackEmpty(opStack))
        return TRUE;
//   printf("%c\n", precedence_table[ tokenToType(stackTop(opStack)) ][ tokenToType(token) ] );
    if( precedence_table[ tokenToType(stackTop(opStack)) ][ tokenToType(token) ] == '#' )
    {
        line;
        ret_error(SYNTAX_ERROR);
    }
    
    if( precedence_table[ tokenToType(stackTop(opStack)) ][ tokenToType(token) ] == '>' )
        return FALSE;
    return TRUE;
}

void check_expression_form()
{   
    if((operands - 1) != operators)
        {
            line;
            ret_error(SYNTAX_ERROR);
        }
    }

void infixToPostfix()
{
    operands = 0,
    operators = 0;
    int compare_operators = 0;
    //tTablePtr table = context;
    int lbrackets = 0;
    while( 1 )
    //get token
    {
        token = get_token();
        
        printf("%s\n",token->data);
        // Ttoken *helper;
        switch(token->type)
        {
            case TOKEN_ID:
            operands++;
                unget_token(1);
                if(isFunctionCall())
                {
                    
                    get_token();
                    token->type = TOKEN_FUNCTION;
                    stackPush(postfixStack,token);
                    get_token();
                    get_token();
                    break;
                }
                if(isFunctionFullNameCall())
                {
                    get_token();
                    token->type = TOKEN_FUNCTION;
                    stackPush(postfixStack,token);
                    get_token();get_token();get_token();get_token();
                    break;
                }
                if(isFullNameVar())
                {
                    get_token();get_token();get_token();
                    stackPush(postfixStack, token);
                    break;
                }
                get_token();
                stackPush(postfixStack, token);
                break;
            case TOKEN_DOUBLE:
            case TOKEN_E:
            case TOKEN_DEC_E:
            case TOKEN_INT:
            case TOKEN_STRING:
                operands++;
                stackPush(postfixStack, token);
                break;
            case TOKEN_PLUS:
            case TOKEN_MINUS:
            case TOKEN_DIV:
            case TOKEN_MUL:
                operators++;
                if( hasBiggerPrio() )
                {
                    stackPush(opStack, token);
                    break;
                } 
                else
                {
                    while( !hasBiggerPrio() && !stackEmpty(opStack) )
                    {
                        stackPush(postfixStack, stackTop(opStack));
                        stackPop(opStack);
                    }
                    stackPush(opStack, token);
                    break;
                }
            case TOKEN_EQUALS:
            case TOKEN_GREATER:
            case TOKEN_LESSER:
            case TOKEN_GR_EQ:
            case TOKEN_LE_EQ:
            case TOKEN_EXCL_MARK:
            case TOKEN_NOT_EQ:
                compare_operators++;
                if(compare_operators > 1)
                {
                    line;
                    ret_error(SYNTAX_ERROR);
                }
                operators++;
                if( hasBiggerPrio() )
                {
                    stackPush(opStack, token);
                    break;
                } 
                else
                {
                    while( !hasBiggerPrio() && !stackEmpty(opStack) )
                    {
                        stackPush(postfixStack, stackTop(opStack));
                        stackPop(opStack);
                    }
                    stackPush(opStack, token);
                    break;
                }
            case TOKEN_L_ROUND:
                hasBiggerPrio();
                lbrackets++;
                stackPush(opStack, token);
                break;
            case TOKEN_R_ROUND:
                while( 1 )
                {
                    // printf("opstck\n");
                    // for(int i = opStack->top; i >= 0; i--)
                    // {
                    //     token = opStack->data[i];
                    //     tok;
                    // }printf("opstck\n");
                    token = stackTop(opStack);
                    if( lbrackets <= 0 )
                    {
                        hasBiggerPrio();
                        unget_token(1);
                        printf("operands: %d | operators: %d\n",operands, operators);
                        return;
                    }
                    
                    if( token->type != TOKEN_L_ROUND)
                    {
                        stackPush(postfixStack, token);
                        stackPop(opStack);
                        
                        continue;
                    }
                    lbrackets--;
                    stackPop(opStack);
                    break;
                        
                    
                }
                break;
            case TOKEN_SEM_CL:
                unget_token(1);
                printf("operands: %d | operators: %d\n",operands, operators);
                return;
            default:
                line;
                ret_error(SYNTAX_ERROR);
                break;
        }
    }
}

void emptyOpStack()
{
    while( !stackEmpty(opStack) )
    {
        token = stackTop(postfixStack);
        stackPush(postfixStack, stackTop(opStack));
        stackPop(opStack);
    }
}

int isFunctionCall()
{
    token = get_token();
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
    return TRUE;
        
}

int isFunctionFullNameCall()
{   
    token = get_token();
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
    return TRUE;
}

int isFullNameVar()
{
    token = get_token();
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
    return TRUE;   
    
}


void expression(TVariable *var)
{
    printf("***EXPRESSION***\n");
    opStack = stackInit();
    postfixStack = stackInit();
    varStack = stackInit();
    
    if(isFunctionCall())
        line;
    else if(isFunctionFullNameCall())
    {
        line;
    }
    else
    {
        infixToPostfix();
        emptyOpStack();
        check_expression_form();
        printStacks();
        
        
    }
    printf("***END EXPRESSION***\n");
    // token->data = "ahoj";
    // stackPush(opStack, storeToken(token));
    // token->data = "ahog";
    // stackPush(opStack, storeToken(token));
    // token->data = "ahoh";
    // stackPush(opStack, storeToken(token));
    
    // token->data = "POSTFIXTSKA";
    // stackPush(postfixStack, storeToken(token));
    
    // while(!stackEmpty(opStack))
    // {
    //     stackPush(postfixStack, stackTop(opStack));
    //     stackPop(opStack);
    // }
    
    //infixToPostfix();
    
}