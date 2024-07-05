#include "query2.h"
#include "errno.h"
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
    size_t dim; //dimension of array                        
    size_t mostPopularID;               // ID of most issued infraction of agency agencyName
    struct agencies * tail;             //next agency
}TAgencies;

typedef struct Query2CDT{
    TListAgency first;                    //list of agencies
}Query2CDT;


void addInfraction2(Query1ADT query1,TListAgency first,size_t infractionID){
    if(query1->infractionsVec[infractionID].infractionName != NULL){// if valid infraction contained in csv infractions,evaluate. If not, ignore it
        if(infractionID > first->dim){
            first->infractions=realloc(first->infractions,sizeof(TInfraction) * infractionID);
            for(int i=first->dim; i < infractionID;i++){
                first->infractions[i].infractionsAmount=0;
                first->infractions[i].infractionName=NULL;
            }
            first->dim=infractionID;
        }
        first->infractions[infractionID].infractionsAmount++;
        if(first->infraccions[infractionID].infraccionName==NULL){
        first->infractions[infractionID].infractionName=malloc(sizeof(char)*(strlen(query1->infractionsVec[infractionID].infractionName)+1));
        strcpy(first->infractions[infractionID].infractionName,query1->infractionsVec[infractionID].infractionName);j
        }

        if(first->infractions[infractionID].infractionsAmount >= first->infractions[first->mostPopularID].infractionsAmount){
            if(first->infractions[infractionID].infractionsAmount > first->infractions[first->mostPopularID].infractionsAmount){
                first->mostPopularID=infractionID;
                    return; //actualizo id y nombre
            }
            if(strcmp(first->infractions[infractionID].infractionName,first->infractions[first->mostPopularID].infractionName) < 0){
                first->infractions[first->mostPopularID].infractionName= malloc((strlen(first->infractions[infractionID].infractionName)+ 1)* sizeof(char));
                if(first->infractions[first->mostPopularID].infractionName == NULL){
                    errno=ENOMEM;
                    return first;
                }
                first->mostPopularID=infractionID;
                    return;
            }
           
        }
    }
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
        first->tail = addAgencyRec(first->tail, name,infractionID);
    }
    addInfraction2(query1,first,infractionID);
    return first;
}

void addAgency(Query2ADT query, char * nameOfAgency, size_t infractionID){
    query->first= addAgencyRec(query->first, nameOfAgency,infractionID);
    return ;
}
//free query2

static void freeRec(TListAgency list){
    if(list == NULL){
        return ;
    }
    freeRec(list->tail);
    free(list->infractions);
    free(list->agencyName);
    return;
}

void freeQuery2(Query2ADT query2){
    freeRec(query2->first);
    free(query2);
    return;
}

//free query 3


static void freeSublist(TlistPlates sublist){
    if(sublist == NULL){
        return ;
    }
    freeSublist(sublist->tail);
    freeSublist(list->Plates);
    free(sublist->nameOfPlate);
    return;
}

static void freeList(TlistPlates list){
    if(list == NULL){
        return ;
    }
    freeList(list->tail);
    freeSublist(list->Plates)
    free(list->infraccionName);
    free(list->MostPopularPlate);
    return;
}

void freeQuery3(Query3ADT query3){
    freeList(query3->first);
}