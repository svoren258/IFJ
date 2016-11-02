#include "expression.h"

int token_to_type(char c)
{
    switch(c)
    {
        case '+': 
            return OP_PLUS;
        case '-':
            return OP_MINUS;
        
    }
    printf("%d\n",OP_PLUS);
    return 44;
}

int has_bigger_prio(char stack_top, char c)
{
    c = '+';
    if(token_to_type(c) == 0)
    dbl;
    if(token_to_type(c) )
    return 1;
}

void expression(Ttoken *token)
{
    
    has_bigger_prio('+', '-');
    
    
    
}