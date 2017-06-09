ALL: EXE LANCEMENT RM
DEBUG: EXE LANCEMENTVAL RM

libs.o: libs.c main.h
	gcc -Wall -o libs.o -c libs.c -g

main.o: main.c main.h
	gcc -Wall -c main.c -o main.o -g -lm

EXE: main.o libs.o main.h
	gcc -Wall -o EXE main.o libs.o -g -lm

LANCEMENT:
	./EXE

LANCEMENTVAL:
	valgrind --leak-check=full ./EXE

RM:
	rm *.o

#NB: when using valgrind to debug: use it on ./EXE not make (rm leaks 10 bytes, 40 others are unidentified)
