all: matrix.o lnc.o
	g++ matrix.o lnc.o
matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp
lnc.o:
	g++ -c lnc.cpp
clean:
	rm a.out matrix.o lnc.o