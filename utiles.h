#ifndef UTILES_H_INCLUDED
#define UTILES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int splitString(char sep, char* cadena, char ***salida){
    int retorno = 0;
    int largo;
    int i;
    int j;
    int isep = 0;
    int init = 0;
    char *strtmp = NULL;

    largo = strlen(cadena);

    for(i = 0; i < largo; i++){
        if(cadena[i] == sep)
            isep++;
    }

    if(isep == 0)
        return retorno;

    isep++;

    if(*salida != NULL){
        i = strlen(*salida);
        while(i > 0){
            if((*salida)[i] != NULL)
                free((*salida)[i]);
            i--;
        }
        free(*salida);
    }

    *salida = (char**)calloc(isep, sizeof(char*)*isep);

    for(i = 0; i <= largo; i++){
        if(cadena[i] == sep || cadena[i] == '\0' || cadena[i] == NULL){
            if( (i-init) > 0 ){
                (*salida)[retorno] = (char*)calloc((i-init), sizeof(char)*(i-init));
                for(j = 0; j <(i - init); j++){
                    (*salida)[retorno][j] = cadena[init+j];
                }
                (*salida)[retorno][j] = '\0';
            }
            else{
                (*salida)[retorno] = NULL;
            }
            init = i+1;
            retorno++;
        }
    }

    return retorno;
}


#endif // UTILES_H_INCLUDED
