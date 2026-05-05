/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - ../../CLASE_QU1R30N.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_administracion_espacios.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administracion_espacios.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h: Dependencia interna del proyecto
 */
#include "../../CLASE_QU1R30N.h"
#include <stdlib.h>
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_administracion_espacios.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administracion_espacios.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"

/*
 * Uso: Ejecuta modelo_administracion_espacios_crear_espacio de forma segura.
 * Entrada ejemplo: modelo_administracion_espacios_crear_espacio(texto)
 */
int modelo_administracion_espacios_crear_espacio(char *texto)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    imprimirMensaje_para_depurar("\n\ntexto=%s\n", texto);

    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"nom_espacio", "string", "NOSE", ""},
            {"usuario_de_negocio", "string", "NOSE", ""},
            {"contraseña_de_negocio", "string", "NOSE", ""},
            {NULL, NULL, NULL, NULL}};

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[2]);
    if (!partes)
    {
        return -2;
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
        liberarStructura(&datos); // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
        return (ret_parse < 0) ? ret_parse : -3; // si el parseo fallo retorna su codigo, si no hay partes retorna -3 // ejemplo: ret_parse=-1
    }
    char *retorno_nombre_completo_espacio = NULL;
    int ret_crear_espacio = crear_espacios(
        (char *)obtenerValorPorOrden(&datos, 0),
        (char *)obtenerValorPorOrden(&datos, 1),
        (char *)obtenerValorPorOrden(&datos, 2),
        &retorno_nombre_completo_espacio);

    modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
    liberarStructura(&datos); // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.

    if (retorno_nombre_completo_espacio)
    {
        free(retorno_nombre_completo_espacio);
    }

    if (ret_crear_espacio < 0)
    {
        return -1;
    }

    return 0;
}
