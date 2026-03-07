#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_arreglos.h"

int arreglo_obtener_entero_por_orden(StructurasDinamicas *datos, int orden, int *salida)
{
    int *ptr = (int *)obtenerValorPorOrden(datos, orden);
    if (!ptr || !salida)
    {
        return -1;
    }
    *salida = *ptr;
    return 0;
}

int arreglo_obtener_flotante_por_orden(StructurasDinamicas *datos, int orden, float *salida)
{
    float *ptr = (float *)obtenerValorPorOrden(datos, orden);
    if (!ptr || !salida)
    {
        return -1;
    }
    *salida = *ptr;
    return 0;
}

int arreglo_obtener_cadena_por_orden(StructurasDinamicas *datos, int orden, char **salida)
{
    char *ptr = (char *)obtenerValorPorOrden(datos, orden);
    if (!ptr || !salida)
    {
        return -1;
    }
    *salida = ptr;
    return 0;
}
