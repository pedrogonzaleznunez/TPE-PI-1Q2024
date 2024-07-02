#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "query2.h"
#include "query1.h"

typedef struct agencies{
    char * agencyName;                  //name of the agency
    int * infractions;                  //array of appearances
    size_t dim;                         //dimension of array
    size_t mostPopularID;               // ID of most issued infraction of agency agencyName
    struct agencies * tail;             //next agency
}TAgencies;

typedef struct agencies * TListAgency;

typedef struct Query2CDT{
    TListAgency first;                    //list of agencies
    size_t size;                          //number of agencies
}Query2CDT;

Query2ADT newQuery2(){
    return calloc(1,sizeof(Query2CDT));
}
//changes in structure, as in execution time is not vible to do an "ordered list" and reorganize it
//we are switching a list for an aparreance vector in which the one w the most appearances will be the one stored in the structure and exported

void addInfraction(TListAgency first,size_t infractionID){
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
        addInfraction(aux,infractionID);
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
