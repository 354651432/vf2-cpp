CC=g++
main: main.o graph.o match.o demo.o 

%.o:%.cpp
	g++ -g -c $? -o $@

.PHONY: clean run
clean:
	-rm *.o
	-rm main

run: main
	@./main