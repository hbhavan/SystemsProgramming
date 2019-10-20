FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors

all: size newer

size: size.o
	g++ $(FLAGS) -o size size.o

size.o: size.cpp
	g++ $(FLAGS) -c size.cpp

newer: newer.o
	g++ $(FLAGS) -o newer newer.o

newer.o: newer.cpp
	g++ $(FLAGS) -c newer.cpp
