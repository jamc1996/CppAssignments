CC = g++
CFLAGS = -Wall -std=c++17

objects = main.o fish.o environment.o 

tank: $(objects)
	$(CC) $(CFLAGS) -o tank $(objects)

main.o: main.cc
	$(CC) $(CFLAGS) -c $<

fish.o: fish.cc fish.h
	$(CC) $(CFLAGS) -c $<

environment.o: environment.cc environment.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(objects) tank
