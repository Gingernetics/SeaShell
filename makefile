all: main functions
	gcc -o seashell.out main.o functions.o

main: main.c seashell.h
	gcc -c main.c seashell.h

functions: functions.c seashell.h
	gcc -c functions.c seashell.h

run: all
	./seashell.out

clean:
	-rm *~
	-rm *.o
	-rm *.h.gch
