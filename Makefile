EXEC:=main
OBJS:=lcgrand.o random_gen.o queue.o
CXX=gcc
CFLAGS=-lm -std=c11

all: $(EXEC).c $(OBJS)
	$(CXX) $^ -o $(EXEC) $(CFLAGS)

%.o: %.c %.h
	$(CXX) -c $^

run:
	./$(EXEC) -t 8 -b 20

docogen:
	cd doc/ && npm install && node doc.js

clean:
	rm *.o $(EXEC) *.gch

cleandoc:
	rm -rf doc/node_modules/