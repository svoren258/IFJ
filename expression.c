#include "expression.h"

char predence_table[12][12] =
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
/* ( */{'<','<','<','<','<','<','<','<','<','<','>','<'},
/* ) */{'>','>','>','>','>','>','>','>','>','>','>','<'}

    
};

tStack *postfix, *opstack;
Ttoken *token;
Ttoken * token2;


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
    return 44;
}

int has_bigger_prio()
{
   printf("%c\n",predence_table[ token_to_type(stackTop(opstack)) ][ token_to_type(token2) ]);
    printf("%d %d\n",token_to_type(stackTop(opstack)), token_to_type(token2) );
    return 55;
}

void expression(Ttoken *token)
{
    opstack = stackInit();
    postfix = stackInit();
    
    token->type = MUL;
    stackPush(opstack,token);
    
    token2 = malloc(sizeof(Ttoken));
    token2->type = PLUS;
    //printf("%d %d\n",MUL, PLUS);
    has_bigger_prio();
    
}