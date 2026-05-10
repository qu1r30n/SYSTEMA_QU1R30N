/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf)
 * - stdlib.h: Memoria dinamica (free)
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h: Construccion de rutas dinamicas
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h: Creacion de archivos
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administrador_de_estructuras_base.h: Dependencia interna del proyecto
 */
#include <stdio.h>
#include <stdlib.h>
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administrador_de_estructuras_base.h"

/*
 * Uso: Ejecuta creacion_de_estructura_base de forma segura.
 * Entrada ejemplo: creacion_de_estructura_base(nombre_de_structura, direccion_del_espacio)
 */
int creacion_de_estructura_base(char *nombre_de_structura, char *direccion_del_espacio) // crea los archivos base de una estructura (inventario, campos, relaciones, indices) en el directorio del espacio indicado // ejemplo: creacion_de_estructura_base("tienda", "espacios\\20260406224536_ferreteria_dan\\20260406224536_ferreteria_dan.txt")
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */

    char *directorios = NULL; // parte de la ruta correspondiente solo a los directorios, extraida por desfragmentar_direccion // ejemplo: "espacios\\20260406224536_ferreteria_dan"
    char *nom_arch = NULL;    // nombre base del archivo sin extension, extraido por desfragmentar_direccion // ejemplo: "20260406224536_ferreteria_dan"
    char *extencion = NULL;   // extension del archivo extraida por desfragmentar_direccion // ejemplo: ".txt"

    if (desfragmentar_direccion(direccion_del_espacio, &directorios, &nom_arch, &extencion) == 0) // separa direccion_del_espacio en sus componentes: directorio, nombre de archivo y extension
    {
        free(directorios);             // libera directorios si desfragmentar_direccion retorno 0 (error o sin datos)
        free(nom_arch);                // libera nom_arch si desfragmentar_direccion retorno 0 (error o sin datos)
        free(extencion);               // libera extencion si desfragmentar_direccion retorno 0 (error o sin datos)
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo desfragmentar la direccion del espacio
    }

    char *nom_columnas = NULL;                                         // cadena que acumula los nombres de columnas del inventario separados por GG_caracter_separacion[0]
    for (int i = 0; GG_ventana_emergente_productos[i][1] != NULL; i++) // itera sobre cada campo definido en GG_ventana_emergente_productos hasta encontrar NULL
    {

        concatenar_formato_separado_por_variable(&nom_columnas, GG_caracter_separacion[0], "%s", GG_ventana_emergente_productos[i][1]); // concatena el nombre del campo actual a nom_columnas usando el separador de GG_caracter_separacion[0]
    }

    const char *archivos_base[][2] = {                                                               // tabla estatica con los nombres de archivos a crear y sus cabeceras de columnas
                                      {"inventario.txt", nom_columnas},                              // archivo de inventario con columnas dinamicas definidas en GG_ventana_emergente_productos
                                      {"campos.txt", "col1|col2|col3|col4|col5|col6|col7|col8"},     // archivo de campos con cabecera generica de 8 columnas
                                      {"relaciones.txt", "col1|col2|col3|col4|col5|col6|col7|col8"}, // archivo de relaciones con cabecera generica de 8 columnas
                                      {"indices.txt", "col1|col2|col3|col4|col5|col6|col7|col8"},    // archivo de indices con cabecera generica de 8 columnas
                                      {NULL, NULL}};                                                 // centinela que marca el final del arreglo

    if (!nombre_de_structura || !direccion_del_espacio) // valida que los parametros de entrada no sean nulos
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error si alguno de los parametros es nulo
    }

    for (int i = 0; archivos_base[i][0] != NULL; i++) // itera sobre cada entrada de archivos_base hasta el centinela NULL
    {
        char *ruta_archivo = NULL; // ruta completa del archivo a crear en esta iteracion del bucle

        if (concatenar_formato_separado_por_variable(&ruta_archivo, NULL, "%s\\%s_%s", directorios, nom_arch, archivos_base[i][0]) < 0) // construye la ruta del archivo base // ejemplo: "espacios\\20260406224536_ferreteria_dan\\20260406224536_ferreteria_dan_inventario.txt"
        {
            free(directorios);             // libera directorios al abortar por error al construir la ruta del archivo base
            free(nom_arch);                // libera nom_arch al abortar por error al construir la ruta del archivo base
            free(extencion);               // libera extencion al abortar por error al construir la ruta del archivo base
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo construir la ruta del archivo base
        }

        if (crearArchivo(ruta_archivo, archivos_base[i][1]) < 0) // crea el archivo base con su cabecera de columnas
        {
            free(ruta_archivo);            // libera ruta_archivo al abortar por error al crear el archivo base
            free(directorios);             // libera directorios al abortar por error al crear el archivo base
            free(nom_arch);                // libera nom_arch al abortar por error al crear el archivo base
            free(extencion);               // libera extencion al abortar por error al crear el archivo base
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo crear el archivo base en el espacio
        }

        free(ruta_archivo); // libera la ruta del archivo creado en esta iteracion antes de continuar con la siguiente
    }

    free(directorios); // libera directorios al finalizar correctamente todos los archivos de la estructura
    free(nom_arch);    // libera nom_arch al finalizar correctamente todos los archivos de la estructura
    free(extencion);   // libera extencion al finalizar correctamente todos los archivos de la estructura

    printf("Creacion de estructura base: %s\n", nombre_de_structura); // informa que la estructura base fue creada exitosamente // ejemplo: "Creacion de estructura base: tienda"
    RETORNAR_PROCESO_ESTANDAR(0);                                     // retorna exito: todos los archivos de la estructura base fueron creados correctamente
}