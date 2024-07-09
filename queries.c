#include "queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "main.h"

#define MAX_LINE_LENGTH 100
#define BLOCK 10
#define SET_ERRNO 0
#define INVALID_ACCESS_MEM 2
#define FAILED_TO_RESERVE_MEM 3

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

struct infractions1{
    unsigned id;                                                //ID of the infraction
    char * infractionName;                                      //Name of the infraction              
    long count;                                                 //amount of times that infraction has been done           
};

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
    char nameOfPlate[PLATE_LENGHT+1];             //name of plate
    size_t cantInfraccion;          //amount of tickets issued under plate nameOfPlate
    struct plate * tail;            //next plate in alphabetical order
}Tplate;

typedef Tplate * TlistPlates;

struct infractions3{
    TlistPlates first ;                                             //ID of the infraction
    char * infractionName;   
    char mostPopularPlate[PLATE_LENGHT+1];                                 //Name of the infraction              
    size_t maxTickets;                                                //amount of times that infraction has been done           
};

typedef struct Query3CDT{
    TInfractions3 * infractionsVec3;                    //array of infractions
    size_t iter;                                        //iterator 
    size_t dim;                                        //dimension of array    
    size_t dimSorted;                         
}Query3CDT;

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

/**
// * @brief Comparator function for qsort in query1
// * @param a First element to compare
// * @param b Second element to compare
// * @return 0 if a and b are equal, a positive number if a is greater than b, a negative number if a is less than b
*/
static int comparator1(TInfractions * a, TInfractions * b){
    int cmp = b->count - a->count;
    
    if( cmp==0 )
        cmp = strcmp(a->infractionName,b->infractionName);
    return cmp;
}
/**
// * @brief Creates a new Query1ADT
// * @return Query1ADT
*/
Query1ADT newQuery1(void){
    return calloc(1, sizeof(Query1CDT));
}


/**
 * @brief Adds a new infraction to the array of infractions
 * @param query1 Query1ADT
 * @param id ID of the infraction
 * @param InfractionName name of the infraction
 * @precondition query1 != NULL
 */
void addInfractionsToVec(Query1ADT query1, unsigned id, char * infractionName){
    errno= SET_ERRNO;
    if(query1 == NULL){
        errno=FAILED_TO_RESERVE_MEM;
        return;
    }
    
    //check if the array is full, if so, realloc for more space
    if(query1->dim % BLOCK == 0){
        query1->infractionsVec = realloc(query1->infractionsVec, (query1->dim + BLOCK) * sizeof(TInfractions));
        if(query1->infractionsVec == NULL){
            errno=FAILED_TO_RESERVE_MEM;
            return ;
        }
        query1->size += BLOCK;
        
    }

    if(query1->sizeNames < id){
        query1->infractionsNames = realloc(query1->infractionsNames, (id) * sizeof(char *));
        if(query1->infractionsNames == NULL){
            errno=FAILED_TO_RESERVE_MEM;
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
            errno=FAILED_TO_RESERVE_MEM;
            return ;
        }
    strcpy(query1->infractionsVec[query1->dim-1].infractionName, infractionName);

    query1->infractionsNames[id-1] = query1->infractionsVec[query1->dim-1].infractionName;

    return;
}
/**
// * @brief Adds an ocurrence to the infraction with id
// * @param query1 Query1ADT
// * @param id ID of the infraction
// * @precondition query1 != NULL
*/
void addInfractionsOcurrences(Query1ADT query1, unsigned id){
    errno=SET_ERRNO;
    if(query1 == NULL || id > query1->dim){
        errno=INVALID_ACCESS_MEM;
        return;
    }
    
    query1->infractionsVec[id-1].count++;
    return;
}
/** 
// * @brief Sorts the array of infractions in decreasing order
// * @param query1 Query1ADT
// * @precondition query1 != NULL
*/
void ricardoSortQuery1(Query1ADT query1){
    errno=SET_ERRNO;
    if(query1 == NULL){
        errno=FAILED_TO_RESERVE_MEM;
        return;
    }

    qsort(query1->infractionsVec, query1->dim, sizeof(TInfractions),(int (*)(const void *, const void *))comparator1);
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

static void freeVec(TInfractions * vec,size_t dim){
    for(size_t idx=0; idx < dim; idx++){
        free(vec[idx].infractionName);
    }
    free(vec);
    return ;
}
/**
 * @brief frees allocted memory
 * @param query1 Query1ADT
 */
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

/**
// * @brief Creates a new Query1ADT
// * @return Query1ADT
*/
Query2ADT newQuery2(void){
    return calloc(1,sizeof(Query2CDT));
}


static TListAgency addAgencyRec(Query1ADT query1, TListAgency agencies, char * nameOfAgency, size_t infractionID){
    int d;
    if(agencies == NULL || (d=strcmp(agencies->agencyName,nameOfAgency))>0){
        TListAgency new = malloc(sizeof(TAgencies));
        if(new == NULL){
            errno=FAILED_TO_RESERVE_MEM;
            return agencies;
        }
        new->agencyName = malloc((strlen(nameOfAgency) + 1)* sizeof(char));
        if(new == NULL){
            errno=FAILED_TO_RESERVE_MEM;
            return agencies;
        }
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

/**
// * @brief Adds infraction into Agency
// * @param query1 Query1ADT
// * @param first Agency to insert the infraction in
// * @param infractionID id of infraction
*/
void addInfraction2(Query1ADT query1,TListAgency first,size_t infractionID){
    if(query1 == NULL || first == NULL){
        return;
    }
    
    if(first->dim < infractionID){

        first->infractions = realloc(first->infractions,infractionID * sizeof(TInfraction2));
        if(first->infractions == NULL){
            errno=FAILED_TO_RESERVE_MEM;
            return ;
        }

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
/**
// * @brief Adds an agency in alphabetical order
// * @param query1 Query1ADT
// * @param query2 Query2ADT
// * @param nameOfAgency name of agency
// * @param infractionID  ID of infractions
*/
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

/**
// * @brief frees allocated memory
// * @param query2 Query2ADT
*/
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

/**
// * @brief Comparator function for qsort in query3
// * @param a First element to compare
// * @param b Second element to compare
// * @return 0 if a and b are equal, a positive number if a is greater than b, a negative number if a is less than b
*/
int comparator3(TInfractions3 * a, TInfractions3 * b){
    return strcmp(a->infractionName,b->infractionName);
}

/**
// * @brief Creates a new Query3ADT
// * @return Query3ADT
*/
Query3ADT newQuery3(void){
    Query3ADT aux = calloc(1,sizeof(Query3CDT));
    return aux;
}
//takes infractionName from query1
/**
// * @brief Creates a new infraction in query3
// * @param query1 Query1ADT
// * @param query3 Query3ADT
*/
void createVec3(Query1ADT query1, Query3ADT query3){
    errno=SET_ERRNO;
    query3->infractionsVec3 = calloc(query1->dim, sizeof(TInfractions3));
    if(query3->infractionsVec3 == NULL){
        errno=FAILED_TO_RESERVE_MEM;
    }
    query3->dim = query1->dim;
    return;
}
/**
// * @brief inserts a plate 
// * @param list list of plates
// * @param plate name of plate
// * @param cant flag of amount of ocurrences
// * @return TlistPlates
*/
TlistPlates addPlate(TlistPlates list, char * plate, int * cant){
    int c;
    if(list==NULL || (c=strcmp(list->nameOfPlate,plate) > 0)){
        TlistPlates aux=malloc(sizeof(Tplate));
        if(aux == NULL){
            errno=FAILED_TO_RESERVE_MEM;
            return list;
        }
        aux->cantInfraccion=1;
        *cant=1;
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
/**
// * @brief adds an infraction to query3
// * @param query1 query1ADT
// * @param query3 Query3ADT
// * @param id ID of infraction
// * @param plate Name of plate
*/
void addInfraction3(Query1ADT query1,Query3ADT query3,int id,char * plate){
    //check if the id is valid
    errno=SET_ERRNO;
    if(id > query1->dim || query1->infractionsNames[id-1]==NULL){
        errno=INVALID_ACCESS_MEM;
        return;
    }
    int cant=0;

    query3->infractionsVec3[id-1].infractionName = query1->infractionsNames[id-1];
    query3->infractionsVec3[id-1].first=addPlate(query3->infractionsVec3[id-1].first,plate,&cant);

    if(cant > query3->infractionsVec3[id-1].maxTickets){
        strcpy(query3->infractionsVec3[id-1].mostPopularPlate,plate);
        query3->infractionsVec3[id-1].maxTickets=cant;

    }else if(cant == query3->infractionsVec3[id-1].maxTickets){
        if(strcmp(query3->infractionsVec3[id-1].mostPopularPlate,plate) > 0){
            strcpy(query3->infractionsVec3[id-1].mostPopularPlate,plate);
        }
    }
    return;
}

static void freeList3(TlistPlates list){
    if(list==NULL){
        return;
    }
    freeList3(list->tail);
    free(list);
    return;
}

static void freeVec3(TInfractions3 * vec,size_t dim){
    for(int i=0; i < dim; i++){
        if(vec[i].first != NULL)
            freeList3(vec[i].first);
    }    
    free(vec);
    return ;
}
/**
// * @brief frees allocated memory
// * @param query3 Query3ADT
*/
void freeQ3(Query3ADT query3){
    freeVec3(query3->infractionsVec3,query3->dim);
    free(query3);
}

static int eliminaCeros(size_t dim, TInfractions3 * vec){
    int i, j;

    for(i = 0, j = 0; i < dim; i++){
        if(vec[i].first != NULL){
            vec[j++] = vec[i];
        }
    }
    return j;
}

void ricardoSortQuery3(Query3ADT query3){
    if(query3 == NULL)
        return;
    query3->dim=eliminaCeros(query3->dim,query3->infractionsVec3);
    qsort(query3->infractionsVec3, query3->dim, sizeof(TInfractions3),(int (*)(const void *, const void *))comparator3);
    return;
}

void printForQuery3(Query3ADT query3, int dim){
    int i;
    for(i=0;i<dim;i++){
        printf("%s;%s;%ld \n",query3->infractionsVec3[i].infractionName,query3->infractionsVec3[i].mostPopularPlate,query3->infractionsVec3[i].maxTickets);     
    }
}

// ------------------------------------------------------------- //
// ------------------------- ITERATORS ------------------------- //
// ------------------------------------------------------------- //

void toBeginQ1(Query1ADT query1){
    query1->iter=0;
}

void toBeginQ2(Query2ADT query2){
    query2->iter = query2->first;
}

void toBeginQ3(Query3ADT query3){
    query3->iter = 0;
}

int hasNextQ1(Query1ADT query1){
    return query1->iter < query1->dim;
}

int hasNextQ2(Query2ADT query2){
    return query2->iter != NULL;
}

int hasNextQ3(Query3ADT query3){
    return query3->iter < query3->dim;
}

TInfractions nextQ1(Query1ADT query1, int * flag){
    if(!hasNextQ1(query1)){
        *flag = 1;
        return query1->infractionsVec[0];
    }
    TInfractions aux = query1->infractionsVec[query1->iter];
    query1->iter++;
    return aux;
}

TListAgency nextQ2(Query2ADT query2, int * flag){ 
    if(!hasNextQ2(query2)){
        *flag = 1;
        return NULL;
    }
    TListAgency aux = query2->iter;
    query2->iter = query2->iter->tail;
    return aux;
}
 

TInfractions3 nextQ3(Query3ADT query3, int * flag){
    if(!hasNextQ3(query3)){
        *flag = 1;
        return query3->infractionsVec3[0];
    }
    
    TInfractions3 aux = query3->infractionsVec3[query3->iter];
    query3->iter++;
    return aux;   
}

static FILE * newFile(char * name){
    FILE * file=fopen(name,"wt");
    if(errno != 0|| file==NULL){
        perror("ERROR - Creating new file\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

void writeQ1File(Query1ADT query1){
    //Header for Q1 .csv
    FILE * streamQ1 = newFile("query1.csv");
    fopen("query1.csv",WRITE);

    fputs("infraction;tickets\n",streamQ1);
    
    //Write rows for Q1 .csv
    int flag = 0;
    TInfractions aux = nextQ1(query1,&flag);

    while(!flag){
        fprintf(streamQ1,"%s;%ld\n", aux.infractionName, aux.count);
        aux = nextQ1(query1,&flag);
    }

    fclose(streamQ1);
}


void writeQ2File(Query2ADT query2, Query1ADT query1){
    //Header for Q2 .csv
    FILE * streamQ2 = newFile("query2.csv");
    fopen("query2.csv",WRITE);

    fputs("issuingAgency;infraccion;tickets\n",streamQ2);
    
    //Write rows for Q2 .csv
    int flag = 0;
    TListAgency aux = nextQ2(query2,&flag);

    while(!flag){
        fprintf(streamQ2,"%s;%s;%ld\n", aux->agencyName, query1->infractionsNames[aux->mostPopularID-1], aux->infractions[aux->mostPopularID-1].infractionsAmount);
        aux = nextQ2(query2,&flag);
    }

    
    fclose(streamQ2);
}

void writeQ3File(Query3ADT query3,Query1ADT query1){
    //Header for Q3 .csv
    FILE * streamQ3 = newFile("query3.csv");
    fopen("query3.csv",WRITE);

    fputs("infraccion;plate;tickets\n",streamQ3);
    
    //Write rows for Q3 .csv
    int flag = 0;
    TInfractions3 aux = nextQ3(query3,&flag);

    while (!flag){
        fprintf(streamQ3,"%s;%s;%ld\n", aux.infractionName, aux.mostPopularPlate, aux.maxTickets);
        aux = nextQ3(query3,&flag);
    }
    
    fclose(streamQ3);
}
