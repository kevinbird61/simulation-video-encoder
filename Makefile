EXEC:=main

$(EXEC): lcgrand.h state_var.h random_gen.h
	gcc -o lcgrand.o -c lcgrand.c
	gcc -o random_gen.o -c random_gen.c
	gcc $(EXEC).c lcgrand.o random_gen.o state_var.h -o $(EXEC) -lm

docogen:
	cd doc/ && npm install && node doc.js

clean:
	rm *.o $(EXEC)

cleandoc:
	rm -rf doc/node_modules/