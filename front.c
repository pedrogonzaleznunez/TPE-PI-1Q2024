#include "front.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "queries.h"

static FILE * newFile(char * name){
    FILE * file=fopen(name,"wt");
    if(errno != 0|| file==NULL){
        perror("ERROR - Creating new file\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

void writeQ1File(Query1ADT query1){
    //Header for Q1 .csv
    FILE * stream = newFile("query1.csv");
    fputs("infraction;tickets\n",stream);
    
    //Write rows for Q1 .csv
    fclose(stream);
}

void writeQ2File(FILE * stream,Query2ADT query2){
    //Header for Q2 .csv
    FILE * stream = newFile("query2.csv");
    fputs("issuingAgency;infraccion;tickets\n",stream);
    
    //Write rows for Q2 .csv
    
    fclose(stream);
}

void writeQ3File(FILE * stream,Query3ADT query3){
    //Header for Q2 .csv
    FILE * stream = newFile("query3.csv");
    fputs("infraccion;plate;tickets\n",stream);
    
    //Write rows for Q2 .csv
    
    fclose(stream);
}


