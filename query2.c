#include <stdio.h>
#include <stdlib.h>
#include "query2.h"

typedef struct agencies{
    char * agency;                  //name of the agency
    TListInfraction first;          //list of infractions
    struct agencies * tail;         //next agency
}TAgencies;

typedef struct agencies * TListAgency;

typedef struct infractions{
    char * infraction;              //name of the infraction
    size_t count;                   //number of infractions
    struct infractions * tail;      //next infraction
}TInfraction;

typedef struct infractions * TListInfraction;

typedef struct Query2CDT{
    TListAgency first;                    //list of agencies
    size_t size;                          //number of agencies
}Query2CDT;

Query2ADT newQuery2(){
    return calloc(1,sizeof(Query2CDT));
}
//fijarme sutilezas de desempate por orden alfabetico, no contemple caso de que strcmp sea cero(ver eso)

static TListInfraction addInfractionRec(TListInfraction list,char * infraction, size_t totalFines){
    int c;
    if(list == NULL || totalFines > list->count || (totalFines == list->count && (c=strcmp(infraction, list->infraction) < 0)) ){
        TListInfraction aux=malloc(sizeof(TInfraction));
        errno=0;
        if(aux == NULL || errno == ENOMEM){
            return list;
        }
        aux->infraction=malloc(sizeof(char) * (strlen(infraction) + 1));
        // if memory not allocated succesfully, set errno and free
        if(aux->infraction == NULL){
            errno=ENOMEM;
            free(aux);
            return list;
        }
        strcpy(aux->infraction,infraction);
        aux->count=totalFines;
        return aux;
    }
    list->tail=addInfractionRec(list->tail,infraction,totalFines);
    return list;
}

static TListAgency findAgency(TListAgency agencies, char * name) {
    TListAgency aux = agencies;
    while ( aux != NULL) {
        int c = strcmp(aux->first, name);
        if ( c == 0) {
            return aux;
        }
        if ( c > 0)
            return NULL;
        aux = aux->tail;
    }
    return NULL;
}

void addInfraction(TListAgency agencies, char *issuingAgency,char * infraction, size_t totalFines){
    TListAgency aux = findAgency(agencies, issuingAgency);
    // not checking if I find the agency or not, since they are extracted from the csv
    aux->first = addInfractionRec(aux->first,infraction,totalFines); // If it failed, errno will be left with a value other than zero
}

static TListAgency addAgencyRec(TListAgency first, char * name, int *ok){
    int d;
    if ( first == NULL || ( d = strcmp(first->agency, name)) > 0) {
        errno = 0;
        TListAgency aux = malloc(sizeof(TAgencies));
        if ( aux==NULL || errno == ENOMEM) {
           return first;  // If an error ocurred, it returns the same list, without making changes
        }
        aux->first= NULL;// ?
        aux->agency= malloc(strlen(name)+1);
        if(aux->agency == NULL){
            errno=ENOMEM;
            free(aux);
            return first;
        }
        strcpy(aux->agency, name);
        aux->tail = first;
        *ok=1;
        return aux;
    }
    if ( d < 0){
        first->tail = addAgencyRec(first->tail, name, ok);
    }
    return first;
}

void addAgency(Query2ADT query, char * nameOfAgency) {
    int ok=0;
    query->first= addPersonRec(query->first, nameOfAgency, &ok);
    if(ok){
        query->size++;
    }
}

