typedef struct plate{
    char * nameOfPlate;
    size_t cantInfraccion;
    struct plate * tail;
}Tplate;

typedef Tplate * TlistPlates;

typedef struct infraccion{
    size_t idInfraccion;
    char * infraccionName;
    TlistPlates MostPopularPlate;
    struct infraccion * nextInfraccion;
}Tinfraccion;

typedef Tinfraccion * TlistInfraccion;

TlistPlates reordenar(TlistPlates plates){
    if(plates==NULL || plates->tail==NULL){
        return plates;
    }
    if(plates->cantInfraccion < plates->tail->cantInfraccion){
        TlistPlates aux=plates->tail;
        plates->tail=reordenar(aux->tail);
        aux->tail=plates;
        return aux;
    }if(plates->cantInfraccion > plates->tail->cantInfraccion){
        plates->tail=reordenar(plates->tail);
        return plates;
    }
    int c;
    if((c=strcmp(plates->nameOfPlate,paltes->tail->nameOfPlate))<=0){
        plates->tail=reordenar(plates->tail);
        return plates;
    }
    TlistPlates aux=plates->tail;
    plates->tail=reordenar(aux->tail);
    aux->tail=plates;
    return aux;
}