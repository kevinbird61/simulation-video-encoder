EXEC:=main

$(EXEC): lcgrand.h state_var.h random_gen.h
	gcc -o lcgrand.o -c lcgrand.c
	gcc -o operation.o -c operation.c
	gcc $(EXEC).c lcgrand.o random_gen.o state_var.h -o $(EXEC) -lm

clean:
	rm *.o $(EXEC)