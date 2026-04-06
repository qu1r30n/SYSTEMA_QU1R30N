/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf)
 * - stdlib.h: Memoria dinamica (free)
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h: Depuracion y utilidades del sistema
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administracion_espacios.h: Dependencia interna del proyecto
 */
#include <stdio.h>
#include <stdlib.h>
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administracion_espacios.h"

int crear_espacios(char *nom_espacio, char *usuario, char *contrasena, char **retorno_nombre_completo_espacio)
{
    char *folio_fecha = NULL;       /* fecha en formato YYYYMMDDHHMMSS usada como folio unico */
    char *nombre_directorio = NULL; /* ruta completa del directorio del espacio */
    char *nombre_archivo = NULL;    /* nombre base del archivo del espacio (folio_nom) */
    char *ruta_archivo = NULL;      /* ruta completa del archivo .txt del espacio */
    char *contenido_inicial = NULL; /* cabecera + primera fila que se escribe en el archivo del espacio */

    char *ruta_archivo_gg = NULL; /* ruta del archivo maestro donde se registran todos los espacios */
    char *linea_gg = NULL;        /* linea que se agrega al archivo maestro con los datos del espacio */

    if (!nom_espacio || !usuario || !contrasena) /* parametros obligatorios nulos */
    {
        return -1;
    }

    folio_fecha = generar_folio("%Y%m%d%H%M%S"); /* genera timestamp unico para el nombre del espacio */
    if (!folio_fecha)                            /* fallo al generar folio de fecha */
        return -1;
    int res;

    res = concatenar_formato_separado_por_variable(&nombre_archivo, NULL, "%s_%s", folio_fecha, nom_espacio); /* nombre_archivo = folio_nom_espacio */
    imprimirMensaje_para_depurar("%s\n", nombre_archivo);
    res = concatenar_formato_separado_por_variable(&nombre_directorio, NULL, "%s%s_%s", GG_archivos[0][0], folio_fecha, nom_espacio); /* nombre_directorio = ruta_base/folio_nom_espacio */
    imprimirMensaje_para_depurar("%s\n", nombre_directorio);
    if (res < 0) /* fallo al construir nombre_directorio */
    {
        free(folio_fecha);
        free(nombre_archivo);
        return -1;
    }

    if (concatenar_formato_separado_por_variable(&ruta_archivo, NULL, "%s\\%s.txt", nombre_directorio, nombre_archivo) < 0) /* ruta_archivo = nombre_directorio\nombre_archivo.txt */
    {
        free(folio_fecha); /* fallo al construir ruta del archivo del espacio */
        free(nombre_directorio);
        free(nombre_archivo);
        return -1;
    }

    imprimirMensaje_para_depurar("%s\n", ruta_archivo);

    if (concatenar_formato_separado_por_variable(&contenido_inicial, NULL, "%s\n%s|%s|%s||1", GG_archivos[0][1], nombre_archivo, usuario, contrasena) < 0) /* contenido = cabecera + fila: nombre|usuario|contrasena||1 */
    {
        free(folio_fecha); /* fallo al construir contenido del archivo del espacio */
        free(nombre_directorio);
        free(ruta_archivo);
        free(nombre_archivo);
        return -1;
    }

    imprimirMensaje_para_depurar("%s\n", contenido_inicial);
    crearArchivo(ruta_archivo, contenido_inicial); /* crea el directorio y archivo del espacio con su contenido inicial */
    printf("Espacio creado: %s (usuario: %s)\n", nombre_directorio, usuario);

    if (concatenar_formato_separado_por_variable(&ruta_archivo_gg, NULL, "%s\\%s", GG_archivos[0][0], GG_archivos[0][2]) < 0) /* ruta_archivo_gg = ruta_base\archivo_maestro */
    {
        free(folio_fecha); /* fallo al construir ruta del archivo maestro de espacios */
        free(nombre_directorio);
        free(ruta_archivo);
        free(nombre_archivo);
        free(contenido_inicial);
        return -1;
    }

    if (concatenar_formato_separado_por_variable(&linea_gg, NULL, "%s|%s|%s|%s|2", nombre_archivo, usuario, contrasena, ruta_archivo) < 0) /* linea_gg = nombre|usuario|contrasena|ruta_archivo|2 */
    {
        free(folio_fecha); /* fallo al construir la linea a registrar en el archivo maestro */
        free(nombre_directorio);
        free(ruta_archivo);
        free(nombre_archivo);
        free(contenido_inicial);
        free(ruta_archivo_gg);
        return -1;
    }

    imprimirMensaje_para_depurar("%s\n", ruta_archivo_gg);

    agregar_fila(ruta_archivo_gg, linea_gg); /* registra el nuevo espacio en el archivo maestro */

    if (retorno_nombre_completo_espacio) /* solo copia el nombre si el caller paso un puntero valido */
    {
        if (concatenar_formato_separado_por_variable(retorno_nombre_completo_espacio, NULL, "%s", nombre_archivo) < 0) /* fallo al copiar nombre al parametro de retorno */
        {
            free(folio_fecha);
            free(nombre_directorio);
            free(ruta_archivo);
            free(nombre_archivo);
            free(contenido_inicial);
            free(ruta_archivo_gg);
            free(linea_gg);
            return -1;
        }
    }

    free(folio_fecha);
    free(nombre_directorio);
    free(ruta_archivo);
    free(nombre_archivo);
    free(contenido_inicial);
    free(ruta_archivo_gg);
    free(linea_gg);
    return 0; /* todo salio bien */
}
