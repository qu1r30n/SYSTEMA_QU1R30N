/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_arreglos.h: Dependencia interna del proyecto
 * - stdlib.h: Memoria dinamica (malloc, realloc, free)
 * - string.h: Manejo de cadenas (strlen, memcpy)
 */
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_arreglos.h"
#include <stdlib.h>
#include <string.h>

void agregar_texto_a_arreglo(char ***arreglo, const char *texto)
{
    if (!arreglo || !texto)
    {
        return;
    }

    int cantidad_actual = 0;
    if (*arreglo)
    {
        while ((*arreglo)[cantidad_actual])
        {
            cantidad_actual++;
        }
    }

    char **nuevo_arreglo = (char **)realloc(*arreglo, (size_t)(cantidad_actual + 2) * sizeof(char *));
    if (!nuevo_arreglo)
    {
        return;
    }

    size_t largo_texto = strlen(texto);
    char *texto_nuevo = (char *)malloc(largo_texto + 1);
    if (!texto_nuevo)
    {
        return;
    }

    memcpy(texto_nuevo, texto, largo_texto + 1);

    nuevo_arreglo[cantidad_actual] = texto_nuevo;
    nuevo_arreglo[cantidad_actual + 1] = NULL;
    *arreglo = nuevo_arreglo;
}
