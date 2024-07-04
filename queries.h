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

void addInfractionsName(Query1ADT query1, unsigned id, char * infractionName);

void printInfractions(Query1ADT query1);

void freeQuery1(Query1ADT query1);

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //



// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 3 ------------------- //
// ------------------------------------------------------------- //



// -------------------------------------------------------------- //
// -------------------- AUXILIARY FUNCTIONS  -------------------- //
// -------------------------------------------------------------- //

#endif
