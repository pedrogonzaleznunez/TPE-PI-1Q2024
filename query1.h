typedef struct Query1CDT * Query1ADT;

Query1ADT newQuery1();

void addInfraction(Query1ADT query1, char * infraction, char * id);

void freeQuery1(Query1ADT query1);