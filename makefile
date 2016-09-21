FLAGS = -Wall -g -std=c++11

all: swamp

swamp:swamp.o
	g++ $(FLAGS) swamp.o -o swamp.out
swamp.o:swamp.cpp
	g++ $(FLAGS) -c swamp.cpp -o swamp.o
clean:
	rm -rf *.dSYM *.o *.out
