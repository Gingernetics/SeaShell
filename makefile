all: main.c seashell_functions.h
	gcc -o seashell.out main.c seashell_functions.h

run: all
	./seashell.out
