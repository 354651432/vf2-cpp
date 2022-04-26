CC=g++
CXXFLAGS=-g
VPATH=.:..

all: clean main

main: main.o graph.o graph-fromjson.o

clean: 
	@-rm -f *.o

run: all
	./main