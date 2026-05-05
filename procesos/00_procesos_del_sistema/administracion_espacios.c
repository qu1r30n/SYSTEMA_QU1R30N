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
#include <string.h>
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administracion_espacios.h"

/*
 * Uso: Ejecuta crear_espacios de forma segura.
 * Entrada ejemplo: crear_espacios(nom_espacio, usuario, contrasena, retorno_nombre_completo_espacio)
 */
int crear_espacios(char *nom_espacio, char *usuario, char *contrasena, char **retorno_nombre_completo_espacio) // crea un nuevo espacio de negocio: genera directorio, archivo principal y registro en el archivo maestro // ejemplo: crear_espacios("ferreteria_dan", "admin", "1234", &retorno)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char *folio_fecha = NULL;       /* fecha en formato YYYYMMDDHHMMSS usada como folio unico */
    char *nombre_directorio = NULL; /* ruta completa del directorio del espacio */
    char *nombre_archivo = NULL;    /* nombre base del archivo del espacio (folio_nom) */
    char *ruta_archivo = NULL;      /* ruta completa del archivo .txt del espacio */
    char *contenido_inicial = NULL; /* cabecera + primera fila que se escribe en el archivo del espacio */

    char *ruta_archivo_gg = NULL; /* ruta del archivo maestro donde se registran todos los espacios */
    char *linea_gg = NULL;        /* linea que se agrega al archivo maestro con los datos del espacio */

    if (!nom_espacio || !usuario || !contrasena) /* parametros obligatorios nulos */
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    folio_fecha = generar_folio("%Y%m%d%H%M%S"); /* genera timestamp unico para el nombre del espacio */
    if (!folio_fecha)                            /* fallo al generar folio de fecha */
        RETORNAR_PROCESO_ESTANDAR(-1);
    int res; // variable temporal para capturar codigos de retorno de concatenar_formato_separado_por_variable

    res = concatenar_formato_separado_por_variable(&nombre_archivo, NULL, "%s_%s", folio_fecha, nom_espacio); /* nombre_archivo = folio_nom_espacio */
    imprimirMensaje_para_depurar("%s\n", nombre_archivo); // imprime nombre_archivo en modo depuracion // ejemplo: "20260406224536_ferreteria_dan"
    res = concatenar_formato_separado_por_variable(&nombre_directorio, NULL, "%s%s_%s", GG_archivos[0][0], folio_fecha, nom_espacio); /* nombre_directorio = ruta_base/folio_nom_espacio */
    imprimirMensaje_para_depurar("%s\n", nombre_directorio); // imprime nombre_directorio en modo depuracion // ejemplo: "espacios\\20260406224536_ferreteria_dan"
    if (res < 0) /* fallo al construir nombre_directorio */
    {
        free(folio_fecha); // libera folio_fecha al abortar por error en nombre_directorio
        free(nombre_archivo); // libera nombre_archivo al abortar por error en nombre_directorio
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo construir nombre_directorio
    }

    if (concatenar_formato_separado_por_variable(&ruta_archivo, NULL, "%s\\%s.txt", nombre_directorio, nombre_archivo) < 0) /* ruta_archivo = nombre_directorio\nombre_archivo.txt */
    {
        free(folio_fecha); /* fallo al construir ruta del archivo del espacio */
        free(nombre_directorio); // libera nombre_directorio al abortar por error en ruta_archivo
        free(nombre_archivo); // libera nombre_archivo al abortar por error en ruta_archivo
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo construir la ruta del archivo del espacio
    }

    imprimirMensaje_para_depurar("%s\n", ruta_archivo); // imprime la ruta completa del archivo del espacio en modo depuracion // ejemplo: "espacios\\20260406224536_ferreteria_dan\\20260406224536_ferreteria_dan.txt"

    if (concatenar_formato_separado_por_variable(&contenido_inicial, NULL, "%s\n%s|%s|%s||1", GG_archivos[0][1], nombre_archivo, usuario, contrasena) < 0) /* contenido = cabecera + fila: nombre|usuario|contrasena||1 */
    {
        free(folio_fecha); /* fallo al construir contenido del archivo del espacio */
        free(nombre_directorio); // libera nombre_directorio al abortar por error en contenido_inicial
        free(ruta_archivo); // libera ruta_archivo al abortar por error en contenido_inicial
        free(nombre_archivo); // libera nombre_archivo al abortar por error en contenido_inicial
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo construir el contenido inicial del archivo del espacio
    }

    imprimirMensaje_para_depurar("%s\n", contenido_inicial); // imprime el contenido inicial del archivo del espacio en modo depuracion
    crearArchivo(ruta_archivo, contenido_inicial); /* crea el directorio y archivo del espacio con su contenido inicial */
    printf("Espacio creado: %s (usuario: %s)\n", nombre_directorio, usuario); // informa al usuario que el espacio fue creado // ejemplo: "Espacio creado: espacios\\20260406224536_ferreteria_dan (usuario: admin)"

    crear_archivos_base_negocio(nombre_archivo); /* crea los archivos base del negocio dentro del nuevo espacio */

    if (concatenar_formato_separado_por_variable(&ruta_archivo_gg, NULL, "%s\\%s", GG_archivos[0][0], GG_archivos[0][2]) < 0) /* ruta_archivo_gg = ruta_base\archivo_maestro */
    {
        free(folio_fecha); /* fallo al construir ruta del archivo maestro de espacios */
        free(nombre_directorio); // libera nombre_directorio al abortar por error en ruta_archivo_gg
        free(ruta_archivo); // libera ruta_archivo al abortar por error en ruta_archivo_gg
        free(nombre_archivo); // libera nombre_archivo al abortar por error en ruta_archivo_gg
        free(contenido_inicial); // libera contenido_inicial al abortar por error en ruta_archivo_gg
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo construir la ruta del archivo maestro de espacios
    }

    if (concatenar_formato_separado_por_variable(&linea_gg, NULL, "%s|%s|%s|%s|2", nombre_archivo, usuario, contrasena, ruta_archivo) < 0) /* linea_gg = nombre|usuario|contrasena|ruta_archivo|2 */
    {
        free(folio_fecha); /* fallo al construir la linea a registrar en el archivo maestro */
        free(nombre_directorio); // libera nombre_directorio al abortar por error en linea_gg
        free(ruta_archivo); // libera ruta_archivo al abortar por error en linea_gg
        free(nombre_archivo); // libera nombre_archivo al abortar por error en linea_gg
        free(contenido_inicial); // libera contenido_inicial al abortar por error en linea_gg
        free(ruta_archivo_gg); // libera ruta_archivo_gg al abortar por error en linea_gg
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo construir la linea para el archivo maestro de espacios
    }

    imprimirMensaje_para_depurar("%s\n", ruta_archivo_gg); // imprime la ruta del archivo maestro en modo depuracion // ejemplo: "espacios\\archivo_espacios.txt"

    agregar_fila(ruta_archivo_gg, linea_gg); /* registra el nuevo espacio en el archivo maestro */

    if (retorno_nombre_completo_espacio) /* solo copia el nombre si el caller paso un puntero valido */
    {
        if (concatenar_formato_separado_por_variable(retorno_nombre_completo_espacio, NULL, "%s", nombre_archivo) < 0) /* fallo al copiar nombre al parametro de retorno */
        {
            free(folio_fecha); // libera folio_fecha al abortar por error al copiar el nombre de retorno
            free(nombre_directorio); // libera nombre_directorio al abortar por error al copiar el nombre de retorno
            free(ruta_archivo); // libera ruta_archivo al abortar por error al copiar el nombre de retorno
            free(nombre_archivo); // libera nombre_archivo al abortar por error al copiar el nombre de retorno
            free(contenido_inicial); // libera contenido_inicial al abortar por error al copiar el nombre de retorno
            free(ruta_archivo_gg); // libera ruta_archivo_gg al abortar por error al copiar el nombre de retorno
            free(linea_gg); // libera linea_gg al abortar por error al copiar el nombre de retorno
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo copiar el nombre del espacio al parametro de retorno
        }
    }

    free(folio_fecha); // libera folio_fecha al finalizar correctamente la creacion del espacio
    free(nombre_directorio); // libera nombre_directorio al finalizar correctamente la creacion del espacio
    free(ruta_archivo); // libera ruta_archivo al finalizar correctamente la creacion del espacio
    free(nombre_archivo); // libera nombre_archivo al finalizar correctamente la creacion del espacio
    free(contenido_inicial); // libera contenido_inicial al finalizar correctamente la creacion del espacio
    free(ruta_archivo_gg); // libera ruta_archivo_gg al finalizar correctamente la creacion del espacio
    free(linea_gg); // libera linea_gg al finalizar correctamente la creacion del espacio
    RETORNAR_PROCESO_ESTANDAR(0); /* todo salio bien */
}

/*
 * Uso: Ejecuta crear_archivos_base_negocio de forma segura.
 * Entrada ejemplo: crear_archivos_base_negocio(id_espacio)
 */
int crear_archivos_base_negocio(const char *id_espacio) // crea todos los archivos y carpetas base dentro del espacio indicado por id_espacio // ejemplo: crear_archivos_base_negocio("20260406224536_ferreteria_dan")
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    int errores = 0; // contador de errores acumulados durante la creacion de archivos base
    const char *base_anterior = GG_direccion_carpetas_base[0]; // guarda la ruta base global actual para restaurarla al terminar // ejemplo: "espacios\\"
    char *base_dinamica = NULL; // ruta base temporal apuntando al espacio recien creado

    if (!id_espacio || !id_espacio[0]) // valida que id_espacio no sea nulo ni cadena vacia
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error si id_espacio es invalido

    if ((strchr(id_espacio, '\\') != NULL) || (strchr(id_espacio, '/') != NULL)) // detecta si id_espacio ya es una ruta completa con separadores de directorio
    {
        if (concatenar_formato_separado_por_variable(&base_dinamica, NULL, "%s", id_espacio) < 0) // usa id_espacio directamente como base_dinamica si ya es una ruta completa
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna error si fallo la copia de la ruta completa a base_dinamica
    }
    else
    {
        if (concatenar_formato_separado_por_variable(&base_dinamica, NULL, "%s%s", GG_archivos[0][0], id_espacio) < 0) // construye base_dinamica concatenando la ruta base con el id del espacio // ejemplo: "espacios\\20260406224536_ferreteria_dan"
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna error si fallo la construccion de base_dinamica
    }

    if (base_dinamica[0]) // verifica que base_dinamica no sea una cadena vacia antes de operar
    {
        size_t len = strlen(base_dinamica); // obtiene la longitud actual de base_dinamica
        if (base_dinamica[len - 1] != '\\' && base_dinamica[len - 1] != '/') // verifica si la ruta ya termina en separador de directorio
        {
            char *tmp = (char *)realloc(base_dinamica, len + 2); // redimensiona base_dinamica para agregar '\\' y '\0' al final
            if (!tmp) // verifica si fallo el realloc
            {
                free(base_dinamica); // libera base_dinamica si fallo el realloc
                RETORNAR_PROCESO_ESTANDAR(-1); // retorna error si no se pudo redimensionar base_dinamica
            }
            base_dinamica = tmp; // actualiza el puntero de base_dinamica al nuevo bloque de memoria
            base_dinamica[len] = '\\'; // agrega separador de directorio al final // ejemplo: "espacios\\20260406224536_ferreteria_dan\\"
            base_dinamica[len + 1] = '\0'; // termina la cadena con el caracter nulo
        }
    }

    GG_direccion_carpetas_base[0] = base_dinamica; // actualiza la ruta base global al nuevo espacio para que los arreglos se recarguen con las rutas correctas

    RecargarArregloArchivos_dir_nom_archivos(); // recarga GG_dir_nom_archivos con las rutas de archivos del nuevo espacio
    RecargarArregloDireccionInventarios(); // recarga GG_direccion_hacer_inventarios con las rutas de inventarios del nuevo espacio

    for (int i = 0; GG_dir_nom_archivos && GG_dir_nom_archivos[i].ruta; i++) // itera sobre cada archivo base registrado en GG_dir_nom_archivos para crearlo
    {
        const char *ruta = GG_dir_nom_archivos[i].ruta; // obtiene la ruta del archivo base en la iteracion actual
        const char *cabecera = GG_dir_nom_archivos[i].cabecera; // obtiene la cabecera que se escribira como primera linea del archivo base
        imprimirMensaje_para_depurar("\n\n ruta: %s \n cabesera[%d]: %s\n", ruta, i, cabecera); // imprime en modo depuracion la ruta y cabecera del archivo a crear

        if (!ruta || !ruta[0]) // salta si la ruta del archivo base es nula o vacia
            continue; // avanza al siguiente elemento de GG_dir_nom_archivos

        int ret = crearArchivo(ruta, cabecera ? cabecera : ""); // crea el archivo base con su cabecera; usa cadena vacia si cabecera es nula
        if (ret < 0) // verifica si la creacion del archivo base fallo
        {
            imprimirMensaje_para_depurar("[crear_archivos_base_negocio] error creando base[%d]: %s\n", i, ruta); // registra en modo depuracion el error con el indice y la ruta del archivo que fallo
            errores++; // incrementa el contador de errores de archivos base
        }
    }

    for (int i = 0; GG_direccion_hacer_inventarios && GG_direccion_hacer_inventarios[i].ruta; i++) // itera sobre cada directorio de inventario registrado en GG_direccion_hacer_inventarios para crearlo
    {
        const char *ruta = GG_direccion_hacer_inventarios[i].ruta; // obtiene la ruta del archivo de inventario en la iteracion actual
        const char *cabecera = GG_direccion_hacer_inventarios[i].cabecera; // obtiene la cabecera que se escribira como primera linea del archivo de inventario

        if (!ruta || !ruta[0]) // salta si la ruta del inventario es nula o vacia
            continue; // avanza al siguiente elemento de GG_direccion_hacer_inventarios

        int ret = crearArchivo(ruta, cabecera ? cabecera : ""); // crea el archivo de inventario con su cabecera; usa cadena vacia si cabecera es nula
        if (ret < 0) // verifica si la creacion del archivo de inventario fallo
        {
            imprimirMensaje_para_depurar("[crear_archivos_base_negocio] error creando inventario[%d]: %s\n", i, ruta); // registra en modo depuracion el error con el indice y la ruta de inventario que fallo
            errores++; // incrementa el contador de errores de archivos de inventario
        }
    }

    GG_direccion_carpetas_base[0] = (char *)base_anterior; // restaura la ruta base global al valor original previo a esta funcion
    free(base_dinamica); // libera la memoria de la ruta base dinamica del espacio creado

    if (errores > 0) // verifica si hubo errores durante la creacion de algun archivo
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error si al menos un archivo base o de inventario no pudo crearse

    RETORNAR_PROCESO_ESTANDAR(0); // retorna exito: todos los archivos base e inventarios del espacio fueron creados correctamente
}
