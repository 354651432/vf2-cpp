CC=g++
CXXFLAGS+=-g -pg
LDFLAGS=-pg

VF2SRCS := $(wildcard vf2-vector/*.cpp)
VF2OBJS := $(patsubst %.cpp,%.o,${VF2SRCS})

main: main.o graph.o match.o demo.o c4.o k14.o graph-fromjson.o p5.o ${VF2OBJS}

main.o: constant.h

%.o: %.h

.PHONY: clean run
clean:
	-rm *.o vf2-vector/*.o
	-rm main

run: main
	@./main
