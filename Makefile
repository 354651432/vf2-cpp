CC=g++
CXXFLAGS+=-g

main: main.o

main.o: graph.hpp vf2.hpp

.PHONY: clean run
clean:
	-rm main

run: main
	@./main
