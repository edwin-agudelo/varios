#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "include/BTEAG.h"
#include "include/DataConta.h"
#include "include/UtilesC.h"
#include "include/Ordenar.h"

/******************************************

*******************************************/
int main(int argc, char** argv)
{
    char *rutaf = NULL;
    //FILE *fp;
    char liner[1024];
    //long ilines = 0;
    long llineas = 0;
    //long ltmp;
    //char **separado;
    //char **archmem;
    //struct stDatos dtmp;
    struct stBtEA *btraiz = NULL;
    struct stBtEA *bttmp = NULL;
    //int itmp;
    //long idir[2] = {0,0};
    time_t tini;
    time_t tfin;
    double dotmp;


    if(argc == 1){
        printf("Por favor ingrese el numero correcto de parametros\n");
        return 1;
    }
    else if(argc == 2){
        rutaf = malloc(sizeof(char) * strlen(argv[1]));
        strcpy(rutaf, argv[1]);
    }
    printf("Usando el archivo: <%s>\n", rutaf);
    /* dtmp.custcode = calloc(30,sizeof(char)); */

    // Abro el archivo y cargo los datos
    /*fp = fopen(rutaf, "r");
    if(fp == NULL){
        printf("No se puede abrir el archivo <%s>, por favor valide\n", rutaf);
    }
    else{
        llineas = tamanoArchivo(fp, 0);
        printf("Cantidad de lineas en el archivo:%ld\n", llineas);
        archmem = malloc(sizeof(char*) * llineas);
        if(archmem == NULL){
            printf("No se pudo crear me memoria para la carga del archivo\n");
            return 1;
        }
        else{
            ltmp = 0;
            while(!feof(fp)){
                if(fgets(liner, 1023, fp) == NULL)
                    break;
                ilines++;
                if(ilines > llineas)
                    break;
                archmem[ltmp] = malloc(sizeof(char)*(strlen(liner)+1));
                if(archmem[ltmp] == NULL){
                    printf("No se puede asignar memoria para cargar la linea %ld\n", ilines);
                    continue;
                }
                strcpy(archmem[ltmp], liner);
                ltmp++;
            }

            // Ahora ordeno el arreglo
            printf("Ordenando\n");
            tini = clock();
            if(ltmp > 30000){
                quickSortIterativo(archmem, 0, (ltmp-1));
            }
            else{
                quickSort(archmem, 0, (ltmp-1));
            }
            tfin = clock();
            dotmp = ((double)(tfin-tini))/CLOCKS_PER_SEC;
            printf("Tiempo total transcurrido en ordenamiento:%.2f\n", dotmp);
            guardarArregloChar(archmem, 0, (ltmp-1), "D:\\SourceCode\\DataProb\\DetalleIVAImpo\\ordenado.txt");
        }
        fclose(fp);

        // Ahora voy con el arbol binario
        printf("Agregando a arbol\n");
        tini = clock();
        btraiz = nuevoNodoOrd(archmem, 0, (ltmp - 1));
        tfin = clock();
        dotmp = ((double)(tfin-tini))/CLOCKS_PER_SEC;
        printf("Tiempo total transcurrido en agregamiento:%.2f\n", dotmp);
        printf("Primer CUSTCODE:%s\n", btraiz->dato.custcode);
    }*/

    btraiz = cargarArchivoDic(rutaf, &llineas);

    if(btraiz != NULL){
        while(1){
            printf("Introduzca un custcode(q para salida):");
            gets(liner);
            if(liner[0] == 'q' || liner[0] == 'Q')
                break;
            printf("custcode a buscar:%s\n", liner);
            tini = clock();
            bttmp = buscarNodo(btraiz, liner);
            tfin = clock();
            dotmp = ((double)(tfin-tini))/CLOCKS_PER_SEC;
            printf("Tiempo total transcurrido en busqueda:%.3f\n", dotmp);
            printf("++++++++++++++++++++++++++++++++++++++\n");
            if(bttmp != NULL){
                printf("CUSTCODE:%s\n", bttmp->dato.custcode);
                printf("IVA:%f\n", bttmp->dato.valoriva);
                printf("CONSUMO:%f\n", bttmp->dato.valorimpo);
            }
            else{
                printf("No se encuentra dato\n");
            }
            printf("++++++++++++++++++++++++++++++++++++++\n");
        }
        liberarNodo(&btraiz);
    }

    free(rutaf);
    return 0;
}
