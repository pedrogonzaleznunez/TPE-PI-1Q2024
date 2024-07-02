typedef struct Query3CDT * Query3ADT;

Query3ADT newQuery3();

void addAgency(Query3ADT query, char * nameOfInfraction,size_t infractionID);

void addInfraction(TListInfraction first,size_t infractionID);