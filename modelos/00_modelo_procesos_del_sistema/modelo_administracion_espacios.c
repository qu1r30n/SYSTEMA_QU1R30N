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

int modelo_administracion_espacios_crear_espacio(char *texto)
{
    imprimirMensaje_para_depurar("\n\ntexto=%s\n", texto);

    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"nom_espacio", "string", "NOSE", ""},
            {"usuario", "string", "NOSE", ""},
            {"contraseña", "string", "NOSE", ""},
            {NULL, NULL, NULL, NULL}};

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[2]);
    if (!partes)
    {
        return -2;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = crearStructuraVacia();
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return (ret_parse < 0) ? ret_parse : -3;
    }
    char *retorno_nombre_completo_espacio = NULL;
    int ret_crear_espacio = crear_espacios(
        (char *)obtenerValorPorOrden(&datos, 0),
        (char *)obtenerValorPorOrden(&datos, 1),
        (char *)obtenerValorPorOrden(&datos, 2),
        &retorno_nombre_completo_espacio);

    modelo_free_split(partes);
    liberarStructura(&datos);

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
