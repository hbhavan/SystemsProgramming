FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors

all: head tail wc true false env

head: head.o
	g++ $(FLAGS) -o head head.o

head.o: head.cpp
	g++ $(FLAGS) -c head.cpp

tail: tail.o
	g++ $(FLAGS) -o tail tail.o

tail.o: tail.cpp
	g++ $(FLAGS) -c tail.cpp

wc: wc.o
	g++ $(FLAGS) -o wc wc.o

wc.o: wc.cpp
	g++ $(FLAGS) -c wc.cpp

true: true.o
	g++ $(FLAGS) -o true true.o

true.o: true.cpp
	g++ $(FLAGS) -c true.cpp

false: false.o
	g++ $(FLAGS) -o false false.o

false.o: false.cpp
	g++ $(FLAGS) -c false.cpp

env: env.o
	g++ $(FLAGS) -o env env.o

env.o: env.cpp
	g++ $(FLAGS) -c env.cpp
