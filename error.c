/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ14        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

#include "error.h"

void ret_error(int error){
    switch(error)
    {
        case(LEX_ERROR):
            fprintf(stderr,"Lexical error!\n");
            break;
        case(SYNTAX_ERROR):
            fprintf(stderr,"Syntax error!\n");
            break;
        case(SEMANTIC_DEF_ERROR):
            fprintf(stderr,"Semantic definition error!\n");
            break;
        case(SEMANTIC_TYPE_ERROR):
            fprintf(stderr,"Semantic type error!\n");
            break;
        case(SEMANTIC_OTHER_ERROR):
            fprintf(stderr,"Semantic error!\n");
            break;
        case(INPUT_READ_ERROR):
            fprintf(stderr,"Error while input reading!\n");
            break;
        case(UNINIT_VAR_ERROR):
            fprintf(stderr,"Uninitialized variable!\n");
            break;
        case(ZERO_DIV_ERROR):
            fprintf(stderr,"Division by zero!\n");
            break;
        case(OTHER_RUNTIME_ERROR):
            fprintf(stderr,"Runtime error!\n");
            break;
        case(INTERNAL_ERROR):
            fprintf(stderr,"Internal error!\n");
            break;
    }
    exit(error);
}