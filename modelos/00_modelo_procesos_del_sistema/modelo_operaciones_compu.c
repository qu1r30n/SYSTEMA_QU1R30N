#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_compu.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h" /* necesitamos la firma de modelo_split */
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include <stddef.h>

void modelo_fechaActual(char *texto)
{
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] =
        {
            {"buffer", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0]);

    if (cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return;
    }

    /* Antes se hacía modelo_split(texto,"|") pero el valor devuelto no
       se utilizaba; quitar la llamada o almacenarla si hace falta.
       El propósito de esta función es simplemente delegar en el proceso. */
    fechaActual(texto, "%Y-%m-%d %H:%M:%S");

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_delay_ms(char *texto)
{
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] =
        {
            {"ms", "int", "0", ""},
            {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0]);

    if (cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return;
    }

    unsigned int ms = *(int *)obtenerValorPorOrden(&datos, 0);
    delay_ms(ms);

    modelo_free_split(partes);
    liberarStructura(&datos);
}
