/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - stdlib.h: Memoria dinamica, conversiones y utilidades generales
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/gestor_de_permisos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 */
#include <stdio.h>  // printf y utilidades de entrada/salida
#include <stdlib.h> // atoi y utilidades generales de conversion
#include <string.h> // strcmp para comparar texto

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/gestor_de_permisos.h" // firma publica de checar_permiso
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"            // leer_archivo, free_lineas, existe_archivo
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h" // split() y free_split()
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"         // separadores globales GG_
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"  // imprimirMensaje_para_depurar

int checar_permiso(int nivel_minimo, const char *ruta_archivo, const char *id_de_espacio, const char *usuario, const char *contrasena, char **retorna_direccion_espacio_negocio, int *retornar_nivel)
{
    if (retorna_direccion_espacio_negocio)
    {
        *retorna_direccion_espacio_negocio = NULL;
    }
    if (retornar_nivel)
    {
        *retornar_nivel = -1;
    }

    // Traza de depuracion con todos los parametros recibidos.
    imprimirMensaje_para_depurar("\n\n%s\n%s\n%s\n%s\n%d", ruta_archivo, id_de_espacio, usuario, contrasena, nivel_minimo);

    // Validar que no lleguen punteros nulos en parametros obligatorios.
    if (!ruta_archivo || !id_de_espacio || !usuario || !contrasena)
    {
        // Retorno -1: error de argumentos.
        return -1;
    }

    // Validar que el archivo de permisos exista antes de intentar leerlo.
    if (!existe_archivo(ruta_archivo))
    {
        // Retorno -1: archivo inexistente o inaccesible.
        return -1;
    }

    // Variable de salida: cantidad de lineas encontradas en el archivo.
    int n_lineas = 0;
    // Cargar todas las lineas del archivo en memoria.
    char **lineas = leer_archivo(ruta_archivo, &n_lineas);
    if (!lineas)
    {
        // Retorno -1: fallo al leer archivo.
        return -1;
    }

    // Resultado por defecto: no tiene permiso (1 = denegado, 0 = permitido).
    int tiene_permiso = 1;
    // Separador de columnas configurado globalmente (normalmente '|').
    const char *sep = GG_caracter_separacion[0]; // separador de columnas del archivo

    // Inicia en 1 para saltar cabecera (fila 0: nombres de columnas).
    for (int i = 1; i < n_lineas; i++)
    {
        // Si la linea viene nula, se ignora.
        if (!lineas[i])
        {
            // Continua con la siguiente fila.
            continue;
        }

        /* Extraer columnas usando split() de operaciones_textos. */
        char **columnas = NULL;
        // Divide una linea en columnas por separador y deja arreglo terminado en NULL.
        split(lineas[i], sep, &columnas);

        // Contador real de columnas encontradas.
        int n_columnas = 0;
        if (columnas)
        {
            // Recorre hasta el NULL final para contar columnas existentes.
            for (int c = 0; columnas[c] != NULL; c++)
            {
                // Traza de cada columna para revisar formato de datos.
                imprimirMensaje_para_depurar("%s\n", columnas[c]);
                // Suma una columna valida.
                n_columnas++;
            }
        }

        // Se requieren 5 columnas: ID|Usuario|Contrasena|Directorio|Nivel
        if (n_columnas >= 5 &&
            // Columna 0 del archivo debe coincidir con el id de espacio solicitado.
            strcmp(columnas[0], id_de_espacio) == 0 &&
            // Columna 1 del archivo debe coincidir con usuario solicitado.
            strcmp(columnas[1], usuario) == 0 &&
            // Columna 2 del archivo debe coincidir con contrasena solicitada.
            strcmp(columnas[2], contrasena) == 0)
        {
            // Convierte nivel del usuario (texto) a entero.
            int nivel_usuario = atoi(columnas[4]);
            if (retornar_nivel)
            {
                *retornar_nivel = nivel_usuario;
            }

            // Devuelve por salida una copia de la direccion del espacio de negocio (columna 3).
            if (retorna_direccion_espacio_negocio && columnas[3])
            {
                *retorna_direccion_espacio_negocio = (char *)malloc(strlen(columnas[3]) + 1);
                strcpy(*retorna_direccion_espacio_negocio, columnas[3]);
            }

            // Con la convención actual: 0 = permitido, 1 = denegado.
            tiene_permiso = (nivel_usuario <= nivel_minimo) ? 0 : 1;
            // Liberar columnas antes de salir del ciclo.
            free_split(columnas);
            // Ya se encontro usuario; se deja de buscar.
            break;
        }

        // Liberar columnas en caso de no coincidir o no cumplir condiciones.
        free_split(columnas);
    }

    // Liberar todas las lineas leidas del archivo.
    free_lineas(lineas, n_lineas);
    // Retornar 0 si tiene permiso, 1 si no tiene, -1 en errores previos.
    return tiene_permiso;
}
