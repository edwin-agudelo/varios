/**
* @file BTEAG.h
* @brief Archivo con funcionalidades de creacion, balanceo y busqueda de un arbol binario
* @author Ing. Edwin A. Agudelo G.
* @date 2020-01-15
*/

#ifndef BTEAG_H_INCLUDED
#define BTEAG_H_INCLUDED

#include "UtilesC.h"
#include "DataConta.h"
#include "Ordenar.h"


/**
* @brief Estructura de datos para almacenar los datos del arbol binario
*/
struct stBtEA{
    struct stDatos dato;
    struct stBtEA *derecha;
    struct stBtEA *izquierda;
    struct stBtEA *padre;
};
typedef struct stBtEA stBtEA;

/**
* @brief Funcion que crear un nuevo nodo para el arbol binario
* @param stDatos *val: Apuntador valido con la info a agregar
* @return stBtEA *: Un nuevo nodo con una copia de los datos
*/
struct stBtEA* nuevoNodo(struct stDatos *val){
    struct stBtEA *tmp = (stBtEA *)malloc(sizeof(struct stBtEA));
    if(tmp != NULL){
        tmp->derecha = NULL;
        tmp->izquierda = NULL;
        tmp->padre = NULL;
        tmp->dato.custcode = (char*)malloc( sizeof(char) * strlen(val->custcode) );
        strcpy(tmp->dato.custcode, val->custcode);
        tmp->dato.customerid = val->customerid;
        tmp->dato.valorfact = val->valorfact;
        tmp->dato.valorimp = val->valorimp;
        tmp->dato.valorimpo = val->valorimpo;
        tmp->dato.valoriva = val->valoriva;
    }
    return tmp;
}


/**
* @brief Funcion que crear nuevos nodos para el arbol binario a partir de un arreglo ordernado
* @param char **arr: Apuntador a un array con los datos a cargar
* @param int inicio: Desde donde se va a ordenar
* @param int fin: Hasta donde se va a ordenar
* @return stBtEA *: Un nuevo nodo con una copia de los datos
*/
struct stBtEA* nuevoNodoOrd(char **arr, int inicio, int fin){
    struct stBtEA *tmp = NULL;
    int m;
    char **separado;
    //int j;

    if(inicio <= fin){
        m = (inicio + fin)/2;
        tmp = (stBtEA *)malloc(sizeof(struct stBtEA));
        if(tmp != NULL){
            separado = str_split(arr[m], ';');
            tmp->dato.custcode = (char*)malloc( sizeof(char) * strlen(separado[0]) );
            strcpy(tmp->dato.custcode, separado[0]);
            tmp->dato.customerid = atof(separado[1]);
            tmp->dato.valorfact = atof(separado[3]);
            tmp->dato.valorimp = atof(separado[4]);
            tmp->dato.valorimpo = atof(separado[6]);
            tmp->dato.valoriva = atof(separado[5]);
            if(inicio != fin){
                tmp->derecha = nuevoNodoOrd(arr, m + 1, fin);
                tmp->izquierda = nuevoNodoOrd(arr, inicio, m - 1);
            }
            else{
                tmp->derecha = NULL;
                tmp->izquierda = NULL;
            }
            tmp->padre = NULL;
            /*for(j = 0; j < 5; j++){
                free(separado[j]);
            }
            free(separado);*/
        }
    }
    return tmp;
}

/**
* @brief Funcion que agrega un nuevo nodo en un arbol binario
* @param stBtEA **nIni: Nodo raiz del arbol
* @param stBtEA *nuevo: Nodo a agregar al arbol
* @return 1: Agregado a la izquierda ; 2: Agregado a la derecha ; -1: No agregado por que el valor ya existe
*/
int insertarNodo(struct stBtEA **nIni, struct stBtEA *nuevo){
    int retorno = 0;
    int itmp;
    struct stBtEA *tmp = NULL;
    int brazos[2] = { 0 , 0 };

    if(*nIni == NULL){
        *nIni = nuevo;
        retorno = 1;
    }
    else{
        tmp = *nIni;
        while(retorno == 0){
            itmp = comparaDatos( &(tmp->dato), &(nuevo->dato));
            if(itmp < 0){ // es menor
                brazos[0]++;
                if(tmp->izquierda == NULL){
                    tmp->izquierda = nuevo;
                    nuevo->padre = tmp;
                    retorno = 1;
                }
                else{
                    tmp = tmp->izquierda;
                }
            }
            else if(itmp > 0){
                brazos[1]++;
                if(tmp->derecha == NULL){
                    tmp->derecha = nuevo;
                    nuevo->padre = tmp;
                    retorno = 2;
                }
                else{
                    tmp = tmp->derecha;
                }
            }
            else{ // son iguales, se descarta el dato
                retorno = -1;
            }
        }
    }
    return retorno;
}


/**
* @brief Funcion que busca un valor(custcode) en un arbol binario
* @param stBtEA **nIni: Nodo raiz del arbol para buscar
* @param char *cadena: Dato a Buscar
* @return stBtEA *: NULL sino lo encuentra o apuntador al nodo
*/
struct stBtEA *buscarNodo(struct stBtEA *nIni, char *cadena){
    struct stBtEA *tmp = NULL;
    int itmp;
    if(nIni != NULL){
        itmp = esElDato( &(nIni->dato), cadena);
        if( itmp == 0){
            tmp = nIni;
        }
        else if( itmp < 0 ){
            tmp = buscarNodo(nIni->derecha, cadena);
        }
        else{
            tmp = buscarNodo(nIni->izquierda, cadena);
        }
    }
    return tmp;
}

/**
* @brief Funcion que libera la memoria de un arbol
* @param stBtEA **nIni: Nodo raiz del arbol
* @return void
*/
void liberarNodo(struct stBtEA **nIni){
    if((*nIni)->derecha != NULL){
        liberarNodo(&((*nIni)->derecha));
    }
    if((*nIni)->izquierda != NULL){
        liberarNodo(&((*nIni)->izquierda));
    }
    free((*nIni)->dato.custcode);
    (*nIni)->dato.custcode = NULL;
    free(*nIni);
    *nIni = NULL;
}


/**
* @brief Funcion que genera un archivo a partir de un arbol binario
* @param stBtEA **nIni: Nodo raiz del arbol
* @param char *ruta: ruta del archivo donde se va a guardar la info
* @return void
*/
void guardarArbolB(struct stBtEA **nIni, char *ruta){
    FILE *fp;
    //int i;
    struct stBtEA *tmp = NULL;
    if((fp = fopen(ruta, "w")) == NULL){
        printf("No se puede abrir el archivo %s\n", ruta);
        return;
    }
    tmp = *nIni;
    while(tmp != NULL){
        fprintf(fp,"%s\n", tmp->dato.custcode);
        if(tmp->izquierda != NULL){
            fprintf(fp,"<");
            tmp = tmp->izquierda;
        }
    }
    fclose(fp);
}

/**
* @brief Funcion que crea un arbol binario a partir de un archivo DIC
* @param char *ruta
* @param int inicio: Desde donde se va a ordenar
* @param int fin: Hasta donde se va a ordenar
* @return stBtEA *: NULL en caso de falla o nodo raiz del arbol
*/
struct stBtEA* cargarArchivoDic(char *ruta, long *cantidad){
    struct stBtEA *tmp = NULL; //malloc(sizeof(struct stBtEA));
    char **archMem;
    long lineas;
    time_t tini;
    time_t tfin;

    // Cargo el archivo en memoria
    tini = clock();
    archMem = cargarArchivoMem(ruta, &lineas);
    tfin = clock();
    verDiferenciaTiempo(tini, tfin, "CargaArchivoMem", 1);
    if(archMem == NULL){
        printf("No se puede realizar la carga del archivo <%s>\n", ruta);
    }
    else{
        printf("Archivo cargado en memoria con %ld lineas\n", (lineas + 1));
        printf("Ordenando\n");
        tini = clock();
        if(lineas > 30000){
            quickSortIterativo(archMem, 0, lineas);
        }
        else{
            quickSort(archMem, 0, lineas);
        }
        tfin = clock();
        verDiferenciaTiempo(tini, tfin, "Ordenamiento", 1);
        printf("Creando Arbol Binario\n");
        tini = clock();
        tmp = nuevoNodoOrd(archMem, 0, lineas);
        tfin = clock();
        verDiferenciaTiempo(tini, tfin, "ArbolBinario", 1);
        if(tmp == NULL){
            printf("No se puede crear el arbol\n");
        }
        else{
            printf("Arbol Listo\n");
        }
    }
    return tmp;
}



#endif // BTEAG_H_INCLUDED

