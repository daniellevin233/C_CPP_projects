CC=g++

all: ikea.o
	$(CC) -Wall ikea.cpp -o ex2

ikea.o: ikea.cpp
	$(CC) -c ikea.cpp

tar:
	tar cvf ex2.tar ikea.cpp Makefile

.PHONY: clean

clean:
	rm -f ikea.o ex2 ex2.tar

