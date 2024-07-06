typedef struct Query2CDT * Query2ADT;

Query2ADT newQuery2(void);

void addInfraction2(Query1ADT query1,TListAgency first,size_t infractionID);

void addAgency(Query1ADT query1,Query2ADT query, char * nameOfAgency, size_t infractionID);

void freeQuery2(Query2ADT query2);