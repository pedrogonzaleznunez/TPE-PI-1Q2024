#include <stdio.h>
#include <errno.h>
#include "query3.h"
typedef struct plates{
    char * nameOfPlate;             //name of plate
    size_t countOfTickets;          //amount of tickets issued under plate nameOfPlate
    struct plates * tail;           //next plate in alphabetical order
}TPlates;

typedef TPlates * TListPlates;
typedef struct infractions{
    char * infractionName;                  //name of the infraction
    TListPlates plates;                     //list of plates in alphabetic order
    char * mostPopularPlateName;            //name of most popular issuer of infraction infractionName
    size_t issuingsOfInfraction;            //amount of times that issuer mostPopularPlateName has done infraction infractionName
    struct infractions * tail;             //next infraction in alphabetical order
}TInfractions;

typedef struct infractions * TListInfraction;

typedef struct Query3CDT{
    TListInfraction first;                    //list of infractions in alphabetic order
}Query3CDT;

Query3ADT newQuery3(){
    return calloc(1,sizeof(Query3CDT));
}

void addPlate(Query3ADT query,char * nameOfInfraction,char * plate){
    TListInfraction aux = findPerson(query->first, nameOfInfraction);
    if ( aux != NULL) {
        aux->plates = addPlateRec(aux->plates,nameOfInfraction);
    }
}

static TListInfraction addInfractionRec(TListInfraction first, char * name){
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
        first->tail = addInfractionRec(first->tail, name);
    }
    return first;
}

void addInfraction(Query3ADT query, char * nameOfInfraction) {
    query->first= addInfractionRec(query->first, nameOfInfraction);
}