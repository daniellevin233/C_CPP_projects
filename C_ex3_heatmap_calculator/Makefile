CC=gcc

all: reader.o calculator.o heat_eqn.o
	$(CC) -Wall reader.c calculator.c heat_eqn.c -o ex3

reader.o: reader.c
	$(CC) -c reader.c

calculator.o: calculator.c calculator.h
	$(CC) -c calculator.c

heat_eqn.o: heat_eqn.c heat_eqn.h
	$(CC) -c heat_eqn.c

.PHONY: clean

clean:
	rm -f reader.o calculator.o heat_eqn.o ex3 ex3.tar

tar: 
	tar cvf ex3.tar reader.c calculator.c Makefile

