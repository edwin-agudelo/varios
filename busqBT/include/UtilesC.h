/**
* @file Ordernar.h
* @brief Archivo con funcionalidades utiles generales
* @author Ing. Edwin A. Agudelo G.
* @date 2020-01-15
*/

#ifndef UTILESC_H_INCLUDED
#define UTILESC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
*
* @brief Funcion que se encarga de contar lineas o sacar el tamano de un archivo
* @param fp: Apuntador a un archivo
* @param opt: 1 - Cuenta Lineas de un archivo de texto ; 2 - Saca el tamano de un archivo binario
* @return Numero correspondiente al valor citado por la opcion; -1 en caso de tener un apuntador nulo, -2 en caso de una opcion no valida
*
* @note Si el archivo esta abierto como binario y se cuentan lineas no va a dar buen resultado, idem si se envia como texto y se toma el tamano
*
*/
long tamanoArchivo(FILE *fp, int opt){
    long retorno = 0;
    long ltmp;
    char liner[1024];

    if(fp == NULL)
        return -1;

    // Me ubico al inicio
    fseek(fp, 0, SEEK_SET);

    // Dependiendo de la opcion
    if(opt == 0){ // contar lineas
        while(!feof(fp)){
            if(fgets(liner, 1023, fp) == NULL)
                break;
            retorno++;
        }
    }
    else if(opt == 1){ // tamano de un archivo
        fseek(fp, 0, SEEK_END);
        retorno = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        ltmp = ftell(fp);
        retorno = retorno - ltmp + 1;
    }
    else{
        retorno = -2;
    }
    fseek(fp, 0, SEEK_SET);
    return retorno;
}

/**
* @brief Funcion para separar una cadena en tokens
* @param a_str: Cadena a separar
* @param a_delim: Separador de campos
* @return char **: Apuntador a las cadenas de caracteres separadas
*/
char** str_split(char* a_str, const char a_delim){
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* cptmp      = NULL;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Cuento la cantidad de elementos a ser tomados */
    while (*tmp){
        if (a_delim == *tmp){
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    count += last_comma < (a_str + strlen(a_str) - 1);

    count++;

    // copio la cadena de caracteres
    cptmp = (char*)malloc(sizeof(char)*strlen(a_str));
    if(cptmp == NULL)
        return NULL;
    strcpy(cptmp, a_str);

    result = (char**)malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(cptmp, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


/**
* @brief Funcion para separar una cadena en tokens
* @param a_str Cadena a separar
* @param a_delim Separador de campos
* @param result Apuntador de apuntadores para almacenar la salida
* @return int Cantidad de cadenas
*/
int str_splitn(char* a_str, const char a_delim, char*** result){
    size_t count     = 0;
    char* tmp        = a_str;
    char* cptmp      = NULL;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    int parts = 0;

    if(a_str == NULL){
        return -1;
    }

    /* Cuento la cantidad de elementos a ser tomados */
    while (*tmp){
        if (a_delim == *tmp){
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    count += last_comma < (a_str + strlen(a_str) - 1);
    count++;

    // copio la cadena de caracteres
    cptmp = (char*)malloc(sizeof(char)*strlen(a_str));
    if(cptmp == NULL)
        return -2;
    strcpy(cptmp, a_str);

    *result = (char**)malloc(sizeof(char*) * count);

    if (*result){
        size_t idx  = 0;
        char* token = strtok(cptmp, delim);
        while (token){
            assert(idx < count);
            **(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
        parts++;
    }
    return parts;
}

/**
* @brief Funcion que carga en memoria un archivo, linea a linea
* @param char *ruta: Ruta desde donde se toma el archivo
* @param long *lineas: Variable donde se guarda cuantos elementos se cargan
* @return char **: NULL en caso de falla o un apuntador de apuntadores
*/
char **cargarArchivoMem(char *ruta, long *lineas){
    long llineas;
    long ilines;
    long ltmp;
    FILE *fp;
    char **archMem = NULL;
    char liner[2048];

    // Intento abrir el archivo
    fp = fopen(ruta, "r");
    if(fp == NULL){
        printf("No se puede abrir el archivo <%s>, por favor valide\n", ruta);
    }
    else{
        llineas = tamanoArchivo(fp, 0);
        printf("Cantidad de lineas en el archivo:%ld\n", llineas);
        archMem = (char**)malloc(sizeof(char*) * llineas);
        if(archMem == NULL){
            printf("No se pudo crear me memoria para la carga del archivo\n");
        }
        else{
            ltmp = 0;
            ilines = 0;
            while(!feof(fp)){
                if(fgets(liner, 1023, fp) == NULL)
                    break;
                ilines++;
                if(ilines > llineas)
                    break;
                archMem[ltmp] = (char*)malloc(sizeof(char)*(strlen(liner)+1));
                if(archMem[ltmp] == NULL){
                    printf("No se puede asignar memoria para cargar la linea %ld\n", ilines);
                    continue;
                }
                strcpy(archMem[ltmp], liner);
                ltmp++;
            }
        }
    }

    if(fp != NULL)
        fclose(fp);

    *lineas = ltmp - 1; // Cantidad de elementos
    return archMem;
}

/**
* @brief Funcion para calcular la diferencia entre 2 marcas de tiempo
* @param time_t inicio: Marca de tiempo inicial
* @param time_t fin: Marca de tiempo final
* @param char *proceso: Se envia el nombre del proceso, NULL en caso no poner nada
* @param int enSeg: Bandera para indicar si se muestra en segundos o no
* @return void
*/
double verDiferenciaTiempo(time_t inicio, time_t fin, char *proceso, int enSeg){
    double dotmp = 0;

    dotmp = ((double)(fin-inicio));
    if(enSeg == 1){
        dotmp = ((double)(fin-inicio))/CLOCKS_PER_SEC;
    }
    if(proceso != NULL){
        printf("Tiempo total transcurrido en [%s]:%.2f\n", proceso, dotmp);
    }
    else{
        printf("Tiempo total transcurrido:%.2f\n", dotmp);
    }

    return dotmp;
}


#endif // UTILESC_H_INCLUDED
