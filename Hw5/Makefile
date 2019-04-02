CC = g++
CFLAGS = -Wall -std=c++11

objects = main.o board.o player.o game.o

play: $(objects)
	$(CC) $(CFLAGS) -o play $(objects)

main.o: main.cc
	$(CC) $(CFLAGS) -c $<

board.o: board.cc board.h
	$(CC) $(CFLAGS) -c $<

player.o: player.cc player.h
	$(CC) $(CFLAGS) -c $<

game.o: game.cc game.h
	$(CC) $(CFLAGS) -c $<

test: play
	./play

.PHONY: clean
clean:
	rm -f play $(objects)
