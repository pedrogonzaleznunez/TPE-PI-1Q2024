#include "front.h"


// void HeaderQ1(FILE * stream){
//     fputs("Infraction;Tickets\n",stream);
// }

// void writeRowQ1(FILE * stream,char * Infraction, char * Tickets){
//     char * info[]={Infraction,Tickets};
//     for (size_t i = 0; i < TOPQ1; i++)
//     {
//         fputs(info[i],stream);
//         switch (i)
//         {
//         case LASTQ1:
//             fputs(ESCAPE_N,stream);
//             break;
        
//         default:
//             fputs(DELIM,stream);
//             break;
//         }
//     }
// }

// void HeaderQ2(FILE * stream){
//     fputs("IssuingAgency;Infraction;Tickets\n",stream);
// }

// void writeRowQ2(FILE * stream,char * agency,char * id,char * Tickets){ // para obtener el nombre del id hay que invocarlo con q1
//      char * info[]={agency,id,Tickets};
//     for (size_t i = 0; i < TOPQ2; i++)
//     {
//         fputs(info[i],stream);
//         switch (i)
//         {
//         case LASTQ2:
//             fputs(ESCAPE_N,stream);
//             break;
        
//         default:
//             fputs(DELIM,stream);
//             break;
//         }
//     }
// }

// FILE * newFile(char * name){
//     errno = SET_ERRNO;
//     FILE * file=fopen(name,WRITETEXT);
//     if(errno != SET_ERRNO || file==NULL){
//         perror("Ocurrio un error mientras se creaba algun archivo\n");
//         exit (EXIT_FAILURE);
//     }
//     return file;
// }