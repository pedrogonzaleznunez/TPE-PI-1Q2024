#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "query1.h"

#define MAX_LINE_LENGTH 1024
#define BLOCK 

typedef struct infractions1{
    char * infraction;
    size_t count;
}TInfractions1;

typedef struct Query1CDT{
    TInfractions1 * infractionsVec; 
    size_t dim; 
}Query1CDT;

Query1ADT newQuery1(){
    return calloc(1, sizeof(Query1CDT));
}

// @brief Carga en el CDT, el id con la respectiva infraccion
// @param query1: CDT
// @param infraction: infraccion string
// @param id: id string
void addInfraction(Query1ADT query1, char * infraction, char * id){

    //cast id to int 
    int idInt = atoi(id);

    if(query1->dim <= idInt){
        query1->infractionsVec = realloc(query1->infractionsVec,sizeof(TInfractions1) * (idInt));

        if(query1->infractionsVec == NULL){
            perror("Failed to allocate memory for new list");
            exit(EXIT_FAILURE);
        }

        for(int i = query1->dim; i <= idInt ;i++ ){
            query1->infractionsVec[i].count = 0;
            query1->infractionsVec[i].infraction = NULL;
        }

        query1->dim = idInt + 1;
    }

    query1->infractionsVec[idInt-1].infraction = malloc(strlen(infraction) + 1);
    strcpy(query1->infractionsVec[idInt-1].infraction,infraction);

    return;
}

static void leerColumna(const char *nombreArchivo, Query1ADT query1,  int columnaID, int columnaInfraction) {
    FILE *archivo = fopen(nombreArchivo, "r");
    
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char linea[MAX_LINE_LENGTH];
    char *token;
    int contadorLinea = 0;

    while (fgets(linea, sizeof(linea), archivo)) {

        contadorLinea++;

        if (contadorLinea == 1) {
            continue; // Skips to header
        }

        token = strtok(linea, ";");
        int contadorColumna = 0;

        char * infraction = NULL;
        char * id = NULL;

        while (token != NULL) {

            if (contadorColumna == columnaID) {
                id = malloc(strlen(token) + 1);
                strcpy(id, token);
            } else if (contadorColumna == columnaInfraction) {
                infraction = malloc(strlen(token) + 1);
                strcpy(infraction, token);
            }
            token = strtok(NULL, ";");
            contadorColumna++;
        }

        addInfraction(query1,infraction,id);
    }

    fclose(archivo);
}

static void leerColumna2(const char * archivoTickets, Query1ADT query1, int columnaID){
    FILE *archivo = fopen(archivoTickets, "r");
    
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char linea[MAX_LINE_LENGTH];
    char *token;
    int contadorLinea = 0;

    while (fgets(linea, sizeof(linea), archivo)) {

        contadorLinea++;

        if (contadorLinea == 1) {
            continue; // skips to header
        }

        token = strtok(linea, ";");
        int contadorColumna = 0;

        char * id = NULL;

        while (token != NULL) {

            if (contadorColumna == columnaID) {
                id = malloc(strlen(token) + 1);
                strcpy(id, token);
            }
            token = strtok(NULL, ";");
            contadorColumna++;
        }

        // load the occurrences into the CDT
        int idInt = atoi(id);
        query1->infractionsVec[idInt-1].count++;

    }

    fclose(archivo);
}

void freeQuery1(Query1ADT query1){
    free(query1);
}

int main(int argc, char *argv[]) {

    const char * archivoTickets = "ticketsNYC1000000.csv";
    const char * archivoInfractions = "infractionsNYC.csv";

    int columna1 = 0; // Leer la columna "id"
    int columna2 = 1; // Leer la columna "description"

    int measure_time = 0;

    Query1ADT query1 = newQuery1();

    if (argc > 1 && strcmp(argv[1], "-time") == 0) {
        measure_time = 1;
    }

    clock_t start, end;
    double cpu_time_used;

    if (measure_time) {
        start = clock();
    }
    // 0 columna "id", 1 columna "description"
    leerColumna(archivoInfractions, query1, 0, 1);
    // 2 columna "id"
    leerColumna2(archivoTickets, query1, 2);

    //Print the results
    for(int i = 0; i < query1->dim; i++){
        if(query1->infractionsVec[i].infraction != NULL){
            printf("ID: %d, Infraction: %s, Count: %ld\n",i+1,query1->infractionsVec[i].infraction,query1->infractionsVec[i].count);
        }
    }

    if (measure_time) {
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nEl programa tardó %f segundos en ejecutarse.\n", cpu_time_used);
    }

    return 0;
}
