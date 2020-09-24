CC=g++

all: testint testset

big_integer.o: big_integer.cpp big_integer.h
	$(CC) -c big_integer.cpp

my_set.o: my_set.cpp my_set.h
	$(CC) -c my_set.cpp

testint: big_integer.o big_int_tester.o
	$(CC) -Wall big_integer.cpp  big_int_tester.cpp -o testint 

big_int_tester.o: big_int_tester.cpp
	$(CC) -c big_int_tester.cpp

testset: my_set.o my_set_tester.o big_integer.o
	$(CC) -Wall my_set.cpp my_set_tester.cpp big_integer.cpp -o testset

my_set_tester.o: my_set_tester.cpp
	$(CC) -c my_set_tester.cpp

.PHONY: clean

clean:
	rm -f big_integer.o my_set.o testint testset ex1.tar

tar:
	tar cvf ex1.tar big_integer.cpp big_integer.h my_set.cpp my_set.h Makefile
