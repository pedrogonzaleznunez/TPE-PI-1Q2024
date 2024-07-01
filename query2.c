#include <stdio.h>
#include <stdlib.h>
#include "query2.h"

typedef struct agencies{
    char * agency;                  //name of the agency
    TListInfraction first;          //list of infractions
    struct agencies * tail;         //next agency
}Tagencies;

typedef struct agencies * TListAgency;

typedef struct infractions{
    char * infraction;              //name of the infraction
    size_t count;                   //number of infractions
    struct infractions * tail;      //next infraction
}TInfraction;

typedef struct infractions * TListInfraction;

typedef struct Quer2CDT{
    TListAgency first;                    //list of agencies
    size_t size;                          //number of agencies
}Quer2CDT;

Query2ADT newQuery2(){
    return calloc(1,sizeof(Quer2CDT));
}




