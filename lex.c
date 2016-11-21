/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/

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
int lineNumber = 1;
int ungetTokenIndex = -1;


//klicova slova
char *keywords[] ={"boolean","break","class","continue","do","double","else","false","for","if","int","return",
                   "String","static","true","void","while"};



int isKeyword(TBuffer *buffer)
{
	if(buffer->used < 2)
		return -1;

    for(int i = 0; i < COUNT_OF_KEYWORDS; i++)
    {
        if(!(strcmp(buffer->data,keywords[i])))
        {
            //buffer->data = keywords[i];
            return i;
        }
    }
    return -1;
}

int bufferInit()
{
	buffer = malloc(sizeof(TBuffer));
    if ((buffer->data = (char*) malloc(STR_LEN_INC)) == NULL)
      return STR_ERROR;
   buffer->data[0] = '\0';
   buffer->used = 0;
   buffer->capacity = STR_LEN_INC;
   return STR_SUCCESS;
}

void bufferClear(TBuffer *s)
// funkce vymaze obsah retezce
{
   s->data[0] = '\0';
   s->used = 0;
}

int  extendBuffer(TBuffer *s1, char c)
{
	if (s1->used + 1 >= s1->capacity)
   {
      // pamet nestaci, je potreba provest realokaci
      if ((s1->data = (char*) realloc(s1->data, s1->used + STR_LEN_INC)) == NULL)
         return STR_ERROR;
      s1->capacity = s1->used + STR_LEN_INC;
   }
   s1->data[s1->used] = c;
   s1->used++;
   s1->data[s1->used] = '\0';
   return STR_SUCCESS;
}

void unget_token(int y)
{
	for(int i = y; i > 0; i--)
	{
		if(ungetTokenIndex >= 1)
			ungetTokenIndex--;
	}
	
}

void pushToken(Ttoken * token)
{
	if(ungetTokenIndex <= 9)
		ungetTokenIndex++;
	
	if(tokenStack->top >= 9)
	{
		for(int i = 0; i <= tokenStack->top - 1; i++)
		{
			tokenStack->data[i] = tokenStack->data[i+1];
			
		}
		tokenStack->data[tokenStack->top] = token;	
		return;
	}
	stackPush(tokenStack, token);
	
}

Ttoken * getTokenFromStack()
{
	// printf("Ungetindex:%d\n",ungetTokenIndex);
	// printf("TOKENSTACK\n");
	// for(int i = tokenStack->top; i >= 0; i--)
	// {
	// 	token = tokenStack->data[i];
	// 	printf("%s \t%d\n",token->data, i);
		
	// }
	// printf("TOKENSTACK\n");
	ungetTokenIndex++;
	token = tokenStack->data[ungetTokenIndex];
	return token;
}

void lexStart()
{

	if(!tokenStack)
		tokenStack = stackInit();
	if(!token)		
		token = malloc(sizeof(Ttoken));
	if(!buffer)
		bufferInit();
}

void lexFinish()
{
	
	free(buffer);
	free(token);
	free(tokenStack);
	fclose(file);
}

Ttoken *get_token(){
	
	if(ungetTokenIndex < tokenStack->top && (ungetTokenIndex > -1))
	{
		// printf("next token is unget ");
		// return getTokenFromStack();
	}
	
	int state = STATE_INIT;
	int c;
	
	
	// if(buffer)
	// {
	// 	char* let = buffer->data;
	// 	free(let);
	// 	free(buffer);	
	// }
	token = malloc(sizeof(Ttoken));
	bufferInit(buffer);
	
	
	
	while( 1 )
	{
		token->lineNumber = lineNumber;
		c = fgetc(file);
		// printf("lex:%c\n",c);
		switch( state )
		{
			
			case STATE_INIT:
			{
				// printf("%c\n",c);
				//printf("%c is to come\n",c);
				if( c == EOF )
				{
					token->type = TOKEN_EOF;
					token->data = "END OF FILE";
					return token;
				}
				if( c == '\n' )
				{
					lineNumber++;					
					break;
				}
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
					
					pushToken(token);
					return token;
				}
				if( c == '}' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_R_CURLY;
					pushToken(token);
					return token;
				}
				if( c == '(' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_L_ROUND;
					pushToken(token);
					return token;
				}
				if( c == ')' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_R_ROUND;
					pushToken(token);
					return token;
				}
				if( c == '[' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_L_SQUARE;
					pushToken(token);
					return token;
				}
				if( c == ']' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_R_SQUARE;
					pushToken(token);
					return token;
				}
				if( c == '.' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_DOT;
					pushToken(token);
					return token;
				}
				if( c == '+' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_PLUS;
					pushToken(token);
					return token;
				}
				if( c == '-' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_MINUS;
					pushToken(token);
					return token;
				}
				
				if( c == '*' )
				{
					extendBuffer(buffer, c);
					token->data = buffer->data;
					token->type = TOKEN_MUL;
					pushToken(token);
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
					pushToken(token);
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
				// if( c == '\'' )
				// {
				// 	state = STATE_STRING_SINGLE;
				// 	break;
				// }
				if( c == ',' )
				{
					extendBuffer(buffer, c);
					token->type = TOKEN_COLON;
					token->data = buffer->data;
					pushToken(token);
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
				ungetc(c, file);
				token->data = buffer->data;
				token->type = TOKEN_INT;
				pushToken(token);
				return token;
		
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
					line;
					ret_error(SYNTAX_ERROR);
				}
				ungetc(c, file);
				token->type = TOKEN_DEC_E;
				token->data = buffer->data;
				pushToken(token);
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
				ungetc(c, file);
				token->type = TOKEN_E;
				token->data = buffer->data;
				pushToken(token);
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
						line;
						ret_error(SYNTAX_ERROR);
					}
					state = STATE_DEC_E;
					break;
				}
				line;
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
				 	switch(token->type)
				 	{
				 		case KEYWORD_INT:
				 		case KEYWORD_DOUBLE:
				 		case KEYWORD_STRING:
				 			token->data = buffer->data;
				 			token->type = TOKEN_TYPE;
				 			return token;
				 	}
				 }

				if( isKeyword(buffer) > 0 )
				{
					token->type = isKeyword(buffer);
					switch(token->type)
					{
						case KEYWORD_INT:
						case KEYWORD_DOUBLE:
						case KEYWORD_STRING:
							token->data = buffer->data;
							token->type = TOKEN_TYPE;
							pushToken(token);
							
							return token;
					}
				}

				
				token->data = buffer->data;
				ungetc(c, file);
				pushToken(token);
				return token;
				
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
				ungetc(c, file);
				token->data = buffer->data;
				pushToken(token);
				return token;
				
			}
			
			case STATE_LINE_COM:
			{
				if( c == '\n' || c == EOF )
				{
					bufferClear(buffer);
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
					bufferClear(buffer);
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
					pushToken(token);
					return token;
				}
				ungetc(c, file);
				token->type = TOKEN_LESSER;
				token->data = buffer->data;
				pushToken(token);
				return token;
			}
			
			case STATE_GREATER:
			{
				if( c == '=' )
				{
					extendBuffer(buffer, c);
					token->type = TOKEN_GR_EQ;
					token->data = buffer->data;
					pushToken(token);
					return token;
				}
				ungetc(c, file);
				token->type = TOKEN_GREATER;
				token->data = buffer->data;
				pushToken(token);
				return token;
			}
			
			case STATE_ASSIGN:
			{
				if( c == '=' )
				{
					extendBuffer(buffer, c);
					token->type = TOKEN_EQUALS;
					token->data = buffer->data;
					pushToken(token);
					return token;
				}
				ungetc(c, file);
				token->type = TOKEN_ASSIGN;
				token->data = buffer->data;
				pushToken(token);
				return token;
			}
			
			case STATE_EXCL_MARK:
			{
				if( c == '=' )
				{
					extendBuffer(buffer, c);
					token->type = TOKEN_NOT_EQ;
					token->data = buffer->data;
					pushToken(token);
					return token;
				}
				line;
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
				pushToken(token);
				return token;
				line;
				ret_error(SYNTAX_ERROR);
				////////NOT SURE
			}
			
			// case STATE_STRING_SINGLE:
			// {
				
			// 	if( c == '\\' )
			// 	{
			// 		state = STATE_ASCII_SINGLE;
			// 		break;
			// 	}
			// 	if( c != '\'' )
			// 	{
			// 		extendBuffer(buffer, c);
			// 		break;
			// 	}
				
			// 	token->type = TOKEN_STRING;
			// 	token->data = buffer->data;
			// 	return token;
			// 	line;
			// 	ret_error(SYNTAX_ERROR);
			// 	////////NOT SURE
			// }
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
					// case '\'':
					// 	extendBuffer(buffer, '\'');
					// 	state = STATE_STRING_SINGLE;
					// 	break;
					case '"':
						extendBuffer(buffer, '"');
						state = STATE_STRING_SINGLE;
						break;
					case '\\':
						extendBuffer(buffer, '\\');
						state = STATE_STRING_SINGLE;
						break;
					// case OCTAL!!!!!!!!
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
				line;
				ret_error(LEX_ERROR);	
			}
			
			
			
			
			
		}
			
		
	}
}