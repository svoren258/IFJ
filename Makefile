FILES=main.c ial.c stack.c parser.c lex.c error.c expression.c
CFLAGS= -Wall -Werror -pedantic


all:
	gcc -std=c99 $(FILES) $(CFLAGS) -o ifj
	
clean:
	rm ifj

