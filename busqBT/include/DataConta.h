/**
* @file DataConta.h
* @brief Archivo de definiciones de datos de negocio para aplicacion
* @author Ing. Edwin A. Agudelo G.
* @date 2020-01-15
*/

#ifndef DATACONTA_H_INCLUDED
#define DATACONTA_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
* @brief Estructura de datos de negocio
*/
struct stDatos{
    char* custcode;
    double customerid;
    double valorfact;
    double valorimp;
    double valoriva;
    double valorimpo;
};


/**
* @brief Funcion compara los valores de custcode para identificar si son iguales
* @param stDatos val1: Estructura a comparar 1
* @param stDatos val2: Estructura a comparar 2
* @return int : -1 en caso de error.
*/
int comparaDatos(struct stDatos *val1, struct stDatos *val2){
    int retorno = 0;
    if(val1 == NULL || val2 == NULL)
        retorno = -1;
    else{
        retorno = strcmp(val1->custcode, val2->custcode);
    }
    return retorno;
}

/**
* @brief Funcion compara una estructura de negocio con un custcode
* @param stDatos val1: Estructura a comparar
* @param char *cadena: Custcode a compara
* @return int : Resultado de la comparacion
*/
int esElDato(struct stDatos *val1, char* cadena){
    int retorno = 0;
    if(val1 == NULL)
        retorno = -1;
    else{
        retorno = strcmp(val1->custcode, cadena);
    }
    return retorno;
}



#endif // DATACONTA_H_INCLUDED
