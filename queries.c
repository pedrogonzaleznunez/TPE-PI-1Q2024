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
    size_t iter;                                      //iterator
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
    TListAgency first;                  //list of agencies
    TListAgency iter;                
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

typedef struct infractions3{
    TlistPlates first ;                                             //ID of the infraction
    char * infractionName;   
    char * mostPopularPlate;                                 //Name of the infraction              
    size_t maxTickets;                                                //amount of times that infraction has been done           
}TInfractions3;

typedef struct Query3CDT{
    TInfractions3 * infractionsVec3;                      //array of infractions
    size_t dim;                                        //dimension of array                                      //amount of infractions
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
    Query3ADT aux= calloc(1,sizeof(Query3CDT));
    return aux;
}
//takes infractionName from query1
//creates a new infraction in query3

void createVec3(Query1ADT query1, Query3ADT query3){
    query3->infractionsVec3 = calloc(query1->dim, sizeof(TInfractions3));
    query3->dim = query1->dim;
    return;
}

TlistPlates addPlate(TlistPlates list, char * plate, int * cant){
    int c;
    if(list==NULL || (c=strcmp(list->nameOfPlate,plate) > 0)){
        TlistPlates aux=malloc(sizeof(Tplate));
        aux->cantInfraccion=1;
        *cant=1;
        aux->nameOfPlate=malloc(sizeof(char) * (strlen(plate)+1));
        strcpy(aux->nameOfPlate,plate);
        aux->tail=list;
        return aux;
    }
    if(c < 0){
        list->tail=addPlate(list->tail,plate,cant);
        return list;
    }
    list->cantInfraccion++;
    *cant=list->cantInfraccion;
    return list;
}

void addInfraction3(Query1ADT query1,Query3ADT query3,int id,char * plate){
    //check if the id is valid
    if(id > query1->dim || query1->infractionsNames[id-1]==NULL){
        return;
    }
    int cant=0;
    query3->infractionsVec3[id-1].infractionName=query1->infractionsNames[id-1];
    query3->infractionsVec3[id-1].first=addPlate(query3->infractionsVec3[id-1].first,plate,&cant);
    if(cant > query3->infractionsVec3[id-1].maxTickets){
        query3->infractionsVec3[id-1].mostPopularPlate=realloc(query3->infractionsVec3[id-1].mostPopularPlate,sizeof(char) * (strlen(plate)+1));
        strcpy(query3->infractionsVec3[id-1].mostPopularPlate,plate);
        query3->infractionsVec3[id-1].maxTickets=cant;

    }else if(cant == query3->infractionsVec3[id-1].maxTickets){
        if(strcmp(query3->infractionsVec3[id-1].mostPopularPlate,plate) > 0){
            query3->infractionsVec3[id-1].mostPopularPlate=realloc(query3->infractionsVec3[id-1].mostPopularPlate,sizeof(char) * (strlen(plate)+1));
            strcpy(query3->infractionsVec3[id-1].mostPopularPlate,plate);
        }
    }
    return;
}

static void freeList(TlistPlates list){
    if(list==NULL){
        return;
    }
    freeList(list->tail);
    free(list->nameOfPlate);
    free(list);
    return;
}

static void freeVec(TInfractions3 * vec,size_t dim){
    for(int i=0; i < dim; i++){
        freelist(vec[i].first);
        free(vec[i].infractionName);
        free(vec[i].mostPopularPlate);
    }
    free(vec);
    return ;
}

void freeQ3(Query3ADT query3){
    freeVec(query3->infractionsVec3,query3->dim);
    free(query3);
}
void sortInfractionsDecreasingQuery3(Query3ADT query3){
    if(query3 == NULL)
        return;

    qsort(query3->infractionsVec3, query3->dim, sizeof(TInfractions3),strcmp);
    return;
}

void printForQuery3(Query3ADT query3){
    int i;
    for(i=0;i<query3->dim;i++){
        printf("%s,%s,%ld \n",query3->infractionsVec3[i].infractionName,query3->infractionsVec3[i].mostPopularPlate,query3->infractionsVec3[i].maxTickets);
    }
    printf("contador: %d",i);
}