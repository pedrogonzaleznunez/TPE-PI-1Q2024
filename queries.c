#include "queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MAX_LINE_LENGTH 100
#define BLOCK 10
#define SET_ERRNO 0
#define TRUE 1
#define FALSE !TRUE

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

typedef struct infractions1{
    unsigned id;                                                //ID of the infraction
    char * infractionName;                                      //Name of the infraction              
    long count;                                                 //amount of times that infraction has been done           
}TInfractions;

typedef struct Query1CDT{
    TInfractions * infractionsVec;                      //array of infractions
    size_t dim;                                        //dimension of array
    size_t size;                                       //amount of infractions
    char ** infractionsNames;
    size_t sizeNames;
}Query1CDT;

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //

typedef struct infractions2{
    char * infractionName;
    size_t infractionsAmount;
}TInfraction2;


typedef struct agencies{
    char * agencyName;                  //name of the agency
    TInfraction2 *infractions;           //array of structures with type TInfraction
    size_t dim;                         //dimension of array                        
    size_t mostPopularID;               // ID of most issued infraction of agency agencyName
    struct agencies * tail;             //next agency
}TAgencies;

typedef struct Query2CDT{
    TListAgency first;                    //list of agencies
}Query2CDT;

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
    errno= SET_ERRNO;
    if(query1 == NULL)
        return;
    
    //check if the array is full, if so, realloc for more space
    if(query1->dim % BLOCK == 0){
        query1->infractionsVec = realloc(query1->infractionsVec, (query1->dim + BLOCK) * sizeof(TInfractions));
        if(query1->infractionsVec == NULL){
            errno=ENOMEM;
            return ;
        }
        query1->size += BLOCK;
        
    }

    if(query1->sizeNames < id){
        query1->infractionsNames = realloc(query1->infractionsNames, (id) * sizeof(char *));
        if(query1->infractionsNames == NULL){
            errno=ENOMEM;
            return ;
        }
        for(int i = query1->sizeNames; i < id; i++){
            query1->infractionsNames[i] = NULL;
        }
        query1->sizeNames = id;
    }

    query1->dim++;
    //save data to the struct
    query1->infractionsVec[query1->dim-1].id = id;
    query1->infractionsVec[query1->dim-1].count = 0;

    query1->infractionsVec[query1->dim-1].infractionName = malloc(( DESCRIP_INFRAC_LENGHT + 2) * sizeof(char));
    if(query1->infractionsVec[query1->dim-1].infractionName == NULL){
            errno=ENOMEM;
            return ;
        }
    strcpy(query1->infractionsVec[query1->dim-1].infractionName, infractionName);

    query1->infractionsNames[id-1] = query1->infractionsVec[query1->dim-1].infractionName;

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


//free query1
static void freeVec(TInfractions * vec,size_t dim){
    for(size_t idx=0; idx < dim; idx++){
        free(vec[idx].infractionName);
    }
    free(vec);
    return ;
}

void freeQuery1(Query1ADT query1){
    if(query1 == NULL)
        return;
    freeVec(query1->infractionsVec,query1->dim);
    free(query1->infractionsNames);
    free(query1);
    return ;
}
// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //

Query2ADT newQuery2(void){
    return calloc(1,sizeof(Query2CDT));
}

static TListAgency addAgencyRec(Query1ADT query1, TListAgency agencies, char * nameOfAgency, size_t infractionID){
    int d;
    if(agencies == NULL || (d=strcmp(agencies->agencyName,nameOfAgency))>0){
        TListAgency new = malloc(sizeof(TAgencies));
        new->agencyName = malloc((strlen(nameOfAgency) + 1)* sizeof(char));
        strcpy(new->agencyName,nameOfAgency);
        new->infractions = NULL;
        new->tail = agencies;
        new->mostPopularID=infractionID;
        new->dim = 0;
        //llamado para agregar la infraccion
        addInfraction2(query1,new,infractionID);
        return new;
    }
    if(d<0){
        agencies->tail = addAgencyRec(query1,agencies->tail,nameOfAgency,infractionID);
        return agencies;
    }
    //if the agency already exists
    addInfraction2(query1,agencies,infractionID);
    return agencies;
        
}

void addInfraction2(Query1ADT query1,TListAgency first,size_t infractionID){
    if(query1 == NULL || first == NULL){
        return;
    }
    
    if(first->dim < infractionID){

        first->infractions = realloc(first->infractions,infractionID * sizeof(TInfraction2));

        for(size_t i = first->dim; i < infractionID; i++){
            first->infractions[i].infractionName = NULL;
            first->infractions[i].infractionsAmount = 0;
        }
        
        first->dim = infractionID;
        
    }

    //add ocurrence of infraction, as it exists
    first->infractions[infractionID-1].infractionsAmount++;

    //check if it is the most popular infraction
    if(first->infractions[infractionID-1].infractionsAmount > first->infractions[first->mostPopularID-1].infractionsAmount){
        first->mostPopularID = infractionID;
    }
    // if it is the same amount of infractions, check if the name is lexicographically smaller
    else if(first->infractions[infractionID-1].infractionsAmount == first->infractions[first->mostPopularID-1].infractionsAmount){
        if(strcmp(query1->infractionsNames[infractionID-1],query1->infractionsNames[first->mostPopularID-1]) < 0)
            first->mostPopularID = infractionID;
    }

    return;
}

void addAgency(Query1ADT query1,Query2ADT query2, char * nameOfAgency, size_t infractionID){    
    if( query1 == NULL || query2 == NULL ||  query1->sizeNames < infractionID || query1->infractionsNames[infractionID-1] == NULL){
        return;
    }
    
    query2->first = addAgencyRec(query1,query2->first,nameOfAgency,infractionID);
    return;
}

//free query2
static void freeList2(TListAgency list){
    if(list == NULL){
        return ;
    }
    freeList2(list->tail);
    free(list->infractions);
    return;
}

void freeQuery2(Query2ADT query2){
    freeList2(query2->first);
    free(query2);
    return;
}

void printInfractions2(Query1ADT query1, Query2ADT query2){
    TListAgency aux = query2->first;
    while(aux != NULL){
        printf("%s;%s;%ld\n",aux->agencyName,query1->infractionsNames[aux->mostPopularID-1],aux->infractions[aux->mostPopularID-1].infractionsAmount);
        aux = aux->tail;
    }
    return;
}

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 3 ------------------- //
// ------------------------------------------------------------- //

Query3ADT newQuery3(void){
    return calloc(1, sizeof(Query3CDT));
}


static TlistPlates addPlates(TlistPlates list,const char *plate, int * toCheck){
    int c;
    if(list==NULL || (c=strcmp(list->nameOfPlate,plate))>0){
        TlistPlates aux=malloc(sizeof(Tplate));
        aux->nameOfPlate=malloc((strlen(plate)+1) * sizeof(char));
        strcpy(aux->nameOfPlate,plate);
        aux->cantInfraccion=1;
        aux->tail=list;
        return aux;
    }
    if(c==0){
        list->cantInfraccion++;
        *toCheck=list->cantInfraccion;
        return list;
    }
    list->tail=addPlates(list->tail,plate,toCheck);
    return list;
}

static TlistInfraccion addInfraccion3(TlistInfraccion list,char * infractionName,int infraccionID,char * plate){
    int c;
    if(list==NULL || (c=strcmp(list->infraccionName,infractionName))>0){
        TlistInfraccion aux=malloc(sizeof(Tinfraccion));
        aux->idInfraccion=infraccionID;
        aux->nextInfraccion=list;
        aux->infraccionName=malloc((strlen(infractionName)+1)*sizeof(char));
        strcpy(aux->infraccionName,infractionName);
        aux->MostPopularPlate=malloc((strlen(plate)+1)*sizeof(char));
        strcpy(aux->MostPopularPlate,plate);
        int p = 0;
        aux->plates=NULL;
        aux->plates=addPlates(aux->plates,plate,&p);
        aux->maxTickets=p;
        return aux;
    }
    if(c==0){
        int maxInfrac=0;
        list->plates=addPlates(list->plates,plate,&maxInfrac);
        if(maxInfrac>list->maxTickets || (list->maxTickets==maxInfrac && (strcmp(list->MostPopularPlate,plate))>0)){
            list->maxTickets=maxInfrac;
            list->MostPopularPlate=realloc(list->MostPopularPlate,((strlen(plate))+1)* sizeof(char));
            strcpy(list->MostPopularPlate,plate);
        }
        return list;
    }
    list->nextInfraccion=addInfraccion3(list->nextInfraccion,infractionName,infraccionID,plate);
    return list;
}

void addTicket(Query1ADT query1, Query3ADT query3, char * plate,int infraccionID){
    if((query1!=NULL && plate!=NULL) && (infraccionID<=query1->sizeNames && query1->infractionsNames[infraccionID-1]!=NULL)){
        query3->first=addInfraccion3(query3->first,query1->infractionsNames[infraccionID-1],infraccionID,plate);
    }
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

