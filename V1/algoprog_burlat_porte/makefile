CC=g++
CFLAGS=-std=c++11 -W -Wall -O3
EXEC=files

files: pixel.o image.o test.o main.o
	$(CC) -O3 pixel.o image.o test.o main.o -o algoprog

main.o: main.cpp 
	$(CC) -o main.o -c main.cpp $(CFLAGS)

test.o: test.cpp
	$(CC) -o test.o -c test.cpp $(CFLAGS)

pixel.o: pixel.cpp
	$(CC) -o pixel.o -c pixel.cpp $(CFLAGS)

image.o: image.cpp
	$(CC) -o image.o -c image.cpp $(CFLAGS)

clean:
	rm -rf *.o
