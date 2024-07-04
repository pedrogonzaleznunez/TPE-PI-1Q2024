#include "queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MAX_LINE_LENGTH 100
#define BLOCK 10
#define TRUE 1
#define FALSE !TRUE

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

typedef struct infractions{
    unsigned id;                                                //ID of the infraction
    char * infractionName;                                      //Name of the infraction              
    long count;                                                 //amount of times that infraction has been done           
}TInfractions;

typedef struct Query1CDT{
    TInfractions * infractionsVec;                      //array of infractions
    size_t dim;                                        //max amount of infractions
}Query1CDT;

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //

// typedef struct agencies{
//     char * agencyName;                  //name of the agency
//     int * infractions;                  //array of appearances
//     size_t dim;                         //dimension of array
//     size_t mostPopularID;               // ID of most issued infraction of agency agencyName
//     struct agencies * tail;             //next agency
// }TAgencies;

// typedef struct Query2CDT{
//     TListAgency first;                    //list of agencies
//     size_t size;                          //number of agencies
// }Query2CDT;

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 3 ------------------- //
// ------------------------------------------------------------- //

// typedef struct plates{
//     char * nameOfPlate;             //name of plate
//     size_t countOfTickets;          //amount of tickets issued under plate nameOfPlate
//     struct plates * tail;           //next plate in alphabetical order
// }TPlates;

// typedef TPlates * TListPlates;

// typedef struct infractions{
//     char * infractionName;                  //name of the infraction
//     char * mostPopularPlateName;            //name of most popular issuer of infraction infractionName
//     TListPlates plates;                     //list of plates in alphabetic order
//     size_t issuingsOfInfraction;            //amount of times that issuer mostPopularPlateName has done infraction infractionName
//     struct infractions * tail;             //next infraction in alphabetical order
// }TInfractions;

// typedef struct infractions * TListInfraction;

// typedef struct Query3CDT{
//     TListInfraction first;                    //list of infractions in alphabetic order
// }Query3CDT;

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

static int comparator(TInfractions * a, TInfractions * b){
    int cmp = b->count - a->count;
    
    if( cmp==0 )
        cmp = strcmp(a->infractionName,b->infractionName);
    return cmp;
}


Query1ADT newQuery1(void){
    return calloc(1, sizeof(Query1CDT));
}

void addInfractionsToVec(Query1ADT query1, unsigned id, char * infractionName){
   
   if(query1 == NULL)
        return;

    query1->infractionsVec = realloc(query1->infractionsVec, (query1->dim + 1) * sizeof(TInfractions));
    query1->dim++;
    query1->infractionsVec[query1->dim-1].id = id;
    query1->infractionsVec[query1->dim-1].count = 0;

    query1->infractionsVec[query1->dim-1].infractionName = malloc((DESCRIP_INFRAC_LENGHT + 1) * sizeof(char));
    strncpy(query1->infractionsVec[query1->dim-1].infractionName, infractionName, DESCRIP_INFRAC_LENGHT);
    query1->infractionsVec[query1->dim-1].infractionName[DESCRIP_INFRAC_LENGHT] = '\0';
    return;
}

void addInfractionsOcurrences(Query1ADT query1, unsigned id){
    if(query1 == NULL || id > query1->dim)
        return;
    
    query1->infractionsVec[id-1].count++;
    return;
}

void sortInfractionsDecreasing(Query1ADT query1){
    if(query1 == NULL)
        return;
    
    qsort(query1->infractionsVec, query1->dim, sizeof(TInfractions),(int (*)(const void *, const void *))comparator);
    return;
}


void printInfractions(Query1ADT query1){
    if(query1 == NULL)
        return;
    for(int i = 0; i < query1->dim; i++){
        if(query1->infractionsVec[i].count > 0){
            printf("%s: %ld\n", query1->infractionsVec[i].infractionName, query1->infractionsVec[i].count);
        }
    }
}

void freeQuery1(Query1ADT query1){
    
}

// void addInfraction2(TListAgency first,size_t infractionID){
//     if(infractionID > first->dim){
//         first->infractions=realloc(first->infractions,sizeof(int) * infractionID);
//         for(int i=first->dim; i < infractionID;i++){
//             first->infractions[i]=0;
//         }
//         first->dim=infractionID;
//     }
//     first->infractions[infractionID]++;
//     if(first->infractions[infractionID] > first->infractions[first->mostPopularID]){
//         first->mostPopularID=infractionID;
//     }else if(first->infractions[infractionID] == first->infractions[first->mostPopularID]){
//         if(strcmp(fetchName(first->infractions[infractionID]),fetchName(first->infractions[first->mostPopularID])) < 0){
//             first->mostPopularID=infractionID;
//         }
//     }
// }

// static TListAgency addAgencyRec(TListAgency first, char * name, int *ok,size_t infractionID){
//     int d;
//     if ( first == NULL || ( d = strcmp(first->agencyName, name)) > 0) {
//         errno = 0;
//         TListAgency aux = malloc(sizeof(TAgencies));
//         if ( aux==NULL || errno == ENOMEM) {
//             free(aux);
//            return first;  // If an error ocurred, it returns the same list, without making changes
//         }
//         aux->agencyName= malloc(strlen(name)+1);
//         if(aux->agencyName == NULL){
//             errno=ENOMEM;
//             free(aux);
//             return first;
//         }
//         strcpy(aux->agencyName, name);
//         aux->tail = first;
//         addInfraction2(aux,infractionID);
//         *ok=1;
//         return aux;
//     }
//     if ( d < 0){
//         first->tail = addAgencyRec(first->tail, name, ok,infractionID);
//     }
//     return first;
// }

// void addAgency(Query2ADT query, char * nameOfAgency, size_t infractionID) {
//     int ok=0;
//     query->first= addAgencyRec(query->first, nameOfAgency, &ok,infractionID);
//     if(ok){
//         query->size++;
//     }
// }

// // implementation of functions for query3

// Query3ADT newQuery3(void){
//     return calloc(1,sizeof(Query3CDT));
// }

// static TListInfraction findInfraction(TListInfraction first, const char * name) {
//     TListInfraction auxF = first;
//     while ( auxF != NULL) {
//         int c = strcmp(auxF->infractionName, name);
//         if ( c == 0) {
//             return auxF;
//         }
//         if ( c > 0){
//             return NULL;
//         }
//         auxF = auxF->tail;
//     }
//     return NULL;
// }

// static char * copyStr(char * s){
//     errno = 0;
//     char * auxS= malloc(strlen(s)+1);
//     if ( auxS==NULL || errno == ENOMEM) {
//         return NULL;
//     }
//     return strcpy(auxS,s);
// }

// static TListPlates addPlate3Rec(TListPlates plates, TListInfraction listAux,char * plate){
//     //insert elem con count++
//     int name;
//     TListPlates auxP;
//     if(plates == NULL || (name=strcmp(plate,plates->nameOfPlate)) > 0){
//         auxP=malloc(sizeof(TPlates));
//         if(auxP == NULL){//control de errores
//             free(auxP);
//         }
//         auxP->nameOfPlate=malloc(sizeof(char) * (strlen(plate) + 1));
//         if(auxP->nameOfPlate == NULL){
//             free(auxP->nameOfPlate);//control de errores
//         }
//         strcpy(auxP->nameOfPlate,plate);
//         auxP->countOfTickets=1;
//     }
//     if(name < 0){
//         auxP->tail=addPlate3Rec(plates->tail,auxP,plate);
//         return auxP;
//     }

//     if( name == 0){// si la patente ya estaba, le sumo una ocurrencia de la multa
//         plates->countOfTickets++;
//         if(plates->countOfTickets > listAux->issuingsOfInfraction){
//             listAux->issuingsOfInfraction=plates->countOfTickets;
//             listAux->mostPopularPlateName=copyString(plate);
//         }else if(plates->countOfTickets == listAux->issuingsOfInfraction){//si son iguales, desempato alfabeticamente
//                 if(strcmp(listAux->mostPopularPlateName, plate) > 0){
//                     listAux->mostPopularPlateName=copyString(plate);
//                 }
//         }
//     }
    
//     return plates;
// }

// void addPlate(Query3ADT query,char * nameOfInfraction,char * plate){
//     TListInfraction auxFind = findInfraction(query->first, nameOfInfraction);
//     if ( auxFind != NULL) {
//         auxFind->plates = addPlate3Rec(auxFind->plates,auxFind,plate);
//     }
// }


// static TListInfraction addInfraction3Rec(TListInfraction first, char * name){
//     int car;
//     if ( first == NULL || ( car = strcmp(first->infractionName, name)) > 0) {
//         errno = 0;
//         TListInfraction aux = malloc(sizeof(TInfractions));
//         if ( aux==NULL || errno == ENOMEM) {
//             free(aux);
//            return first;  // If an error ocurred, it returns the same list, without making changes
//         }
//         aux->infractionName= malloc(strlen(name)+1);
//         if(aux->infractionName == NULL){
//             errno=ENOMEM;
//             free(aux);
//             return first;
//         }
//         strcpy(aux->infractionName, name);
//         aux->tail = first;
//         return aux;
//     }
//     if ( car < 0){
//         first->tail = addInfraction3Rec(first->tail, name);
//     }
//     return first;
// }

// void addInfraction3(Query3ADT query, char * nameOfInfraction) {
//     query->first= addInfractionRec(query->first, nameOfInfraction);
// }

