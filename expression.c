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

tStack *postfixStack, *opStack, *varStack;
Ttoken *token;

#define DEBUG
#ifdef DEBUG
void printStacks(){
    printf("Postfix\n");
    while(!stackEmpty(postfixStack))
    {
        token = stackTop(postfixStack);
        stackPop(postfixStack);
        printf("%s %d\n",token->data, token->type);
    }
    
    printf("opStack\n");
    while(!stackEmpty(opStack))
    {
        token = stackTop(opStack);
        stackPop(opStack);
        printf("%s %d\n",token->data, token->type);
    }
    
    printf("varstack\n");
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
        case PLUS: 
            return OP_PLUS;
        case MINUS:
            return OP_MINUS;
        case MUL:
            return OP_MUL;
        case DIV:
            return OP_DIVISION;
        case GREATER:
            return OP_GREATER;
        case LESSER:
            return OP_LESSER;
        case GR_EQ:
            return OP_GREQUAL;
        case LE_EQ:
            return OP_LEQUAL;
        case N_EQ:
            return OP_NOTEQUAL;
        case EQUALS:
            return OP_EQUAL;
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
    
   int lbracket = 0;
    while( 1 )
    //get token
    {
        Ttoken *helper;
        switch(token->type)
        {
            
            case INTGR:
            case DBLE:
            case ID:
            case N_DEC_E:
            case DEC_E:
            case DEC:
                stackPush(postfixStack, storeToken(token));
                break;
            case PLUS:
            case MINUS:
            case DIV:
            case MUL:
                if( hasBiggerPrio() )
                {
                    stackPush(opStack, storeToken(token));
                   
                    break;
                } 
                else
                {
                    while( !hasBiggerPrio() && !stackEmpty(opStack) )
                    {
                        stackPush(postfixStack, stackTop(opStack));
                        stackPop(opStack);
                    }
                
                    break;
                }
            case LB:
                lbracket++;
                stackPush(opStack, storeToken(token));
                break;
            case PB:
                while( 1 )
                {
                    helper = stackTop(opStack);
                    if( helper->type == LB)
                    {
                        stackPush(postfixStack, helper);
                        stackPop(opStack);
                        lbracket--;
                        break;
                    }
                    if( stackEmpty(opStack) )
                    {
                        //unget token
                        break;
                    }
                }
            case SEM_CL:
                
            default:
                printf("default\n");
        }
        token->type = SEM_CL;
    }
}

void expression(Ttoken *token)
{
    opStack = stackInit();
    postfixStack = stackInit();
    varStack = stackInit();
    
    //token = get_token();
    
    
    infixToPostfix();
    printStacks();
}