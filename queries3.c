#include <stdlib.h>
#include <stdio.h>
#include "errno.h"
#include "queries.h"
#include "queries.c"
typedef struct plate{
    char * nameOfPlate;
    size_t cantInfraccion;
    struct plate * tail;
}Tplate;

typedef Tplate * TlistPlates;

typedef struct infraccion{
    size_t idInfraccion;
    char * infraccionName;
    TlistPlates plates;
    char * MostPopularPlate;
    size_t maxTickets;
    struct infraccion * nextInfraccion;
}Tinfraccion;

typedef Tinfraccion * TlistInfraccion;

typedef struct Query3CDT{
    TlistInfraccion first;
}Query3CDT;


TlistPlates addPlate(TlistPlates listPlates, char * plate, int * toCheck){
    int c;
    if(listPlates==NULL || (c=strcmp(listPlates->nameOfPlate,plate))>0){
        TlistPlates aux=malloc(sizeof(*aux));
        if ( aux == NULL || errno == ENOMEM) {
           return listPlates;  // If an error ocurred, it returns the same list, without making changes
        }
        aux->nameOfPlate=malloc((strlen(plate)+1)*sizeof(char));
        if(aux->nameOfPlate == NULL || errno ==ENOMEM){
            errno=ENOMEM;
            return listPlates;
        }
        strcpy(aux->nameOfPlate,plate);
        aux->cantInfraccion=1;
        *toCheck=1;
        aux->tail=listPlates;
        return aux;
    }if(c<0){
        listPlates->tail=addPlate(listPlates->tail,plate,toCheck);
        return listPlates;
    }
    listPlates->cantInfraccion++;
    *toCheck=listPlates->cantInfraccion;
    return listPlates;
}

TlistInfraccion addInfractionRec(TlistInfraccion infraccionList, char * infraccionName, size_t infraccionID, char * plate){
    int c;
    if(infraccionList==NULL || (c=strcmp(infraccionList->infraccionName,infraccionName))>0){
        TlistInfraccion aux=malloc(sizeof(*aux));
        if(aux== NULL || errno == ENOMEM){
            errno=ENOMEM;
            return infraccionList;
        }
        aux->nextInfraccion=infraccionList;
        aux->idInfraccion=infraccionID;
        aux->infraccionName=malloc((stlen(infraccionName)+1)*sizeof(char));
        if(aux->infraccionName== NULL || errno == ENOMEM){
            errno=ENOMEM;
            return infraccionList;
        }
        strcpy(aux->infraccionName,infraccionName);
        int c;
        aux->plates=addPlate(aux->plates,plate,&c);
        aux->maxTickets=c;
        aux->MostPopularPlate=malloc((stlen(plate)+1)*sizeof(char));
        if(aux->MostPopularPlate== NULL || errno == ENOMEM){
            errno=ENOMEM;
            return infraccionList;
        }
        strcpy(aux->MostPopularPlate,plate);
        return aux;
    }
    if(c<0){
        infraccionList->nextInfraccion=addInfractionRec(infraccionList->nextInfraccion,infraccionName,infraccionID,plate);
        return infraccionList;
    }
    int maxInfraccion;
    infraccionList->plates=addPlate(infraccionList->plates,plate,&maxInfraccion);
    if(maxInfraccion>=infraccionList->maxTickets){
        if(maxInfraccion>infraccionList->maxTickets){
            infraccionList->maxTickets=maxInfraccion;
            infraccionList->MostPopularPlate=malloc((stlen(plate)+1)*sizeof(char));
        if(infraccionList->MostPopularPlate== NULL || errno == ENOMEM){
            errno=ENOMEM;
            return infraccionList;
        }
            strcpy(infraccionList->MostPopularPlate,plate);
            return infraccionList;
        }
        int y;
        if((y=strcmp(infraccionList->MostPopularPlate,plate))>0){
            infraccionList->MostPopularPlate=malloc((stlen(plate)+1)*sizeof(char));
            if(infraccionList->MostPopularPlate== NULL || errno == ENOMEM){
                errno=ENOMEM;
                return infraccionList;
            }
            strcpy(infraccionList->MostPopularPlate,plate);
        }
    }    
    return infraccionList;
}

void addTicket(Query1ADT query1,Query3ADT query3, size_t infraccionID, char * plate){
    if(query1->infractionsVec[infraccionID].infractionName!=NULL){
        char * infraccionName = malloc((strlen(query1->infractionsVec[infraccionID].infractionName)+1)*sizeof(char));
        strcpy(infraccionName,query1->infractionsVec[infraccionID].infractionName);
        query3->first=addInfractionRec(query3->first, infraccionName, infraccionID, plate);
    }
}

Query3ADT newQuery3(void){
    return calloc(1, sizeof(Query3CDT));
}

void printForQuery3(Query3ADT query3){
    TlistInfraccion aux=query3->first;
    while(aux!=NULL){
        printf("%s;%s;%d \n",aux->infraccionName,aux->MostPopularPlate,aux->maxTickets);
        aux=aux->nextInfraccion;
    }
}



static void freeSublist3(TlistPlates sublist){
    if(sublist == NULL){
        return ;
    }
    freeSublist(sublist->tail);
    free(sublist->nameOfPlate);
    free(sublist);
    return;
}


static void freeList3(TlistInfraccion list){
    if(list == NULL){
        return ;
    }
    freeList(list->nextInfraccion);
    freeSublist(list->plates);
    free(list->infraccionName);
    free(list->MostPopularPlate);
    free(list);
    return;
}


void freeInfraccion3(Query3ADT query3){
    freeList(query3->first);
    free(query3);
}