/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - stdlib.h: Memoria dinamica, conversiones y utilidades generales
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - sys/stat.h: Informacion y operaciones de sistema de archivos
 * - direct.h: Funciones de directorios en Windows
 * - xc.h: Cabecera del compilador para microcontroladores PIC
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h: Dependencia interna del proyecto
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#include <sys/stat.h>

#elif defined(__linux__)
#include <sys/stat.h>

#elif defined(__XC)
#define _XTAL_FREQ 4000000
#include <xc.h>
/* PIC16F: Sin sistema de archivos. Las funciones son stubs. */

#else
#include <sys/stat.h>
#endif

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

/*
 * Uso: Ejecuta ruta_es_absoluta de forma segura.
 * Entrada ejemplo: ruta_es_absoluta(ruta)
 */
static int ruta_es_absoluta(const char *ruta) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (!ruta || !ruta[0])            // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

#ifdef _WIN32
    if ((ruta[0] && ruta[1] == ':') ||          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        (ruta[0] == '\\' && ruta[1] == '\\') || // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
        (ruta[0] == '/'))                       // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
    {
        RETORNAR_PROCESO_ESTANDAR(1);           // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1
    }
#else
    if (ruta[0] == '/')               // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1
    }
#endif

    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
}

/*
 * Uso: Ejecuta buscar_ultimo_separador de forma segura.
 * Entrada ejemplo: buscar_ultimo_separador(ruta)
 */
static char *buscar_ultimo_separador(char *ruta) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char *sep_linux = strrchr(ruta, '/');    // busca la última aparición del carácter indicado dentro de la cadena actual // ejemplo: último separador de carpeta
    char *sep_windows = strrchr(ruta, '\\'); // busca la última aparición del carácter indicado dentro de la cadena actual // ejemplo: último separador de carpeta

    if (!sep_linux)         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return sep_windows; // retorna el valor calculado en esta ruta de ejecución // ejemplo: sep_windows
    }
    if (!sep_windows)       // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return sep_linux;   // retorna el valor calculado en esta ruta de ejecución // ejemplo: sep_linux
    }

    return (sep_linux > sep_windows) ? sep_linux : sep_windows; // retorna el valor calculado en esta ruta de ejecución // ejemplo: (sep_linux > sep_windows) ? sep_linux : sep_windows
}

/* =======================
FUNCIONES BASE
======================== */

/*
 * Uso: Ejecuta crearDirectorio de forma segura.
 * Entrada ejemplo: crearDirectorio(ruta)
 */
int crearDirectorio(const char *ruta) // crea el directorio requerido antes de trabajar con archivos dentro de él // ejemplo: carpeta padre
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    char *ruta_trabajo = NULL; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

    if (!ruta) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        imprimirMensaje_para_depurar("[crearDirectorio] ruta es NULL\n"); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
        RETORNAR_PROCESO_ESTANDAR(-1);                                    // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    imprimirMensaje_para_depurar("[crearDirectorio] ruta: %s\n", ruta); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada

    int es_absoluta = ruta_es_absoluta(ruta);                                           // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    imprimirMensaje_para_depurar("[crearDirectorio] ruta absoluta: %d\n", es_absoluta); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada

    if (es_absoluta) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        ruta_trabajo = (char *)malloc(strlen(ruta) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!ruta_trabajo)                               // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            imprimirMensaje_para_depurar("[crearDirectorio] malloc fallo para ruta_trabajo completa\n"); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
            RETORNAR_PROCESO_ESTANDAR(-1);                                                               // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
        }
        strcpy(ruta_trabajo, ruta); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
    }
    else // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
    {
        ruta_trabajo = (char *)malloc(strlen(ruta) + 3); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!ruta_trabajo)                               // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            imprimirMensaje_para_depurar("[crearDirectorio] malloc fallo para ruta_trabajo local\n"); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
            RETORNAR_PROCESO_ESTANDAR(-1);                                                            // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
        }
#ifdef _WIN32
        strcpy(ruta_trabajo, ".\\"); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
#else
        strcpy(ruta_trabajo, "./"); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
#endif
        strcat(ruta_trabajo, ruta); // concatena texto al final de la cadena actual para construir la ruta o fila // ejemplo: anexar nombre de archivo
    }

    imprimirMensaje_para_depurar("[crearDirectorio] ruta_trabajo: %s\n", ruta_trabajo); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada

    int estado_creacion = -1; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

#ifdef _WIN32
    const char separador = '\\'; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
#else
    const char separador = '/'; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
#endif

    char separador_txt[2] = {separador, '\0'}; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    size_t len_ruta = strlen(ruta_trabajo);    // obtiene la longitud de la cadena usada en este cálculo // ejemplo: 15 caracteres

    char *ruta_normalizada = (char *)malloc(len_ruta + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!ruta_normalizada)                                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        imprimirMensaje_para_depurar("[crearDirectorio] malloc fallo para ruta_normalizada\n"); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
        free(ruta_trabajo);                                                                     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        RETORNAR_PROCESO_ESTANDAR(-1);                                                          // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    for (size_t i = 0; i < len_ruta; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char c = ruta_trabajo[i];            // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        if (c == '/' || c == '\\')           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            ruta_normalizada[i] = separador; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        }
        else                                 // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
        {
            ruta_normalizada[i] = c;         // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        }
    }
    ruta_normalizada[len_ruta] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

    char **partes = NULL;                                           // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n_partes = split(ruta_normalizada, separador_txt, &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
    if (n_partes < 0 || !partes)                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(ruta_normalizada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        free(ruta_trabajo);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    int indice_ultimo = -1;            // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    for (int i = 0; i < n_partes; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (partes[i] && partes[i][0] != '\0') // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            indice_ultimo = i;                 // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
        }
    }

    if (indice_ultimo < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        free(ruta_normalizada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        free(ruta_trabajo);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    char *acumulada = NULL; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int inicio = 0;         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

#ifdef _WIN32
    if (partes[0] && strlen(partes[0]) == 2 && partes[0][1] == ':') // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (concatenar_formato_separado_por_variable(&acumulada, NULL, "%s%s", partes[0], separador_txt) < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free(ruta_normalizada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            free(ruta_trabajo);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
        }
        inicio = 1; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
    }
#else
    if (ruta_normalizada[0] == separador) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (concatenar_formato_separado_por_variable(&acumulada, NULL, "%s", separador_txt) < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free(ruta_normalizada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            free(ruta_trabajo);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
        }
    }
#endif

    estado_creacion = 1;                    // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
    for (int i = inicio; i < n_partes; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (!partes[i] || partes[i][0] == '\0') // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (acumulada && acumulada[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            const char *fin = acumulada; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
            while (*fin != '\0')         // itera mientras la condición siga siendo verdadera // ejemplo: puntero != NULL
            {
                fin++;                   // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
            }

            if (*(fin - 1) != separador) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                if (concatenar_formato_separado_por_variable(&acumulada, NULL, "%s", separador_txt) < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    free(acumulada);               // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                    free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
                    free(ruta_normalizada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                    free(ruta_trabajo);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                    RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
                }
            }
        }

        if (concatenar_formato_separado_por_variable(&acumulada, NULL, "%s", partes[i]) < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(acumulada);               // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free(ruta_normalizada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            free(ruta_trabajo);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
        }

        errno = 0;            // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
        int resultado_mkdir = // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
#ifdef _WIN32
            mkdir(acumulada); // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
#else
            mkdir(acumulada, 0777); // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
#endif

        if (i == indice_ultimo) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            if (resultado_mkdir == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                estado_creacion = 0;  // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
            }
            else if (errno == EEXIST) // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
            {
                estado_creacion = 1;  // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
            }
            else                      // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
            {
                free(acumulada);               // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
                free(ruta_normalizada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                free(ruta_trabajo);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
            }
        }
        else if (resultado_mkdir != 0 && errno != EEXIST) // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
        {
            free(acumulada);               // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free(ruta_normalizada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            free(ruta_trabajo);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
            RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
        }
    }

    free(acumulada);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    free_split(partes);     // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    free(ruta_normalizada); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    if (estado_creacion == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        imprimirMensaje_para_depurar("[crearDirectorio] creado: %s\n", ruta_trabajo); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
        free(ruta_trabajo);                                                           // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        RETORNAR_PROCESO_ESTANDAR(0);                                                 // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }
    else if (estado_creacion == 1) // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
    {
        imprimirMensaje_para_depurar("[crearDirectorio] ya existe, se omite: %s\n", ruta_trabajo); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
        free(ruta_trabajo);                                                                        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        RETORNAR_PROCESO_ESTANDAR(1);                                                              // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1
    }
    else // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
    {
        imprimirMensaje_para_depurar("[crearDirectorio] error al crear: %s\n", ruta_trabajo); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
        free(ruta_trabajo);                                                                   // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        RETORNAR_PROCESO_ESTANDAR(-1);                                                        // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

#elif defined(__XC)
    (void)ruta;                    // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
#endif
}

/*
 * Uso: Ejecuta crearArchivo de forma segura.
 * Entrada ejemplo: crearArchivo(ruta, cabecera)
 */
int crearArchivo(const char *ruta, const char *cabecera) // crea el archivo si todavía no existe usando la cabecera indicada // ejemplo: metadata inicial
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    imprimirMensaje_para_depurar("%s\n", ruta); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
#if defined(_WIN32) || defined(__linux__)
    if (!ruta) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        imprimirMensaje_para_depurar("[crearArchivo] ruta es NULL\n"); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
        RETORNAR_PROCESO_ESTANDAR(-1);                                 // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    char *ruta_trabajo = NULL;                // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int es_absoluta = ruta_es_absoluta(ruta); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

    if (es_absoluta) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        ruta_trabajo = (char *)malloc(strlen(ruta) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!ruta_trabajo)                               // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            imprimirMensaje_para_depurar("[crearArchivo] malloc fallo para ruta_trabajo completa\n"); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
            RETORNAR_PROCESO_ESTANDAR(-1);                                                            // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
        }
        strcpy(ruta_trabajo, ruta); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
    }
    else // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
    {
        ruta_trabajo = (char *)malloc(strlen(ruta) + 3); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!ruta_trabajo)                               // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            imprimirMensaje_para_depurar("[crearArchivo] malloc fallo para ruta_trabajo local\n"); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
            RETORNAR_PROCESO_ESTANDAR(-1);                                                         // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
        }
#ifdef _WIN32
        strcpy(ruta_trabajo, ".\\"); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
#else
        strcpy(ruta_trabajo, "./"); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
#endif
        strcat(ruta_trabajo, ruta); // concatena texto al final de la cadena actual para construir la ruta o fila // ejemplo: anexar nombre de archivo
    }

    imprimirMensaje_para_depurar("[crearArchivo] ruta original: %s\n", ruta);        // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
    imprimirMensaje_para_depurar("[crearArchivo] ruta_trabajo: %s\n", ruta_trabajo); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada

    int estado_directorio = 0; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

    /* Crear el directorio padre si la ruta contiene un separador */
    char *dir_padre = (char *)malloc(strlen(ruta_trabajo) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (dir_padre)                                              // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        strcpy(dir_padre, ruta_trabajo);                // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
        char *sep = buscar_ultimo_separador(dir_padre); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        if (sep)                                        // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            *sep = '\0';                                                                              // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
            imprimirMensaje_para_depurar("[crearArchivo] creando directorio padre: %s\n", dir_padre); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada

            estado_directorio = crearDirectorio(dir_padre); // crea el directorio requerido antes de trabajar con archivos dentro de él // ejemplo: carpeta padre
            if (estado_directorio == -1)                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                imprimirMensaje_para_depurar("[crearArchivo] error al crear directorio padre: %s\n", dir_padre); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
                free(dir_padre);                                                                                 // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                free(ruta_trabajo);                                                                              // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                RETORNAR_PROCESO_ESTANDAR(-2);                                                                   // retorna el valor calculado en esta ruta de ejecución // ejemplo: -2
            }
        }
        free(dir_padre); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    }

    /* Verificar si el archivo ya existe */
    FILE *f = fopen(ruta_trabajo, "r"); // abre el archivo indicado en el modo solicitado para trabajar con su contenido // ejemplo: modo lectura
    if (f)                              // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        imprimirMensaje_para_depurar("[crearArchivo] el archivo ya existe: %s\n", ruta_trabajo); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
        fclose(f);                                                                               // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura
        free(ruta_trabajo);                                                                      // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        RETORNAR_PROCESO_ESTANDAR(1);                                                            // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1
    }

    /* Crear el archivo */
    f = fopen(ruta_trabajo, "w"); // abre el archivo indicado en el modo solicitado para trabajar con su contenido // ejemplo: modo lectura
    if (f)                        // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (cabecera)                                                                      // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            fprintf(f, "%s\n", cabecera);                                                  // escribe texto formateado dentro del archivo abierto actualmente // ejemplo: una fila con salto de línea
        }
        fclose(f);                                                                         // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura
        imprimirMensaje_para_depurar("[crearArchivo] archivo creado: %s\n", ruta_trabajo); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
    }
    else // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
    {
        imprimirMensaje_para_depurar("[crearArchivo] error al crear archivo: %s\n", ruta_trabajo); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
        free(ruta_trabajo);                                                                        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        RETORNAR_PROCESO_ESTANDAR(-1);                                                             // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    free(ruta_trabajo); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    if (estado_directorio == 1)       // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(2); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 2
    }

    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)cabecera;               // marca el parámetro como no usado en esta rama de compilación // ejemplo: cabecera
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
#endif
}

/*
 * Uso: Ejecuta leer_archivo de forma segura.
 * Entrada ejemplo: leer_archivo(ruta, n_lineas_out)
 */
char **leer_archivo(const char *ruta, int *n_lineas_out) // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    imprimirMensaje_para_depurar("\n\nruta: %s", ruta); // envía un mensaje de depuración para seguir el flujo de ejecución // ejemplo: ruta creada
#if defined(_WIN32) || defined(__linux__)               // Solo compila este código en Windows o Linux

    if (n_lineas_out == NULL) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return NULL;          // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL
    }

    FILE *f = fopen(ruta, "r"); // abre el archivo indicado en el modo solicitado para trabajar con su contenido // ejemplo: modo lectura
    if (!f)                     // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        *n_lineas_out = 0; // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
        return NULL;       // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL
    }

    char **lineas = NULL; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n = 0;            // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int capacidad = 10;   // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

    lineas = (char **)malloc(capacidad * sizeof(char *)); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!lineas)                                          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        fclose(f);         // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura
        *n_lineas_out = 0; // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
        return NULL;       // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL
    }

    // lectura dinamica: cada linea crece con realloc segun lo que llegue, sin limite fijo
    int c;                     // caracter leido uno a uno del archivo
    char *linea_actual = NULL; // acumula los caracteres de la linea en curso
    int longitud_linea = 0;    // cantidad de caracteres acumulados en la linea actual
    int capacidad_linea = 0;   // capacidad reservada para linea_actual

    while ((c = fgetc(f)) != EOF) // lee caracter por caracter hasta el fin del archivo
    {
        if (c == '\r') // ignora el retorno de carro de Windows (\r\n)
        {
            continue;
        }

        if (c == '\n' || c == EOF) // fin de linea: guarda lo acumulado
        {
            // asegura espacio para el terminador nulo
            char *temp_linea = (char *)realloc(linea_actual, longitud_linea + 1);
            if (!temp_linea)
            {
                free(linea_actual);
                free_lineas(lineas, n);
                fclose(f);
                *n_lineas_out = 0;
                return NULL;
            }
            linea_actual = temp_linea;
            linea_actual[longitud_linea] = '\0'; // termina el string

            // agranda el arreglo de punteros si es necesario
            if (n >= capacidad)
            {
                capacidad *= 2;
                char **temp_arr = (char **)realloc(lineas, capacidad * sizeof(char *));
                if (!temp_arr)
                {
                    free(linea_actual);
                    free_lineas(lineas, n);
                    fclose(f);
                    *n_lineas_out = 0;
                    return NULL;
                }
                lineas = temp_arr;
            }

            lineas[n] = linea_actual; // guarda la linea terminada en el arreglo
            imprimirMensaje_para_depurar("\n%s", lineas[n]);
            n++;

            linea_actual = NULL; // reinicia para la siguiente linea
            longitud_linea = 0;
            capacidad_linea = 0;
        }
        else // caracter normal: agregar a la linea en curso
        {
            if (longitud_linea >= capacidad_linea) // necesita mas espacio
            {
                int nueva_cap = (capacidad_linea == 0) ? 64 : capacidad_linea * 2;
                char *temp_linea = (char *)realloc(linea_actual, nueva_cap);
                if (!temp_linea)
                {
                    free(linea_actual);
                    free_lineas(lineas, n);
                    fclose(f);
                    *n_lineas_out = 0;
                    return NULL;
                }
                linea_actual = temp_linea;
                capacidad_linea = nueva_cap;
            }
            linea_actual[longitud_linea++] = (char)c; // agrega el caracter a la linea
        }
    }

    // si el archivo no termina con '\n', guardar el ultimo fragmento pendiente
    if (linea_actual && longitud_linea > 0)
    {
        char *temp_linea = (char *)realloc(linea_actual, longitud_linea + 1);
        if (!temp_linea)
        {
            free(linea_actual);
            free_lineas(lineas, n);
            fclose(f);
            *n_lineas_out = 0;
            return NULL;
        }
        linea_actual = temp_linea;
        linea_actual[longitud_linea] = '\0';

        if (n >= capacidad)
        {
            capacidad *= 2;
            char **temp_arr = (char **)realloc(lineas, capacidad * sizeof(char *));
            if (!temp_arr)
            {
                free(linea_actual);
                free_lineas(lineas, n);
                fclose(f);
                *n_lineas_out = 0;
                return NULL;
            }
            lineas = temp_arr;
        }

        lineas[n] = linea_actual;
        imprimirMensaje_para_depurar("\n%s", lineas[n]);
        n++;
    }
    else
    {
        free(linea_actual); // linea vacia al final, solo liberar
    }

    fclose(f);         // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura
    *n_lineas_out = n; // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
    return lineas;     // retorna el valor calculado en esta ruta de ejecución // ejemplo: lineas

#elif defined(__XC) // Caso especial (por ejemplo, compilador embebido XC)

    (void)ruta;         // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)n_lineas_out; // marca el parámetro como no usado en esta rama de compilación // ejemplo: n_lineas_out
    return NULL;        // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL

#endif
}

/*
 * Uso: Ejecuta guardar_archivo de forma segura.
 * Entrada ejemplo: guardar_archivo(ruta, lineas, n_lineas)
 */
void guardar_archivo(const char *ruta, char **lineas, int n_lineas) // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "w"); // abre el archivo indicado en el modo solicitado para trabajar con su contenido // ejemplo: modo lectura
    if (!f)                     // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < n_lineas; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        fprintf(f, "%s\n", lineas[i]); // escribe texto formateado dentro del archivo abierto actualmente // ejemplo: una fila con salto de línea
    }

    fclose(f); // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura

#elif defined(__XC)
    (void)ruta;     // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)lineas;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: lineas
    (void)n_lineas; // marca el parámetro como no usado en esta rama de compilación // ejemplo: n_lineas

#endif
}

/*
 * Uso: Ejecuta free_lineas de forma segura.
 * Entrada ejemplo: free_lineas(lineas, n_lineas)
 */
void free_lineas(char **lineas, int n_lineas) // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    if (lineas == NULL) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;         // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < n_lineas; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (lineas[i])       // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
    }
    free(lineas); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

#elif defined(__XC)
    (void)lineas;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: lineas
    (void)n_lineas; // marca el parámetro como no usado en esta rama de compilación // ejemplo: n_lineas

#endif
}

/*
 * Uso: Ejecuta agregar_fila de forma segura.
 * Entrada ejemplo: agregar_fila(ruta, fila)
 */
void agregar_fila(const char *ruta, const char *fila) // agrega una nueva fila al final del archivo de destino // ejemplo: nuevo producto
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "a"); // abre el archivo indicado en el modo solicitado para trabajar con su contenido // ejemplo: modo lectura
    if (f)                      // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        fprintf(f, "%s\n", fila); // escribe texto formateado dentro del archivo abierto actualmente // ejemplo: una fila con salto de línea
        fclose(f);                // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura
    }

#elif defined(__XC)
    (void)ruta; // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)fila; // marca el parámetro como no usado en esta rama de compilación // ejemplo: fila

#endif
}

/*
 * Uso: Ejecuta existe_archivo de forma segura.
 * Entrada ejemplo: existe_archivo(ruta)
 */
int existe_archivo(const char *ruta) // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "r"); // abre el archivo indicado en el modo solicitado para trabajar con su contenido // ejemplo: modo lectura
    if (f)                      // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        fclose(f);                    // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura
        RETORNAR_PROCESO_ESTANDAR(1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1
    }
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/* =======================
OPERACIONES DE CELDAS Y FILAS
======================== */

/*
 * Uso: Ejecuta seleccionar_fila_por_celda de forma segura.
 * Entrada ejemplo: seleccionar_fila_por_celda(ruta, col_buscar, valor_buscar, salida_out)
 */
int seleccionar_fila_por_celda(const char *ruta, int col_buscar, // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                               const char *valor_buscar,         // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                               char ***salida_out)               // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    if (salida_out == NULL)           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    int n_total = 0;// declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &n_total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        *salida_out = NULL;           // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    char **resultado = NULL;                                 // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int encontrados = 0;                                     // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int capacidad = 10;                                      // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    resultado = (char **)malloc(capacidad * sizeof(char *)); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!resultado)                                          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, n_total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        *salida_out = NULL;           // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    for (int i = 0; i < n_total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n < 0)                                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (col_buscar < n && strcmp(partes[col_buscar], valor_buscar) == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            if (encontrados >= capacidad) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                capacidad *= 2;                                                        // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
                char **temp = (char **)realloc(resultado, capacidad * sizeof(char *)); // redimensiona memoria dinámica para ampliar o ajustar la capacidad actual // ejemplo: duplicar el arreglo de punteros
                if (!temp)                                                             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    free_split(partes);                  // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
                    free_lineas(resultado, encontrados); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                    free_lineas(lineas, n_total);        // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                    *salida_out = NULL;                  // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
                    RETORNAR_PROCESO_ESTANDAR(0);        // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
                }
                resultado = temp; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
            }

            resultado[encontrados] = (char *)malloc(strlen(lineas[i]) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
            if (!resultado[encontrados])                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free_split(partes);                  // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
                free_lineas(resultado, encontrados); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                free_lineas(lineas, n_total);        // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                *salida_out = NULL;                  // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
                RETORNAR_PROCESO_ESTANDAR(0);        // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
            }
            strcpy(resultado[encontrados], lineas[i]); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
            encontrados++;                             // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
        }

        free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    free_lineas(lineas, n_total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    *salida_out = resultado;                // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
    RETORNAR_PROCESO_ESTANDAR(encontrados); // retorna el valor calculado en esta ruta de ejecución // ejemplo: encontrados

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)col_buscar;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_buscar
    (void)valor_buscar;           // marca el parámetro como no usado en esta rama de compilación // ejemplo: valor_buscar
    (void)salida_out;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: salida_out
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/*
 * Uso: Ejecuta eliminar_fila_por_celda de forma segura.
 * Entrada ejemplo: eliminar_fila_por_celda(ruta, col_buscar, valor_buscar)
 */
void eliminar_fila_por_celda(const char *ruta, int col_buscar, // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                             const char *valor_buscar)         // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    char **resultado = NULL;                                 // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n_resultado = 0;                                     // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int capacidad = 10;                                      // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    resultado = (char **)malloc(capacidad * sizeof(char *)); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!resultado)                                          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE

        int eliminar = 0;                                                             // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        if (n > 0 && col_buscar < n && strcmp(partes[col_buscar], valor_buscar) == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            eliminar = 1;                                                             // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
        }

        if (n > 0)              // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }

        if (!eliminar) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            if (n_resultado >= capacidad) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                capacidad *= 2;                                                        // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
                char **temp = (char **)realloc(resultado, capacidad * sizeof(char *)); // redimensiona memoria dinámica para ampliar o ajustar la capacidad actual // ejemplo: duplicar el arreglo de punteros
                if (!temp)                                                             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    free_lineas(resultado, n_resultado); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                    free_lineas(lineas, total);          // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                    return;                              // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
                }
                resultado = temp; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
            }

            resultado[n_resultado] = (char *)malloc(strlen(lineas[i]) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
            if (!resultado[n_resultado])                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free_lineas(resultado, n_resultado); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                free_lineas(lineas, total);          // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                return;                              // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
            }
            strcpy(resultado[n_resultado], lineas[i]); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
            n_resultado++;                             // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
        }
    }

    free_lineas(lineas, total);                    // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    guardar_archivo(ruta, resultado, n_resultado); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(resultado, n_resultado);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;         // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)col_buscar;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_buscar
    (void)valor_buscar; // marca el parámetro como no usado en esta rama de compilación // ejemplo: valor_buscar

#endif
}

/*
 * Uso: Ejecuta editar_celda_por_celda de forma segura.
 * Entrada ejemplo: editar_celda_por_celda(ruta, col_buscar, valor_buscar, col_editar, nuevo_valor)
 */
void editar_celda_por_celda(const char *ruta, int col_buscar,        // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                            const char *valor_buscar,                // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                            int col_editar, const char *nuevo_valor) // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (col_buscar >= n || strcmp(partes[col_buscar], valor_buscar) != 0 || col_editar >= n) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        /* Reconstruir la fila */
        char *nueva_linea = malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!nueva_linea)                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);         // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
        }
        nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

        for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
            }

            const char *celda = (j == col_editar) ? nuevo_valor : partes[j]; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);     // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }

        if (lineas[i])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        lineas[i] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        free_split(partes);      // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;         // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)col_buscar;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_buscar
    (void)valor_buscar; // marca el parámetro como no usado en esta rama de compilación // ejemplo: valor_buscar
    (void)col_editar;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_editar
    (void)nuevo_valor;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: nuevo_valor

#endif
}

/*
 * Uso: Ejecuta editar_celda de forma segura.
 * Entrada ejemplo: editar_celda(ruta, colBuscar, valorBuscar, colEditar, nuevoValor)
 */
void editar_celda(const char *ruta, int colBuscar, const char *valorBuscar, // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                  int colEditar, const char *nuevoValor)                    // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    editar_celda_por_celda(ruta, colBuscar, valorBuscar, colEditar, nuevoValor); // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
}

/*
 * Uso: Ejecuta eliminar_fila de forma segura.
 * Entrada ejemplo: eliminar_fila(ruta, filaEliminar)
 */
void eliminar_fila(const char *ruta, int filaEliminar) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    char **resultado = NULL;                                 // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n_resultado = 0;                                     // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int capacidad = 10;                                      // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    resultado = (char **)malloc(capacidad * sizeof(char *)); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!resultado)                                          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (i == filaEliminar) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;          // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (n_resultado >= capacidad) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            capacidad *= 2;                                                        // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
            char **temp = (char **)realloc(resultado, capacidad * sizeof(char *)); // redimensiona memoria dinámica para ampliar o ajustar la capacidad actual // ejemplo: duplicar el arreglo de punteros
            if (!temp)                                                             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free_lineas(resultado, n_resultado); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                free_lineas(lineas, total);          // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                return;                              // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
            }
            resultado = temp; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
        }

        resultado[n_resultado] = (char *)malloc(strlen(lineas[i]) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!resultado[n_resultado])                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_lineas(resultado, n_resultado); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            free_lineas(lineas, total);          // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            return;                              // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
        }
        strcpy(resultado[n_resultado], lineas[i]); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
        n_resultado++;                             // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
    }

    free_lineas(lineas, total);                    // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    guardar_archivo(ruta, resultado, n_resultado); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(resultado, n_resultado);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;         // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)filaEliminar; // marca el parámetro como no usado en esta rama de compilación // ejemplo: filaEliminar

#endif
}

/*
 * Uso: Ejecuta editar_fila de forma segura.
 * Entrada ejemplo: editar_fila(ruta, fila, nueva)
 */
void editar_fila(const char *ruta, int fila, const char *nueva) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    if (fila >= 0 && fila < total) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(lineas[fila]);                               // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        lineas[fila] = (char *)malloc(strlen(nueva) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (lineas[fila])                                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            strcpy(lineas[fila], nueva);                  // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
        }
    }

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)fila;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: fila
    (void)nueva; // marca el parámetro como no usado en esta rama de compilación // ejemplo: nueva

#endif
}

/*
 * Uso: Ejecuta incrementar_celda de forma segura.
 * Entrada ejemplo: incrementar_celda(ruta, colBuscar, valorBuscar, colEditar, inc)
 */
void incrementar_celda(const char *ruta, int colBuscar, const char *valorBuscar, // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                       int colEditar, int inc)                                   // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (colBuscar >= n || strcmp(partes[colBuscar], valorBuscar) != 0 || colEditar >= n) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        double valor_actual = atof(partes[colEditar]);            // convierte el texto numérico a double para operar con él // ejemplo: 15.5
        char nuevo[64];                                           // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
        snprintf(nuevo, sizeof(nuevo), "%g", valor_actual + inc); // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt

        char *nueva_linea = malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!nueva_linea)                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);         // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
        }
        nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

        for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
            }
            const char *celda = (j == colEditar) ? nuevo : partes[j];                            // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);                         // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }

        if (lineas[i])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        lineas[i] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        free_split(partes);      // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)colBuscar;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: colBuscar
    (void)valorBuscar; // marca el parámetro como no usado en esta rama de compilación // ejemplo: valorBuscar
    (void)colEditar;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: colEditar
    (void)inc;         // marca el parámetro como no usado en esta rama de compilación // ejemplo: inc

#endif
}

/*
 * Uso: Ejecuta editar_columna_completa de forma segura.
 * Entrada ejemplo: editar_columna_completa(ruta, col, nuevo)
 */
void editar_columna_completa(const char *ruta, int col, const char *nuevo) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }
        if (col >= n)                                                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        char *nueva_linea = malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!nueva_linea)                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);         // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
        }
        nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

        for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
            }
            const char *celda = (j == col) ? nuevo : partes[j];                                  // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);                         // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }

        if (lineas[i])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        lineas[i] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        free_split(partes);      // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)col;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: col
    (void)nuevo; // marca el parámetro como no usado en esta rama de compilación // ejemplo: nuevo

#endif
}

/*
 * Uso: Ejecuta eliminar_columna de forma segura.
 * Entrada ejemplo: eliminar_columna(ruta, col)
 */
void eliminar_columna(const char *ruta, int col) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        char *nueva_linea = malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!nueva_linea)                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);         // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
        }
        nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

        int es_primero = 1;         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (j == col)                                                                        // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                continue;                                                                        // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
            }
            if (!es_primero)                                                                     // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
            }
            strncat(nueva_linea, partes[j], 8192 - strlen(nueva_linea) - 1);                     // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
            es_primero = 0;                                                                      // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
        }

        if (lineas[i])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        lineas[i] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        free_split(partes);      // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta; // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)col;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: col

#endif
}

/*
 * Uso: Ejecuta agregar_columna de forma segura.
 * Entrada ejemplo: agregar_columna(ruta, nombre)
 */
void agregar_columna(const char *ruta, const char *nombre) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        size_t largo = strlen(lineas[i]);// obtiene la longitud de la cadena usada en este cálculo // ejemplo: 15 caracteres
        const char *valor = (i == 0) ? nombre : "";         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        size_t len_sep = strlen(GG_caracter_separacion[0]); // obtiene la longitud de la cadena usada en este cálculo // ejemplo: 15 caracteres
        size_t len_val = strlen(valor);                     // obtiene la longitud de la cadena usada en este cálculo // ejemplo: 15 caracteres

        if (largo + len_sep + len_val < 8191) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            strncat(lineas[i], GG_caracter_separacion[0], 8191 - largo); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
            strncat(lineas[i], valor, 8191 - largo - len_sep);           // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }
    }

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)nombre; // marca el parámetro como no usado en esta rama de compilación // ejemplo: nombre

#endif
}

/* =======================
BÚSQUEDA Y FILTRADO
======================== */

/*
 * Uso: Ejecuta buscar_fila de forma segura.
 * Entrada ejemplo: buscar_fila(ruta, colBuscar, valorBuscar, salida_out)
 */
int buscar_fila(const char *ruta, int colBuscar, const char *valorBuscar, // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                char **salida_out)                                        // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(-1);          // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        int coincide = (colBuscar < n && strcmp(partes[colBuscar], valorBuscar) == 0); // compara dos cadenas para saber si representan el mismo valor // ejemplo: ID_TOT contra la cabecera leída
        free_split(partes);                                                            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales

        if (coincide) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            if (salida_out != NULL) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                *salida_out = (char *)malloc(strlen(lineas[i]) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
                if (*salida_out)                                     // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    strcpy(*salida_out, lineas[i]);                  // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
                }
            }
            free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            RETORNAR_PROCESO_ESTANDAR(i); // retorna el valor calculado en esta ruta de ejecución // ejemplo: i
        }
    }

    free_lineas(lineas, total);    // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1

#elif defined(__XC)
    (void)ruta;                    // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)colBuscar;               // marca el parámetro como no usado en esta rama de compilación // ejemplo: colBuscar
    (void)valorBuscar;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: valorBuscar
    (void)salida_out;              // marca el parámetro como no usado en esta rama de compilación // ejemplo: salida_out
    RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1

#endif
}

/*
 * Uso: Ejecuta agregar_sino_existe de forma segura.
 * Entrada ejemplo: agregar_sino_existe(ruta, colBuscar, valorBuscar, fila_nueva)
 */
int agregar_sino_existe(const char *ruta, int colBuscar, const char *valorBuscar, // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                        const char *fila_nueva)                                   // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int idx = buscar_fila(ruta, colBuscar, valorBuscar, NULL); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (idx >= 0)                                              // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0);                          // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    agregar_fila(ruta, fila_nueva); // agrega una nueva fila al final del archivo de destino // ejemplo: nuevo producto
    RETORNAR_PROCESO_ESTANDAR(1);   // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1

#elif defined(__XC)
    (void)ruta;                    // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)colBuscar;               // marca el parámetro como no usado en esta rama de compilación // ejemplo: colBuscar
    (void)valorBuscar;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: valorBuscar
    (void)fila_nueva;              // marca el parámetro como no usado en esta rama de compilación // ejemplo: fila_nueva
    RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1

#endif
}

/*
 * Uso: Ejecuta editar_celda_id_fila de forma segura.
 * Entrada ejemplo: editar_celda_id_fila(ruta, id_fila, col, nuevo_valor)
 */
int editar_celda_id_fila(const char *ruta, int id_fila, int col, // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                         const char *nuevo_valor)                // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0);           // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    if (id_fila < 0 || id_fila >= total) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    char **partes = NULL;                                               // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n = split(lineas[id_fila], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
    if (n <= 0 || col >= n)                                             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (n > 0)                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);       // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    char *nueva_linea = malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!nueva_linea)                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_split(partes);           // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }
    nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

    for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }
        const char *celda = (j == col) ? nuevo_valor : partes[j];                            // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);                         // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
    }

    if (lineas[id_fila])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(lineas[id_fila]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    }
    lineas[id_fila] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
    free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    RETORNAR_PROCESO_ESTANDAR(1);         // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id_fila;                // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_fila
    (void)col;                    // marca el parámetro como no usado en esta rama de compilación // ejemplo: col
    (void)nuevo_valor;            // marca el parámetro como no usado en esta rama de compilación // ejemplo: nuevo_valor
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/*
 * Uso: Ejecuta incrementar_celda_id_fila de forma segura.
 * Entrada ejemplo: incrementar_celda_id_fila(ruta, id_fila, col, incremento)
 */
int incrementar_celda_id_fila(const char *ruta, int id_fila, int col, // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                              double incremento)                      // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0);           // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    if (id_fila < 0 || id_fila >= total) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    char **partes = NULL;                                               // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n = split(lineas[id_fila], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
    if (n <= 0 || col >= n)                                             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (n > 0)                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);       // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    double valor_actual = atof(partes[col]);                         // convierte el texto numérico a double para operar con él // ejemplo: 15.5
    char nuevo[64];                                                  // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
    snprintf(nuevo, sizeof(nuevo), "%g", valor_actual + incremento); // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt

    char *nueva_linea = malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!nueva_linea)                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_split(partes);           // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }
    nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

    for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }
        const char *celda = (j == col) ? nuevo : partes[j];                                  // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);                         // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
    }

    if (lineas[id_fila])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(lineas[id_fila]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    }
    lineas[id_fila] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
    free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    RETORNAR_PROCESO_ESTANDAR(1);         // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id_fila;                // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_fila
    (void)col;                    // marca el parámetro como no usado en esta rama de compilación // ejemplo: col
    (void)incremento;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: incremento
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/*
 * Uso: Ejecuta borrar_celdas_excepto_primera de forma segura.
 * Entrada ejemplo: borrar_celdas_excepto_primera(ruta, colBuscar, valorBuscar)
 */
void borrar_celdas_excepto_primera(const char *ruta, int colBuscar, // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                                   const char *valorBuscar)         // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (colBuscar >= n || strcmp(partes[colBuscar], valorBuscar) != 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        char *nueva_linea = malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!nueva_linea)                 // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);         // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
        }
        nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

        strncat(nueva_linea, partes[0], 8191); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        for (int j = 1; j < n; j++)            // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }

        if (lineas[i])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        lineas[i] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        free_split(partes);      // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)colBuscar;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: colBuscar
    (void)valorBuscar; // marca el parámetro como no usado en esta rama de compilación // ejemplo: valorBuscar

#endif
}

/*
 * Uso: Ejecuta reescribir_archivo de forma segura.
 * Entrada ejemplo: reescribir_archivo(ruta, lineas, n_lineas)
 */
void reescribir_archivo(const char *ruta, char **lineas, int n_lineas) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    guardar_archivo(ruta, lineas, n_lineas); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla

#elif defined(__XC)
    (void)ruta;     // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)lineas;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: lineas
    (void)n_lineas; // marca el parámetro como no usado en esta rama de compilación // ejemplo: n_lineas

#endif
}

/*
 * Uso: Ejecuta generar_ruta_archivo de forma segura.
 * Entrada ejemplo: generar_ruta_archivo(ruta, id, cant_por_arch, salida, tam_salida)
 */
void generar_ruta_archivo(const char *ruta, long id, long cant_por_arch, // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt
                          char *salida, size_t tam_salida)               // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    if (salida == NULL || tam_salida == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                            // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    salida[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

    if (ruta != NULL && ruta[0] != '\0') // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        strncat(salida, ruta, tam_salida - strlen(salida) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        size_t largo = strlen(salida);                          // obtiene la longitud de la cadena usada en este cálculo // ejemplo: 15 caracteres
#ifdef _WIN32
        if (largo > 0 && salida[largo - 1] != '\\')        // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            strncat(salida, "\\", tam_salida - largo - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }
#else
        if (largo > 0 && salida[largo - 1] != '/')        // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            strncat(salida, "/", tam_salida - largo - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }
#endif
    }

    char id_str[32];                             // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
    snprintf(id_str, sizeof(id_str), "%ld", id); // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt
    size_t id_len = strlen(id_str);              // obtiene la longitud de la cadena usada en este cálculo // ejemplo: 15 caracteres

    char cant_str[32];                                          // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
    snprintf(cant_str, sizeof(cant_str), "%ld", cant_por_arch); // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt
    size_t n_ceros = strlen(cant_str) - 1;                      // obtiene la longitud de la cadena usada en este cálculo // ejemplo: 15 caracteres

    long potencia = cant_por_arch;       // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    for (size_t i = 2; i <= id_len; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char seg[32]; // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
#ifdef _WIN32
        snprintf(seg, sizeof(seg), "%ld\\", potencia); // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt
#else
        snprintf(seg, sizeof(seg), "%ld/", potencia); // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt
#endif
        strncat(salida, seg, tam_salida - strlen(salida) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        potencia *= cant_por_arch;                             // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
    }

    size_t prefijo_len = (id_len > n_ceros) ? (id_len - n_ceros) : 0; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char nom[64] = "";                                                // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    strncat(nom, id_str, prefijo_len);                                // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
    for (size_t i = 0; i < n_ceros; i++)                              // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        strncat(nom, "0", sizeof(nom) - strlen(nom) - 1);             // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
    }
    strncat(nom, ".txt", sizeof(nom) - strlen(nom) - 1);              // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor

    strncat(salida, nom, tam_salida - strlen(salida) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor

#elif defined(__XC)
    (void)ruta;          // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id;            // marca el parámetro como no usado en esta rama de compilación // ejemplo: id
    (void)cant_por_arch; // marca el parámetro como no usado en esta rama de compilación // ejemplo: cant_por_arch
    (void)salida;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: salida
    (void)tam_salida;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: tam_salida

#endif
}

/* =======================
HELPERS ESTATICOS PARA INFO_DIVIDIDA
======================== */

/* Lee ID_TOT y CANT_POR_ARCH del archivo metadata. Retorna 0 en exito, -1 en error. */
static int leer_config_metadata(const char *ruta_metadata, long *id_total_out, long *cant_por_arch_out) // lee los campos de configuracion del archivo metadata de info dividida
{
#if defined(_WIN32) || defined(__linux__)
    int n = 0;
    char **lineas = leer_archivo(ruta_metadata, &n);
    if (!lineas || n <= 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (lineas) { free_lineas(lineas, n); } // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        return -1;                              // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    long id_total = 0, cant = 100;
    for (int i = 0; i < n; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **p = NULL;
        int np = split(lineas[i], GG_caracter_separacion[0], &p); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (np >= 2 && p) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            if (strcmp(p[0], "ID_TOT") == 0)            { id_total = atol(p[1]); }
            else if (strcmp(p[0], "CANT_POR_ARCH") == 0) { long v = atol(p[1]); if (v > 0) { cant = v; } }
        }
        if (p) { free_split(p); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }
    free_lineas(lineas, n); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

    if (id_total_out)      { *id_total_out      = id_total; }
    if (cant_por_arch_out) { *cant_por_arch_out = cant;     }
    return 0;

#elif defined(__XC)
    (void)ruta_metadata;
    (void)id_total_out;
    (void)cant_por_arch_out;
    return -1;
#endif
}

/* Construye la ruta de la carpeta "_DAT" a partir de la ruta del metadata. El caller debe free(). */
static char *construir_carpeta_data(const char *ruta_metadata) // deriva la ruta de la carpeta de datos divididos a partir del archivo metadata
{
#if defined(_WIN32) || defined(__linux__)
    char *copia = NULL;
    if (concatenar_formato_separado_por_variable(&copia, NULL, "%s", ruta_metadata) < 0) { return NULL; } // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito

    char *sep   = buscar_ultimo_separador(copia); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char *punto = strrchr(copia, '.');             // busca la última aparición del carácter indicado dentro de la cadena actual // ejemplo: último separador de carpeta
    if (punto && (!sep || punto > sep)) { *punto = '\0'; } // elimina la extensión del archivo dejando solo la ruta base

    char *resultado = NULL;
    if (concatenar_formato_separado_por_variable(&resultado, NULL, "%s_DAT", copia) < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(copia); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        return NULL; // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL
    }
    free(copia); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    return resultado; // retorna el valor calculado en esta ruta de ejecución // ejemplo: resultado

#elif defined(__XC)
    (void)ruta_metadata;
    return NULL;
#endif
}

/* Calcula la posicion de una fila dentro de su archivo usando los primeros 1-2 digitos del ID. */
static long calcular_posicion_en_archivo(const char *id) // calcula el indice de fila dentro del archivo de datos a partir del ID
{
    if (!id || !id[0]) { return 0; }
    size_t len  = strlen(id);
    char   tmp[3];
    if (len >= 2) { tmp[0] = id[0]; tmp[1] = id[1]; tmp[2] = '\0'; }
    else          { tmp[0] = id[0]; tmp[1] = '\0'; }
    return atol(tmp);
}

/* Reconstruye una fila uniendo celdas[] con GG_caracter_separacion[0]. El caller debe free(). */
static char *reconstruir_fila(char **celdas, int nc) // une un arreglo de celdas usando el separador estandar del sistema
{
    char *nueva = NULL;
    for (int i = 0; i < nc; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (i > 0)
        {
            concatenar_formato_separado_por_variable(&nueva, NULL, "%s%s", GG_caracter_separacion[0], celdas[i] ? celdas[i] : ""); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        }
        else
        {
            concatenar_formato_separado_por_variable(&nueva, NULL, "%s", celdas[i] ? celdas[i] : ""); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        }
    }
    return nueva;
}

/* =======================
FUNCIONES ADICIONALES DEL C#
======================== */

/*
 * Uso: Ejecuta leer_info_dividida de forma segura.
 * Entrada ejemplo: leer_info_dividida(ruta)
 */
char *leer_info_dividida(const char *ruta) // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "r"); // abre el archivo indicado en el modo solicitado para trabajar con su contenido // ejemplo: modo lectura
    if (!f)                     // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return NULL;            // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL
    }

    fseek(f, 0, SEEK_END); // mueve el cursor del archivo a la posición necesaria para la operación siguiente // ejemplo: ir al final del archivo
    long tam = ftell(f);   // obtiene la posición actual del cursor para conocer el tamaño del archivo // ejemplo: 2048 bytes
    fseek(f, 0, SEEK_SET); // mueve el cursor del archivo a la posición necesaria para la operación siguiente // ejemplo: ir al final del archivo

    char *resultado = (char *)malloc(tam + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!resultado)                            // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        fclose(f);   // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura
        return NULL; // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL
    }

    size_t bytes_leidos = fread(resultado, 1, tam, f); // lee un bloque de bytes del archivo hacia memoria dinámica // ejemplo: contenido completo del archivo
    resultado[bytes_leidos] = '\0';                    // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
    fclose(f);                                         // cierra el archivo abierto para liberar el descriptor del sistema // ejemplo: termina la lectura

    return resultado; // retorna el valor calculado en esta ruta de ejecución // ejemplo: resultado

#elif defined(__XC)
    (void)ruta;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    return NULL; // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL

#endif
}

/*crear_archivo_info_dividida
 *
 * ------------------------------------------------------------
 * Crea (si no existe) el archivo metadata para info dividida.
 *
 * ENTRADA:
 * - direccion_archivos: ruta del metadata principal.
 *Ejemplo: "espacios\\mi_espacio.txt"
 * - nom_columnas_si_no_existe_archivo: encabezados de columnas.
 *Ejemplo: "ID|NOMBRE|PRECIO"
 *
 * ARCHIVO QUE CREA (si no existe):
 * - espacios\\mi_espacio.txt
 *
 * CONTENIDO INICIAL EJEMPLO:
 * tipo_info|info
 * ID_TOT|0
 * COLUMNAS|ID|NOMBRE|PRECIO
 * CANT_POR_ARCH|100
 *
 * RETORNO:
 * - 0: metadata creado
 * - 1 o 2: ya existia (segun crearArchivo/crearDirectorio)
 * - <0: error
 */
/*
 * Uso: Ejecuta crear_archivo_info_dividida de forma segura.
 * Entrada ejemplo: crear_archivo_info_dividida(direccion_archivos, nom_columnas_si_no_existe_archivo)
 */
static int crear_archivo_info_dividida(const char *direccion_archivos,                // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                                       const char *nom_columnas_si_no_existe_archivo) // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    if (!direccion_archivos || !direccion_archivos[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(-1);                 // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    if (!nom_columnas_si_no_existe_archivo)     // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        nom_columnas_si_no_existe_archivo = ""; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
    }

    char *cabecera_metadata = NULL;                                                                      // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (concatenar_formato_separado_por_variable(                                                        // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            &cabecera_metadata, NULL,                                                                    // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
            "tipo_info%sinfo\nID_TOT%s0\nCOLUMNAS%s%s\nCANT_POR_ARCH%s%s",                               // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
            GG_caracter_separacion[0], GG_caracter_separacion[0], GG_caracter_separacion[0],             // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
            nom_columnas_si_no_existe_archivo, GG_caracter_separacion[0], GG_cantidado_por_archivo) < 0) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1
    }

    int estado_creacion_metadata = crearArchivo(direccion_archivos, cabecera_metadata); // crea el archivo si todavía no existe usando la cabecera indicada // ejemplo: metadata inicial
    free(cabecera_metadata);                                                            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    RETORNAR_PROCESO_ESTANDAR(estado_creacion_metadata);                                // retorna el valor calculado en esta ruta de ejecución // ejemplo: estado_creacion_metadata

#elif defined(__XC)
    (void)direccion_archivos;                // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion_archivos
    (void)nom_columnas_si_no_existe_archivo; // marca el parámetro como no usado en esta rama de compilación // ejemplo: nom_columnas_si_no_existe_archivo
    RETORNAR_PROCESO_ESTANDAR(-1);           // retorna el valor calculado en esta ruta de ejecución // ejemplo: -1

#endif
}

/*
 * Uso: Agrega una nueva fila al almacenamiento dividido y actualiza ID_TOT en el metadata.
 * Parametros:
 *   direccion    - ruta del archivo metadata
 *   agregando    - fila a insertar (sin ID, campos separados con SEP[0]; puede ser NULL)
 *   nom_columnas - cabecera de columnas si se crea el archivo por primera vez (puede ser NULL)
 */
char *agregar_info_dividida(const char *direccion,    // ruta del archivo metadata
                            const char *agregando,    // fila a insertar (sin ID, separada con SEP[0])
                            const char *nom_columnas) // cabecera de columnas si se crea el archivo por primera vez
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

    if (!direccion || !direccion[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta;                                                                                                                // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    const char *nom_columnas_si_no_existe_archivo = nom_columnas ? nom_columnas : ""; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    const char *agregando_val                     = agregando    ? agregando    : ""; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    

    int estado_creacion_metadata = crear_archivo_info_dividida(direccion,                            // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
                                                               nom_columnas_si_no_existe_archivo); // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso

    if (estado_creacion_metadata < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror no pudo crear metadata", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta;                                                                                                                        // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    int n_lineas = 0;                                        // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(direccion, &n_lineas);      // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (!lineas || n_lineas <= 0)                            // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (lineas)                                                                                                                             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_lineas(lineas, n_lineas);                                                                                                      // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        }
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror no pudo leer metadata", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta;                                                                                                                       // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    long id_total = 0;                                                // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    long cantidad_filas_por_archivo = atol(GG_cantidado_por_archivo); // convierte el texto numérico a long para cálculos de identificadores o tamaños // ejemplo: 100
    char *columnas = NULL;                                            // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

    if (cantidad_filas_por_archivo <= 0)  // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        cantidad_filas_por_archivo = 100; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
    }

    for (int i = 0; i < n_lineas; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                                // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n_partes = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n_partes >= 2 && partes)                                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            if (strcmp(partes[0], "ID_TOT") == 0)        // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                id_total = atol(partes[1]);              // convierte el texto numérico a long para cálculos de identificadores o tamaños // ejemplo: 100
            }
            else if (strcmp(partes[0], "COLUMNAS") == 0) // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
            {
                char *tmp_col = (char *)malloc(strlen(partes[1]) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
                if (!tmp_col)                                          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    free_split(partes);                                                                                                          // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
                    free_lineas(lineas, n_lineas);                                                                                               // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                    concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                    return respuesta;                                                                                                            // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
                }
                strcpy(tmp_col, partes[1]); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
                if (columnas)               // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    free(columnas);         // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                }
                columnas = tmp_col;         // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
            }
            else if (strcmp(partes[0], "CANT_POR_ARCH") == 0) // ejecuta la rama alternativa cuando la condición previa no se cumplió // ejemplo: usar valor por defecto
            {
                long tmp = atol(partes[1]);           // convierte el texto numérico a long para cálculos de identificadores o tamaños // ejemplo: 100
                if (tmp > 0)                          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    cantidad_filas_por_archivo = tmp; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
                }
            }
        }

        if (partes)             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }
    }

    char *ruta_base_sin_ext = NULL;                                                                   // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (concatenar_formato_separado_por_variable(&ruta_base_sin_ext, NULL, "%s", direccion) < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (columnas)                                                                                                                // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(columnas);                                                                                                          // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        free_lineas(lineas, n_lineas);                                                                                               // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta;                                                                                                            // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    char *sep = buscar_ultimo_separador(ruta_base_sin_ext);// declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char *punto = strrchr(ruta_base_sin_ext, '.');          // busca la última aparición del carácter indicado dentro de la cadena actual // ejemplo: último separador de carpeta
    if (punto && (!sep || punto > sep))                     // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        *punto = '\0';                                      // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
    }

    char *carpeta_data = NULL;                                                                          // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (concatenar_formato_separado_por_variable(&carpeta_data, NULL, "%s_DAT", ruta_base_sin_ext) < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(ruta_base_sin_ext);                                                                                                     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        if (columnas)                                                                                                                // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(columnas);                                                                                                          // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        free_lineas(lineas, n_lineas);                                                                                               // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta;                                                                                                            // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }
    free(ruta_base_sin_ext); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    size_t tam_ruta_data = strlen(carpeta_data) + 128; // obtiene la longitud de la cadena usada en este cálculo // ejemplo: 15 caracteres
    char *ruta_data = (char *)malloc(tam_ruta_data);   // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!ruta_data)                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(carpeta_data);                                                                                                          // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        if (columnas)                                                                                                                // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(columnas);                                                                                                          // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        free_lineas(lineas, n_lineas);                                                                                               // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta;                                                                                                            // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    generar_ruta_archivo(carpeta_data, id_total, cantidad_filas_por_archivo, ruta_data, tam_ruta_data); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt
    free(carpeta_data);                                                                                 // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    char *cabecera_columnas = columnas                                                                                                                          // elige la fuente de columnas y reemplaza el separador para usarla como cabecera del archivo de datos
        ? ReemplazarCaracteres_de_texto_string(columnas, GG_caracter_separacion[1], GG_caracter_separacion[0])                                                  // reemplaza el separador interno por el separador estándar en las columnas del metadata
        : ReemplazarCaracteres_de_texto_string(nom_columnas_si_no_existe_archivo, GG_caracter_separacion[1], GG_caracter_separacion[0]);                        // mismo reemplazo sobre las columnas por defecto si no había metadata
    int estado_creacion_data = crearArchivo(ruta_data, cabecera_columnas);                                                                                      // crea el archivo si todavía no existe usando la cabecera indicada // ejemplo: metadata inicial
    free(cabecera_columnas);                                                                                                                                    // libera la cadena generada por el reemplazo de separadores
    if (estado_creacion_data < 0)                                                                                // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(ruta_data);                                                                                                                                 // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        if (columnas)                                                                                                                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(columnas);                                                                                                                              // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        free_lineas(lineas, n_lineas);                                                                                                                   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror no pudo crear archivo de datos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta;                                                                                                                                // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    char *fila_nueva = NULL;// declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (concatenar_formato_separado_por_variable(&fila_nueva, NULL, "%ld%s%s", // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                                                 id_total + 1,                 // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                                                 GG_caracter_separacion[0],    // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                                                 agregando_val) < 0)           // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
    {
        free(ruta_data);                                                                                                             // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        if (columnas)                                                                                                                // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(columnas);                                                                                                          // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        free_lineas(lineas, n_lineas);                                                                                               // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta;                                                                                                            // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    agregar_fila(ruta_data, fila_nueva);// agrega una nueva fila al final del archivo de destino // ejemplo: nuevo producto

    char nuevo_id_total[64];                                                    // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
    snprintf(nuevo_id_total, sizeof(nuevo_id_total), "%ld", id_total + 1);      // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt
    editar_celda_por_celda(direccion, 0, "ID_TOT", 1, nuevo_id_total); // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso

    concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s",                             // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                                             GG_caracter_para_confirmacion_o_error[0], fila_nueva); // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso

    free(fila_nueva);              // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    free(ruta_data);               // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    if (columnas)                  // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(columnas);            // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    }
    free_lineas(lineas, n_lineas); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    return respuesta;              // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)agregando;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: agregando
    (void)nom_columnas; // marca el parámetro como no usado en esta rama de compilación // ejemplo: nom_columnas
    return NULL; // retorna el valor calculado en esta ruta de ejecución // ejemplo: NULL

#endif
}

/*
 * Uso: Ejecuta incrementa_celda_solo_prog de forma segura.
 * Entrada ejemplo: incrementa_celda_solo_prog(ruta, id_principal, programa_id, col_editar, incremento)
 */
int incrementa_celda_solo_prog(const char *ruta, const char *id_principal,                 // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                               const char *programa_id, int col_editar, double incremento) // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0);           // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    int encontrados = 0; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        /* Verificación: col 0 == id_principal Y col 2 == programa_id */
        if (n > 0 && strcmp(partes[0], id_principal) != 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }
        if (n <= 2 || strcmp(partes[2], programa_id) != 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }
        if (col_editar >= n) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        double valor_actual = atof(partes[col_editar]);                  // convierte el texto numérico a double para operar con él // ejemplo: 15.5
        char nuevo[64];                                                  // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
        snprintf(nuevo, sizeof(nuevo), "%g", valor_actual + incremento); // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt

        char *nueva_linea = (char *)malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!nueva_linea)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);                     // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(lineas, total);             // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            RETORNAR_PROCESO_ESTANDAR(encontrados); // retorna el valor calculado en esta ruta de ejecución // ejemplo: encontrados
        }
        nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

        for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
            }
            const char *celda = (j == col_editar) ? nuevo : partes[j];                           // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);                         // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }

        if (lineas[i])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        lineas[i] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        free_split(partes);      // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        encontrados++;           // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
    }

    guardar_archivo(ruta, lineas, total);   // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);             // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    RETORNAR_PROCESO_ESTANDAR(encontrados); // retorna el valor calculado en esta ruta de ejecución // ejemplo: encontrados

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id_principal;           // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_principal
    (void)programa_id;            // marca el parámetro como no usado en esta rama de compilación // ejemplo: programa_id
    (void)col_editar;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_editar
    (void)incremento;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: incremento
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/*
 * Uso: Ejecuta eliminar_fila_para_multiples_programas_solo_prog de forma segura.
 * Entrada ejemplo: eliminar_fila_para_multiples_programas_solo_prog(ruta, id_a_eliminar, programa_id)
 */
void eliminar_fila_para_multiples_programas_solo_prog(const char *ruta,          // continúa enviando argumentos o elementos dentro de la expresión actual // ejemplo: siguiente parámetro de la llamada
                                                      const char *id_a_eliminar, // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                                                      const char *programa_id)   // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    char **resultado = NULL;                                 // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n_resultado = 0;                                     // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int capacidad = 10;                                      // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    resultado = (char **)malloc(capacidad * sizeof(char *)); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!resultado)                                          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE

        int eliminar = 0;                                     // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        if (n > 0 && strcmp(partes[0], id_a_eliminar) == 0 && // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            n > 2 && strcmp(partes[2], programa_id) == 0)     // compara dos cadenas para saber si representan el mismo valor // ejemplo: ID_TOT contra la cabecera leída
        {
            eliminar = 1;                                     // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
        }

        if (n > 0)              // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }

        if (!eliminar) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            if (n_resultado >= capacidad) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                capacidad *= 2;                                                        // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
                char **temp = (char **)realloc(resultado, capacidad * sizeof(char *)); // redimensiona memoria dinámica para ampliar o ajustar la capacidad actual // ejemplo: duplicar el arreglo de punteros
                if (!temp)                                                             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    free_lineas(resultado, n_resultado); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                    free_lineas(lineas, total);          // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                    return;                              // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
                }
                resultado = temp; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
            }

            resultado[n_resultado] = (char *)malloc(strlen(lineas[i]) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
            if (!resultado[n_resultado])                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free_lineas(resultado, n_resultado); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                free_lineas(lineas, total);          // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                return;                              // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
            }
            strcpy(resultado[n_resultado], lineas[i]); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
            n_resultado++;                             // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
        }
    }

    free_lineas(lineas, total);                    // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    guardar_archivo(ruta, resultado, n_resultado); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(resultado, n_resultado);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;          // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id_a_eliminar; // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_a_eliminar
    (void)programa_id;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: programa_id

#endif
}

/*
 * Uso: Ejecuta editar_fila_espesifica_sin_arreglo_gg de forma segura.
 * Entrada ejemplo: editar_fila_espesifica_sin_arreglo_gg(ruta, id_fila, col_editar, nuevo_valor)
 */
int editar_fila_espesifica_sin_arreglo_gg(const char *ruta, const char *id_fila,   // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                                          int col_editar, const char *nuevo_valor) // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0);           // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (strcmp(partes[0], id_fila) != 0 || col_editar >= n) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        char *nueva_linea = (char *)malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!nueva_linea)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);           // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
        }
        nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

        for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
            }
            const char *celda = (j == col_editar) ? nuevo_valor : partes[j];                     // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);                         // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }

        if (lineas[i])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        lineas[i] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        free_split(partes);      // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales

        guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
        free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(1);         // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1
    }

    free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id_fila;                // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_fila
    (void)col_editar;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_editar
    (void)nuevo_valor;            // marca el parámetro como no usado en esta rama de compilación // ejemplo: nuevo_valor
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/*
 * Uso: Ejecuta leer_solo_prog de forma segura.
 * Entrada ejemplo: leer_solo_prog(ruta, programa_id, salida_out)
 */
int leer_solo_prog(const char *ruta, const char *programa_id, char ***salida_out) // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    if (salida_out == NULL)           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        *salida_out = NULL;           // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    char **resultado = NULL;                                 // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int encontrados = 0;                                     // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int capacidad = 10;                                      // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    resultado = (char **)malloc(capacidad * sizeof(char *)); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!resultado)                                          // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        *salida_out = NULL;           // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (n <= 2 || strcmp(partes[2], programa_id) != 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (encontrados >= capacidad) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            capacidad *= 2;                                                        // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
            char **temp = (char **)realloc(resultado, capacidad * sizeof(char *)); // redimensiona memoria dinámica para ampliar o ajustar la capacidad actual // ejemplo: duplicar el arreglo de punteros
            if (!temp)                                                             // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free_split(partes);                  // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
                free_lineas(resultado, encontrados); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                free_lineas(lineas, total);          // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
                *salida_out = NULL;                  // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
                RETORNAR_PROCESO_ESTANDAR(0);        // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
            }
            resultado = temp; // actualiza la variable con el nuevo valor calculado en esta etapa // ejemplo: total = 0
        }

        resultado[encontrados] = (char *)malloc(strlen(lineas[i]) + 1); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!resultado[encontrados])                                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);                  // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(resultado, encontrados); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            free_lineas(lineas, total);          // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            *salida_out = NULL;                  // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
            RETORNAR_PROCESO_ESTANDAR(0);        // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
        }
        strcpy(resultado[encontrados], lineas[i]); // copia una cadena completa al destino indicado // ejemplo: duplicar la ruta original
        encontrados++;                             // mantiene esta instrucción dentro del flujo actual sin alterar la lógica original // ejemplo: paso intermedio del proceso
        free_split(partes);                        // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    free_lineas(lineas, total);             // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    *salida_out = resultado;                // escribe el valor indicado en la dirección apuntada por el puntero // ejemplo: *n_lineas_out = 0
    RETORNAR_PROCESO_ESTANDAR(encontrados); // retorna el valor calculado en esta ruta de ejecución // ejemplo: encontrados

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)programa_id;            // marca el parámetro como no usado en esta rama de compilación // ejemplo: programa_id
    (void)salida_out;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: salida_out
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/*
 * Uso: Ejecuta editar_celda_id_fila_solo_prog de forma segura.
 * Entrada ejemplo: editar_celda_id_fila_solo_prog(ruta, id_fila, col_editar, nuevo_valor, programa_id)
 */
int editar_celda_id_fila_solo_prog(const char *ruta, int id_fila,           // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                                   int col_editar, const char *nuevo_valor, // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                                   const char *programa_id)                 // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0);           // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    if (id_fila < 0 || id_fila >= total) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    char **partes = NULL;                                                             // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n = split(lineas[id_fila], GG_caracter_separacion[0], &partes);               // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
    if (n <= 0 || col_editar >= n || (n <= 2 || strcmp(partes[2], programa_id) != 0)) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (n > 0)                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);       // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    char *nueva_linea = (char *)malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!nueva_linea)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_split(partes);           // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }
    nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

    for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }
        const char *celda = (j == col_editar) ? nuevo_valor : partes[j];                     // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);                         // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
    }

    if (lineas[id_fila])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(lineas[id_fila]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    }
    lineas[id_fila] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
    free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    RETORNAR_PROCESO_ESTANDAR(1);         // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id_fila;                // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_fila
    (void)col_editar;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_editar
    (void)nuevo_valor;            // marca el parámetro como no usado en esta rama de compilación // ejemplo: nuevo_valor
    (void)programa_id;            // marca el parámetro como no usado en esta rama de compilación // ejemplo: programa_id
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/*
 * Uso: Ejecuta incrementa_celda_id_fila_solo_prog de forma segura.
 * Entrada ejemplo: incrementa_celda_id_fila_solo_prog(ruta, id_fila, col, incremento, programa_id)
 */
int incrementa_celda_id_fila_solo_prog(const char *ruta, int id_fila, int col,     // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
                                       double incremento, const char *programa_id) // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        RETORNAR_PROCESO_ESTANDAR(0);           // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    if (id_fila < 0 || id_fila >= total) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    char **partes = NULL;                                                      // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    int n = split(lineas[id_fila], GG_caracter_separacion[0], &partes);        // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
    if (n <= 0 || col >= n || (n <= 2 || strcmp(partes[2], programa_id) != 0)) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (n > 0)                    // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);       // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }

    double valor_actual = atof(partes[col]);                         // convierte el texto numérico a double para operar con él // ejemplo: 15.5
    char nuevo[64];                                                  // declara una variable que se usará en las operaciones siguientes // ejemplo: buffer temporal
    snprintf(nuevo, sizeof(nuevo), "%g", valor_actual + incremento); // formatea texto seguro dentro del buffer indicado respetando su tamaño // ejemplo: 1000.txt

    char *nueva_linea = (char *)malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!nueva_linea)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free_split(partes);           // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        free_lineas(lineas, total);   // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0
    }
    nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

    for (int j = 0; j < n; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        if (j > 0)                                                                           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }
        const char *celda = (j == col) ? nuevo : partes[j];                                  // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);                         // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
    }

    if (lineas[id_fila])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(lineas[id_fila]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    }
    lineas[id_fila] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
    free_split(partes);            // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    RETORNAR_PROCESO_ESTANDAR(1);         // retorna el valor calculado en esta ruta de ejecución // ejemplo: 1

#elif defined(__XC)
    (void)ruta;                   // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id_fila;                // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_fila
    (void)col;                    // marca el parámetro como no usado en esta rama de compilación // ejemplo: col
    (void)incremento;             // marca el parámetro como no usado en esta rama de compilación // ejemplo: incremento
    (void)programa_id;            // marca el parámetro como no usado en esta rama de compilación // ejemplo: programa_id
    RETORNAR_PROCESO_ESTANDAR(0); // retorna el valor calculado en esta ruta de ejecución // ejemplo: 0

#endif
}

/*
 * Uso: Ejecuta borrar_contenido_excepto_id de forma segura.
 * Entrada ejemplo: borrar_contenido_excepto_id(ruta, id_fila)
 */
void borrar_contenido_excepto_id(const char *ruta, const char *id_fila) // ejecuta la llamada o condición representada en esta línea // ejemplo: operación completada
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
#if defined(_WIN32) || defined(__linux__)
    int total = 0;                              // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    char **lineas = leer_archivo(ruta, &total); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    if (lineas == NULL)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return;                                 // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
    }

    for (int i = 0; i < total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        char **partes = NULL;                                         // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
        int n = split(lineas[i], GG_caracter_separacion[0], &partes); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (n <= 0)                                                   // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            continue;                                                 // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        if (strcmp(partes[0], id_fila) != 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            continue;           // salta al siguiente ciclo de la iteración actual // ejemplo: pasa al siguiente registro
        }

        char *nueva_linea = (char *)malloc(8192); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!nueva_linea)                         // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free_split(partes);         // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            free_lineas(lineas, total); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
            return;                     // sale de la función actual sin devolver un valor adicional // ejemplo: termina aquí
        }
        nueva_linea[0] = '\0'; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea

        strncat(nueva_linea, partes[0], 8191); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        for (int j = 1; j < n; j++)            // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1); // concatena texto al final del buffer cuidando el espacio disponible // ejemplo: agregar separador y valor
        }

        if (lineas[i])           // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            free(lineas[i]);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        }
        lineas[i] = nueva_linea; // actualiza una posición específica del arreglo actual // ejemplo: lineas[i] = nueva_linea
        free_split(partes);      // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    guardar_archivo(ruta, lineas, total); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
    free_lineas(lineas, total);           // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído

#elif defined(__XC)
    (void)ruta;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: ruta
    (void)id_fila; // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_fila

#endif
}

/* =======================
FUNCIONES INFO_DIVIDIDA PORTADAS DEL C#
======================== */

/*
 * Uso: Lee todas las filas de datos de un almacenamiento dividido y las retorna unidas.
 * Entrada ejemplo: leer_todo_info_dividida("espacios\\mi_espacio.txt")
 * Retorna string con todas las filas separadas por SEP_FUNC[3]. El caller debe free().
 */
char *leer_todo_info_dividida(const char *ruta) // lee todos los registros distribuidos en archivos divididos y los retorna como una sola cadena
{
#if defined(_WIN32) || defined(__linux__)
    if (!ruta || !ruta[0]) { return NULL; } // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL

    long id_total = 0, cant_por_arch = 100;
    if (leer_config_metadata(ruta, &id_total, &cant_por_arch) < 0) { return NULL; } // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL

    char *carpeta_data = construir_carpeta_data(ruta); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (!carpeta_data) { return NULL; }                // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL

    char *resultado = NULL; // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0

    for (long i = 1; i <= id_total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        size_t tam    = strlen(carpeta_data) + 128;
        char  *ruta_a = (char *)malloc(tam); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!ruta_a) { break; }              // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL

        generar_ruta_archivo(carpeta_data, i, cant_por_arch, ruta_a, tam); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt

        int    nl     = 0;
        char **lineas = leer_archivo(ruta_a, &nl); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
        free(ruta_a);                              // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

        long cont = 0;
        if (lineas && nl > 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            for (int j = 0; j < nl && cont < cant_por_arch; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
            {
                if (cont > 0) // salta la primera línea del archivo (encabezado de columnas)
                {
                    if (!resultado)
                    {
                        concatenar_formato_separado_por_variable(&resultado, NULL, "%s", lineas[j]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                    }
                    else
                    {
                        concatenar_formato_separado_por_variable(&resultado, NULL, "%s%s",
                            GG_caracter_separacion_funciones_espesificas[3], lineas[j]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                    }
                }
                cont++;
            }
            free_lineas(lineas, nl); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        }

        i += cont; // avanza i por la cantidad de líneas leídas (el for agrega 1 más en la siguiente iteración)
    }

    free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    if (!resultado)
    {
        resultado = (char *)calloc(1, 1); // retorna string vacío en lugar de NULL cuando no hay datos aún
    }
    return resultado; // retorna el valor calculado en esta ruta de ejecución // ejemplo: resultado

#elif defined(__XC)
    (void)ruta;
    return NULL;
#endif
}

/*
 * Uso: Agrega una fila solo si no existe un registro con el mismo valor en la columna indicada.
 * Parametros:
 *   direccion      - ruta del archivo metadata
 *   col_comp       - indice de columna donde comparar (0 = primera)
 *   comparar       - valor a buscar en col_comp
 *   texto_agr      - fila a insertar si no existe (sin ID, con SEP[0])
 *   nom_cols       - cabecera de columnas si se crea el archivo por primera vez
 * Retorna "1<SEP_C>fila" o "0<SEP_C>ya existe..." El caller debe free().
 */
char *agregar_sino_existe_info_dividida(const char *direccion, // ruta del archivo metadata
                                        long        col_comp,  // indice de columna de comparacion
                                        const char *comparar,  // valor a buscar en col_comp
                                        const char *texto_agr, // fila a insertar si no existe
                                        const char *nom_cols)  // cabecera de columnas para archivo nuevo
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    crear_archivo_info_dividida(direccion, nom_cols ? nom_cols : ""); // crea el archivo metadata si todavía no existe usando la cabecera indicada // ejemplo: metadata inicial

    char *todo = leer_todo_info_dividida(direccion); // lee todos los registros para buscar si ya existe el valor

    int   id_encontrado   = -1;
    char *info_encontrada = NULL;

    if (todo && todo[0] && comparar) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        char **filas  = NULL;
        int    nf     = split(todo, GG_caracter_separacion_funciones_espesificas[3], &filas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        for (int i = 0; i < nf && filas; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            char **celdas = NULL;
            int    nc     = split(filas[i], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
            if (nc > (int)col_comp && celdas && strcmp(celdas[(int)col_comp], comparar) == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                id_encontrado = i + 1;
                concatenar_formato_separado_por_variable(&info_encontrada, NULL, "%s", filas[i]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                if (celdas) { free_split(celdas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
                break;
            }
            if (celdas) { free_split(celdas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }
        if (filas) { free_split(filas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }
    free(todo); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    if (id_encontrado == -1) // no se encontró: agregar
    {
        respuesta = agregar_info_dividida(direccion, texto_agr, nom_cols); // delega en agregar_info_dividida para insertar la nueva fila
    }
    else // ya existe
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%s%d%sya existe no se guardo%s%s",
            GG_caracter_para_confirmacion_o_error[0], id_encontrado,
            GG_caracter_para_confirmacion_o_error[0],
            GG_caracter_para_confirmacion_o_error[0],
            info_encontrada ? info_encontrada : ""); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
    }

    if (info_encontrada) { free(info_encontrada); } // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)col_comp;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_comp
    (void)comparar;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: comparar
    (void)texto_agr;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: texto_agr
    (void)nom_cols;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: nom_cols
    return NULL;
#endif
}

/*
 * Uso: Obtiene un registro por su ID en almacenamiento dividido.
 * Parametros:
 *   direccion - ruta del archivo metadata
 *   id        - identificador del registro a obtener
 * Retorna "1<SEP_C>fila" o "0<SEP_C>no_se_encontro_informacion". El caller debe free().
 */
char *seleccionar_id_info_dividida(const char *direccion, // ruta del archivo metadata
                                   const char *id)        // identificador del registro a obtener
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0] || !id || !id[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    long        id_num    = atol(id);
    long        cant      = 100;
    leer_config_metadata(direccion, NULL, &cant); // lee CANT_POR_ARCH del metadata para derivar la ruta del archivo de datos

    char *carpeta_data = construir_carpeta_data(direccion); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (!carpeta_data) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    size_t  tam    = strlen(carpeta_data) + 128;
    char   *ruta_a = (char *)malloc(tam); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!ruta_a) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    generar_ruta_archivo(carpeta_data, id_num, cant, ruta_a, tam); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt
    free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    int    nl     = 0;
    char **lineas = leer_archivo(ruta_a, &nl); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo
    free(ruta_a);                              // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    long posicion = calcular_posicion_en_archivo(id); // calcula el índice de fila dentro del archivo a partir del ID
    int  encontro = 0;

    if (lineas && nl > 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        for (long j = 0; j < nl; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (posicion == j) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s",
                    GG_caracter_para_confirmacion_o_error[0], lineas[j]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                encontro = 1;
                break;
            }
        }
        free_lineas(lineas, nl); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    }

    if (!encontro) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno_se_encontro_informacion",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
    }

    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion; // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)id;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: id
    return NULL;
#endif
}

/*
 * Uso: Igual a seleccionar_id_info_dividida pero también retorna la ruta del archivo y la posicion de fila.
 * Parametros:
 *   direccion - ruta del archivo metadata
 *   id        - identificador del registro a obtener
 * Retorna "1<SEP_C>fila<SEP_C>ruta_archivo<SEP_C>posicion" o "0<SEP_C>no_se_encontro_informacion". El caller debe free().
 */
char *seleccionar_id_info_dividida_extrae(const char *direccion, // ruta del archivo metadata
                                          const char *id)        // identificador del registro a obtener
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0] || !id || !id[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    long        id_num    = atol(id);
    long        cant      = 100;
    leer_config_metadata(direccion, NULL, &cant); // lee CANT_POR_ARCH del metadata para derivar la ruta del archivo de datos

    char *carpeta_data = construir_carpeta_data(direccion); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (!carpeta_data) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    size_t  tam    = strlen(carpeta_data) + 128;
    char   *ruta_a = (char *)malloc(tam); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!ruta_a) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    generar_ruta_archivo(carpeta_data, id_num, cant, ruta_a, tam); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt
    free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    int    nl     = 0;
    char **lineas = leer_archivo(ruta_a, &nl); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo

    long posicion = calcular_posicion_en_archivo(id); // calcula el índice de fila dentro del archivo a partir del ID
    int  encontro = 0;

    if (lineas && nl > 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        for (long j = 0; j < nl; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (posicion == j) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s%s%s%s%ld",
                    GG_caracter_para_confirmacion_o_error[0], lineas[j],
                    GG_caracter_para_confirmacion_o_error[0], ruta_a,
                    GG_caracter_para_confirmacion_o_error[0], j); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                encontro = 1;
                break;
            }
        }
        free_lineas(lineas, nl); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    }

    if (!encontro) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno_se_encontro_informacion",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
    }

    free(ruta_a);  // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion; // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)id;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: id
    return NULL;
#endif
}

/*
 * Uso: Edita una columna en el registro que coincide por columna de busqueda o por ID.
 * Parametros:
 *   direccion       - ruta del archivo metadata
 *   id              - identificador del registro objetivo
 *   info_a_comparar - valor a buscar (vacio = buscar por id)
 *   col_comparar    - columna donde buscar info_a_comparar (vacio = buscar por id)
 *   nuevos_datos    - valor a escribir en la columna editada
 *   col_editar      - indice de la columna a modificar
 * Retorna "1<SEP_C>informacion_editada" o "0<SEP_C>no_se_encontro_informacion". El caller debe free().
 */
char *editar_id_info_dividida(const char *direccion,       // ruta del archivo metadata
                               const char *id,             // identificador del registro objetivo
                               const char *info_a_comparar,// valor de busqueda (NULL = buscar por id)
                               const char *col_comparar,   // columna donde buscar (NULL = buscar por id)
                               const char *nuevos_datos,   // nuevo valor para la celda editada
                               int         col_editar)     // indice de columna a modificar
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    long id_num = atol(id ? id : "0");
    long cant   = 100;
    leer_config_metadata(direccion, NULL, &cant); // lee CANT_POR_ARCH del metadata para derivar la ruta del archivo de datos

    char *carpeta_data = construir_carpeta_data(direccion); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (!carpeta_data) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    size_t  tam    = strlen(carpeta_data) + 128;
    char   *ruta_a = (char *)malloc(tam); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!ruta_a) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    generar_ruta_archivo(carpeta_data, id_num, cant, ruta_a, tam); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt
    free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    int    nl     = 0;
    char **lineas = leer_archivo(ruta_a, &nl); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo

    int encontro = 0;
    int col_comp = (info_a_comparar && info_a_comparar[0] && col_comparar && col_comparar[0])
                   ? atoi(col_comparar) : -1; // determina si la búsqueda es por valor en columna o por ID

    if (lineas && nl > 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        for (int i = 0; i < nl; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            char **celdas = NULL;
            int    nc     = split(lineas[i], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
            int    coincide = 0;

            if (col_comp >= 0) // busca por valor en columna específica
            {
                if (nc > col_comp && celdas && strcmp(celdas[col_comp], info_a_comparar) == 0) { coincide = 1; }
            }
            else // busca por ID (columna 0)
            {
                if (nc > 0 && celdas && strcmp(celdas[0], id) == 0) { coincide = 1; }
            }

            if (coincide && nc > col_editar && celdas) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free(celdas[col_editar]);    // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                celdas[col_editar] = NULL;
                concatenar_formato_separado_por_variable(&celdas[col_editar], NULL, "%s", nuevos_datos ? nuevos_datos : ""); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito

                char *nueva = reconstruir_fila(celdas, nc); // reconstruye la fila con el valor editado
                if (nueva) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    free(lineas[i]);  // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                    lineas[i] = nueva;
                    encontro  = 1;
                }
            }
            if (celdas) { free_split(celdas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }

        if (encontro)
        {
            guardar_archivo(ruta_a, lineas, nl); // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
            concatenar_formato_separado_por_variable(&respuesta, NULL, "1%sinformacion_editada",
                GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        }
        else
        {
            concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno_se_encontro_informacion",
                GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        }
        free_lineas(lineas, nl); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    }
    else
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno_se_encontro_informacion",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        if (lineas) { free_lineas(lineas, nl); } // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    }

    free(ruta_a);  // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion;       // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)id;              // marca el parámetro como no usado en esta rama de compilación // ejemplo: id
    (void)info_a_comparar; // marca el parámetro como no usado en esta rama de compilación // ejemplo: info_a_comparar
    (void)col_comparar;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_comparar
    (void)nuevos_datos;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: nuevos_datos
    (void)col_editar;      // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_editar
    return NULL;
#endif
}

/*
 * Uso: Edita multiples celdas de un registro por ID usando SEP[4] para separar columnas y valores.
 * Parametros:
 *   direccion - ruta del archivo metadata
 *   id        - identificador del registro objetivo
 *   cols_str  - columnas a editar separadas con SEP[4]
 *   vals_str  - nuevos valores separados con SEP[4] (misma cantidad que cols_str)
 * Retorna "1<SEP_C>fila_editada" o "0<SEP_C>no_se_encontro_informacion". El caller debe free().
 */
char *editar_celda_id_info_dividida(const char *direccion, // ruta del archivo metadata
                                    const char *id,        // identificador del registro objetivo
                                    const char *cols_str,  // columnas a editar (sep SEP[4])
                                    const char *vals_str)  // nuevos valores (sep SEP[4])
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    long        id_num     = atol(id ? id : "0");
    long        cant       = 100;
    leer_config_metadata(direccion, NULL, &cant); // lee CANT_POR_ARCH del metadata para derivar la ruta del archivo de datos

    char *carpeta_data = construir_carpeta_data(direccion); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (!carpeta_data) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    size_t  tam    = strlen(carpeta_data) + 128;
    char   *ruta_a = (char *)malloc(tam); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!ruta_a) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    generar_ruta_archivo(carpeta_data, id_num, cant, ruta_a, tam); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt
    free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    int    nl     = 0;
    char **lineas = leer_archivo(ruta_a, &nl); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo

    long posicion = calcular_posicion_en_archivo(id); // calcula el índice de fila dentro del archivo a partir del ID
    int  encontro = 0;

    if (lineas && nl > 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        char **cols_arr = NULL;
        int    nc_cols  = split(cols_str, GG_caracter_separacion_funciones_espesificas[4], &cols_arr); // divide las columnas a editar usando el separador de nivel 4
        char **vals_arr = NULL;
        int    nc_vals  = split(vals_str, GG_caracter_separacion_funciones_espesificas[4], &vals_arr); // divide los nuevos valores usando el separador de nivel 4

        for (long j = 0; j < nl; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (posicion != j) { continue; }

            char **celdas = NULL;
            int    nc     = split(lineas[j], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
            if (nc <= 0 || !celdas) { break; }

            for (int k = 0; k < nc_cols && k < nc_vals && cols_arr && vals_arr; k++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
            {
                int col_idx = atoi(cols_arr[k]);
                if (col_idx >= 0 && col_idx < nc) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    free(celdas[col_idx]); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                    celdas[col_idx] = NULL;
                    concatenar_formato_separado_por_variable(&celdas[col_idx], NULL, "%s", vals_arr[k] ? vals_arr[k] : ""); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                }
            }

            char *nueva = reconstruir_fila(celdas, nc); // reconstruye la fila con las celdas editadas
            if (nueva) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free(lineas[j]);  // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                lineas[j] = nueva;
                encontro  = 1;
                concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s",
                    GG_caracter_para_confirmacion_o_error[0], nueva); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
            }
            free_split(celdas); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            break;
        }

        if (cols_arr) { free_split(cols_arr); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        if (vals_arr) { free_split(vals_arr); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        if (encontro) { guardar_archivo(ruta_a, lineas, nl); } // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
        free_lineas(lineas, nl); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    }

    if (!encontro && !respuesta) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno_se_encontro_informacion",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
    }

    free(ruta_a);  // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion; // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)id;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: id
    (void)cols_str;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: cols_str
    (void)vals_str;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: vals_str
    return NULL;
#endif
}

/*
 * Uso: Incrementa numericamente multiples celdas de un registro por ID.
 * Parametros:
 *   direccion  - ruta del archivo metadata
 *   id         - identificador del registro objetivo
 *   cols_str   - columnas a incrementar separadas con SEP[4] (SEP[5] es reemplazado por SEP[0] internamente)
 *   cants_str  - cantidades a sumar separadas con SEP[4] (pueden ser negativas)
 * Retorna "1<SEP_C>fila_editada" o "0<SEP_C>no_se_encontro_informacion". El caller debe free().
 */
char *incrementa_celda_id_info_dividida(const char *direccion, // ruta del archivo metadata
                                        const char *id,        // identificador del registro objetivo
                                        const char *cols_str,  // columnas a incrementar (sep SEP[4])
                                        const char *cants_str) // cantidades a sumar (sep SEP[4])
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    long        id_num     = atol(id ? id : "0");
    long        cant       = 100;
    leer_config_metadata(direccion, NULL, &cant); // lee CANT_POR_ARCH del metadata para derivar la ruta del archivo de datos

    char *cols_str_proc = ReemplazarCaracteres_de_texto_string(cols_str ? cols_str : "",
        GG_caracter_separacion_funciones_espesificas[5],
        GG_caracter_separacion[0]); // reemplaza SEP[5] con SEP[0] en la lista de columnas (comportamiento del C# original)
    if (!cols_str_proc) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    char *carpeta_data_incr = construir_carpeta_data(direccion); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (!carpeta_data_incr) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(cols_str_proc); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        return NULL;
    }

    size_t  tam_incr    = strlen(carpeta_data_incr) + 128;
    char   *ruta_a_incr = (char *)malloc(tam_incr); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!ruta_a_incr) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(carpeta_data_incr); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        free(cols_str_proc);     // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        return NULL;
    }

    generar_ruta_archivo(carpeta_data_incr, id_num, cant, ruta_a_incr, tam_incr); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt
    free(carpeta_data_incr); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    int    nl     = 0;
    char **lineas = leer_archivo(ruta_a_incr, &nl); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo

    long posicion = calcular_posicion_en_archivo(id ? id : "0"); // calcula el índice de fila dentro del archivo a partir del ID
    int  encontro = 0;

    if (lineas && nl > 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        char **cols_arr  = NULL;
        int    nc_cols   = split(cols_str_proc, GG_caracter_separacion_funciones_espesificas[4], &cols_arr); // divide las columnas a incrementar usando el separador de nivel 4
        char **cants_arr = NULL;
        int    nc_cants  = split(cants_str, GG_caracter_separacion_funciones_espesificas[4], &cants_arr); // divide las cantidades usando el separador de nivel 4

        for (long j = 0; j < nl; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (posicion != j) { continue; }

            char **celdas = NULL;
            int    nc     = split(lineas[j], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
            if (nc <= 0 || !celdas) { break; }

            for (int k = 0; k < nc_cols && k < nc_cants && cols_arr && cants_arr; k++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
            {
                int    col_idx   = atoi(cols_arr[k]);
                double inc       = atof(cants_arr[k]);
                if (col_idx >= 0 && col_idx < nc) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    double val_actual = atof(celdas[col_idx] ? celdas[col_idx] : "0");
                    char   nuevo_val[64];
                    snprintf(nuevo_val, sizeof(nuevo_val), "%g", val_actual + inc); // formatea el nuevo valor numérico en texto
                    free(celdas[col_idx]); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                    celdas[col_idx] = NULL;
                    concatenar_formato_separado_por_variable(&celdas[col_idx], NULL, "%s", nuevo_val); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                }
            }

            char *nueva = reconstruir_fila(celdas, nc); // reconstruye la fila con los valores incrementados
            if (nueva) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free(lineas[j]);  // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                lineas[j] = nueva;
                encontro  = 1;
                concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s",
                    GG_caracter_para_confirmacion_o_error[0], nueva); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
            }
            free_split(celdas); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            break;
        }

        if (cols_arr)  { free_split(cols_arr);  } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        if (cants_arr) { free_split(cants_arr); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        if (encontro)  { guardar_archivo(ruta_a_incr, lineas, nl); } // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
        free_lineas(lineas, nl); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    }

    if (!encontro && !respuesta) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno_se_encontro_informacion",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
    }

    free(cols_str_proc); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    free(ruta_a_incr);   // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)id;         // marca el parámetro como no usado en esta rama de compilación // ejemplo: id
    (void)cols_str;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: cols_str
    (void)cants_str;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: cants_str
    return NULL;
#endif
}

/*
 * Uso: Incrementa celdas por ID; si el valor resultante es negativo o la celda esta vacia,
 *      copia el valor de una columna fuente y señala que se debe descontar un paquete.
 * Parametros:
 *   direccion        - ruta del archivo metadata
 *   id               - identificador del registro objetivo
 *   cols_str         - columnas a incrementar separadas con SEP[4]
 *   cants_str        - cantidades a sumar separadas con SEP[4] (pueden ser negativas)
 *   cols_fuente_str  - columnas fuente para copiar cuando hay deficit, separadas con SEP[4]
 * Retorna "2<SEP_C>fila<SEP_C>bultos_a_quitar" si hay deficit, "1<SEP_C>fila" si OK. El caller debe free().
 */
char *incrementa_celda_id_info_dividida_copia_si_cero(const char *direccion,       // ruta del archivo metadata
                                                       const char *id,              // identificador del registro objetivo
                                                       const char *cols_str,        // columnas a incrementar (sep SEP[4])
                                                       const char *cants_str,       // cantidades a sumar (sep SEP[4])
                                                       const char *cols_fuente_str) // columnas fuente para copiar al haber deficit (sep SEP[4])
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    long        id_num     = atol(id ? id : "0");
    long        cant       = 100;
    leer_config_metadata(direccion, NULL, &cant); // lee CANT_POR_ARCH del metadata para derivar la ruta del archivo de datos

    char *cols_str_cero = ReemplazarCaracteres_de_texto_string(cols_str ? cols_str : "",
        GG_caracter_separacion_funciones_espesificas[5],
        GG_caracter_separacion[0]); // reemplaza SEP[5] con SEP[0] en la lista de columnas
    if (!cols_str_cero) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    char *carpeta_data = construir_carpeta_data(direccion); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (!carpeta_data) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(cols_str_cero); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        return NULL;
    }

    size_t  tam    = strlen(carpeta_data) + 128;
    char   *ruta_a = (char *)malloc(tam); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
    if (!ruta_a) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        free(carpeta_data);  // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        free(cols_str_cero); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        return NULL;
    }

    generar_ruta_archivo(carpeta_data, id_num, cant, ruta_a, tam); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt
    free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    int    nl     = 0;
    char **lineas = leer_archivo(ruta_a, &nl); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo

    long posicion = calcular_posicion_en_archivo(id ? id : "0"); // calcula el índice de fila dentro del archivo a partir del ID
    int  encontro = 0;

    if (lineas && nl > 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        char **cols_arr  = NULL;
        int    nc_cols   = split(cols_str_cero, GG_caracter_separacion_funciones_espesificas[4], &cols_arr); // divide las columnas a incrementar usando el separador de nivel 4
        char **cants_arr = NULL;
        int    nc_cants  = split(cants_str, GG_caracter_separacion_funciones_espesificas[4], &cants_arr); // divide las cantidades usando el separador de nivel 4
        char **cop_arr   = NULL;
        int    nc_cop    = split(cols_fuente_str ? cols_fuente_str : "", GG_caracter_separacion_funciones_espesificas[4], &cop_arr); // divide las columnas fuente de copia usando el separador de nivel 4

        for (long j = 0; j < nl; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (posicion != j) { continue; }

            char **celdas = NULL;
            int    nc     = split(lineas[j], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
            if (nc <= 0 || !celdas) { break; }

            int decrementa_paquete = 0;
            int bultos_a_quitar   = 0;

            for (int k = 0; k < nc_cols && k < nc_cants && cols_arr && cants_arr; k++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
            {
                int    col_idx        = atoi(cols_arr[k]);
                double incremento_val = atof(cants_arr[k]);
                double val_col6       = (nc > 6 && celdas[6]) ? atof(celdas[6]) : 0.0; // usa columna 6 como stock actual (igual al C# original)
                double kilos_totales  = val_col6 + incremento_val;
                int    celda_vacia    = (col_idx >= 0 && col_idx < nc && (!celdas[col_idx] || !celdas[col_idx][0]));

                if (kilos_totales <= 0.0 || celda_vacia) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    double val_col10 = (nc > 10 && celdas[10]) ? atof(celdas[10]) : 1.0;
                    if (val_col10 < 1.0) { val_col10 = 1.0; }
                    if ((-kilos_totales) > val_col10) // el déficit supera el tamaño del paquete: calcular cuántos paquetes quitar
                    {
                        bultos_a_quitar = (int)((kilos_totales / val_col10)) + 1;
                    }

                    if (k < nc_cop && cop_arr && cop_arr[k] && cop_arr[k][0]) // copia el valor de la columna fuente en la columna destino
                    {
                        int col_cop = atoi(cop_arr[k]);
                        if (col_cop >= 0 && col_cop < nc && col_idx >= 0 && col_idx < nc) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                        {
                            free(celdas[col_idx]); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                            celdas[col_idx] = NULL;
                            concatenar_formato_separado_por_variable(&celdas[col_idx], NULL, "%s", celdas[col_cop] ? celdas[col_cop] : ""); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                        }
                    }
                    decrementa_paquete = 1;
                }

                if (col_idx >= 0 && col_idx < nc) // establece el valor final (kilos resultantes pueden ser negativos)
                {
                    char nuevo_val[64];
                    snprintf(nuevo_val, sizeof(nuevo_val), "%g", kilos_totales); // formatea el nuevo valor numérico en texto
                    free(celdas[col_idx]); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                    celdas[col_idx] = NULL;
                    concatenar_formato_separado_por_variable(&celdas[col_idx], NULL, "%s", nuevo_val); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                }
            }

            char *nueva = reconstruir_fila(celdas, nc); // reconstruye la fila con los nuevos valores
            if (nueva) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                free(lineas[j]);  // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                lineas[j] = nueva;
                encontro  = 1;
                if (decrementa_paquete) // retorna código 2 para indicar que se debe descontar un paquete
                {
                    concatenar_formato_separado_por_variable(&respuesta, NULL, "2%s%s%s%d",
                        GG_caracter_para_confirmacion_o_error[0], nueva,
                        GG_caracter_para_confirmacion_o_error[0], bultos_a_quitar); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                }
                else
                {
                    concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s",
                        GG_caracter_para_confirmacion_o_error[0], nueva); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                }
            }
            free_split(celdas); // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
            break;
        }

        if (cols_arr)  { free_split(cols_arr);  } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        if (cants_arr) { free_split(cants_arr); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        if (cop_arr)   { free_split(cop_arr);   } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        if (encontro)  { guardar_archivo(ruta_a, lineas, nl); } // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
        free_lineas(lineas, nl); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
    }

    if (!encontro && !respuesta) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno_se_encontro_informacion",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
    }

    free(cols_str_cero); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    free(ruta_a);        // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)id;               // marca el parámetro como no usado en esta rama de compilación // ejemplo: id
    (void)cols_str;         // marca el parámetro como no usado en esta rama de compilación // ejemplo: cols_str
    (void)cants_str;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: cants_str
    (void)cols_fuente_str;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: cols_fuente_str
    return NULL;
#endif
}

/*
 * Uso: Busca un registro por valor en una columna e incrementa celdas numericas al encontrarlo.
 * Parametros:
 *   direccion       - ruta del archivo metadata
 *   dato_a_buscar   - valor a buscar en col_buscar
 *   col_buscar      - indice de columna donde buscar
 *   cols_inc_str    - columnas a incrementar separadas con SEP[4]
 *   cants_inc_str   - cantidades a sumar separadas con SEP[4]
 *   agregar_fallback- fila a agregar si no se encuentra el valor (puede ser NULL o vacio)
 * Retorna "1" si encontró y editó, "0" si no encontró. El caller debe free().
 */
char *incrementa_celda_busqueda_info_dividida(const char *direccion,          // ruta del archivo metadata
                                              const char *dato_a_buscar,      // valor a buscar
                                              int         col_buscar,         // columna donde buscar
                                              const char *cols_inc_str,       // columnas a incrementar (sep SEP[4])
                                              const char *cants_inc_str,      // cantidades a sumar (sep SEP[4])
                                              const char *agregar_fallback)   // fila a agregar si no se encuentra
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    long id_total = 0, cant_por_arch = 100;
    if (leer_config_metadata(direccion, &id_total, &cant_por_arch) < 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror al leer metadata",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    char *carpeta_data = construir_carpeta_data(direccion); // declara e inicializa una variable con el valor necesario para continuar el proceso // ejemplo: contador en 0
    if (!carpeta_data) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        return NULL;
    }

    char **cols_arr  = NULL;
    int    nc_cols   = split(cols_inc_str, GG_caracter_separacion_funciones_espesificas[4], &cols_arr); // divide las columnas a incrementar usando el separador de nivel 4
    char **cants_arr = NULL;
    int    nc_cants  = split(cants_inc_str, GG_caracter_separacion_funciones_espesificas[4], &cants_arr); // divide las cantidades usando el separador de nivel 4
    int    encontro  = 0;

    for (long i = 1; i <= id_total; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
    {
        size_t  tam    = strlen(carpeta_data) + 128;
        char   *ruta_a = (char *)malloc(tam); // reserva memoria dinámica para almacenar el dato o buffer requerido // ejemplo: espacio para una nueva cadena
        if (!ruta_a) { break; } // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL

        generar_ruta_archivo(carpeta_data, i, cant_por_arch, ruta_a, tam); // construye la ruta del archivo segmentado según el identificador actual // ejemplo: datos/100/1000.txt

        int    nl     = 0;
        char **lineas = leer_archivo(ruta_a, &nl); // carga el archivo completo en memoria para procesar sus filas // ejemplo: inventario completo

        long cont      = 0;
        int  modifico  = 0;

        if (lineas && nl > 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            for (int j = 0; j < nl && cont < cant_por_arch; j++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
            {
                if (cont == 0) { cont++; continue; } // salta el encabezado de columnas del archivo de datos

                char **celdas = NULL;
                int    nc     = split(lineas[j], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE

                if (nc > col_buscar && celdas && strcmp(celdas[col_buscar], dato_a_buscar) == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                {
                    for (int k = 0; k < nc_cols && k < nc_cants && cols_arr && cants_arr; k++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
                    {
                        int    col_idx = atoi(cols_arr[k]);
                        double inc     = atof(cants_arr[k]);
                        if (col_idx >= 0 && col_idx < nc) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                        {
                            double val = atof(celdas[col_idx] ? celdas[col_idx] : "0");
                            char   nv[64];
                            snprintf(nv, sizeof(nv), "%g", val + inc); // formatea el nuevo valor numérico en texto
                            free(celdas[col_idx]); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                            celdas[col_idx] = NULL;
                            concatenar_formato_separado_por_variable(&celdas[col_idx], NULL, "%s", nv); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                        }
                    }
                    char *nueva = reconstruir_fila(celdas, nc); // reconstruye la fila con los valores incrementados
                    if (nueva) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
                    {
                        free(lineas[j]); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
                        lineas[j] = nueva;
                        modifico  = 1;
                        encontro  = 1;
                    }
                }
                if (celdas) { free_split(celdas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
                cont++;
            }

            if (modifico) { guardar_archivo(ruta_a, lineas, nl); } // reescribe el archivo con las líneas ya modificadas en memoria // ejemplo: guardar cambios de una tabla
            free_lineas(lineas, nl); // libera el arreglo de líneas y sus cadenas asociadas // ejemplo: contenido del archivo leído
        }

        free(ruta_a); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        i += cont;    // avanza i por la cantidad de líneas procesadas (el for agrega 1 más en la siguiente iteración)
    }

    if (!encontro && agregar_fallback && agregar_fallback[0]) // si no se encontró y hay un valor por defecto, agregarlo
    {
        char *res = agregar_info_dividida(direccion, agregar_fallback, NULL); // agrega la fila que no se encontró
        if (res) { free(res); } // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
    }

    if (cols_arr)  { free_split(cols_arr);  } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    if (cants_arr) { free_split(cants_arr); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    free(carpeta_data); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    concatenar_formato_separado_por_variable(&respuesta, NULL, "%s", encontro ? "1" : "0"); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion;        // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)dato_a_buscar;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: dato_a_buscar
    (void)col_buscar;       // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_buscar
    (void)cols_inc_str;     // marca el parámetro como no usado en esta rama de compilación // ejemplo: cols_inc_str
    (void)cants_inc_str;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: cants_inc_str
    (void)agregar_fallback; // marca el parámetro como no usado en esta rama de compilación // ejemplo: agregar_fallback
    return NULL;
#endif
}

/*
 * Uso: Busca un registro por valor en una columna dentro del almacenamiento dividido.
 * Parametros:
 *   direccion    - ruta del archivo metadata
 *   dato_buscar  - valor a buscar
 *   col_buscar   - indice de columna donde buscar
 *   id_hint      - posicion aproximada donde buscar primero (-1 para busqueda completa)
 * Retorna "1<SEP_C>fila<SEP_C>id" o "0<SEP_C>no encontro el producto". El caller debe free().
 */
char *buscar_info_dividida(const char *direccion,  // ruta del archivo metadata
                           const char *dato_buscar, // valor a buscar
                           int         col_buscar,  // indice de columna donde buscar
                           int         id_hint)     // posicion aproximada (-1 para busqueda completa)
{
#if defined(_WIN32) || defined(__linux__)
    char *respuesta = NULL;
    if (!direccion || !direccion[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    char *todo = leer_todo_info_dividida(direccion); // carga todos los registros para la búsqueda

    if (!todo || !todo[0]) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        if (todo) { free(todo); } // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno encontro el producto",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
        return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta
    }

    char **filas  = NULL;
    int    nf     = split(todo, GG_caracter_separacion_funciones_espesificas[3], &filas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
    free(todo); // libera memoria dinámica previamente reservada para evitar fugas // ejemplo: buffer temporal

    int encontro = 0;

    if (id_hint >= 0 && id_hint < nf && filas && filas[id_hint]) // verifica primero en la posición sugerida por el hint
    {
        char **celdas = NULL;
        int    nc     = split(filas[id_hint], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
        if (nc > col_buscar && celdas && strcmp(celdas[col_buscar], dato_buscar) == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
        {
            concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s%s%d",
                GG_caracter_para_confirmacion_o_error[0], filas[id_hint],
                GG_caracter_para_confirmacion_o_error[0], id_hint); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
            encontro = 1;
        }
        if (celdas) { free_split(celdas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
    }

    if (!encontro && id_hint > 0) // busca en el rango anterior al hint
    {
        int inicio = (id_hint > 10) ? (id_hint - 10) : 0;
        for (int i = inicio; i < id_hint && !encontro; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (!filas || !filas[i]) { continue; }
            char **celdas = NULL;
            int    nc     = split(filas[i], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
            if (nc > col_buscar && celdas && strcmp(celdas[col_buscar], dato_buscar) == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s%s%d",
                    GG_caracter_para_confirmacion_o_error[0], filas[i],
                    GG_caracter_para_confirmacion_o_error[0], i + 1); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                encontro = 1;
            }
            if (celdas) { free_split(celdas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }
    }

    if (!encontro) // búsqueda completa si el hint no ayudó
    {
        for (int i = 0; i < nf && !encontro; i++) // recorre una secuencia controlando el índice de esta iteración // ejemplo: i de 0 a total-1
        {
            if (!filas || !filas[i]) { continue; }
            char **celdas = NULL;
            int    nc     = split(filas[i], GG_caracter_separacion[0], &celdas); // divide el texto usando el separador configurado para trabajar cada campo por separado // ejemplo: ID|NOMBRE
            if (nc > col_buscar && celdas && strcmp(celdas[col_buscar], dato_buscar) == 0) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
            {
                concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s%s%d",
                    GG_caracter_para_confirmacion_o_error[0], filas[i],
                    GG_caracter_para_confirmacion_o_error[0], i + 1); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
                encontro = 1;
            }
            if (celdas) { free_split(celdas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales
        }
    }

    if (filas) { free_split(filas); } // libera el arreglo de partes generado por split cuando ya no se necesita // ejemplo: columnas temporales

    if (!encontro) // evalúa la condición para decidir si entra al bloque actual // ejemplo: ruta != NULL
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sno encontro el producto",
            GG_caracter_para_confirmacion_o_error[0]); // arma una cadena dinámica con formato seguro usando los valores indicados // ejemplo: respuesta de éxito
    }

    return respuesta; // retorna el valor calculado en esta ruta de ejecución // ejemplo: respuesta

#elif defined(__XC)
    (void)direccion;    // marca el parámetro como no usado en esta rama de compilación // ejemplo: direccion
    (void)dato_buscar;  // marca el parámetro como no usado en esta rama de compilación // ejemplo: dato_buscar
    (void)col_buscar;   // marca el parámetro como no usado en esta rama de compilación // ejemplo: col_buscar
    (void)id_hint;      // marca el parámetro como no usado en esta rama de compilación // ejemplo: id_hint
    return NULL;
#endif
}
