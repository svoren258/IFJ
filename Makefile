FILES=main.c ial.c stack.c lex.c error.c expression.c parser.c
CFLAGS= -Wall -Werror -pedantic


all:
	gcc -std=c99 $(FILES) $(CFLAGS) -o ifj
	
clean:
	rm ifj

