#include <stdio.h>
#include <stdlib.h>
#include "configura.h"


int main()
{
    int palabras = 0;
    int i;
    char prueba[] = "Esto;es;;una;prueba;";
    char prueba2[] = "Yolanda:Enid:Palacios:Perdigon";
    char **salida;
    salida = NULL;
    printf("Hello world!\n");
    palabras = splitString(';', prueba, &salida);
    printf("Mensaje:%s\n", prueba);
    for(i = 0; i < palabras; i++){
        printf("Palabra %d:%s\n", i, salida[i]);
    }
    palabras = splitString(':', prueba2, &salida);
    printf("Mensaje:%s\n", prueba2);
    for(i = 0; i < palabras; i++){
        printf("Palabra %d:%s\n", i, salida[i]);
    }
    return 0;
}
