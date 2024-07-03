#include "queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1024
#define TRUE 1
#define FALSE !TRUE

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

typedef struct infractions1{
    char * infraction;
    size_t count;
}TInfractions1;

typedef struct Query1CDT{
    TInfractions1 * infractionsVec; 
    size_t dim;
}Query1CDT;

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //

typedef struct agencies{
    char * agencyName;                  //name of the agency
    int * infractions;                  //array of appearances
    size_t dim;                         //dimension of array
    size_t mostPopularID;               // ID of most issued infraction of agency agencyName
    struct agencies * tail;             //next agency
}TAgencies;

typedef struct Query2CDT{
    TListAgency first;                    //list of agencies
    size_t size;                          //number of agencies
}Query2CDT;

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 3 ------------------- //
// ------------------------------------------------------------- //

typedef struct plates{
    char * nameOfPlate;             //name of plate
    size_t countOfTickets;          //amount of tickets issued under plate nameOfPlate
    struct plates * tail;           //next plate in alphabetical order
}TPlates;

typedef TPlates * TListPlates;

typedef struct infractions{
    char * infractionName;                  //name of the infraction
    char * mostPopularPlateName;            //name of most popular issuer of infraction infractionName
    TListPlates plates;                     //list of plates in alphabetic order
    size_t issuingsOfInfraction;            //amount of times that issuer mostPopularPlateName has done infraction infractionName
    struct infractions * tail;             //next infraction in alphabetical order
}TInfractions;

typedef struct infractions * TListInfraction;

typedef struct Query3CDT{
    TListInfraction first;                    //list of infractions in alphabetic order
}Query3CDT;

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

int getDim(Query1ADT query1){
    return query1->dim;
}

Query1ADT newQuery1(void){
    return calloc(1, sizeof(Query1CDT));
}

void addInfractionQ1(Query1ADT query1, char * infraction, size_t id){

    if(query1->dim <= id){
        query1->infractionsVec = realloc(query1->infractionsVec,sizeof(TInfractions1) * (id));

        if(query1->infractionsVec == NULL){
            perror("Failed to allocate memory for new list");
            exit(EXIT_FAILURE);
        }

        for(int i = query1->dim; i <= id ;i++ ){
            query1->infractionsVec[i].count = 0;
            query1->infractionsVec[i].infraction = NULL;
        }

        query1->dim = id + 1;
    }

    query1->infractionsVec[id-1].infraction = malloc(strlen(infraction) + 1);
    strcpy(query1->infractionsVec[id-1].infraction,infraction);

    return;
}

void addTicketsQ1(Query1ADT query1, size_t id){
    if(id >= query1->dim){
        return;
        //CONTROL DE ERROR
    }
    query1->infractionsVec[id].count++;
    return;
}

void freeQuery1(Query1ADT query1){
    free(query1->infractionsVec);
    free(query1);
}


void readInfractions(const char *fileToRead) {

    FILE *file = fopen(fileToRead, "r");
    
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char *token;
    int lineCount = 0,columnCount = 0, found = FALSE, idColumn, descriptionColumn;
    char * descrition, *id;

    while (fgets(line, sizeof(line), file)) {

        token = strtok(line, ";");

        if(lineCount == 0){

            while(token != NULL && !found) {
                
                if(strcmp(token, "id") == 0){
                    idColumn = lineCount;
                } 
                else if(strcmp(token, "description")== 0){
                    descriptionColumn = lineCount;
                    found = TRUE;
                    lineCount++;
                }

                token = strtok(NULL, ";");
            }
        }
        
        while (token != NULL) {
            if (columnCount == idColumn) {
                id = malloc(strlen(token) + 1);
                if (id == NULL) {
                    perror("Failed to allocate memory for plate");
                    exit(EXIT_FAILURE);
                }
                strcpy(id, token);
            } else if (columnCount == descriptionColumn) {
                descrition = malloc(strlen(token) + 1);
                if (descrition == NULL) {
                    perror("Failed to allocate memory for descrition");
                    exit(EXIT_FAILURE);
                }
                strcpy(descrition, token);
            }
            token = strtok(NULL, ";");
            columnCount++;
        }        
    }

    fclose(file);
}

void addInfraction2(TListAgency first,size_t infractionID){
    if(infractionID > first->dim){
        first->infractions=realloc(first->infractions,sizeof(int) * infractionID);
        for(int i=first->dim; i < infractionID;i++){
            first->infractions[i]=0;
        }
        first->dim=infractionID;
    }
    first->infractions[infractionID]++;
    if(first->infractions[infractionID] > first->infractions[first->mostPopularID]){
        first->mostPopularID=infractionID;
    }else if(first->infractions[infractionID] == first->infractions[first->mostPopularID]){
        if(strcmp(fetchName(first->infractions[infractionID]),fetchName(first->infractions[first->mostPopularID])) < 0){
            first->mostPopularID=infractionID;
        }
    }
}

static TListAgency addAgencyRec(TListAgency first, char * name, int *ok,size_t infractionID){
    int d;
    if ( first == NULL || ( d = strcmp(first->agencyName, name)) > 0) {
        errno = 0;
        TListAgency aux = malloc(sizeof(TAgencies));
        if ( aux==NULL || errno == ENOMEM) {
            free(aux);
           return first;  // If an error ocurred, it returns the same list, without making changes
        }
        aux->agencyName= malloc(strlen(name)+1);
        if(aux->agencyName == NULL){
            errno=ENOMEM;
            free(aux);
            return first;
        }
        strcpy(aux->agencyName, name);
        aux->tail = first;
        addInfraction2(aux,infractionID);
        *ok=1;
        return aux;
    }
    if ( d < 0){
        first->tail = addAgencyRec(first->tail, name, ok,infractionID);
    }
    return first;
}

void addAgency(Query2ADT query, char * nameOfAgency, size_t infractionID) {
    int ok=0;
    query->first= addAgencyRec(query->first, nameOfAgency, &ok,infractionID);
    if(ok){
        query->size++;
    }
}

// implementation of functions for query3

Query3ADT newQuery3(void){
    return calloc(1,sizeof(Query3CDT));
}

static TListInfraction findInfraction(TListInfraction first, const char * name) {
    TListInfraction auxF = first;
    while ( auxF != NULL) {
        int c = strcmp(auxF->infractionName, name);
        if ( c == 0) {
            return auxF;
        }
        if ( c > 0){
            return NULL;
        }
        auxF = auxF->tail;
    }
    return NULL;
}

static char * copyStr(char * s){
    errno = 0;
    char * auxS= malloc(strlen(s)+1);
    if ( auxS==NULL || errno == ENOMEM) {
        return NULL;
    }
    return strcpy(auxS,s);
}

static TListPlates addPlate3Rec(TListPlates plates, TListInfraction listAux,char * plate){
    //insert elem con count++
    int name;
    TListPlates auxP;
    if(plates == NULL || (name=strcmp(plate,plates->nameOfPlate)) > 0){
        auxP=malloc(sizeof(TPlates));
        if(auxP == NULL){//control de errores
            free(auxP);
        }
        auxP->nameOfPlate=malloc(sizeof(char) * (strlen(plate) + 1));
        if(auxP->nameOfPlate == NULL){
            free(auxP->nameOfPlate);//control de errores
        }
        strcpy(auxP->nameOfPlate,plate);
        auxP->countOfTickets=1;
    }
    if(name < 0){
        auxP->tail=addPlate3Rec(plates->tail,auxP,plate);
        return auxP;
    }

    if( name == 0){// si la patente ya estaba, le sumo una ocurrencia de la multa
        plates->countOfTickets++;
        if(plates->countOfTickets > listAux->issuingsOfInfraction){
            listAux->issuingsOfInfraction=plates->countOfTickets;
            listAux->mostPopularPlateName=copyString(plate);
        }else if(plates->countOfTickets == listAux->issuingsOfInfraction){//si son iguales, desempato alfabeticamente
                if(strcmp(listAux->mostPopularPlateName, plate) > 0){
                    listAux->mostPopularPlateName=copyString(plate);
                }
        }
    }
    
    return plates;
}

void addPlate(Query3ADT query,char * nameOfInfraction,char * plate){
    TListInfraction auxFind = findInfraction(query->first, nameOfInfraction);
    if ( auxFind != NULL) {
        auxFind->plates = addPlate3Rec(auxFind->plates,auxFind,plate);
    }
}


static TListInfraction addInfraction3Rec(TListInfraction first, char * name){
    int car;
    if ( first == NULL || ( car = strcmp(first->infractionName, name)) > 0) {
        errno = 0;
        TListInfraction aux = malloc(sizeof(TInfractions));
        if ( aux==NULL || errno == ENOMEM) {
            free(aux);
           return first;  // If an error ocurred, it returns the same list, without making changes
        }
        aux->infractionName= malloc(strlen(name)+1);
        if(aux->infractionName == NULL){
            errno=ENOMEM;
            free(aux);
            return first;
        }
        strcpy(aux->infractionName, name);
        aux->tail = first;
        return aux;
    }
    if ( car < 0){
        first->tail = addInfraction3Rec(first->tail, name);
    }
    return first;
}

void addInfraction3(Query3ADT query, char * nameOfInfraction) {
    query->first= addInfractionRec(query->first, nameOfInfraction);
}

