CC = g++
CFLAGS = -Wall -std=c++11

objects = main.o fish.o environment.o simulation.o

tank: $(objects)
	$(CC) $(CFLAGS) -o tank $(objects)

main.o: main.cc
	$(CC) $(CFLAGS) -c $<

fish.o: fish.cc fish.h
	$(CC) $(CFLAGS) -c $<

environment.o: environment.cc environment.h
	$(CC) $(CFLAGS) -c $<

simulation.o: simulation.cc simulation.h
	$(CC) $(CFLAGS) -c $<

test: $(objects) tank
	./tank -m 10000 -s 30 -t 300
	./tank -m 12 -s 3 -t 6 -i 10 -v


clean:
	rm -f $(objects) tank
