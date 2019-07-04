#ifndef CONFIGURA_H_INCLUDED
#define CONFIGURA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "utiles.h"

/**
    Estructura basica para la carga de parametros
*/
struct CONFIG{
    int idConf;
    char* llave;
    char* valor;
    struct CONFIG *siguiente;
};

int agregarParam(struct CONFIG *conf, char *llave, char *valor){
    if(conf == NULL){
       conf = malloc(sizeof(struct CONFIG));
       conf->siguiente = NULL;
       conf->idConf = 1;
       conf->llave = (char*)malloc(sizeof(char)*strlen(llave));
       strcpy(conf->llave, llave);
       conf->valor = (char*)malloc(sizeof(char)*strlen(valor));
       strcpy(conf->valor, valor);
    }
    else{
        conf->idConf += agregarParam(conf->siguiente, llave, valor);
    }
    return conf->idConf;
}


/**
    Funcion para cargar la configuracion de parametros
*/
int cargaConfig(char *ruta, struct CONFIG *param){
    int retorno = 0;
    char linea[1024];
    int ilineas = 0;
    int iparams = 0;
    int itmp;
    char **par;
    FILE *fh;

    // Inicio probando el acceso
    if(access(ruta, R_OK) != 0){
        perror("Error hacia el archivo de configuracion");
        return retorno;
    }

    fh = fopen(ruta, "r");

    if(fh == NULL){
        perror("Error abriendo el archivo");
        return retorno;
    }

    par = NULL;

    while(fgets(linea,1024, fh) != NULL){
        ilineas++;
        if(linea[0] == '#' || linea[0] == '\n' || linea[0] == '\r' || linea[0] == ';')
            continue;
        if(strchr(linea, '=') == NULL)
            continue;
        // Procedo a separar
        itmp = splitString('=', linea, &par);
        if(itmp != 2)
            continue;

        agregarParam(param, par[0], par[1]);
    }

    fclose(fh);
    retorno = iparams;

    // Devuelvo la cantidad de parametros
    return retorno;
}

#endif // CONFIGURA_H_INCLUDED
