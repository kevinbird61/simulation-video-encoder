EXEC:=main
OBJS:=main.o lcgrand.o random_gen.o queue.o
OBJDIR=result
CXX=gcc
CFLAGS=-lm -std=c11
CFLAGS_G=-lm -std=c11 -g

all: $(OBJS)
	$(CXX) $^ -o $(EXEC) $(CFLAGS)

gdb: $(OBJS)
	$(CXX) $^ -o $(EXEC) $(CFLAGS_G)

%.o: %.c %.h
	$(CXX) -c $^

$(OBJDIR):
	mkdir -p $@

run: all
	./$(EXEC) -n 1 -t 8 -b 20 -a 0.1 -f 0.01668335001 -c 265.5

proj: all $(OBJDIR)
	./$(EXEC) -n 1 -t 8 -b 20 > $(OBJDIR)/buffer20.txt
	./$(EXEC) -n 1 -t 8 -b 40 > $(OBJDIR)/buffer40.txt
	./$(EXEC) -n 1 -t 8 -b 60 > $(OBJDIR)/buffer60.txt
	./$(EXEC) -n 1 -t 8 -b 80 > $(OBJDIR)/buffer80.txt
	./$(EXEC) -n 1 -t 8 -b 100 > $(OBJDIR)/buffer100.txt

run_g:
	gdb --args $(EXEC) -n 1 -t 8 -b 20

docogen:
	cd doc/ && npm install && node doc.js

clean:
	rm *.o $(EXEC) *.gch 
	rm -rf $(OBJDIR)/

cleandoc:
	rm -rf doc/node_modules/