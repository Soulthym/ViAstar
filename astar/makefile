ALL: EXE LANCEMENT RM
DEBUG: EXE LANCEMENTVAL RM

easyalloc.o: easyalloc.c main.h
	gcc -Wall -o easyalloc.o -c easyalloc.c -g

main.o: astar.c main.h
	gcc -Wall -c main.c -o main.o -g

EXE: main.o easyalloc.o main.h
	gcc -Wall -o EXE main.o easyalloc.o -g

LANCEMENT:
	./EXE

LANCEMENTVAL:
	valgrind --leak-check=full ./EXE

RM:
	rm *.o

#NB: when using valgrind to debug: use it on ./EXE not make (rm leaks 10 bytes, 40 others are unidentified)
