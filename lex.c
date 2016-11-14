#include "lex.h"
#include <string.h>
#include <ctype.h>

#define COUNT_OF_KEYWORDS 17

//globalni promene
Ttoken *token;
File *file;

//klicova slova
char *keywords[] ={"boolean","break","class","continue","do","double","else","false","for","if","int","return",
	"String","static","true","void","while"};

void IsKeyword(Ttoken *token)
{
	for(int i = 0; i < COUNT_OF_KEYWORDS; i++)
	{
		if(!(strcmp(token->data,keywords[i])))
		{
			token->type = KEYWORD;
			return;
		}
	}
}

//funkce rozsiri token
int ExtendToken(Ttoken *token, int lenght)
{
	token->data = realloc(token->data, lenght+20);
	if(token->data = NULL)
	{
		return -1;
	}
	else
	{
		return lenght+20;
	}
}

//funkce nastavujici vstupni soubor
void SetFile(File *soubor)
{
	file = soubor;
}	

Ttoken *get_token(Ttoken *token)
{
	tState type = INIT;
	bool cont = false;
	int lenght = 20;
	int c;

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

				ExtendToken(&token, lenght);
				break;
			}

			case GREATER:
			{
				if (c == '=')
            	{
               		type = GR_EQ;
                	ExtendToken(&token, lenght);

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
                	ExtendToken(&token, lenght);

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
                	ExtendToken(&token, lenght);

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
                	ExtendToken(&token, lenght);

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
                	ExtendToken(&token, lenght);

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
                	ExtendToken(&token, lenght);

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
					ExtendToken(&token, lenght);
				}
				else if (c == '.')
				{
					type = DEC;
					ExtendToken(&token, lenght);
				}
				else if((c == 'e') || (c == 'E'))
				{
					type = N_DEC_E;
					ExtendToken(&token, lenght);
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
					type N_DEC_E;
					ExtendToken(&token, lenght);
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
					type DEC;
					ExtendToken(&token, lenght);
				}
				else if((c == 'e')||(c == 'E'))
				{
					type DEC_E;
					ExtendToken(&token, lenght);
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
					type DEC_E;
					ExtendToken(&token, lenght);
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
					ExtendToken(&token, lenght);
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
					ExtendToken(&token, lenght);
				}
				else if(c == '*')
				{
					token->type = B_COM_A;
					ExtendToken(&token, lenght);
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
					ExtendToken(&token, lenght);
				}
				else
				{
					token->type = IsKeyword(&token)
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
			case LPB:
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
			case MUL:
			case DIV:
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
		}

		/*if(error)
		{
			break;
		}*/
	}
	return *token; //to záleží	
}

