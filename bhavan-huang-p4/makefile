FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors

all: shell

shell: shell.o
	g++ $(FLAGS) -o shell shell.o

shell.o: shell.cpp
	g++ $(FLAGS) -c shell.cpp

clean:
	rm -f shell
	rm -f shell.o
