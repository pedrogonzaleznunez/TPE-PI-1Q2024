typedef struct Query1CDT * Query1ADT;

Query1ADT newQuery1();

void addInfraction(Query1ADT query1, char * infraction, char * id);

void freeQuery1(Query1ADT query1);

// pending function, if not succesful, we will save the names of mostPopularID
char * fetchName( size_t id);
