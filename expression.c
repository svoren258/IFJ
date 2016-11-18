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
/*!= */{'<','<','<','<','<','<','<','<','<','>','>','<'},
/* ( */{'<','<','<','<','<','<','<','<','<','<','<','<'},
/* ) */{'>','>','>','>','>','>','>','>','>','>','>','>'}

    
};

TStack *postfixStack, *opStack, *varStack;
Ttoken *token;

#define DEBUG
#ifdef DEBUG
void printStacks(){
    printf("-----\nPostfix\n");
    printf("vvvvvvvvvvvvv\n");
    while(!stackEmpty(postfixStack))
    {
        token = stackTop(postfixStack);
        stackPop(postfixStack);
        printf("%s %d\n",token->data, token->type);
    }
    
    printf("-----\nopStack\n");
    printf("vvvvvvvvvvvvv\n");
    while(!stackEmpty(opStack))
    {
        token = stackTop(opStack);
        stackPop(opStack);
        printf("%s %d\n",token->data, token->type);
    }
    
    printf("-----\nvarstack\n");
    printf("vvvvvvvvvvvvv\n");
    while(!stackEmpty(varStack))
    {
        token = stackTop(varStack);
        stackPop(varStack);
        printf("%s %d\n",token->data, token->type);
    }
        
        
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

Ttoken *storeToken(Ttoken * token)
{
    Ttoken * token_store;
    token_store = malloc(sizeof(Ttoken));
    token_store->data = token->data;
    token_store->type = token->type;
    return token_store;
}

//returns true if current Token has bigger priority than the top of the opStack
int hasBiggerPrio()
{
   printf("%c\n", precedence_table[ tokenToType(stackTop(opStack)) ][ tokenToType(token) ] );
    if( precedence_table[ tokenToType(stackTop(opStack)) ][ tokenToType(token) ] == '>' )
        return FALSE;
    return TRUE;
}

void infixToPostfix()
{
    
//   int lbracket = 0;
    while( 1 )
    //get token
    {
        token = get_token();
        // Ttoken *helper;
        switch(token->type)
        {
            
            // case TOKEN_DOUBLE:
            // case TOKEN_ID:
            // case TOKEN_E:
            // case TOKEN_DEC_E:
            // case TOKEN_INT:
            //     stackPush(postfixStack, storeToken(token));
            //     break;
            // case TOKEN_PLUS:
            // case TOKEN_MINUS:
            // case TOKEN_DIV:
            // case TOKEN_MUL:
            //     if( hasBiggerPrio() )
            //     {
            //         stackPush(opStack, storeToken(token));
                   
            //         break;
            //     } 
            //     else
            //     {
            //         while( !hasBiggerPrio() && !stackEmpty(opStack) )
            //         {
            //             stackPush(postfixStack, stackTop(opStack));
            //             stackPop(opStack);
            //         }
                
            //         break;
            //     }
            // case TOKEN_L_ROUND:
            //     lbracket++;
            //     stackPush(opStack, storeToken(token));
            //     break;
            // case TOKEN_R_ROUND:
            //     while( 1 )
            //     {
            //         helper = stackTop(opStack);
            //         if( helper->type == TOKEN_L_ROUND)
            //         {
            //             stackPush(postfixStack, helper);
            //             stackPop(opStack);
            //             lbracket--;
            //             break;
            //         }
            //         if( stackEmpty(opStack) )
            //         {
            //             //unget token
            //             break;
            //         }
            //     }
            case TOKEN_SEM_CL:
                unget_token(token);
                return;
            default:
                break;
        }
    }
}

int functionNewCall()
{
    if(token->type != TOKEN_ID)
        return FALSE;
    token = get_token();
    
    if(token->type != TOKEN_L_ROUND)
        return FALSE;
        
    token = get_token();
    if(token->type != TOKEN_R_ROUND)
        return FALSE;
        
    return TRUE;
        
}

int functionBuiltIn()
{
    if(token->type != TOKEN_ID)
        return FALSE;
    
    token = get_token();
    if(token->type != TOKEN_DOT)
        return FALSE;
        
    token = get_token();
    if(token->type != TOKEN_ID)
        return FALSE;
        
    token = get_token();
    if(token->type != TOKEN_L_ROUND)
        return FALSE;
        
    token = get_token();
    if(token->type == TOKEN_R_ROUND)
        return TRUE;
    return FALSE;
}

void expression(Ttoken *token, TVariable *var)
{
    opStack = stackInit();
    postfixStack = stackInit();
    varStack = stackInit();
    
    if(functionNewCall() || functionBuiltIn())
    {
        return;
    } else {
        infixToPostfix();
    }
    
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
    // printStacks();
}