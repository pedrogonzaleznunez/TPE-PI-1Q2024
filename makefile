COMPILER = gcc
OUTPUT_FILE_NYC = parkingTicketsNYC
OUTPUT_FILE_CHI = parkingTicketsCHI
FRONT = main.c
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -g
FORMATNYC = -DFORMATNYC\=1
FORMATCHI = -DFORMATCHI\=1

all: programForNYC programForCHI clean

programForNYC: mainNYC.o 
	$(COMPILER) $(CFLAGS) mainNYC.o -o $(OUTPUT_FILE_NYC)

programForCHI: mainCHI.o 
	$(COMPILER) $(CFLAGS) mainCHI.o -o $(OUTPUT_FILE_CHI)

mainNYC.o: $(FRONT) 
	$(COMPILER) $(FORMATNYC) $(CFLAGS) -c $(FRONT) -o mainNYC.o
	
mainCHI.o: $(FRONT)
	$(COMPILER) $(FORMATCHI) $(CFLAGS) -c $(FRONT) -o mainCHI.o

clean:
	rm -f *.o
