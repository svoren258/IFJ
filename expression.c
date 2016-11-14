#include "expression.h"

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

tStack *postfixStack, *opStack;
Ttoken *token;



int token_to_type(Ttoken *token)
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
   printf("BUG\n");
    return 42;
}

Ttoken *store_token(Ttoken * token)
{
    Ttoken * token_store;
    token_store = malloc(sizeof(Ttoken));
    token_store->data = token->data;
    token_store->type = token->type;
    return token_store;
}

int has_bigger_prio()
{
   printf("%c\n", precedence_table[ token_to_type(stackTop(opStack)) ][ token_to_type(token) ] );
    if( precedence_table[ token_to_type(stackTop(opStack)) ][ token_to_type(token) ] == '>' )
        return FALSE;
    return TRUE;
}

void expression(Ttoken *token)
{
    opStack = stackInit();
    postfixStack = stackInit();
    
    token->type = PLUS;
    stackPush(opStack,store_token(token));
    
    
    token->type = MUL;
    //printf("%d %d\n",MUL, PLUS);
    if( has_bigger_prio() )
        printf("is bigger prio\n");
    else
        printf("is lower prio\n");
    
}