#include "lex.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT_OF_KEYWORDS 17

//globalni promene
        Ttoken *token;
FILE *file;
TBuffer *buffer;
TStack *tokenStack;
char *printToken();

#define line printf("LINE:%d\n",__LINE__);

//klicova slova
char *keywords[] ={"boolean","break","class","continue","do","double","else","false","for","if","int","return",
                   "String","static","true","void","while"};



int isKeyword(TBuffer *buffer)
{

    for(int i = 0; i < COUNT_OF_KEYWORDS; i++)
    {
        if(!(strcmp(buffer->data,keywords[i])))
        {
            buffer->data = keywords[i];
            return i;
        }
    }
    return -1;
}

TBuffer *bufferInit(TBuffer *buffer)
{

    buffer = malloc(sizeof(TBuffer));
    if(!buffer)
    {
        line
        ret_error(INTERNAL_ERROR);
    }

    buffer->capacity = 1;
    buffer->used = 0;
    return buffer;
}

TBuffer * extendBuffer(TBuffer *buffer, char c)
{
    buffer->data = realloc(buffer->data, buffer->capacity);
    if(!buffer)
    {
        line
        ret_error(INTERNAL_ERROR);
    }

    buffer->data[buffer->used] = c;
    buffer->capacity++;
    buffer->used++;
    return buffer;
}

void ungetToken(Ttoken * token)
{
    stackPush(tokenStack, token);
}

Ttoken *getTokenFromStack()
{
    token = stackTop(tokenStack);
    stackPop(tokenStack);
    return token;
}

void lexFinish()
{
    free(buffer);
    free(token);
    free(tokenStack);
    fclose(file);
}

Ttoken *getToken(){


    if(!tokenStack)
    {
        tokenStack = stackInit();
    }
    if(!stackEmpty(tokenStack))
    {
        return getTokenFromStack();
    }

    int state = STATE_INIT;
    int c;

    if(!token)
        token = malloc(sizeof(Ttoken));


    free(buffer);
    buffer = bufferInit(buffer);



    while( 1 )
    {
        c = fgetc(file);
        //printf("%c\n",c);
        switch( state )
        {

            case STATE_INIT:
            {
                //printf("%c is to come\n",c);
                if( c == EOF )
                {
                    token->type = TOKEN_EOF;
                    token->data = "END OF FILE";
                    return token;
                }
                if( c == '\n' )
                    break;
                if( c == ' ' )
                    break;
                if( isdigit(c) )
                {
                    extendBuffer(buffer, c);
                    state		= STATE_INT;
                    token->type = TOKEN_INT;
                    break;
                }
                if( isalpha(c) )
                {
                    extendBuffer(buffer, c);
                    state		= STATE_ID;
                    token->type = TOKEN_ID;
                    break;
                }
                if( c == '{' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_L_CURLY;
                    return token;
                }
                if( c == '}' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_R_CURLY;
                    return token;
                }
                if( c == '(' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_L_ROUND;
                    return token;
                }
                if( c == ')' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_R_ROUND;
                    return token;
                }
                if( c == '[' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_L_SQUARE;
                    return token;
                }
                if( c == ']' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_R_SQUARE;
                    return token;
                }
                if( c == '.' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_DOT;
                    return token;
                }
                if( c == '+' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_PLUS;
                    return token;
                }
                if( c == '-' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_MINUS;
                    return token;
                }

                if( c == '*' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_MUL;
                    return token;
                }
                if( c == '/' )
                {
                    extendBuffer(buffer, c);
                    state		= STATE_DIV;
                    token->type = TOKEN_DIV;
                    break;
                }
                if( c == ';' )
                {
                    extendBuffer(buffer, c);
                    token->data = buffer->data;
                    token->type = TOKEN_SEM_CL;
                    return token;
                }

                if( c == '<' )
                {
                    extendBuffer(buffer, c);
                    state = STATE_LESSER;
                    break;
                }

                if( c == '>' )
                {
                    extendBuffer(buffer, c);
                    state = STATE_GREATER;
                    break;
                }
                if( c == '=' )
                {
                    extendBuffer(buffer, c);
                    state = STATE_ASSIGN;
                    break;
                }

                if( c == '!' )
                {
                    extendBuffer(buffer, c);
                    state = STATE_EXCL_MARK;
                    break;
                }
                if( c == '"' )
                {
                    //not sure, should the apostrophe be included in the string?
                    state = STATE_STRING_DOUBLE;
                    break;
                }
                if( c == '\'' )
                {
                    state = STATE_STRING_SINGLE;
                    break;
                }
                if( c == ',' )
                {
                    extendBuffer(buffer, c);
                    token->type = TOKEN_COLON;
                    token->data = buffer->data;
                    return token;
                }
                //TODO \n \t \" a podobne srandy
                ret_error(LEX_ERROR);
                break;

            }
/********************************END FIRST STATE*****************************/
/********************************BEGIN NEXT STATE***************************/
            case STATE_INT:
            {
                if( isdigit(c) )
                {
                    extendBuffer(buffer, c);
                    break;
                }
                if( c == '.' )
                {
                    extendBuffer(buffer, c);
                    state = STATE_FUT_DOUBLE;
                    break;
                }
                if( c == 'e' )
                {
                    extendBuffer(buffer, c);
                    state = STATE_E;
                    break;
                }
                if( isalpha(c) )
                {
                    ret_error(LEX_ERROR);
                }
                token->data = buffer->data;
                token->type = TOKEN_INT;
                return token;

                line
                ret_error(LEX_ERROR);
            }

            case STATE_DEC_E:
            {
                if( isdigit(c) )
                {
                    extendBuffer(buffer, c);
                    break;
                }
                if( isalpha(c) )
                {
                    line
                    ret_error(SYNTAX_ERROR);
                }
                token->type = TOKEN_DEC_E;
                token->data = buffer->data;
                return token;
            }

            case STATE_E:
            {
                if( isdigit(c) )
                {
                    extendBuffer(buffer, c);
                    break;
                }
                if( isalpha(c) )
                {
                    ret_error(SYNTAX_ERROR);
                }
                token->type = TOKEN_E;
                token->data = buffer->data;
                return token;
            }

            case STATE_FUT_DOUBLE:
            {
                if( isdigit(c) )
                {
                    token->type = TOKEN_DOUBLE;
                    extendBuffer(buffer, c);
                    break;
                }
                if( c == 'e' )
                {
                    if( token->type != TOKEN_DOUBLE )
                    {
                        line
                        ret_error(SYNTAX_ERROR);
                    }
                    state = STATE_DEC_E;
                    break;
                }
                line
                ret_error(SYNTAX_ERROR);

            }

            case STATE_ID:
            {
                token->type = TOKEN_ID;
                if( isalnum(c) )
                {
                    extendBuffer(buffer, c);
                    break;
                }

                if( isKeyword(buffer) > 0 )
                {
                    token->type = isKeyword(buffer);
                }
                token->data = buffer->data;
                ungetc(c, file);
                return token;
                break;
            }

                // case STATE_PLUS:
                // {
                // 	if( c == '+')
                // 	{
                // 		extendBuffer(buffer, c);
                // 		state		= STATE_INC;
                // 		token->type = TOKEN_INC;
                // 		break;
                // 	}
                // 	state = STATE_END;
                // 	break;

                // }

                // case STATE_MINUS:
                // {
                // 	if( c == '-' )
                // 	{
                // 		extendBuffer(buffer, c);
                // 		state		= STATE_DEC;
                // 		token->type = TOKEN_DEC;
                // 		break;
                // 	}
                // 	state = STATE_END;
                // 	break;

                // }

                // case STATE_INC:
                // {
                // 	if( c == ';' )
                // 	{
                // 		ungetc(c, file);
                // 		state = STATE_END;
                // 		break;
                // 	}
                // 	line
                // 	ret_error(SYNTAX_ERROR);
                // }

                // case STATE_DEC:
                // {
                // 	if( c == ';' )
                // 	{
                // 		ungetc(c, file);
                // 		state = STATE_END;
                // 		break;
                // 	}
                // 	line
                // 	ret_error(SYNTAX_ERROR);
                // }

            case STATE_DIV:
            {
                if( c == '/' )
                {
                    state = STATE_LINE_COM;
                    break;
                }
                if( c == '*' )
                {
                    state = STATE_BEGIN_COM;
                    break;
                }
                break;
            }

            case STATE_LINE_COM:
            {
                if( c == '\n' || c == EOF )
                {
                    buffer = bufferInit(buffer);
                    state = STATE_INIT;
                    break;
                }
                break;
            }

            case STATE_BEGIN_COM:
            {
                if( c == '*' )
                {
                    state = STATE_END_COM;
                    break;
                }
                break;
            }

            case STATE_END_COM:
            {
                if( c == '/' )
                {
                    buffer = bufferInit(buffer);
                    state = STATE_INIT;
                    break;
                }
                state = STATE_BEGIN_COM;
                break;
            }

            case STATE_LESSER:
            {
                if( c == '=' )
                {
                    extendBuffer(buffer, c);
                    token->type = TOKEN_LE_EQ;
                    token->data = buffer->data;
                    return token;
                }
                ungetc(c, file);
                token->type = TOKEN_LESSER;
                token->data = buffer->data;
                return token;
            }

            case STATE_GREATER:
            {
                if( c == '=' )
                {
                    extendBuffer(buffer, c);
                    token->type = TOKEN_GR_EQ;
                    token->data = buffer->data;
                    return token;
                }
                ungetc(c, file);
                token->type = TOKEN_GREATER;
                token->data = buffer->data;
                return token;
            }

            case STATE_ASSIGN:
            {
                if( c == '=' )
                {
                    extendBuffer(buffer, c);
                    token->type = TOKEN_EQUALS;
                    token->data = buffer->data;
                    return token;
                }
                ungetc(c, file);
                token->type = TOKEN_ASSIGN;
                token->data = buffer->data;
                return token;
            }

            case STATE_EXCL_MARK:
            {
                if( c == '=' )
                {
                    extendBuffer(buffer, c);
                    token->type = TOKEN_NOT_EQ;
                    token->data = buffer->data;
                    return token;
                }
                line
                ret_error(SYNTAX_ERROR);
                ////////NOT SURE
            }

            case STATE_STRING_DOUBLE:
            {
                if( c == '\\')
                {
                    state = STATE_ASCII_DOUBLE;
                    break;
                }
                if( c != '"' )
                {
                    extendBuffer(buffer, c);
                    break;
                }

                token->type = TOKEN_STRING;
                token->data = buffer->data;
                return token;
                line
                ret_error(SYNTAX_ERROR);
                ////////NOT SURE
            }

            case STATE_STRING_SINGLE:
            {

                if( c == '\\' )
                {
                    state = STATE_ASCII_SINGLE;
                    break;
                }
                if( c != '\'' )
                {
                    extendBuffer(buffer, c);
                    break;
                }

                token->type = TOKEN_STRING;
                token->data = buffer->data;
                return token;
                line
                ret_error(SYNTAX_ERROR);
                ////////NOT SURE
            }
            case STATE_ASCII_SINGLE:
            {
                switch(c)
                {
                    case 'n':
                        extendBuffer(buffer, '\n');
                        state = STATE_STRING_SINGLE;
                        break;
                    case 't':
                        extendBuffer(buffer, '\t');
                        state = STATE_STRING_SINGLE;
                        break;
                    case '\'':
                        extendBuffer(buffer, '\'');
                        state = STATE_STRING_SINGLE;
                        break;
                    case '"':
                        extendBuffer(buffer, '"');
                        state = STATE_STRING_SINGLE;
                        break;
                    case '\\':
                        extendBuffer(buffer, '\\');
                        state = STATE_STRING_SINGLE;
                        break;
                    default:
                        ret_error(LEX_ERROR);
                }
                break;
            }

            case STATE_ASCII_DOUBLE:
            {
                switch(c)
                {
                    case 'n':
                        extendBuffer(buffer, '\n');
                        state = STATE_STRING_DOUBLE;
                        break;
                    case 't':
                        extendBuffer(buffer, '\t');
                        state = STATE_STRING_DOUBLE;
                        break;
                    case '\'':
                        extendBuffer(buffer, '\'');
                        state = STATE_STRING_DOUBLE;
                        break;
                    case '"':
                        extendBuffer(buffer, '"');
                        state = STATE_STRING_DOUBLE;
                        break;
                    case '\\':
                        extendBuffer(buffer, '\\');
                        state = STATE_STRING_DOUBLE;
                        break;
                    default:
                        ret_error(LEX_ERROR);
                }
                break;
            }



            default:
            {
                line
                ret_error(LEX_ERROR);
            }





        }


    }
}
