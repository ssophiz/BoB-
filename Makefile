sum : sum.o main.o
	g++ -o sum sum.o main.o

sum.o : sum.h sum.cpp
