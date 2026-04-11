/*
 * Modulo: ControladorMonitoreoArchivo
 * Lee la ruta definida en GG_archivos y detecta si existe una linea extra.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/ControladorMonitoreoArchivo.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

void respuesta(char *info_respuesta)
{
    const char *directorio = GG_archivos[2][0];
    const char *archivo = GG_archivos[2][2];
    char *ruta = NULL;

    if (info_respuesta == NULL || info_respuesta[0] == '\0' ||
        directorio == NULL || archivo == NULL)
    {
        return;
    }

    if (concatenar_formato_separado_por_variable(&ruta, NULL, "%s", directorio) < 0)
    {
        free(ruta);
        return;
    }

    if (concatenar_formato_separado_por_variable(&ruta, NULL, "%s", archivo) < 0)
    {
        free(ruta);
        return;
    }

    agregar_fila(ruta, info_respuesta);
    free(ruta);
}

int monitoreo_archivo_entrada(char **retorno_comando)
{
    const char *directorio = GG_archivos[2][0];
    const char *archivo = GG_archivos[2][2];
    char *ruta = NULL;
    int n_lineas = 0;
    char **lineas = NULL;

    if (retorno_comando == NULL)
    {
        return -1;
    }

    *retorno_comando = NULL;

    if (directorio == NULL || archivo == NULL)
    {
        return -1;
    }

    if (concatenar_formato_separado_por_variable(&ruta, NULL, "%s", directorio) < 0)
    {
        free(ruta);
        return -1;
    }

    if (concatenar_formato_separado_por_variable(&ruta, NULL, "%s", archivo) < 0)
    {
        free(ruta);
        return -1;
    }

    lineas = leer_archivo(ruta, &n_lineas);
    free(ruta);
    if (lineas == NULL)
    {
        return -1;
    }

    if (n_lineas > 1)
    {
        const char *linea_encontrada = lineas[n_lineas - 1];
        if (linea_encontrada != NULL)
        {
            *retorno_comando = (char *)malloc(strlen(linea_encontrada) + 1);
            if (*retorno_comando == NULL)
            {
                free_lineas(lineas, n_lineas);
                return -1;
            }

            strcpy(*retorno_comando, linea_encontrada);
            free_lineas(lineas, n_lineas);
            return 1;
        }
    }

    free_lineas(lineas, n_lineas);
    return 0;
}
