CC=gcc

ex2.o: battleships.o battleships_game.o battleships.h 
	$(CC) -Wall  battleships.c battleships_game.c battleships.h -o ex2.exe

battleships: battleships.o battleships_game.o 
	$(CC) battleships.o battleships_game.o -o battleships

battleships.o: battleships.c battleships.h
	$(CC) -c battleships.c

battleships_game.o: battleships_game.c battleships.h
	$(CC) -c battleships_game.c

.PHONY: clean

clean:
	rm battleships_game.o battleships.o
