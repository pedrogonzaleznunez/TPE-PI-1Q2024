#include <stdio.h>
#include "queries.h"
#include "query2.h"
#include "errno.h"
//esto despues veo donde lo pongo

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
typedef struct infractions{
    char * infractionName;
    size_t infractionsAmount;
}TInfraction;

typedef struct agencies* TListAgency;

typedef struct agencies{
    char * agencyName;                  //name of the agency
    TInfraction *infractions;           //array of structures with type TInfraction
    size_t dim;                         //dimension of array                        
    size_t mostPopularID;               // ID of most issued infraction of agency agencyName
    struct agencies * tail;             //next agency
}TAgencies;

typedef struct Query2CDT{
    TListAgency first;                    //list of agencies
}Query2CDT;

typedef struct Query1CDT * Query1ADT;

Query2ADT newQuery2(void){
    return calloc(1,sizeof(Query2CDT));
}

static void copyStr(TInfraction * vec,size_t infractionID,char * s){
    vec[infractionID].infractionName= realloc(vec[infractionID].infractionName,(strlen(s) + 1));
        if(vec[infractionID].infractionName == NULL){
            errno=ENOMEM;
            return;
        }
        strcpy(vec[infractionID].infractionName,s);
        return;
}

void addInfraction2(Query1ADT query1,TListAgency first,size_t infractionID){
    if(query1->infractionsVec[infractionID].infractionName != NULL){// if valid infraction contained in csv infractions,evaluate. If not, ignore it
        if(infractionID > first->dim){
            first->infractions=realloc(first->infractions,sizeof(TInfraction) * infractionID);
            if(first->infractions == NULL){
                errno=ENOMEM;
                return first;
            }
            for(int i=first->dim; i < infractionID;i++){
                first->infractions[i].infractionsAmount=0;
                first->infractions[i].infractionName=NULL;
            }
            first->dim=infractionID + 1;
        }
        first->infractions[infractionID].infractionsAmount++;
        if(first->infractions[infractionID].infractionName==NULL){
            copyStr(first->infractions,infractionID,query1->infractionsVec[infractionID].infractionName);
        }

        if(first->infractions[infractionID].infractionsAmount >= first->infractions[first->mostPopularID].infractionsAmount){
            if(first->infractions[infractionID].infractionsAmount > first->infractions[first->mostPopularID].infractionsAmount){
                copyStr(first->infractions,first->mostPopularID,query1->infractionsVec[infractionID].infractionName);
                if(first->infractions[first->mostPopularID].infractionName == NULL){
                    free(first->infractions[first->mostPopularID].infractionName);
                    return ;
                }
                first->mostPopularID=infractionID;
                return; //actualizo id y nombre
            }
            if(strcmp(first->infractions[infractionID].infractionName,first->infractions[first->mostPopularID].infractionName) < 0){
                copyStr(first->infractions,first->mostPopularID,first->infractions[infractionID].infractionName);
                first->mostPopularID=infractionID;
            }
           
        }
    }
    return ;
}


static TListAgency addAgencyRec(Query1ADT query1, TListAgency first, char * name, size_t infractionID){
    int d;
    if ( first == NULL || ( d = strcmp(first->agencyName, name)) > 0) {
        errno = 0;
        TListAgency aux = malloc(sizeof(TAgencies));
        if ( aux == NULL || errno == ENOMEM) {
           return first;  // If an error ocurred, it returns the same list, without making changes
        }
        aux->agencyName= malloc((strlen(name)+ 1)* sizeof(char));
        if(aux->agencyName == NULL){
            errno=ENOMEM;
            return first;
        }
        strcpy(aux->agencyName, name);
        aux->tail = first;
        addInfraction2(query1,aux,infractionID);
        return aux;
    }
    if ( d < 0){
        first->tail = addAgencyRec(query1,first->tail, name,infractionID);
    }
    addInfraction2(query1,first,infractionID);
    return first;
}

void addAgency(Query1ADT query1,Query2ADT query, char * nameOfAgency, size_t infractionID){
    query->first= addAgencyRec(query1,query->first, nameOfAgency,infractionID);
    return ;
}
//free query2
static void freeVec(struct infractions * vec,size_t dim){
    for(int i=0; i < dim;i++){
        free(vec[i].infractionName);
    }
    return ;
}

static void freeList2(TListAgency list){
    if(list == NULL){
        return ;
    }
    freeList2(list->tail);
    freeVec(list->infractions,list->dim);
    free(list->infractions);
    return;
}

void freeQuery2(Query2ADT query2){
    freeList2(query2->first);
    free(query2);
    return;
}