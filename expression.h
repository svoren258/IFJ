#include "defs.h"
#include "lex.h"

#ifndef EXPRESSION_H
#define EXPRESSION_H

// char  predence_table[4][4] =
// { /*    +   -   *   /  */
// /* + */{'>','>','<','<'},
// /* - */{'>','>','<','<'},
// /* * */{'>','>','>','>'},
// /* / */{'>','>','>','>'}
    
// };

enum{
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLICATION,
    OP_DIVISION
    
    
    
};
void expression(Ttoken *token);

#endif