/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - ../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_compu.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 * - stddef.h: Tipos base como size_t y NULL
 */
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_compu.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h" /* necesitamos la firma de modelo_split */
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include <stddef.h>

/*
 * Uso: Ejecuta modelo_fechaActual de forma segura.
 * Entrada ejemplo: modelo_fechaActual(texto)
 */
void modelo_fechaActual(char *texto)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] = {{"buffer", "string", "nose", ""}, {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0; // contador de filas en nombres_variables[] hasta encontrar NULL // ejemplo: 3
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++; // avanza al siguiente parametro esperado // ejemplo: 0->1->2->NULL
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return;
    }

    int cuantas_partes = 0; // contador de partes resultantes del split // ejemplo: 3
    while (partes[cuantas_partes])
    {
        cuantas_partes++; // incrementa contador de partes // ejemplo: 0->1->2
    }

    StructurasDinamicas datos = crearStructuraVacia(); // crea estructura dinamica vacia para guardar los valores parseados // ejemplo: datos con 0 campos
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0) // aborta si el parseo fallo o no hay partes para procesar // ejemplo: ret_parse=-1 -> retorna
    {
        modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
        liberarStructura(&datos);  // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
        return;
    }

    /* Antes se hacía modelo_split(texto,"|") pero el valor devuelto no
       se utilizaba; quitar la llamada o almacenarla si hace falta.
       El propósito de esta función es simplemente delegar en el proceso. */
    fechaActual(texto, "%Y-%m-%d %H:%M:%S");

    modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
    liberarStructura(&datos);  // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
}

/*
 * Uso: Ejecuta modelo_delay_ms de forma segura.
 * Entrada ejemplo: modelo_delay_ms(texto)
 */
void modelo_delay_ms(char *texto)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (!texto)
    {
        return;
    }

    char *nombres_variables[][4] = {{"ms", "int", "0", ""}, {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0; // contador de filas en nombres_variables[] hasta encontrar NULL // ejemplo: 3
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++; // avanza al siguiente parametro esperado // ejemplo: 0->1->2->NULL
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return;
    }

    int cuantas_partes = 0; // contador de partes resultantes del split // ejemplo: 3
    while (partes[cuantas_partes])
    {
        cuantas_partes++; // incrementa contador de partes // ejemplo: 0->1->2
    }

    StructurasDinamicas datos = crearStructuraVacia(); // crea estructura dinamica vacia para guardar los valores parseados // ejemplo: datos con 0 campos
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0) // aborta si el parseo fallo o no hay partes para procesar // ejemplo: ret_parse=-1 -> retorna
    {
        modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
        liberarStructura(&datos);  // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
        return;
    }

    unsigned int ms = *(int *)obtenerValorPorOrden(&datos, 0);
    delay_ms(ms);

    modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
    liberarStructura(&datos);  // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
}
