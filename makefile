COMPILER = gcc
OUTPUT_FILE_NYC = parkingTicketsNYC
OUTPUT_FILE_CHI = parkingTicketsCHI
FRONT = main.c
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -g
FORMATNYC = -DFORMATNYC=1
FORMATCHI = -DFORMATCHI=1

all: $(OUTPUT_FILE_NYC) $(OUTPUT_FILE_CHI)

$(OUTPUT_FILE_NYC): mainNYC.o queries.o
	$(COMPILER) $(CFLAGS) mainNYC.o queries.o -o $(OUTPUT_FILE_NYC)

$(OUTPUT_FILE_CHI): mainCHI.o queries.o
	$(COMPILER) $(CFLAGS) mainCHI.o queries.o -o $(OUTPUT_FILE_CHI)

mainNYC.o: $(FRONT)
	$(COMPILER) $(FORMATNYC) $(CFLAGS) -c $(FRONT) -o mainNYC.o

mainCHI.o: $(FRONT)
	$(COMPILER) $(FORMATCHI) $(CFLAGS) -c $(FRONT) -o mainCHI.o

queries.o: queries.c queries.h
	$(COMPILER) $(CFLAGS) -c queries.c -o queries.o

clean:
	rm -f *.o 