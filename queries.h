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

/**
// * @brief Creates a new Query1ADT
// * @return Query1ADT
*/
Query1ADT newQuery1(void);

/**
// * @brief Adds an ocurrence to the infraction with id
// * @param query1 Query1ADT
// * @param id ID of the infraction
// * @precondition query1 != NULL
*/
void addInfractionsOcurrences(Query1ADT query1, unsigned id);

/**
 * @brief Adds a new infraction to the array of infractions
 * @param query1 Query1ADT
 * @param id ID of the infraction
 * @param InfractionName name of the infraction
 * @precondition query1 != NULL
 */
void addInfractionsToVec(Query1ADT query1, unsigned id, char * infractionName);

/** 
// * @brief Sorts the array of infractions in decreasing order
// * @param query1 Query1ADT
// * @precondition query1 != NULL
*/
void ricardoSortQuery1(Query1ADT query1);

//temporal function
void printInfractions(Query1ADT query1);

/**
 * @brief frees allocted memory
 * @param query1 Query1ADT
 */
void freeQuery1(Query1ADT query1);

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //

typedef struct agencies* TListAgency;

/**
// * @brief Creates a new Query1ADT
// * @return Query1ADT
*/
Query2ADT newQuery2(void);

/**
// * @brief Adds infraction into Agency
// * @param query1 Query1ADT
// * @param first Agency to insert the infraction in
// * @param infractionID id of infraction
*/
void addInfraction2(Query1ADT query1,TListAgency first,size_t infractionID);

/**
// * @brief Adds an agency in alphabetical order
// * @param query1 Query1ADT
// * @param query2 Query2ADT
// * @param nameOfAgency name of agency
// * @param infractionID  ID of infractions
*/
void addAgency(Query1ADT query1,Query2ADT query2, char * nameOfAgency, size_t infractionID);

/**
// * @brief frees allocated memory
// * @param query2 Query2ADT
*/
void freeQuery2(Query2ADT query2);

//temporal function
void printInfractions2(Query1ADT query1, Query2ADT query2);

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 3 ------------------- //
// ------------------------------------------------------------- //
typedef struct infractions3 TInfractions3;

/**
// * @brief Creates a new Query3ADT
// * @return Query3ADT
*/
Query3ADT newQuery3(void);

/**
// * @brief adds an infraction to query3
// * @param query1 query1ADT
// * @param query3 Query3ADT
// * @param id ID of infraction
// * @param plate Name of plate
*/
void addInfraction3(Query1ADT query1,Query3ADT query3,int id,char * plate);

/**
// * @brief Creates a new infraction in query3
// * @param query1 Query1ADT
// * @param query3 Query3ADT
*/
void createVec3(Query1ADT query1, Query3ADT query3);
//temporal function
void printForQuery3(Query3ADT query3, int dim);

void freeInfraccion3(Query3ADT query3);

/**
// * @brief frees allocated memory
// * @param query3 Query3ADT
*/
void freeQuery3(Query3ADT query3);

void ricardoSortQuery3(Query3ADT query3);

// -------------------------------------------------------------- //
// ------------------------- ITERATORS  ------------------------- //
// -------------------------------------------------------------- //

typedef struct query1Iterator{
    char * infractionName;
    unsigned long count;
}query1Iterator;

typedef struct query2Iterator{
    char * agencyName;
    char * infractions;
    unsigned mostPopularID;
}query2Iterator;

typedef struct query3Iterator{
    char * infractionName;
    char * mostPopularPlate;
    unsigned long maxTickets;
}query3Iterator;

void toBeginQ1(Query1ADT query1);
void toBeginQ2(Query2ADT query2);
void toBeginQ3(Query3ADT query3);

int hasNextQ1(Query1ADT query1);
int hasNextQ2(Query2ADT query2);
int hasNextQ3(Query3ADT query3);

query1Iterator nextQ1(Query1ADT query1, int * flag);
query2Iterator nextQ2(Query2ADT query2, Query1ADT query1, int * flag);
query3Iterator nextQ3(Query3ADT query3, int * flag);

#endif
