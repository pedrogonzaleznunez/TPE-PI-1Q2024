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
    size_t dim;                                        //dimension of array
    size_t size;                                       //amount of infractions
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

typedef struct plate{
    char * nameOfPlate;             //name of plate
    size_t cantInfraccion;          //amount of tickets issued under plate nameOfPlate
    struct plate * tail;            //next plate in alphabetical order
}Tplate;

typedef Tplate * TlistPlates;

typedef struct infraccion{
    size_t idInfraccion;
    char * infraccionName;                  //name of the infraction
    TlistPlates plates;                     //list of plates in alphabetic order
    char * MostPopularPlate;                //name of most popular issuer of infraction infractionName
    size_t maxTickets;                      //amount of times that issuer mostPopularPlateName has done infraction infractionName
    struct infraccion * nextInfraccion;     //next infraction in alphabetical order
}Tinfraccion;

typedef Tinfraccion * TlistInfraccion;

typedef struct Query3CDT{
    TlistInfraccion first;            //list of infractions in alphabetic order
}Query3CDT;


// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

// * @brief Comparator function for qsort
// * @param a First element to compare
// * @param b Second element to compare
// * @return 0 if a and b are equal, a positive number if a is greater than b, a negative number if a is less than b
static int comparator(TInfractions * a, TInfractions * b){
    int cmp = b->count - a->count;
    
    if( cmp==0 )
        cmp = strcmp(a->infractionName,b->infractionName);
    return cmp;
}

// * @brief Creates a new Query1ADT
// * @return Query1ADT
// * @precondition None
Query1ADT newQuery1(void){
    return calloc(1, sizeof(Query1CDT));
}

// * @brief Adds a new infraction to the array of infractions
// * @param query1 Query1ADT
// * @param id ID of the infraction
// * @param infractionName Name of the infraction
// * @precondition query1 != NULL
void addInfractionsToVec(Query1ADT query1, unsigned id, char * infractionName){
    if(query1 == NULL)
        return;
    
    //check if the array is full, if so, realloc for more space
    if(query1->dim % BLOCK == 0){
        query1->infractionsVec = realloc(query1->infractionsVec, (query1->dim + BLOCK) * sizeof(TInfractions));
        query1->size += BLOCK;
        
    }
    query1->dim++;

    //save data to the struct
    query1->infractionsVec[query1->dim-1].id = id;
    query1->infractionsVec[query1->dim-1].count = 0;

    query1->infractionsVec[query1->dim-1].infractionName = malloc(( DESCRIP_INFRAC_LENGHT + 2) * sizeof(char));
    strcpy(query1->infractionsVec[query1->dim-1].infractionName, infractionName);

    return;
}

// * @brief Adds an ocurrence to the infraction with id
// * @param query1 Query1ADT
// * @param id ID of the infraction
// * @precondition query1 != NULL
void addInfractionsOcurrences(Query1ADT query1, unsigned id){
    if(query1 == NULL || id > query1->dim)
        return;
    
    query1->infractionsVec[id-1].count++;
    return;
}

// * @brief Sorts the array of infractions in decreasing order
// * @param query1 Query1ADT
// * @precondition query1 != NULL
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
        aux->infraccionName=malloc((strlen(infraccionName)+1)*sizeof(char));
        if(aux->infraccionName== NULL || errno == ENOMEM){
            errno=ENOMEM;
            return infraccionList;
        }
        strcpy(aux->infraccionName,infraccionName);
        int c;
        aux->plates=addPlate(aux->plates,plate,&c);
        aux->maxTickets=c;
        aux->MostPopularPlate=malloc((strlen(plate)+1)*sizeof(char));
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
            infraccionList->MostPopularPlate=malloc((strlen(plate)+1)*sizeof(char));
            if(infraccionList->MostPopularPlate== NULL || errno == ENOMEM){
                errno=ENOMEM;
                return infraccionList;
            }
            strcpy(infraccionList->MostPopularPlate,plate);
            return infraccionList;
        }
        int y;
        if((y=strcmp(infraccionList->MostPopularPlate,plate))>0){
            infraccionList->MostPopularPlate=malloc((strlen(plate)+1)*sizeof(char));
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
        printf("%s;%s;%ld \n",aux->infraccionName,aux->MostPopularPlate,aux->maxTickets);
        aux=aux->nextInfraccion;
    }
}



static void freeSublist3(TlistPlates sublist){
    if(sublist == NULL){
        return ;
    }
    freeSublist3(sublist->tail);
    free(sublist->nameOfPlate);
    free(sublist);
    return;
}


static void freeList3(TlistInfraccion list){
    if(list == NULL){
        return ;
    }
    freeList3(list->nextInfraccion);
    freeSublist3(list->plates);
    free(list->infraccionName);
    free(list->MostPopularPlate);
    free(list);
    return;
}


void freeInfraccion3(Query3ADT query3){
    freeList3(query3->first);
    free(query3);
}

