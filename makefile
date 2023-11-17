all: main.o
	g++ main.o -o main -lsfml-system -lsfml-graphics -lsfml-window
main.o: main.cc
	g++ -c main.cc
