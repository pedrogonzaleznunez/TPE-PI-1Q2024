COMPILER = gcc
OUTPUT_FILE_NYC = parkingTicketsNYC
OUTPUT_FILE_CHI = parkingTicketsCHI
FRONT = main.c
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -g
FORMATNYC = -DFORMATNYC=1
FORMATCHI = -DFORMATCHI=1

all: $(OUTPUT_FILE_NYC) $(OUTPUT_FILE_CHI)

$(OUTPUT_FILE_NYC): mainNYC.o queriesNYC.o
	$(COMPILER) $(CFLAGS) mainNYC.o queriesNYC.o -o $(OUTPUT_FILE_NYC)

$(OUTPUT_FILE_CHI): mainCHI.o queriesCHI.o
	$(COMPILER) $(CFLAGS) mainCHI.o queriesCHI.o -o $(OUTPUT_FILE_CHI)

mainNYC.o: $(FRONT)
	$(COMPILER) $(FORMATNYC) $(CFLAGS) -c $(FRONT) -o mainNYC.o

mainCHI.o: $(FRONT)
	$(COMPILER) $(FORMATCHI) $(CFLAGS) -c $(FRONT) -o mainCHI.o

queriesNYC.o: queries.c queries.h
	$(COMPILER) $(FORMATNYC) $(CFLAGS) -c queries.c -o queriesNYC.o

queriesCHI.o: queries.c queries.h
	$(COMPILER) $(FORMATCHI) $(CFLAGS) -c queries.c -o queriesCHI.o

clean:
	rm -f *.o 
