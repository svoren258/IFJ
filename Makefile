FILES=main.c ial.c parser.c lex.c error.c
CFLAGS= -Wall -Werror -pedantic

all:
	gcc -std=c99 $(FILES) $(CFLAGS) -o ifj

