CC = gcc
CFLAGS = -Wall -g
LIBS = -lm

all: calc format
	
calc: 
	$(CC) calc.c $(CFLAGS) $(LIBS) -o calc

format:
	$(CC) format.c $(CFLAGS) $(LIBS) -o format

clean:
	rm calc
	rm format