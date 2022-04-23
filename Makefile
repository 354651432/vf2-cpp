CC=g++
CXXFLAGS+=-g
main: main.o graph.o match.o demo.o c4.o k14.o

main.o: constant.h

.PHONY: clean run
clean:
	-rm *.o
	-rm main

run: main
	@./main