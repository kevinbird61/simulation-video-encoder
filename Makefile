EXEC:=main
OBJS:=main.o lcgrand.o random_gen.o queue.o
CXX=gcc
CFLAGS=-lm -std=c11
CFLAGS_G=-lm -std=c11 -g

all: $(OBJS)
	$(CXX) $^ -o $(EXEC) $(CFLAGS)

gdb: $(OBJS)
	$(CXX) $^ -o $(EXEC) $(CFLAGS_G)

%.o: %.c %.h
	$(CXX) -c $^

run:
	./$(EXEC) -n 1 -t 8 -b 20

run_g:
	gdb --args $(EXEC) -n 1 -t 8 -b 20

docogen:
	cd doc/ && npm install && node doc.js

clean:
	rm *.o $(EXEC) *.gch

cleandoc:
	rm -rf doc/node_modules/