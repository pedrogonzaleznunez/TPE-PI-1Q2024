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

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

Query1ADT newQuery1(void);

void addInfractionsOcurrences(Query1ADT query1, unsigned id);

void addInfractionsToVec(Query1ADT query1, unsigned id, char * infractionName);

void sortInfractionsDecreasing(Query1ADT query1);

//temporal function
void printInfractions(Query1ADT query1);

void freeQuery1(Query1ADT query1);

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //


// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERIES ------------------- //
// ------------------------------------------------------------- //

typedef struct Query3CDT * Query3ADT;

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 3 ------------------- //
// ------------------------------------------------------------- //

Query3ADT newQuery3(void);

void addTicket(Query3ADT query3, char * infraccionName, size_t infraccionID, char * plate);

TlistInfraccion addInfractionRec(TlistInfraccion infraccionList, char * infraccionName, size_t infraccionID, char * plate);

TlistPlates addPlate(TlistPlates listPlates, char * plate, int * toCheck);

// -------------------------------------------------------------- //
// -------------------- AUXILIARY FUNCTIONS  -------------------- //
// -------------------------------------------------------------- //

#endif
