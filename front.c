// #include "front.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <errno.h>
// #include "queries.h"

// //FrontEnd functions
// FILE * newFile(char * name){
//     FILE * file=fopen(name,"wt");
//     if(errno != 0|| file==NULL){
//         perror("ERROR - Creating new file\n");
//         exit(EXIT_FAILURE);
//     }
//     return file;
// }

// void writeQ1File(FILE * stream,Query1ADT query1){
//     //Header for Q1 .csv
//     fputs("infraction;tickets\n",stream);
    
//     //Write rows for Q1 .csv
    
//     fclose(stream);
// }

// void writeQ2File(FILE * stream,Query2ADT query2){
//     //Header for Q2 .csv
//     fputs("issuingAgency;infraccion;tickets\n",stream);
    
//     //Write rows for Q2 .csv
    
//     fclose(stream);
// }

// void writeQ3File(FILE * stream,Query3ADT query3){
//     //Header for Q2 .csv
//     fputs("infraccion;plate;tickets\n",stream);
    
//     //Write rows for Q2 .csv
    
//     fclose(stream);
// }

// //Agregar queries.c --> iteradores

// void toBeginQ1(Query1ADT query1){
//     query1->iter=0;
// }

// void toBeginQ2(Query2ADT query2){
//     query2->iter = query2->first;
// }

// void toBeginQ3(Query3ADT query3){
//     query3->iter = query3->first;
// }

// int hasNextQ1(Query1ADT query1){
//     return query1->iter < query1->dim;
// }

// int hasNextQ2(Query2ADT query2){
//     return query2->tail != NULL;
// }

// int hasNextQ3(Query3ADT query3){
//     return query3->tail != NULL;
// }

// TInfractions nextQ1(Query1ADT query1){
//     if(!hasNextQ1(query1)){
//         exit(1);
//     }
//     TIntInfractions aux = query1->infraction[query1->iter];
//     query1->iter++;
//     return aux;
// }

// TAgencies nextQ2(Query2ADT query2){
//     if(!hasNextQ2(query2)){
//         exit(1);
//     }
//     TAgencies aux = query2->tail->data;
//     query2->tail = query2->tail->next;
//     return aux;
// }

// TTickets nextQ3(Query3ADT query3){
//     if(!hasNextQ3(query3)){
//         exit(1);
//     }
//     TTickets aux = query3->tail->data;
//     query3->tail = query3->tail->next;
//     return aux;
// }

