typedef struct Query2CDT * Query2ADT;

Query2ADT newQuery2();

void addAgency(Query2ADT query, char * nameOfAgency,size_t infractionID);

void addInfraction(TListAgency first,size_t infractionID);



