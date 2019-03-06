CC = g++
CFLAGS = -Wall -std=c++11

objects = main.o Board.o

play: $(objects)
	$(CC) $(CFLAGS) -o play $(objects)

main.o: main.cc
	$(CC) $(CFLAGS) -c $<

Board.o: Board.cc Board.h
	$(CC) $(CFLAGS) -c $<

test: play
	./play

.PHONY: clean
clean:
	rm -f play $(objects)
