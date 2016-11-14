#include "expression.h"
#include "list.h"
#include "defs.h"

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
    token->type = ID;
    while( token->type != SEM_CL )
    //get token
    {
        switch(token->type)
        {
            case INTGR:
            case DBLE:
            case ID:
                printf("LOL\n");
                break;
            case PLUS:
            case MINUS:
            case DIV:
            case MUL:
            case MOD:
                printf("sign\n");
                break;
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
    
    TVariable *var;
    var = generateVar();
    
    var->name = "Variable";
    var = generateVar();
    var->name = "variable2";
    var = stackTop(varStack);
    printf("%s\n",var->name);
    stackPop(varStack);
    var = stackTop(varStack);
    printf("%s\n",var->name);
    // tList *insList;
    // insList = malloc(sizeof(tList));
    // InitList(insList);
    
    // tElemPtr newItem;
    // newItem = malloc(sizeof(struct tElem));
    // newItem->operation = MUL;
    // printf("%d\n",newItem->operation);
    // newItem->add3 = token->data;
    
    // printf("%s\n",newItem->add3);
    
    infixToPostfix();
}