// ------------------------------------------------------------- //
// ------------------- STRUCTURE FOR QUERIES ------------------- //
// ------------------------------------------------------------- //

typedef struct Query1CDT * Query1ADT;
typedef struct Query2CDT * Query2ADT;
typedef struct Query3CDT * Query3ADT;

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 1 ------------------- //
// ------------------------------------------------------------- //

Query1ADT newQuery1();


void addInfractionQ1(Query1ADT query1, char * infraction, char * id);

/**
* @brief releases resources used by the Query1 ADT
* @param Query1ADT receives pointer to corresponding CDT
*/
void freeQuery1(Query1ADT query1);

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 2 ------------------- //
// ------------------------------------------------------------- //

Query2ADT newQuery2();

void addAgency(Query2ADT query, char * nameOfAgency,size_t infractionID);

void addInfractionQ2(TListAgency first,size_t infractionID);

/**
* @brief releases resources used by the Query2ADT
* @param Query2ADT receives pointer to corresponding CDT
*/
void freeQuery2(Query2ADT query2);

// ------------------------------------------------------------- //
// ------------------- FUNCTIONS FOR QUERY 3 ------------------- //
// ------------------------------------------------------------- //


Query3ADT newQuery3();

void addInfractionQ3(Query3ADT query, char * nameOfInfraction);

void addPlate();

/**
* @brief releases resources used by the Query3ADT
* @param Query3ADT receives pointer to corresponding CDT
*/
void freeQuery3(Query3ADT query3);

// -------------------------------------------------------------- //
// -------------------- AUXILIARY FUNCTIONS  -------------------- //
// -------------------------------------------------------------- //

// pending function, if not succesful, we will save the names of mostPopularID
char * fetchName( size_t id);
