#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "front.h"
#include "main.h"
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
    FILE * streamQ1 = newFile("query1.csv");
    fopen("query1.csv",WRITE);

    //Header for Q1 .csv
    fputs("infraction;tickets\n",streamQ1);
    
    //Write rows for Q1 .csv
    int flag = 0;
    query1Iterator aux = nextQ1(query1,&flag);

    while(!flag){
        fprintf(streamQ1,"%s;%ld\n", aux.infractionName, aux.count);
        aux = nextQ1(query1,&flag);
    }

    fclose(streamQ1);
}


void writeQ2File(Query2ADT query2, Query1ADT query1){
    //Header for Q2 .csv
    FILE * streamQ2 = newFile("query2.csv");
    fopen("query2.csv",WRITE);

    fputs("issuingAgency;infraccion;tickets\n",streamQ2);
    
    //Write rows for Q2 .csv
    int flag = 0;
    query2Iterator aux = nextQ2(query2,query1,&flag);

    while(!flag){
        fprintf(streamQ2,"%s;%s;%u\n", aux.agencyName, aux.infractions, aux.mostPopularID);
        aux = nextQ2(query2,query1,&flag);
    }

    
    fclose(streamQ2);
}

void writeQ3File(Query3ADT query3,Query1ADT query1){
    //Header for Q3 .csv
    FILE * streamQ3 = newFile("query3.csv");
    fopen("query3.csv",WRITE);

    fputs("infraccion;plate;tickets\n",streamQ3);
    
    //Write rows for Q3 .csv
    int flag = 0;
    query3Iterator aux = nextQ3(query3,&flag);

    while (!flag){
        fprintf(streamQ3,"%s;%s;%ld\n", aux.infractionName, aux.mostPopularPlate, aux.maxTickets);
        aux = nextQ3(query3,&flag);
    }
    
    fclose(streamQ3);
}
