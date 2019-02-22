CC = g++
CFLAGS = -Wall

objects = test_Matrix.o Matrix.o

mat_test: $(objects)
	$(CC) $(CFLAGS) -o mat_test $(objects)

test_Matrix.o: test_Matrix.cc
	$(CC) $(CFLAGS) -c $<

Matrix.o: Matrix.cc Matrix.h
	$(CC) $(CFLAGS) -c $< 


test: mat_test
	./mat_test

.PHONY: clean
clean:
	rm -f mat_test $(objects)
