CC=g++
CXXFLAGS+=-g -pg
LDFLAGS=-pg

main: main.o graph.o match.o c4.o k14.o graph-fromjson.o p5.o

%.o: %.h

.PHONY: clean run
clean:
	-rm main

run: main
	@./main
