typedef struct Query2CDT * Query2ADT;

Query2ADT newQuery2();
void addAgency(Query2ADT query, char * nameOfAgency);
void addInfraction(TListInfraction list,char * infraction,size_t totalFines);



