#include "lex.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT_OF_KEYWORDS 17

//globalni promene
Ttoken token;
FILE *file;

char *printToken();



//klicova slova
char *keywords[] ={"boolean","break","class","continue","do","double","else","false","for","if","int","return",
	"String","static","true","void","while"};

void IsKeyword(Ttoken *token)
{

	for(int i = 0; i < COUNT_OF_KEYWORDS; i++)
	{
		if(!(strcmp(token->data,keywords[i])))
		{
			token->type = KEYWORDS;
			return;
		}
	}
}

//funkce rozsiri token
int ExtendToken(Ttoken *token, unsigned length)
{
	if(length >= token->len){
		token->len += 20;
		token->data = realloc(token->data, token->len);
		if(token->data == NULL)
		{
			return -1;
		}
		else
		{

			return 0;
		}
	}
	return -23402459;
	//FIX THIS!!!
}

//funkce nastavujici vstupni soubor
void SetFile(FILE *soubor)
{
	file = soubor;
}	

int get_token(Ttoken *token)
{
	tState type = INIT;
	bool cont = false;
	int length = 0;
	int c;

	token->len = 20;
	token->data = malloc(20);

	while(!cont && (c = getc(file)))
	{
		switch(type)
		{
			case INIT:
			{
				if((isalpha(c))||(c=='_'))
				{
					type = ID;
				}
				else if(isdigit(c))
				{
					type = N_DEC;
				}
				else if(c == '.')
				{
					type = DOT;
				}
				else if(c == ',')
				{
					type = COMMA;
				}
				else if(c == '(')
				{
					type = LB;
				}
				else if(c == ')')
				{
					type = PB;
				}
				else if(c == '[')
				{
					type = LSB;
				}
				else if(c == ']')
				{
					type = PSB;
				}
				else if(c == '{')
				{
					type = LDB;
				}
				else if(c == '}')
				{
					type = PDB;
				}
				else if(c == '%')
				{
					type = MOD;
				}
				else if(c == ':')
				{
					type = SEM_CL;
				}
				else if(c == '"')
				{
					type = QUOTE;
				}
				else if(c == ';')
				{
					type = COLON;
					break;
				}
				else if(c == EOF)
				{
					type = END;
					break;
				}
				else if(c == '<')
				{
					type = LESSER;
					break;
				}
				else if(c == '>')
				{
					type = GREATER;
					break;
				}
				else if(c == '!')
				{
					type = EXPL;
					break;
				}
				else if(c == '=')
				{
					type = EQUATE;
					break;
				}
				else if(c == '&')
				{
					type = AND_A;
					break;
				}
				else if(c == '|')
				{
					type = OR_A;
					break;
				}
				else if(c == '+')
				{
					type = PLUS;
					break;
				}
				else if(c == '-')
				{
					type = MINUS;
					break;
				}
				else if(c == '*')
				{
					type = MUL;
					break;
				}
				else if(c == '/')
				{
					type = DIV;
					break;
				}

				if(ExtendToken(token, length)) return 99;
				break;
			}

			case GREATER:
			{
				if (c == '=')
            	{
               		type = GR_EQ;
                	if(ExtendToken(token, length)) return 99;

            	}
            	else
            	{
                	token->type = type;
                	type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
            	}

            	break;
			}

			case LESSER:
			{
				if (c == '=')
            	{
               		type = LE_EQ;
                	if(ExtendToken(token, length)) return 99;

            	}
            	else
            	{
                	token->type = type;
                	type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
            	}

            	break;
			}

			case EXPL:
			{
				if (c == '=')
            	{
               		type = N_EQ;
                	if(ExtendToken(token, length)) return 99;

            	}
            	else
            	{
                	token->type = type;
                	type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
            	}

            	break;
			}

			case EQUATE:
			{
				if (c == '=')
            	{
               		type = EQUALS;
                	if(ExtendToken(token, length)) return 99;

            	}
            	else
            	{
                	token->type = type;
                	type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
            	}

            	break;
			}

			case AND_A:
			{
				if (c == '&')
            	{
               		type = AND_B;
                	if(ExtendToken(token, length)) return 99;

            	}
            	else
            	{
                	token->type = type;
                	type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
            	}

            	break;
			}

			case OR_A:
			{
				if (c == '|')
            	{
               		type = OR_B;
                	if(ExtendToken(token, length)) return 99;

            	}
            	else
            	{
                	token->type = type;
                	type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
            	}

            	break;
			}

			case N_DEC:
			{
				if(isdigit(c))
				{
					type = N_DEC;
					if(ExtendToken(token, length)) return 99;
				}
				else if (c == '.')
				{
					type = DEC;
					if(ExtendToken(token, length)) return 99;
				}
				else if((c == 'e') || (c == 'E'))
				{
					type = N_DEC_E;
					if(ExtendToken(token, length)) return 99;
				}
				else 
				{
					token->type = INTGR;
					type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
				}
				break;
			}

			case N_DEC_E:
			{
				if(isdigit(c))
				{
					type = N_DEC_E;
					if(ExtendToken(token, length)) return 99;
				}
				else 
				{
					token->type = INTGR;
					type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
				}
				break;
			}

			case DEC:
			{
				if(isdigit(c))
				{
					type = DEC;
					if(ExtendToken(token, length)) return 99;
				}
				else if((c == 'e')||(c == 'E'))
				{
					type = DEC_E;
					if(ExtendToken(token, length)) return 99;
				}
				else 
				{
					token->type = DBLE;
					type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
				}
				break;
			}

			case DEC_E:
			{
				if(isdigit(c))
				{
					type = DEC_E;
					if(ExtendToken(token, length)) return 99;
				}
				else 
				{
					token->type = DBLE;
					type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
				}
				break;
			}

			case MUL:
			{
				if(c == '/')
				{
					token->type = B_COM_B;
					if(ExtendToken(token, length)) return 99;
				}
				else
				{
					token->type = type;
                	type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
				}
				break;
			}

			case DIV:
			{
				if(c == '/')
				{
					token->type = COM;
					if(ExtendToken(token, length)) return 99;
				}
				else if(c == '*')
				{
					token->type = B_COM_A;
					if(ExtendToken(token, length)) return 99;
				}
				else
				{
					token->type = type;
                	type = END;
                	if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
				}
				break;
			}

			case ID:
			{
				if ((isalpha(c) || isdigit(c) || (c == '_')))
				{
					token->type = type;
					if(ExtendToken(token, length)) return 99;
				}
				else
				{
					IsKeyword(token);
					type = END;
					if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
				}
				break;
			}

			case DOT:
			case COMMA:
			case LB:
			case PB:
			case LSB:
			case PSB:
			case LDB:
			case PDB:
			case MOD:
			case AND_B:
			case OR_B:
			case SEM_CL:
			case QUOTE:
			case COLON:
			case EQUALS:
			case N_EQ:
			case LE_EQ:
			case GR_EQ:
			case COM:
			case B_COM_A:
			case B_COM_B:
			case KEYWORDS:

			{
				token->type = type;
				type = END;
				if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
                break;
			}

			case END:
			{
				if (!isspace(c))
                	{
        				ungetc(c, file);
                	}
                cont = true;
                break;
			}
			default:
			break;//PROBABLY WRONG FIX THIS!!!
		}

		/*if(error)
		{
			break;
		}*/
	}
	return 0; //to záleží	
}


char *printToken()
{

	switch(token.type)
	{
		case KEYWORDS: 	return "keywords";	// klíčová slova
		case PLUS: 		return "+";			// +
		case MINUS:		return	"-";		// -
		case MUL:		return	"*";		// *
		case DIV:		return	"/";		// /
		case MOD:		return	"%%";		// %
		case EQUATE:	return	"=";		// =
		case EQUALS:	return	"==";		// ==
		case GREATER:	return	">";		// >
		case LESSER:	return	"<";		// <
		case GR_EQ:		return	">=";		// >=
		case LE_EQ:		return	"<=";		// <=
		case EXPL:		return	"!";		// !
		case N_EQ:		return	"!=";		// !=
		case DOT:		return	".";		// .
		case SEM_CL:	return	";";		// ;
		case COLON:		return	":";		// :
		case QUOTE:		return	"\"";		// "
		case OR_A:		return	"|";		// |
		case OR_B:		return	"||";		// ||
		case AND_A:		return	"&";		// &
		case AND_B:		return	"&&";		// &&
		case LB:		return	"(";		// (
		case PB:		return	")";		// )
		case LSB:		return	"[";		// [
		case PSB:		return	"]";		// ]
		case LDB:		return	"{";		// {
		case PDB:		return	"}";		// }
		case N_DEC:		return	"[0-9]";		// [0-9]
		case N_DEC_E:	return	"[0-9e0-9]";		// [0-9e0-9]
		case DEC:		return	"[0-9.0-9]";		// [0-9.0-9]
		case DEC_E:		return	"[0-9.0-9e0-9]";	// [0-9.0-9e0-9]
		case COM:		return	"//";				// //
		case B_COM_A:	return	"/*";			// /*
		case B_COM_B:	return	"*/";		// */
		case ID:		return	token.data;	// [a-Z0-9]
		case STRNG:		return	"string";	// string
		case INTGR:		return	"integer";	// integer
		case DBLE:		return	"double";	// double
		case COMMA:		return	",";		// ,
		case INIT:		return "INIT";
		case END:		return "END";
	}
	return "ERROR";//CORRECT? FIX THIS!!!
}
