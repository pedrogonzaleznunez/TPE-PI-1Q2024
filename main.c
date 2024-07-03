//Funciones de lectura de archivos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

void readInfractionsFile(char const argv[]);
void readTicketsFile(char const argv[]);

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

    readInfractionsFile(argv[INFRACTIONS_FILE]);
    readTicketsFile(argv[TICKETS_FILE]);
}   

// @brief Reads infraction's file and inserts the data into the CDT. 
// @param fileToRead File to read
void readInfractionsFile(char const argv[]) {

    //check if the main.h file is correctly formatted
    if ((FORMATCHI == 1 && FORMATNYC == 1)||(FORMATCHI == 0 && FORMATNYC == 0)){
        perror("[ERROR] Compilation error \n");
        exit(EXIT_FAILURE);
    }

    errno = SET_ERRNO;
    FILE *file = fopen(&argv[INFRACTIONS_FILE], READ);

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
        
        if(lineCounter == 1){
            lineCounter++;
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

        // --> functions to insert data into the CDT

        lineCounter++;
    }
    fclose(file);
    return;
}

void readTicketsFile(char const argv[]){
    //check if the main.h file is correctly formatted
    if ((FORMATCHI == 1 && FORMATNYC == 1)||(FORMATCHI == 0 && FORMATNYC == 0)){
        perror("[ERROR] Compilation error \n");
        exit(EXIT_FAILURE);
    }

    errno = SET_ERRNO;
    FILE *file = fopen(&argv[TICKETS_FILE], READ);

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
        
        if(lineCounter == 1){
            lineCounter++;
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

        // --> functions to insert data into the CDT

        lineCounter++;
    }
    fclose(file);
    return;
}
