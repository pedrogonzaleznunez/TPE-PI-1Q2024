#include <stdlib.h>
#include <stdio.h>
#include "errno.h"
#include "queries.h"
typedef struct plate{
    char * nameOfPlate;
    size_t cantInfraccion;
    struct plate * tail;
}Tplate;

typedef Tplate * TlistPlates;

typedef struct infraccion{
    size_t idInfraccion;
    char * infraccionName;
    TlistPlates plates;
    char * MostPopularPlate;
    size_t maxMultas;
    struct infraccion * nextInfraccion;
}Tinfraccion;

typedef Tinfraccion * TlistInfraccion;

typedef struct query3CDT{
    TlistInfraccion first;
}query3CDT;


// TlistPlates reordenarRec(TlistPlates plates, int * flag){
//     if(plates==NULL || plates->tail==NULL){
//         return plates;
//     }
//     if(plates->cantInfraccion < plates->tail->cantInfraccion){
//         TlistPlates aux=plates->tail;
//         plates->tail=reordenar(aux->tail);
//         aux->tail=plates;
//         *flag=1;
//         return aux;
//     }if(plates->cantInfraccion > plates->tail->cantInfraccion){
//         plates->tail=reordenar(plates->tail);
//         return plates;
//     }
//     int c;
//     if((c=strcmp(plates->nameOfPlate,paltes->tail->nameOfPlate))<=0){
//         plates->tail=reordenar(plates->tail);
//         return plates;
//     }
//     TlistPlates aux=plates->tail;
//     plates->tail=reordenar(aux->tail);
//     aux->tail=plates;
//     return aux;
// }

// void reordenar(TlistPlates plates){
//     int cambio=1;
//     while(cambio){
//         cambio=0;
//         reordenar(plates,&cambio);
//     }
// }


TlistPlates addPlate(TlistPlates listPlates, char * plate, int * toCheck){
    int c;
    if(listPlates==NULL || (c=strcmp(listPlates->nameOfPlate,plate))>0){
        TlistPlates aux=malloc(sizeof(*aux));
        // if ( aux == NULL || errno == ENOMEM) {
        //    return listPlates;  // If an error ocurred, it returns the same list, without making changes
        // }
        aux->nameOfPlate=malloc((strlen(plate)+1)*sizeof(char));
        // if(aux->nameOfPlate == NULL){
        //     errno=ENOMEM;
        //     return listPlates;
        // }
        strcpy(aux->nameOfPlate,plate);
        aux->cantInfraccion=1;
        *toCheck=1;
        aux->tail=listPlates;
        return aux;
    }if(c<0){
        listPlates->tail=addPlate(listPlates->tail,plate,toCheck);
        return listPlates;
    }
    listPlates->cantInfraccion++;
    *toCheck=listPlates->cantInfraccion;
    return listPlates;
}

TlistInfraccion addInfractionRec(TlistInfraccion infraccionList, char * infraccionName, size_t infraccionID, char * plate){
    int c;
    if(infraccionList==NULL || (c=strcmp(infraccionList->infraccionName,infraccionName))>0){
        TlistInfraccion aux=malloc(sizeof(*aux));
        // if(aux== NULL){
        //     errno=ENOMEM;
        //     return infraccionList;
        // }
        aux->nextInfraccion=infraccionList;
        aux->idInfraccion=infraccionID;
        aux->infraccionName=malloc((stlen(infraccionName)+1)*sizeof(char));
        // if(aux->infraccionName== NULL){
        //     errno=ENOMEM;
        //     return infraccionList;
        // }
        strcpy(aux->infraccionName,infraccionName);
        int c;
        aux->plates=addPlate(aux->plates,plate,&c);
        aux->maxMultas=c;
        aux->MostPopularPlate=malloc((stlen(plate)+1)*sizeof(char));
        // if(aux->MostPopularPlate== NULL){
        //     errno=ENOMEM;
        //     return infraccionList;
        // }
        strcpy(aux->MostPopularPlate,plate);
        return aux;
    }
    if(c<0){
        infraccionList->nextInfraccion=addInfractionRec(infraccionList->nextInfraccion,infraccionName,infraccionID,plate);
        return infraccionList;
    }
    int maxInfraccion;
    infraccionList->plates=addPlate(infraccionList->plates,plate,&maxInfraccion);
    if(maxInfraccion>=infraccionList->maxMultas){
        if(maxInfraccion>infraccionList->maxMultas){
            infraccionList->maxMultas=maxInfraccion;
            infraccionList->MostPopularPlate=malloc((stlen(plate)+1)*sizeof(char));
        // if(infraccionList->MostPopularPlate== NULL){
        //     errno=ENOMEM;
        //     return infraccionList;
        // }
            strcpy(infraccionList->MostPopularPlate,plate);
            return infraccionList;
        }
        int y;
        if((y=strcmp(infraccionList->MostPopularPlate,plate))>0){
            infraccionList->MostPopularPlate=malloc((stlen(plate)+1)*sizeof(char));
        // if(infraccionList->MostPopularPlate== NULL){
        //     errno=ENOMEM;
        //     return infraccionList;
        // }
            strcpy(infraccionList->MostPopularPlate,plate);
        }
    }    
    return infraccionList;
}

void addInfraction(query3ADT query3, char * infraccionName, size_t infraccionID, char * plate){
    query3->first=addInfractionRec(query3->first, infraccionName, infraccionID, plate);
}

static void freeSublist(TlistPlates sublist){
    if(sublist == NULL){
        return ;
    }
    freeSublist(sublist->tail);
    free(sublist->nameOfPlate);
    // free(sublist);
    return;
}


static void freeList(TlistInfraccion list){
    if(list == NULL){
        return ;
    }
    freeList(list->nextInfraccion);
    freeSublist(list->plates);
    free(list->infraccionName);
    free(list->MostPopularPlate);
// free(list); ??
    return;
}


void freeInfraccion3(query3ADT query3){
    freeList(query3->first);
}