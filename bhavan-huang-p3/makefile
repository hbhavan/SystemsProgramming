FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors

all: size newer dirlist forkpid

size: size.o
	g++ $(FLAGS) -o size size.o

size.o: size.cpp
	g++ $(FLAGS) -c size.cpp

newer: newer.o
	g++ $(FLAGS) -o newer newer.o

newer.o: newer.cpp
	g++ $(FLAGS) -c newer.cpp

dirlist: dirlist.o
	g++ $(FLAGS) -o dirlist dirlist.o

dirlist.o: dirlist.cpp
	g++ $(FLAGS) -c dirlist.cpp

forkpid: forkpid.o
	g++ $(FLAGS) -o forkpid forkpid.o

forkpid.o: forkpid.cpp
	g++ $(FLAGS) -c forkpid.cpp

clean:
	rm -rf size
	rm -rf newer
	rm -rf dirlist
	rm -rf forkpid
	rm -rf *o
