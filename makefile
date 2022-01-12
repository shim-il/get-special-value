seek: seek.o
	gcc -g -Wall -ansi -pedantic seek.c -o seek

seek.o: seek.c data.h
	gcc -c -Wall -ansi -pedantic seek.c -o seek.o

