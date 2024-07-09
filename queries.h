#ifndef __QUERIES_H_
#define __QUERIES_H_
#include <stdlib.h>


// #define DESCRIP_INFRAC_LENGHT 0
// #define ISSUING_AGENCY_LENGHT 0
// #define PLATE_LENGHT 0

#ifndef FORMATCHI
#define FORMATCHI 0
#endif

#ifndef FORMATNYC
#define FORMATNYC 0
#endif

#if FORMATNYC
    #define DESCRIP_INFRAC_LENGHT 30
    #define ISSUING_AGENCY_LENGHT 35
    #define PLATE_LENGHT 10

#elif FORMATCHI
    #define DESCRIP_INFRAC_LENGHT 50
    #define ISSUING_AGENCY_LENGHT 13
    #define PLATE_LENGHT 10
#endif

// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERIES ------------------- //
// ------------------------------------------------------------- //

typedef struct Query1CDT * Query1ADT;
typedef struct Query2CDT * Query2ADT;
typedef struct Query3CDT * Query3ADT;

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //
typedef struct infractions1 TInfractions;

Query1ADT newQuery1(void);

void addInfractionsOcurrences(Query1ADT query1, unsigned id);

void addInfractionsToVec(Query1ADT query1, unsigned id, char * infractionName);

void ricardoSortQuery1(Query1ADT query1);

//temporal function
void printInfractions(Query1ADT query1);

void freeQuery1(Query1ADT query1);

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //

typedef struct agencies* TListAgency;

Query2ADT newQuery2(void);

void addInfraction2(Query1ADT query1,TListAgency first,size_t infractionID);

void addAgency(Query1ADT query1,Query2ADT query2, char * nameOfAgency, size_t infractionID);

void freeQuery2(Query2ADT query2);

//temporal function
void printInfractions2(Query1ADT query1, Query2ADT query2);

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 3 ------------------- //
// ------------------------------------------------------------- //
typedef struct infractions3 TInfractions3;

Query3ADT newQuery3(void);

void addInfraction3(Query1ADT query1,Query3ADT query3,int id,char * plate);

void createVec3(Query1ADT query1, Query3ADT query3);
//temporal function
void printForQuery3(Query3ADT query3, int dim);

void freeInfraccion3(Query3ADT query3);

void freeQ3(Query3ADT query3);

int ricardoSortQuery3(Query3ADT query3);

// -------------------------------------------------------------- //
// ------------------------- ITERATORS  ------------------------- //
// -------------------------------------------------------------- //

void toBeginQ1(Query1ADT query1);
void toBeginQ2(Query2ADT query2);
void toBeginQ3(Query3ADT query3);

int hasNextQ1(Query1ADT query1);
int hasNextQ2(Query2ADT query2);
int hasNextQ3(Query3ADT query3);

TInfractions nextQ1(Query1ADT query1, int * flag);
TListAgency nextQ2(Query2ADT query2, int * flag);
TInfractions3 nextQ3(Query3ADT query3, int * flag);


#endif

