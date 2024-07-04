typedef struct plate{
    char * nameOfPlate;
    size_t cantInfraccion;
    struct plate * tail;
}Tplate;

typedef Tplate * TlistPlates;

typedef struct infraccion{
    size_t idInfraccion;
    char * infraccionName;
    TlistPlates Plates;
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
        aux->nameOfPlate=malloc((strlen(plate)+1)*sizeof(char));
        strcpy(aux->nameOfPlate,plate);
        aux->cantInfraccion=1;
        *toCheck=1;
        aux->tail=listPlates;
    }if(c<0){
        listPlates->tail=addPlate(listPlates->tail,plate);
        return listPlates;
    }
    listPlates->cantInfraccion++;
    *toCheck=cantInfraccion;
    return listPlates;
}

TlistInfraccion addInfractionRec(TlistInfraccion infraccionList, char * infraccionName, size_t infraccionID, char * plate){
    int c;
    if(infraccionList==NULL || (c=strcmp(infraccionList->infraccionName,infraccionName))>0){
        TlistInfraccion aux=calloc(1,sizeof(*aux));
        aux->nextInfraccion=infraccionList;
        aux->idInfraccion=infraccionID;
        aux->infraccionName=malloc((stlen(infraccionName)+1)*sizeof(char));
        strcpy(aux->infraccionName,infraccionName);
        int c;
        aux->plate=addPlate(aux->plate,plate,&c);
        aux->maxMultas=c;
        aux->MostPopularPlate=malloc((stlen(plate)+1)*sizeof(char));
        strcpy(aux->MostPopularPlate,plate);
        return aux;
    }if(c<0){
        infraccionList->nextInfraccion=addInfractionRec(infraccionList->tail,infraccionName,infraccionID,plate);
        return infraccionList;
    }
    int maxInfraccion;
    infraccionList->Plate=addPlate(infraccion->plate,plate,&maxInfraccion);
    if(maxInfraccion>=infraccionList->maxMultas){
        int y;
        if((y=strcmp(infraccionList->MostPopularPlate,plate))<0){
            return infraccionList;
        }
        infraccionList->maxMultas=maxInfraccion;
        infraccionList->MostPopularPlate=malloc((stlen(plate)+1)*sizeof(char));
        strcpy(infraccionList->MostPopularPlate,plate);
    }    
    return infraccionList;
}

void addInfraction(query3CDT query3,char * infraccionName, size_t infraccionID, char * plate){
    query3->first=addInfractionRec(query3->first, infraccionName, infraccionID, plate);
}