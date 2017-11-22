all: main.c
	gcc -o seashell.out main.c

run: all
	./seashell.out
