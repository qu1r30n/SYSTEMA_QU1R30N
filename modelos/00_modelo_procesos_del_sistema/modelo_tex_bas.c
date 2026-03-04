#include <stdio.h>
#include <stddef.h>
#include <string.h>

#ifdef _WIN32
#include <stdlib.h>
#include <sys/stat.h>
#include <direct.h>

#elif defined(__linux__)
#include <stdlib.h>
#include <sys/stat.h>

#elif defined(__XC)
#define _XTAL_FREQ 4000000
#include <xc.h>
/* PIC16F: Sin archivos. Las funciones son stubs. */

#else
#include <stdlib.h>
#include <sys/stat.h>
#endif

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"

/* ===== MODELO DE PROCESOS DEL SISTEMA: OPERACIONES DE TEXTOS ===== */
// Crear directorio
void modelo_crearDirectorio(char *texto)
{
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] =
        {
            {"ruta", "string", "nose", ""},
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

    char *ruta = (char *)obtenerValorPorOrden(&datos, 0);
    crearDirectorio(ruta);

    modelo_free_split(partes);
    liberarStructura(&datos);
}

// Crear archivo
void modelo_crearArchivo(char *texto)
{
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] =
        {
            {"ruta", "string", "nose", ""},
            {"contenido", "string", "nose", ""},
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

    char *ruta = (char *)obtenerValorPorOrden(&datos, 0);
    char *contenido = (char *)obtenerValorPorOrden(&datos, 1);
    crearArchivo(ruta, contenido);

    modelo_free_split(partes);
    liberarStructura(&datos);
}

// Leer archivo
void modelo_leer_archivo(char *texto)
{
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] =
        {
            {"ruta", "string", "nose", ""},
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

    char *ruta = (char *)obtenerValorPorOrden(&datos, 0);
    char lineas[MAX_LINEAS][MAX_LINEA];
    leer_archivo(ruta, lineas);

    modelo_free_split(partes);
    liberarStructura(&datos);
}

// Guardar archivo
void modelo_guardar_archivo(char *texto)
{
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] =
        {
            {"ruta", "string", "nose", ""},
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

    char *ruta = (char *)obtenerValorPorOrden(&datos, 0);
    char lineas[MAX_LINEAS][MAX_LINEA];
    guardar_archivo(ruta, lineas, 0);

    modelo_free_split(partes);
    liberarStructura(&datos);
}

// Agregar fila
void modelo_agregar_fila(char *texto)
{
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] =
        {
            {"ruta", "string", "nose", ""},
            {"fila", "string", "nose", ""},
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

    char *ruta = (char *)obtenerValorPorOrden(&datos, 0);
    char *fila = (char *)obtenerValorPorOrden(&datos, 1);
    agregar_fila(ruta, fila);

    modelo_free_split(partes);
    liberarStructura(&datos);
}
