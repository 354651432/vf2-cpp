CC=g++
CXXFLAGS+=-g
main: main.o graph.o match.o demo.o c4.o k14.o graph-fromjson.o

main.o: constant.h
graph.o: graph.h

.PHONY: clean run
clean:
	-rm *.o
	-rm main

run: main
	@./main