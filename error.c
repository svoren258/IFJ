/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#include "error.h"
#include "defs.h"
Ttoken * token;
void ret_error(int error){
    switch(error)
    {
        case(LEX_ERROR):
            fprintf(stderr,"Lexical error on line !\n");
            break;
        case(SYNTAX_ERROR):
            fprintf(stderr,"Syntax error on line !\n");
            break;
        case(SEMANTIC_DEF_ERROR):
            fprintf(stderr,"Semantic definition error on line !\n");
            break;
        case(SEMANTIC_TYPE_ERROR):
            fprintf(stderr,"Semantic type error on line !\n");
            break;
        case(SEMANTIC_OTHER_ERROR):
            fprintf(stderr,"Semantic error on line !\n");
            break;
        case(INPUT_READ_ERROR):
            fprintf(stderr,"Error while input reading on line !\n");
            break;
        case(UNINIT_VAR_ERROR):
            fprintf(stderr,"Uninitialized variable on line !\n");
            break;
        case(ZERO_DIV_ERROR):
            fprintf(stderr,"Division by zero on line !\n");
            break;
        case(OTHER_RUNTIME_ERROR):
            fprintf(stderr,"Runtime error on line !\n");
            break;
        case(INTERNAL_ERROR):
            fprintf(stderr,"Internal error on line !\n");
            break;
    }
    // printf("error number: \n", error);
    exit(error);

}