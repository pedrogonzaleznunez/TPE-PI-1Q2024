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
char * getInfractionName(Query1ADT query, unsigned id);

Query1ADT newQuery1(void){
    return calloc(1, sizeof(Query1CDT));
}

// static int comparator(TInfractions a, TInfractions b){
//     int cmp=a.count-b.count;
//     if( cmp==0)
//         cmp=strcmp(getInfractionName(query1, a.id), getInfractionName(query1, b.id));
//     return cmp;
// };

// static void swap( Query1ADT query, size_t n, size_t m){
// 	TInfractions aux = query->infractionsByOcurrences[n];
// 	query->infractionsByOcurrences[n] = query->infractionsByOcurrences[m];
// 	query->infractionsByOcurrences[m] = aux;
// }

static int where( Query1ADT query, unsigned id){
    for( int i = 0; i < query->dimOcurrences; i++ )
		if( query->infractionsByOcurrences[i].id == id)
			return i;
	return -1;
}

void addInfractionsOcurrences(Query1ADT query1, unsigned id){
    if(query1 == NULL)
        return;
    
    int n = where(query1, id);
    
    if(where(query1, id) < 0){
        if(query1->dimOcurrences % BLOCK == 0)
            query1->infractionsByOcurrences = realloc(query1->infractionsByOcurrences, (query1->dimOcurrences + 1 + BLOCK)*sizeof(TInfractions));

        query1->infractionsByOcurrences[query1->dimOcurrences].id = id;
        query1->infractionsByOcurrences[query1->dimOcurrences].count = 1;
        query1->dimOcurrences++;
    }

    else{
        query1->infractionsByOcurrences[n].count++;
    }
    return;
}

void sortInfractionsDecreasing(Query1ADT query1){
    if(query1 == NULL)
        return;
    
    qsort(query1->infractionsByOcurrences, query1->dimOcurrences, sizeof(TInfractions),strcasecmp);

}

// void addInfractionsName(Query1ADT query1, unsigned id, char * infractionName){
//     if(query1 == NULL)
//         return;
//     if(id > query1->dimNames){
//         query1->infractionsName = realloc(query1->infractionsName, id * sizeof(char *));
//         for( int i = query1->dimNames; i < id; i++)
//             query1->infractionsName[i] = NULL;
//         query1->dimNames = id;
//     }

//     query1->infractionsName[id-1] = malloc((DESCRIP_INFRAC_LENGHT + 1) * sizeof(char));
//     //strcpy(query1->infractionsName[id-1], infractionName);
//     strncpy(query1->infractionsName[id-1], infractionName, DESCRIP_INFRAC_LENGHT);
//     query1->infractionsName[id-1][DESCRIP_INFRAC_LENGHT] = '\0';
//     return;
// }

void printInfractions(Query1ADT query1){
    if(query1 == NULL)
        return;
    for( int i = 0; i < query1->dimOcurrences; i++){
        if(getInfractionName(query1, query1->infractionsByOcurrences[i].id) == NULL)
            continue;
        printf("%s: %ld\n", getInfractionName(query1, query1->infractionsByOcurrences[i].id), query1->infractionsByOcurrences[i].count);
        puts("");
    }
}

void freeQuery1(Query1ADT query1){
    if(query1 == NULL)
        return;
    free(query1->infractionsByOcurrences);
    for( int i = 0; i < query1->dimNames; i++){
        free(query1->infractionsName[i]);
    }
    free(query1->infractionsName);
    free(query1);

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

