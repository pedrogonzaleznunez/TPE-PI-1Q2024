#include "front.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "queries.h"

//FrontEnd functions
FILE * newFile(char * name){
    FILE * file=fopen(name,"wt");
    if(errno != 0|| file==NULL){
        perror("ERROR - Creating new file\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

void writeQ1File(FILE * stream,Query1ADT query1){
    //Header for Q1 .csv
    fputs("Infraction;Tickets\n",stream);
    
    //Write rows for Q1 .csv
    for (size_t i = 0; i < query1->dim; i++)
        fprintf(stream,"%s;%ld\n",query1->infractionsVec[i].infractionName,query1->infractionsVec[i].count);

    fclose(stream);
}
