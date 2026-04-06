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
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administrador_de_estructuras_base.h"

int creacion_de_estructura_base(char *nombre_de_structura, char *direccion_del_espacio)
{

    char *directorios = NULL;
    char *nom_arch = NULL;
    char *extencion = NULL;

    if (desfragmentar_direccion(direccion_del_espacio, &directorios, &nom_arch, &extencion) == 0)
    {
        free(directorios);
        free(nom_arch);
        free(extencion);
        return -1;
    }

    char *nom_columnas = NULL;
    for (int i = 0; GG_ventana_emergente_productos[i][1] != NULL; i++)
    {

        concatenar_formato_separado_por_variable(&nom_columnas, GG_caracter_separacion[0], "%s", GG_ventana_emergente_productos[i][1]);
    }

    const char *archivos_base[][2] = {
        {"inventario.txt", nom_columnas},
        {"campos.txt", "col1|col2|col3|col4|col5|col6|col7|col8"},
        {"relaciones.txt", "col1|col2|col3|col4|col5|col6|col7|col8"},
        {"indices.txt", "col1|col2|col3|col4|col5|col6|col7|col8"},
        {NULL, NULL}};

    if (!nombre_de_structura || !direccion_del_espacio)
    {
        return -1;
    }

    for (int i = 0; archivos_base[i][0] != NULL; i++)
    {
        char *ruta_archivo = NULL;

        if (concatenar_formato_separado_por_variable(&ruta_archivo, NULL, "%s\\%s_%s", directorios, nom_arch, archivos_base[i][0]) < 0)
        {
            free(directorios);
            free(nom_arch);
            free(extencion);
            return -1;
        }

        if (crearArchivo(ruta_archivo, archivos_base[i][1]) < 0)
        {
            free(ruta_archivo);
            free(directorios);
            free(nom_arch);
            free(extencion);
            return -1;
        }

        free(ruta_archivo);
    }

    free(directorios);
    free(nom_arch);
    free(extencion);

    printf("Creacion de estructura base: %s\n", nombre_de_structura);
    return 0;
}