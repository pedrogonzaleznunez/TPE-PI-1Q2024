//Funciones de lectura de archivos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "queries.h"
#include "main.h"



#if FORMATNYC
    #define NYC_INFRACTIONS
    #define NYC_TICKETS

#elif FORMATCHI
    #define CHI_INFRACTIONS
    #define CHI_TICKETS
#endif


#define MAX_LINE_LENGTH 100
#define SET_ERRNO 0
#define FORMAT_ERROR 1
#define OPENING_FILE_ERROR 2
#define ESCAPE_N "\n"
#define TOPQ1 2
#define LASTQ1 (TOPQ1-1)
#define TOPQ2 3
#define LASTQ2 (TOPQ2-1)
#define TOPQ3 3
#define LASTQ3 (TOPQ3-1)
#define WRITETEXT "wt"

void readInfractionsFile(char const argv[], Query1ADT query1);
void readTicketsFile(char const argv[], Query1ADT query1,Query2ADT query2,Query3ADT query3);

// @brief Main function
// @param argc Number of files
// @param argv path to tickets file
// @param argv path to infractions file
// @return 0 if the program was executed successfully, error number otherwise
int main(int argc, char const *argv[]){
    if( argc != 3){
        perror("Usage: ./parkingTickets### <tickets_file> <infractions_file>");
        exit(FORMAT_ERROR);
    }

    // [1st] Create CDTs
    Query1ADT query1 = newQuery1();
    Query2ADT query2 = newQuery3();
    Query3ADT query3 = newQuery3();

    // [2nd] Read files
    readInfractionsFile(argv[INFRACTIONS_FILE], query1);
    readTicketsFile(argv[TICKETS_FILE], query1,query2,query3);
    
    // [3rd] Sort infractions
    sortInfractionsDecreasing(query1);
    printInfractions(query1);

    // [4th] Write files
    FILE * fileQ1 = newFile("query1.csv");
    writeQ1File(fileQ1,query1);


    //Free resources
    freeQuery1(query1);
    
    return 0;
}   

void deleteChar(char *string, char toDeleteChar) {
    int i, j;
    int len = strlen(string);

    for (i = 0, j = 0; i < len; i++) {
        if (string[i] != toDeleteChar) {
            string[j++] = string[i];
        }
    }
    string[j] = '\0'; // Agrega el terminador nulo al final de la cadena resultante
}


// @brief Reads infraction's file and inserts the data into the CDT. 
// @param fileToRead File to read
void readInfractionsFile(char const * argv, Query1ADT query1){

    FILE *file = fopen(argv, READ);

    //check if the file was opened correctly
    if (file == NULL){
        perror("[ERROR] Error opening file");
        exit(OPENING_FILE_ERROR);
    }

    char line[MAX_LINE_LENGTH];
    long lineCounter = 0;
    int columnCounter;
    char * token, * id, * descrip;

    while(fgets(line, MAX_LINE_LENGTH, file) != NULL){
        
        lineCounter++;
        if(lineCounter == 1){
            continue;
        }

        token = strtok(line, DELIM);

        for(columnCounter = 0; token != NULL; columnCounter++){
            if (columnCounter == infractionIdA) {
                id = token;
            }
            else if (columnCounter == description) {
                descrip = token;
                deleteChar(descrip, '\n');
            }
            
            token = strtok(NULL, DELIM);
        }

        //insert data into the CDT
        addInfractionsToVec(query1, atoi(id), descrip);
        
        lineCounter++;
    }
    fclose(file);
    return;
}

void readTicketsFile(char const * argv, Query1ADT query1,Query2ADT query2, Query3ADT query3){
    
    FILE *file = fopen(argv, READ);

    //check if the file was opened correctly
    if (file == NULL){
        perror("[ERROR] Error opening file");
        exit(OPENING_FILE_ERROR);
    }

    char line[MAX_LINE_LENGTH];
    long lineCounter = 0;
    int columnCounter;
    char * token, * plate, * id, * agency;

    while(fgets(line, MAX_LINE_LENGTH, file) != NULL){
        
        lineCounter++;
        if(lineCounter == 1){
            continue;
        }

        token = strtok(line, DELIM);

        for(columnCounter = 0; token != NULL; columnCounter++){
            if (columnCounter == plateNumber) {
                plate = token;
                deleteChar(plate, '\n');
            }
            else if (columnCounter == infractionId) {
                id = token;
            }
            else if (columnCounter == issuingAgency) {
                agency = token;
                deleteChar(agency, '\n');
            }
            
            token = strtok(NULL, DELIM);
        }

        //insert data into the CDT
        addInfractionsOcurrences(query1, atoi(id));
        //addAgency(query1,query2,agency,atoi(id));
        //addTicket(query1,query3,atoi(id),plate);

        lineCounter++;
    }
    fclose(file);
    return;
}


