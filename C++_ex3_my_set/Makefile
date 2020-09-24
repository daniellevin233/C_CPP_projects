CC=g++
F= -Wall -Wextra -Wvla -std=c++14 -g

all: testset

testset: my_set.h my_set.hpp my_set_tester.o
	$(CC) $(F) my_set_tester.cpp -o testset

my_set_tester.o: my_set_tester.cpp
	$(CC) my_set_tester.cpp

tar:
	tar cvf ex3.tar my_set.h my_set.hpp Makefile

.PHONY: clean

clean:
	rm -f my_set.o my_set_tester.o testset ex3.tar
