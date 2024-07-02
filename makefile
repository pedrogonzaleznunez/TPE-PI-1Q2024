COMPILER = gcc
OUTPUT_FILE_NYC = parkingTicketsNYC
OUTPUT_FILE_CHI = parkingTicketsCHI
FRONT = main.c
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -g
FORMATNYC = -DFORMATNYC\=1
FORMATCHI = -DFORMATCHI\=1

all: 

clean:
	rm -f *.o