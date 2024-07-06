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

void readInfractionsFile(char const argv[], Query1ADT query1);
void readTicketsFile(char const argv[], Query1ADT query1,Query2ADT query2,Query3ADT query3);

// @brief Main function
// @param argc Number of files
// @param argv path to tickets file
// @param argv path to infractions file
// @return 0 if the program was executed successfully, error number otherwise
int main(int argc, char const *argv[]){
    if( argc != 3){
        perror("Usage: ./main <tickets_file> <infractions_file>");
        exit(FORMAT_ERROR);
    }

    //Create CDTs
    Query1ADT query1 = newQuery1();
    Query2ADT query2 = newQuery2();
    Query3ADT query3 = newQuery3();

    //Read files
    readInfractionsFile(argv[INFRACTIONS_FILE], query1);
    readTicketsFile(argv[TICKETS_FILE], query1,query2,query3);

    printInfractions(query1);

    //Front

    //Free resources
    freeInfraccion3(query3);
    freeQuery2(query2);
    freeQuery1(query1);
    return 0;
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
            }
            else if (columnCounter == infractionId) {
                id = token;
            }
            else if (columnCounter == issuingAgency) {
                agency = token;
            }
            
            token = strtok(NULL, DELIM);
        }

        //insert data into the CDT
        addInfractionsOcurrences(query1, atoi(id));
        addAgency(query1,query2,agency,atoi(id));
        addTicket(query1,query3,atoi(id),plate);

        lineCounter++;
    }
    fclose(file);
    return;
}
