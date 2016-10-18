FILES=main.c ial.c parser.c lex.c
CFLAGS= -Wall -Werror -pedantic

all:
	gcc $(FILES) $(CFLAGS) -o ifj

