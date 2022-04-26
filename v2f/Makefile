CC=g++
CXXFLAGS=-g
VPATH=.:..

all: clean main

main: main.o graph.o graph-fromjson.o

clean: 
	@-rm -f main.o main

run: all
	./main