all: matrix.o main.o
	g++ matrix.o main.o
matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp
main.o:
	g++ -c main.cpp
clean:
	rm a.out matrix.o main.o