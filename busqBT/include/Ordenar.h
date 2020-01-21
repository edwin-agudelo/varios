/**
* @file Ordernar.h
* @brief Archivo con funcionalidades de ordenamiento con base al custcode
* @author Ing. Edwin A. Agudelo G.
* @date 2020-01-15
*/

#ifndef ORDENAR_H_INCLUDED
#define ORDENAR_H_INCLUDED

//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Propios
#include "UtilesC.h"

/**
* @brief Funcion para intercambiar datos en un arreglo de apuntadores
* @param char **x: Apuntador de origen
* @param char **y: Apuntador de destino
* @return void
*/
void intercambiar(char** x, char** y){
    char *tmp = *x;
    *x = *y;
    *y = tmp;
}


/**
* @brief Funcion para partir un arreglo en fracciones para ordenar
* @param char **arr: Apuntador al arreglo a partir
* @param int inicio: posicion inicial en el arreglo que se va a ordernar
* @param int fin: posicion final en el arreglo que se va a ordernar
* @return int posicion en la que se encuentra un punto de reordenamiento
*/
int particionar(char **arr, int inicio, int fin){
    char *pivot = arr[fin];
    int pindex = inicio;
    int i;

    for(i = inicio; i < fin; i++){
        if(strncmp(arr[i], pivot, 10) <= 0){ // comparo los 10 primeros digitos del custcode, riesgo de las maestras
            intercambiar(&(arr[i]), &(arr[pindex]));
            pindex++;
        }
    }
    intercambiar(&(arr[fin]), &(arr[pindex]));
    return pindex;
}


/**
* @brief Funcion recursiva de ordenamiento QuickSort
* @param char **arr: Apuntador al arreglo a arreglar
* @param int inicio: posicion inicial en el arreglo que se va a ordernar
* @param int fin: posicion final en el arreglo que se va a ordernar
* @return void
*/
void quickSort(char **arr, int inicio, int fin){
    int pindex;
    if(inicio < fin){
        pindex = particionar(arr, inicio, fin);
        quickSort(arr, inicio, pindex+1);
        quickSort(arr, pindex-1, fin);
    }
}

/**
* @brief Funcion iterativa de ordenamiento QuickSort
* @param char **arr: Apuntador al arreglo a arreglar
* @param int inicio: posicion inicial en el arreglo que se va a ordernar
* @param int fin: posicion final en el arreglo que se va a ordernar
* @return void
*/
void quickSortIterativo(char **arr, int inicio, int fin)
{
    // creo un arreglo auxiliar
    int pila[fin - inicio + 1];
    int interacciones = 0;
    int pasos = 0;
    double dotmp;
    time_t tini;
    time_t tfin;

    // initialize top of stack
    int top = -1;

    // tomo el inicio y el fin
    pila[++top] = inicio;
    pila[++top] = fin;

    tini = clock();

    // Voy tomando los rangos a evaluar a partir de la pila
    while (top >= 0) {
        // Pop h and l
        fin = pila[top--];
        inicio = pila[top--];

        interacciones++;
        if( interacciones == 10000 ){
            interacciones = 0;
            tfin = clock();
            dotmp = ((double)(tfin-tini))/CLOCKS_PER_SEC;
            tini = tfin;
            printf("Interacciones:%d\n", (pasos+1));
            printf("Top:%d\n", top);
            printf("Elementos eval:%d - %d\n", inicio, fin);
            printf("Tiempo transcurrido:%.2f\n", dotmp);
            pasos++;
        }

        // voy cambiando los datos a evaluar
        // en el arreglo que voy arreglando
        int p = particionar(arr, inicio, fin);

        // si no quedan elementos
        // actualizo elementos en la pila
        if (p > inicio) {
            pila[++top] = inicio;
            pila[++top] = p - 1;
        }

        if (p < fin) {
            pila[++top] = p + 1;
            pila[++top] = fin;
        }
    }
}

/**
* @brief Funcion para escribir en disco un arreglo de apuntadores char*
* @param char **arr: Apuntador al arreglo a arreglar
* @param int inicio: posicion inicial en el arreglo que se va a ordernar
* @param int fin: posicion final en el arreglo que se va a ordernar
* @param char *ruta: ruta donde va a quedar el archivo
* @return void
*/
void guardarArregloChar(char **arr, int inicio, int fin, char *ruta){
    FILE *fp;
    int i;
    if((fp = fopen(ruta, "w")) == NULL){
        printf("No se puede abrir el archivo %s\n", ruta);
        return;
    }
    for(i = inicio; i < fin; i++){
        fprintf(fp, "%s\n",arr[i]);
    }
    fclose(fp);
}

#endif // ORDENAR_H_INCLUDED
