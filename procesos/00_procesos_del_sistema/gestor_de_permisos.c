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
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"  // imprimirMensaje_para_depurar
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h" // split() y free_split()
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"            // leer_archivo, free_lineas, existe_archivo
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"         // separadores globales GG_

/*
 * Uso: Ejecuta checar_permiso de forma segura.
 * Entrada ejemplo: checar_permiso(nivel_minimo, ruta_archivo, id_de_espacio, usuario, contrasena, retorna_direccion_espacio_negocio, retornar_nivel)
 */
int checar_permiso(int nivel_minimo, const char *ruta_archivo, const char *id_de_espacio, const char *usuario, const char *contrasena, char **retorna_direccion_espacio_negocio, int *retornar_nivel)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
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
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // Validar que el archivo de permisos exista antes de intentar leerlo.
    if (!existe_archivo(ruta_archivo))
    {
        // Retorno -1: archivo inexistente o inaccesible.
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // Variable de salida: cantidad de lineas encontradas en el archivo.
    int n_lineas = 0;
    // Cargar todas las lineas del archivo en memoria.
    char **lineas = leer_archivo(ruta_archivo, &n_lineas);
    if (!lineas)
    {
        // Retorno -1: fallo al leer archivo.
        RETORNAR_PROCESO_ESTANDAR(-1);
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
                imprimirMensaje_para_depurar("\n\n:%s", columnas[c]);
                // Suma una columna valida.
                n_columnas++;
            }
        }

        imprimirMensaje_para_depurar("\n\n%s:%s\n%s:%s\n%s:%s\n", columnas[0], id_de_espacio, columnas[1], usuario, columnas[2], contrasena);

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
    RETORNAR_PROCESO_ESTANDAR(tiene_permiso);
}

/*
 * Uso: Verifica permiso del negocio sin retornar directorio; se usa cuando ya se tiene la ruta del archivo y solo se necesita validar las credenciales.
 * Entrada ejemplo: checar_permiso_negocios(2, "espacios\\negocio\\archivo_usuarios.txt", "0", "administrador_negocio", "54321", &nivel)
 */
int checar_permiso_negocios(int nivel_minimo, const char *ruta_archivo, const char *id_de_espacio, const char *usuario, const char *contrasena, int *retornar_nivel)
{
    if (retornar_nivel) // solo escribe si el puntero es valido
    {
        *retornar_nivel = -1; // valor por defecto: sin permiso; se sobreescribe si se encuentra el usuario
    }

    imprimirMensaje_para_depurar("\n\n%s\n%s\n%s\n%s\n%d", ruta_archivo, id_de_espacio, usuario, contrasena, nivel_minimo); // traza de los parametros recibidos para depuracion

    if (!ruta_archivo || !id_de_espacio || !usuario || !contrasena) // valida que ningun parametro obligatorio sea nulo
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // error: parametro faltante
    }

    if (!existe_archivo(ruta_archivo)) // verifica que el archivo de usuarios del negocio exista antes de intentar abrirlo
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // error: archivo inexistente o inaccesible
    }

    int n_lineas = 0;
    char **lineas = leer_archivo(ruta_archivo, &n_lineas); // carga todas las filas del archivo en memoria; ejemplo archivo: "ID|Usuario|Contraseña|Directorio|Nivel"
    if (!lineas)                                           // si fallo la lectura no hay nada que procesar
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // error: fallo al leer el archivo
    }

    int tiene_permiso = 1;                       // valor por defecto: sin permiso (1=denegado, 0=permitido)
    const char *sep = GG_caracter_separacion[0]; // separador de columnas del archivo; normalmente '|'

    for (int i = 1; i < n_lineas; i++) // inicia en 1 para saltar la cabecera (fila 0 con nombres de columnas)
    {
        if (!lineas[i]) // linea nula: la ignora y sigue
        {
            continue;
        }

        char **columnas = NULL;
        split(lineas[i], sep, &columnas); // divide la fila en columnas por el separador; ejemplo: "0|administrador_negocio|54321||2" → ["0","administrador_negocio","54321","","2"]

        int n_columnas = 0;
        if (columnas)
        {
            for (int c = 0; columnas[c] != NULL; c++) // cuenta las columnas disponibles en esta fila
            {
                imprimirMensaje_para_depurar("\n\n:%s", columnas[c]); // muestra cada columna para depuracion
                n_columnas++;
            }
        }

        imprimirMensaje_para_depurar("\n\n%s:%s\n%s:%s\n%s:%s\n", columnas[0], id_de_espacio, columnas[1], usuario, columnas[2], contrasena); // compara los valores del archivo con los recibidos

        // el archivo de negocio tiene estructura: ID|Usuario|Contraseña|Directorio|Nivel
        // columna 0 = id del usuario, columna 1 = nombre de usuario, columna 2 = contraseña, columna 4 = nivel
        if (n_columnas >= 5 && strcmp(columnas[0], id_de_espacio) == 0 && // columna 0 debe coincidir con el id_usuario_negocio; ejemplo: "0"
            strcmp(columnas[1], usuario) == 0 &&                          // columna 1 debe coincidir con el nombre de usuario; ejemplo: "administrador_negocio"
            strcmp(columnas[2], contrasena) == 0)                         // columna 2 debe coincidir con la contraseña; ejemplo: "54321"
        {
            int nivel_usuario = atoi(columnas[4]); // convierte el nivel de texto a entero; ejemplo: "2" → 2
            if (retornar_nivel)
            {
                *retornar_nivel = nivel_usuario; // devuelve el nivel leido al caller
            }
            // columna 3 (directorio) se ignora: no se retorna porque el caller ya tiene la ruta
            tiene_permiso = (nivel_usuario <= nivel_minimo) ? 0 : 1; // 0=permitido si su nivel es <= nivel_minimo; 1=denegado si es mayor
            free_split(columnas);                                    // libera antes de salir del ciclo
            break;                                                   // usuario encontrado, no es necesario seguir buscando
        }

        free_split(columnas); // libera columnas si esta fila no coincidio
    }

    free_lineas(lineas, n_lineas);            // libera todas las filas leidas del archivo
    RETORNAR_PROCESO_ESTANDAR(tiene_permiso); // 0=tiene permiso, 1=no tiene, -1=error
}
