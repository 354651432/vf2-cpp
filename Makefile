CC=g++
CXXFLAGS+=-g -pg
LDFLAGS=-pg
main: main.o graph.o match.o demo.o c4.o k14.o graph-fromjson.o p5.o

main.o: constant.h

%.o: %.h

.PHONY: clean run
clean:
	-rm *.o
	-rm main

run: main
	@./main