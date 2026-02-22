#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"

char** modelo_split(char* texto, const char* sep) 
{
    char** salida = NULL;
    
    int resultado = split(texto, sep, &salida);

    if(resultado == -1) 
    {
        // Error al hacer split
        return NULL;
    }

    return salida; // char** terminado en NULL
}

void modelo_free_split(char** arreglo)
{
    /* Si es NULL, no hacer nada */
    if (arreglo == NULL)
        return;

    int i = 0;

    /* Recorrer hasta encontrar NULL */
    while (arreglo[i] != NULL)
    {
        free(arreglo[i]);
        i++;
    }

    /* Liberar arreglo principal */
    free(arreglo);
}
