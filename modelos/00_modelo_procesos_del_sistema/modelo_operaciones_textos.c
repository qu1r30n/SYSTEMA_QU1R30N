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


int modelo_texto_a_int_seguro(char *texto) 
{
    int valor_int;
    texto_a_int_seguro(texto, &valor_int);
    return valor_int;
}

float modelo_texto_a_float_seguro( char *texto) 
{
    float valor_float;
    texto_a_float_seguro(texto, &valor_float);
    return valor_float;
}

