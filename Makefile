inv: lcgrand.h
	gcc -o lcgrand.o -c lcgrand.c
	gcc inv.c lcgrand.h lcgrand.o -o inv -lm