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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <sys/stat.h>
#include <direct.h>

#elif defined(__linux__)
#include <sys/stat.h>

#elif defined(__XC)
#define _XTAL_FREQ 4000000
#include <xc.h>
/* PIC16F: Sin sistema de archivos. Las funciones son stubs. */

#else
#include <sys/stat.h>
#endif

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

static int ruta_es_absoluta(const char *ruta)
{
    if (!ruta || !ruta[0])
        return 0;

#ifdef _WIN32
    if ((ruta[0] && ruta[1] == ':') ||
        (ruta[0] == '\\' && ruta[1] == '\\') ||
        (ruta[0] == '/'))
        return 1;
#else
    if (ruta[0] == '/')
        return 1;
#endif

    return 0;
}

static char *buscar_ultimo_separador(char *ruta)
{
    char *sep_linux = strrchr(ruta, '/');
    char *sep_windows = strrchr(ruta, '\\');

    if (!sep_linux)
        return sep_windows;
    if (!sep_windows)
        return sep_linux;

    return (sep_linux > sep_windows) ? sep_linux : sep_windows;
}

/* =======================
   FUNCIONES BASE
   ======================== */

int crearDirectorio(const char *ruta)
{
#if defined(_WIN32) || defined(__linux__)
    char *ruta_trabajo = NULL;

    if (!ruta)
    {
        imprimirMensaje_para_depurar("[crearDirectorio] ruta es NULL\n");
        return -1;
    }

    imprimirMensaje_para_depurar("[crearDirectorio] ruta: %s\n", ruta);

    int es_absoluta = ruta_es_absoluta(ruta);
    imprimirMensaje_para_depurar("[crearDirectorio] ruta absoluta: %d\n", es_absoluta);

    if (es_absoluta)
    {
        ruta_trabajo = (char *)malloc(strlen(ruta) + 1);
        if (!ruta_trabajo)
        {
            imprimirMensaje_para_depurar("[crearDirectorio] malloc fallo para ruta_trabajo completa\n");
            return -1;
        }
        strcpy(ruta_trabajo, ruta);
    }
    else
    {
        ruta_trabajo = (char *)malloc(strlen(ruta) + 3);
        if (!ruta_trabajo)
        {
            imprimirMensaje_para_depurar("[crearDirectorio] malloc fallo para ruta_trabajo local\n");
            return -1;
        }
#ifdef _WIN32
        strcpy(ruta_trabajo, ".\\");
#else
        strcpy(ruta_trabajo, "./");
#endif
        strcat(ruta_trabajo, ruta);
    }

    imprimirMensaje_para_depurar("[crearDirectorio] ruta_trabajo: %s\n", ruta_trabajo);

    int estado_creacion = -1;

#ifdef _WIN32
    const char separador = '\\';
#else
    const char separador = '/';
#endif

    char separador_txt[2] = {separador, '\0'};
    size_t len_ruta = strlen(ruta_trabajo);

    char *ruta_normalizada = (char *)malloc(len_ruta + 1);
    if (!ruta_normalizada)
    {
        imprimirMensaje_para_depurar("[crearDirectorio] malloc fallo para ruta_normalizada\n");
        free(ruta_trabajo);
        return -1;
    }

    for (size_t i = 0; i < len_ruta; i++)
    {
        char c = ruta_trabajo[i];
        if (c == '/' || c == '\\')
            ruta_normalizada[i] = separador;
        else
            ruta_normalizada[i] = c;
    }
    ruta_normalizada[len_ruta] = '\0';

    char **partes = NULL;
    int n_partes = split(ruta_normalizada, separador_txt, &partes);
    if (n_partes < 0 || !partes)
    {
        free(ruta_normalizada);
        free(ruta_trabajo);
        return -1;
    }

    int indice_ultimo = -1;
    for (int i = 0; i < n_partes; i++)
    {
        if (partes[i] && partes[i][0] != '\0')
            indice_ultimo = i;
    }

    if (indice_ultimo < 0)
    {
        free_split(partes);
        free(ruta_normalizada);
        free(ruta_trabajo);
        return -1;
    }

    char *acumulada = NULL;
    int inicio = 0;

#ifdef _WIN32
    if (partes[0] && strlen(partes[0]) == 2 && partes[0][1] == ':')
    {
        if (concatenar_formato_separado_por_variable(&acumulada, NULL, "%s%s", partes[0], separador_txt) < 0)
        {
            free_split(partes);
            free(ruta_normalizada);
            free(ruta_trabajo);
            return -1;
        }
        inicio = 1;
    }
#else
    if (ruta_normalizada[0] == separador)
    {
        if (concatenar_formato_separado_por_variable(&acumulada, NULL, "%s", separador_txt) < 0)
        {
            free_split(partes);
            free(ruta_normalizada);
            free(ruta_trabajo);
            return -1;
        }
    }
#endif

    estado_creacion = 1;
    for (int i = inicio; i < n_partes; i++)
    {
        if (!partes[i] || partes[i][0] == '\0')
            continue;

        if (acumulada && acumulada[0])
        {
            const char *fin = acumulada;
            while (*fin != '\0')
                fin++;

            if (*(fin - 1) != separador)
            {
                if (concatenar_formato_separado_por_variable(&acumulada, NULL, "%s", separador_txt) < 0)
                {
                    free(acumulada);
                    free_split(partes);
                    free(ruta_normalizada);
                    free(ruta_trabajo);
                    return -1;
                }
            }
        }

        if (concatenar_formato_separado_por_variable(&acumulada, NULL, "%s", partes[i]) < 0)
        {
            free(acumulada);
            free_split(partes);
            free(ruta_normalizada);
            free(ruta_trabajo);
            return -1;
        }

        errno = 0;
        int resultado_mkdir =
#ifdef _WIN32
            mkdir(acumulada);
#else
            mkdir(acumulada, 0777);
#endif

        if (i == indice_ultimo)
        {
            if (resultado_mkdir == 0)
                estado_creacion = 0;
            else if (errno == EEXIST)
                estado_creacion = 1;
            else
            {
                free(acumulada);
                free_split(partes);
                free(ruta_normalizada);
                free(ruta_trabajo);
                return -1;
            }
        }
        else if (resultado_mkdir != 0 && errno != EEXIST)
        {
            free(acumulada);
            free_split(partes);
            free(ruta_normalizada);
            free(ruta_trabajo);
            return -1;
        }
    }

    free(acumulada);
    free_split(partes);
    free(ruta_normalizada);

    if (estado_creacion == 0)
    {
        imprimirMensaje_para_depurar("[crearDirectorio] creado: %s\n", ruta_trabajo);
        free(ruta_trabajo);
        return 0;
    }
    else if (estado_creacion == 1)
    {
        imprimirMensaje_para_depurar("[crearDirectorio] ya existe, se omite: %s\n", ruta_trabajo);
        free(ruta_trabajo);
        return 1;
    }
    else
    {
        imprimirMensaje_para_depurar("[crearDirectorio] error al crear: %s\n", ruta_trabajo);
        free(ruta_trabajo);
        return -1;
    }

#elif defined(__XC)
    (void)ruta;
    return -1;
#endif
}

int crearArchivo(const char *ruta, const char *cabecera)
{
    imprimirMensaje_para_depurar("%s\n", ruta);
#if defined(_WIN32) || defined(__linux__)
    if (!ruta)
    {
        imprimirMensaje_para_depurar("[crearArchivo] ruta es NULL\n");
        return -1;
    }

    char *ruta_trabajo = NULL;
    int es_absoluta = ruta_es_absoluta(ruta);

    if (es_absoluta)
    {
        ruta_trabajo = (char *)malloc(strlen(ruta) + 1);
        if (!ruta_trabajo)
        {
            imprimirMensaje_para_depurar("[crearArchivo] malloc fallo para ruta_trabajo completa\n");
            return -1;
        }
        strcpy(ruta_trabajo, ruta);
    }
    else
    {
        ruta_trabajo = (char *)malloc(strlen(ruta) + 3);
        if (!ruta_trabajo)
        {
            imprimirMensaje_para_depurar("[crearArchivo] malloc fallo para ruta_trabajo local\n");
            return -1;
        }
#ifdef _WIN32
        strcpy(ruta_trabajo, ".\\");
#else
        strcpy(ruta_trabajo, "./");
#endif
        strcat(ruta_trabajo, ruta);
    }

    imprimirMensaje_para_depurar("[crearArchivo] ruta original: %s\n", ruta);
    imprimirMensaje_para_depurar("[crearArchivo] ruta_trabajo: %s\n", ruta_trabajo);

    int estado_directorio = 0;

    /* Crear el directorio padre si la ruta contiene un separador */
    char *dir_padre = (char *)malloc(strlen(ruta_trabajo) + 1);
    if (dir_padre)
    {
        strcpy(dir_padre, ruta_trabajo);
        char *sep = buscar_ultimo_separador(dir_padre);
        if (sep)
        {
            *sep = '\0';
            imprimirMensaje_para_depurar("[crearArchivo] creando directorio padre: %s\n", dir_padre);

            estado_directorio = crearDirectorio(dir_padre);
            if (estado_directorio == -1)
            {
                imprimirMensaje_para_depurar("[crearArchivo] error al crear directorio padre: %s\n", dir_padre);
                free(dir_padre);
                free(ruta_trabajo);
                return -2;
            }
        }
        free(dir_padre);
    }

    /* Verificar si el archivo ya existe */
    FILE *f = fopen(ruta_trabajo, "r");
    if (f)
    {
        imprimirMensaje_para_depurar("[crearArchivo] el archivo ya existe: %s\n", ruta_trabajo);
        fclose(f);
        free(ruta_trabajo);
        return 1;
    }

    /* Crear el archivo */
    f = fopen(ruta_trabajo, "w");
    if (f)
    {
        if (cabecera)
            fprintf(f, "%s\n", cabecera);
        fclose(f);
        imprimirMensaje_para_depurar("[crearArchivo] archivo creado: %s\n", ruta_trabajo);
    }
    else
    {
        imprimirMensaje_para_depurar("[crearArchivo] error al crear archivo: %s\n", ruta_trabajo);
        free(ruta_trabajo);
        return -1;
    }

    free(ruta_trabajo);

    if (estado_directorio == 1)
        return 2;

    return 0;

#elif defined(__XC)
    (void)ruta;
    (void)cabecera;
    return 0;
#endif
}

char **leer_archivo(const char *ruta, int *n_lineas_out)
{
#if defined(_WIN32) || defined(__linux__)
    if (n_lineas_out == NULL)
        return NULL;

    FILE *f = fopen(ruta, "r");
    if (!f)
    {
        *n_lineas_out = 0;
        return NULL;
    }

    char **lineas = NULL;
    int n = 0;
    int capacidad = 10;
    lineas = (char **)malloc(capacidad * sizeof(char *));
    if (!lineas)
    {
        fclose(f);
        *n_lineas_out = 0;
        return NULL;
    }

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), f))
    {
        if (n >= capacidad)
        {
            capacidad *= 2;
            char **temp = (char **)realloc(lineas, capacidad * sizeof(char *));
            if (!temp)
            {
                free_lineas(lineas, n);
                fclose(f);
                *n_lineas_out = 0;
                return NULL;
            }
            lineas = temp;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        lineas[n] = (char *)malloc(strlen(buffer) + 1);
        if (!lineas[n])
        {
            free_lineas(lineas, n);
            fclose(f);
            *n_lineas_out = 0;
            return NULL;
        }
        strcpy(lineas[n], buffer);
        n++;
    }

    fclose(f);
    *n_lineas_out = n;
    return lineas;

#elif defined(__XC)
    (void)ruta;
    (void)n_lineas_out;
    return NULL;

#endif
}

void guardar_archivo(const char *ruta, char **lineas, int n_lineas)
{
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "w");
    if (!f)
        return;

    for (int i = 0; i < n_lineas; i++)
        fprintf(f, "%s\n", lineas[i]);

    fclose(f);

#elif defined(__XC)
    (void)ruta;
    (void)lineas;
    (void)n_lineas;

#endif
}

void free_lineas(char **lineas, int n_lineas)
{
#if defined(_WIN32) || defined(__linux__)
    if (lineas == NULL)
        return;

    for (int i = 0; i < n_lineas; i++)
    {
        if (lineas[i])
            free(lineas[i]);
    }
    free(lineas);

#elif defined(__XC)
    (void)lineas;
    (void)n_lineas;

#endif
}

void agregar_fila(const char *ruta, const char *fila)
{
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "a");
    if (f)
    {
        fprintf(f, "%s\n", fila);
        fclose(f);
    }

#elif defined(__XC)
    (void)ruta;
    (void)fila;

#endif
}

int existe_archivo(const char *ruta)
{
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "r");
    if (f)
    {
        fclose(f);
        return 1;
    }
    return 0;

#elif defined(__XC)
    (void)ruta;
    return 0;

#endif
}

/* =======================
   OPERACIONES DE CELDAS Y FILAS
   ======================== */

int seleccionar_fila_por_celda(const char *ruta, int col_buscar,
                               const char *valor_buscar,
                               char ***salida_out)
{
#if defined(_WIN32) || defined(__linux__)
    if (salida_out == NULL)
        return 0;

    int n_total = 0;
    char **lineas = leer_archivo(ruta, &n_total);
    if (lineas == NULL)
    {
        *salida_out = NULL;
        return 0;
    }

    char **resultado = NULL;
    int encontrados = 0;
    int capacidad = 10;
    resultado = (char **)malloc(capacidad * sizeof(char *));
    if (!resultado)
    {
        free_lineas(lineas, n_total);
        *salida_out = NULL;
        return 0;
    }

    for (int i = 0; i < n_total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n < 0)
            continue;

        if (col_buscar < n && strcmp(partes[col_buscar], valor_buscar) == 0)
        {
            if (encontrados >= capacidad)
            {
                capacidad *= 2;
                char **temp = (char **)realloc(resultado, capacidad * sizeof(char *));
                if (!temp)
                {
                    free_split(partes);
                    free_lineas(resultado, encontrados);
                    free_lineas(lineas, n_total);
                    *salida_out = NULL;
                    return 0;
                }
                resultado = temp;
            }

            resultado[encontrados] = (char *)malloc(strlen(lineas[i]) + 1);
            if (!resultado[encontrados])
            {
                free_split(partes);
                free_lineas(resultado, encontrados);
                free_lineas(lineas, n_total);
                *salida_out = NULL;
                return 0;
            }
            strcpy(resultado[encontrados], lineas[i]);
            encontrados++;
        }

        free_split(partes);
    }

    free_lineas(lineas, n_total);
    *salida_out = resultado;
    return encontrados;

#elif defined(__XC)
    (void)ruta;
    (void)col_buscar;
    (void)valor_buscar;
    (void)salida_out;
    return 0;

#endif
}

void eliminar_fila_por_celda(const char *ruta, int col_buscar,
                             const char *valor_buscar)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    char **resultado = NULL;
    int n_resultado = 0;
    int capacidad = 10;
    resultado = (char **)malloc(capacidad * sizeof(char *));
    if (!resultado)
    {
        free_lineas(lineas, total);
        return;
    }

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);

        int eliminar = 0;
        if (n > 0 && col_buscar < n && strcmp(partes[col_buscar], valor_buscar) == 0)
            eliminar = 1;

        if (n > 0)
            free_split(partes);

        if (!eliminar)
        {
            if (n_resultado >= capacidad)
            {
                capacidad *= 2;
                char **temp = (char **)realloc(resultado, capacidad * sizeof(char *));
                if (!temp)
                {
                    free_lineas(resultado, n_resultado);
                    free_lineas(lineas, total);
                    return;
                }
                resultado = temp;
            }

            resultado[n_resultado] = (char *)malloc(strlen(lineas[i]) + 1);
            if (!resultado[n_resultado])
            {
                free_lineas(resultado, n_resultado);
                free_lineas(lineas, total);
                return;
            }
            strcpy(resultado[n_resultado], lineas[i]);
            n_resultado++;
        }
    }

    free_lineas(lineas, total);
    guardar_archivo(ruta, resultado, n_resultado);
    free_lineas(resultado, n_resultado);

#elif defined(__XC)
    (void)ruta;
    (void)col_buscar;
    (void)valor_buscar;

#endif
}

void editar_celda_por_celda(const char *ruta, int col_buscar,
                            const char *valor_buscar,
                            int col_editar, const char *nuevo_valor)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        if (col_buscar >= n || strcmp(partes[col_buscar], valor_buscar) != 0 || col_editar >= n)
        {
            free_split(partes);
            continue;
        }

        /* Reconstruir la fila */
        char *nueva_linea = malloc(8192);
        if (!nueva_linea)
        {
            free_split(partes);
            free_lineas(lineas, total);
            return;
        }
        nueva_linea[0] = '\0';

        for (int j = 0; j < n; j++)
        {
            if (j > 0)
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);

            const char *celda = (j == col_editar) ? nuevo_valor : partes[j];
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
        }

        if (lineas[i])
            free(lineas[i]);
        lineas[i] = nueva_linea;
        free_split(partes);
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);

#elif defined(__XC)
    (void)ruta;
    (void)col_buscar;
    (void)valor_buscar;
    (void)col_editar;
    (void)nuevo_valor;

#endif
}

void editar_celda(const char *ruta, int colBuscar, const char *valorBuscar,
                  int colEditar, const char *nuevoValor)
{
    editar_celda_por_celda(ruta, colBuscar, valorBuscar, colEditar, nuevoValor);
}

void eliminar_fila(const char *ruta, int filaEliminar)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    char **resultado = NULL;
    int n_resultado = 0;
    int capacidad = 10;
    resultado = (char **)malloc(capacidad * sizeof(char *));
    if (!resultado)
    {
        free_lineas(lineas, total);
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (i == filaEliminar)
            continue;

        if (n_resultado >= capacidad)
        {
            capacidad *= 2;
            char **temp = (char **)realloc(resultado, capacidad * sizeof(char *));
            if (!temp)
            {
                free_lineas(resultado, n_resultado);
                free_lineas(lineas, total);
                return;
            }
            resultado = temp;
        }

        resultado[n_resultado] = (char *)malloc(strlen(lineas[i]) + 1);
        if (!resultado[n_resultado])
        {
            free_lineas(resultado, n_resultado);
            free_lineas(lineas, total);
            return;
        }
        strcpy(resultado[n_resultado], lineas[i]);
        n_resultado++;
    }

    free_lineas(lineas, total);
    guardar_archivo(ruta, resultado, n_resultado);
    free_lineas(resultado, n_resultado);

#elif defined(__XC)
    (void)ruta;
    (void)filaEliminar;

#endif
}

void editar_fila(const char *ruta, int fila, const char *nueva)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    if (fila >= 0 && fila < total)
    {
        free(lineas[fila]);
        lineas[fila] = (char *)malloc(strlen(nueva) + 1);
        if (lineas[fila])
            strcpy(lineas[fila], nueva);
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);

#elif defined(__XC)
    (void)ruta;
    (void)fila;
    (void)nueva;

#endif
}

void incrementar_celda(const char *ruta, int colBuscar, const char *valorBuscar,
                       int colEditar, int inc)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        if (colBuscar >= n || strcmp(partes[colBuscar], valorBuscar) != 0 || colEditar >= n)
        {
            free_split(partes);
            continue;
        }

        double valor_actual = atof(partes[colEditar]);
        char nuevo[64];
        snprintf(nuevo, sizeof(nuevo), "%g", valor_actual + inc);

        char *nueva_linea = malloc(8192);
        if (!nueva_linea)
        {
            free_split(partes);
            free_lineas(lineas, total);
            return;
        }
        nueva_linea[0] = '\0';

        for (int j = 0; j < n; j++)
        {
            if (j > 0)
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
            const char *celda = (j == colEditar) ? nuevo : partes[j];
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
        }

        if (lineas[i])
            free(lineas[i]);
        lineas[i] = nueva_linea;
        free_split(partes);
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);

#elif defined(__XC)
    (void)ruta;
    (void)colBuscar;
    (void)valorBuscar;
    (void)colEditar;
    (void)inc;

#endif
}

void editar_columna_completa(const char *ruta, int col, const char *nuevo)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;
        if (col >= n)
        {
            free_split(partes);
            continue;
        }

        char *nueva_linea = malloc(8192);
        if (!nueva_linea)
        {
            free_split(partes);
            free_lineas(lineas, total);
            return;
        }
        nueva_linea[0] = '\0';

        for (int j = 0; j < n; j++)
        {
            if (j > 0)
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
            const char *celda = (j == col) ? nuevo : partes[j];
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
        }

        if (lineas[i])
            free(lineas[i]);
        lineas[i] = nueva_linea;
        free_split(partes);
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);

#elif defined(__XC)
    (void)ruta;
    (void)col;
    (void)nuevo;

#endif
}

void eliminar_columna(const char *ruta, int col)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        char *nueva_linea = malloc(8192);
        if (!nueva_linea)
        {
            free_split(partes);
            free_lineas(lineas, total);
            return;
        }
        nueva_linea[0] = '\0';

        int es_primero = 1;
        for (int j = 0; j < n; j++)
        {
            if (j == col)
                continue;
            if (!es_primero)
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
            strncat(nueva_linea, partes[j], 8192 - strlen(nueva_linea) - 1);
            es_primero = 0;
        }

        if (lineas[i])
            free(lineas[i]);
        lineas[i] = nueva_linea;
        free_split(partes);
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);

#elif defined(__XC)
    (void)ruta;
    (void)col;

#endif
}

void agregar_columna(const char *ruta, const char *nombre)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    for (int i = 0; i < total; i++)
    {
        size_t largo = strlen(lineas[i]);
        const char *valor = (i == 0) ? nombre : "";
        size_t len_sep = strlen(GG_caracter_separacion[0]);
        size_t len_val = strlen(valor);

        if (largo + len_sep + len_val < 8191)
        {
            strncat(lineas[i], GG_caracter_separacion[0], 8191 - largo);
            strncat(lineas[i], valor, 8191 - largo - len_sep);
        }
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);

#elif defined(__XC)
    (void)ruta;
    (void)nombre;

#endif
}

/* =======================
   BÚSQUEDA Y FILTRADO
   ======================== */

int buscar_fila(const char *ruta, int colBuscar, const char *valorBuscar,
                char **salida_out)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return -1;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        int coincide = (colBuscar < n && strcmp(partes[colBuscar], valorBuscar) == 0);
        free_split(partes);

        if (coincide)
        {
            if (salida_out != NULL)
            {
                *salida_out = (char *)malloc(strlen(lineas[i]) + 1);
                if (*salida_out)
                    strcpy(*salida_out, lineas[i]);
            }
            free_lineas(lineas, total);
            return i;
        }
    }

    free_lineas(lineas, total);
    return -1;

#elif defined(__XC)
    (void)ruta;
    (void)colBuscar;
    (void)valorBuscar;
    (void)salida_out;
    return -1;

#endif
}

int agregar_sino_existe(const char *ruta, int colBuscar, const char *valorBuscar,
                        const char *fila_nueva)
{
#if defined(_WIN32) || defined(__linux__)
    int idx = buscar_fila(ruta, colBuscar, valorBuscar, NULL);
    if (idx >= 0)
        return 0;

    agregar_fila(ruta, fila_nueva);
    return 1;

#elif defined(__XC)
    (void)ruta;
    (void)colBuscar;
    (void)valorBuscar;
    (void)fila_nueva;
    return -1;

#endif
}

int editar_celda_id_fila(const char *ruta, int id_fila, int col,
                         const char *nuevo_valor)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return 0;

    if (id_fila < 0 || id_fila >= total)
    {
        free_lineas(lineas, total);
        return 0;
    }

    char **partes = NULL;
    int n = split(lineas[id_fila], GG_caracter_separacion[0], &partes);
    if (n <= 0 || col >= n)
    {
        if (n > 0)
            free_split(partes);
        free_lineas(lineas, total);
        return 0;
    }

    char *nueva_linea = malloc(8192);
    if (!nueva_linea)
    {
        free_split(partes);
        free_lineas(lineas, total);
        return 0;
    }
    nueva_linea[0] = '\0';

    for (int j = 0; j < n; j++)
    {
        if (j > 0)
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
        const char *celda = (j == col) ? nuevo_valor : partes[j];
        strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
    }

    if (lineas[id_fila])
        free(lineas[id_fila]);
    lineas[id_fila] = nueva_linea;
    free_split(partes);

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);
    return 1;

#elif defined(__XC)
    (void)ruta;
    (void)id_fila;
    (void)col;
    (void)nuevo_valor;
    return 0;

#endif
}

int incrementar_celda_id_fila(const char *ruta, int id_fila, int col,
                              double incremento)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return 0;

    if (id_fila < 0 || id_fila >= total)
    {
        free_lineas(lineas, total);
        return 0;
    }

    char **partes = NULL;
    int n = split(lineas[id_fila], GG_caracter_separacion[0], &partes);
    if (n <= 0 || col >= n)
    {
        if (n > 0)
            free_split(partes);
        free_lineas(lineas, total);
        return 0;
    }

    double valor_actual = atof(partes[col]);
    char nuevo[64];
    snprintf(nuevo, sizeof(nuevo), "%g", valor_actual + incremento);

    char *nueva_linea = malloc(8192);
    if (!nueva_linea)
    {
        free_split(partes);
        free_lineas(lineas, total);
        return 0;
    }
    nueva_linea[0] = '\0';

    for (int j = 0; j < n; j++)
    {
        if (j > 0)
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
        const char *celda = (j == col) ? nuevo : partes[j];
        strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
    }

    if (lineas[id_fila])
        free(lineas[id_fila]);
    lineas[id_fila] = nueva_linea;
    free_split(partes);

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);
    return 1;

#elif defined(__XC)
    (void)ruta;
    (void)id_fila;
    (void)col;
    (void)incremento;
    return 0;

#endif
}

void borrar_celdas_excepto_primera(const char *ruta, int colBuscar,
                                   const char *valorBuscar)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        if (colBuscar >= n || strcmp(partes[colBuscar], valorBuscar) != 0)
        {
            free_split(partes);
            continue;
        }

        char *nueva_linea = malloc(8192);
        if (!nueva_linea)
        {
            free_split(partes);
            free_lineas(lineas, total);
            return;
        }
        nueva_linea[0] = '\0';

        strncat(nueva_linea, partes[0], 8191);
        for (int j = 1; j < n; j++)
        {
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
        }

        if (lineas[i])
            free(lineas[i]);
        lineas[i] = nueva_linea;
        free_split(partes);
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);

#elif defined(__XC)
    (void)ruta;
    (void)colBuscar;
    (void)valorBuscar;

#endif
}

void reescribir_archivo(const char *ruta, char **lineas, int n_lineas)
{
#if defined(_WIN32) || defined(__linux__)
    guardar_archivo(ruta, lineas, n_lineas);

#elif defined(__XC)
    (void)ruta;
    (void)lineas;
    (void)n_lineas;

#endif
}

void generar_ruta_archivo(const char *ruta, long id, long cant_por_arch,
                          char *salida, size_t tam_salida)
{
#if defined(_WIN32) || defined(__linux__)
    if (salida == NULL || tam_salida == 0)
        return;

    salida[0] = '\0';

    if (ruta != NULL && ruta[0] != '\0')
    {
        strncat(salida, ruta, tam_salida - strlen(salida) - 1);
        size_t largo = strlen(salida);
#ifdef _WIN32
        if (largo > 0 && salida[largo - 1] != '\\')
            strncat(salida, "\\", tam_salida - largo - 1);
#else
        if (largo > 0 && salida[largo - 1] != '/')
            strncat(salida, "/", tam_salida - largo - 1);
#endif
    }

    char id_str[32];
    snprintf(id_str, sizeof(id_str), "%ld", id);
    size_t id_len = strlen(id_str);

    char cant_str[32];
    snprintf(cant_str, sizeof(cant_str), "%ld", cant_por_arch);
    size_t n_ceros = strlen(cant_str) - 1;

    long potencia = cant_por_arch;
    for (size_t i = 2; i <= id_len; i++)
    {
        char seg[32];
#ifdef _WIN32
        snprintf(seg, sizeof(seg), "%ld\\", potencia);
#else
        snprintf(seg, sizeof(seg), "%ld/", potencia);
#endif
        strncat(salida, seg, tam_salida - strlen(salida) - 1);
        potencia *= cant_por_arch;
    }

    size_t prefijo_len = (id_len > n_ceros) ? (id_len - n_ceros) : 0;
    char nom[64] = "";
    strncat(nom, id_str, prefijo_len);
    for (size_t i = 0; i < n_ceros; i++)
        strncat(nom, "0", sizeof(nom) - strlen(nom) - 1);
    strncat(nom, ".txt", sizeof(nom) - strlen(nom) - 1);

    strncat(salida, nom, tam_salida - strlen(salida) - 1);

#elif defined(__XC)
    (void)ruta;
    (void)id;
    (void)cant_por_arch;
    (void)salida;
    (void)tam_salida;

#endif
}

/* =======================
   FUNCIONES ADICIONALES DEL C#
   ======================== */

char *leer_info_dividida(const char *ruta)
{
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "r");
    if (!f)
        return NULL;

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *resultado = (char *)malloc(tam + 1);
    if (!resultado)
    {
        fclose(f);
        return NULL;
    }

    size_t bytes_leidos = fread(resultado, 1, tam, f);
    resultado[bytes_leidos] = '\0';
    fclose(f);

    return resultado;

#elif defined(__XC)
    (void)ruta;
    return NULL;

#endif
}

/*crear_archivo_info_dividida
 * 
 * ------------------------------------------------------------
 * Crea (si no existe) el archivo metadata para info dividida.
 *
 * ENTRADA:
 * - direccion_archivos: ruta del metadata principal.
 *   Ejemplo: "espacios\\mi_espacio.txt"
 * - nom_columnas_si_no_existe_archivo: encabezados de columnas.
 *   Ejemplo: "ID|NOMBRE|PRECIO"
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
static int crear_archivo_info_dividida(const char *direccion_archivos,
                                       const char *nom_columnas_si_no_existe_archivo)
{
#if defined(_WIN32) || defined(__linux__)
    if (!direccion_archivos || !direccion_archivos[0])
        return -1;

    if (!nom_columnas_si_no_existe_archivo)
        nom_columnas_si_no_existe_archivo = "";

    char *cabecera_metadata = NULL;
    if (concatenar_formato_separado_por_variable(
            &cabecera_metadata, NULL,
            "tipo_info%sinfo\nID_TOT%s0\nCOLUMNAS%s%s\nCANT_POR_ARCH%s%s",
            GG_caracter_separacion[0], GG_caracter_separacion[0], GG_caracter_separacion[0],
            nom_columnas_si_no_existe_archivo, GG_caracter_separacion[0], GG_cantidado_por_archivo) < 0)
    {
        return -1;
    }

    int estado_creacion_metadata = crearArchivo(direccion_archivos, cabecera_metadata);
    free(cabecera_metadata);
    return estado_creacion_metadata;

#elif defined(__XC)
    (void)direccion_archivos;
    (void)nom_columnas_si_no_existe_archivo;
    return -1;

#endif
}

char *agregar_info_dividida(const char *datos)
{
#if defined(_WIN32) || defined(__linux__)
    /*
     * agregar_info_dividida
     * ------------------------------------------------------------
     * Agrega una fila a un archivo de datos dividido por bloques,
     * y actualiza ID_TOT en el metadata.
     *
     * ENTRADA (string "datos"):
     * - Formato: direccion_archivos + SEP_FUNC[3] + fila + SEP_FUNC[3] + columnas
     * - Ejemplo:
     *   "espacios\\mi_espacio.txt╬laptop|acer|15000╬ID|NOMBRE|PRECIO"
     *   (donde SEP_FUNC[3] actualmente es GG_caracter_separacion_funciones_espesificas[3])
     *
     * ARCHIVOS QUE PUEDE CREAR:
     * 1) Metadata:
     *    - espacios\\mi_espacio.txt
     *    - Si no existe, se crea con:
     *      tipo_info|info
     *      ID_TOT|0
     *      COLUMNAS|ID|NOMBRE|PRECIO
     *      CANT_POR_ARCH|100
     *
     * 2) Archivo de datos dividido:
     *    - espacios\\mi_espacio_DAT\\100.txt (o ruta generada equivalente)
     *    - Si no existe, se crea con cabecera de columnas.
     *
     * FILA AGREGADA (ejemplo):
     * - Si ID_TOT era 0 y agregando = "laptop|acer|15000",
     *   se agrega: "1|laptop|acer|15000"
     * - Luego metadata queda con: ID_TOT|1
     *
     * SALIDA:
     * - Exito: "1<SEP_CONFIRMACION>1|laptop|acer|15000"
     * - Error: "0<SEP_CONFIRMACION>mensaje"
     */
    char *respuesta = NULL;
    char **datos_espliteados = NULL;
    int n_datos = 0;

    if (!datos || !datos[0])
    {
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }

    n_datos = split(datos, GG_caracter_separacion_funciones_espesificas[3], &datos_espliteados);
    if (n_datos <= 0 || !datos_espliteados || !datos_espliteados[0] || !datos_espliteados[0][0])
    {
        if (datos_espliteados)
            free_split(datos_espliteados);
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%sparametros invalidos", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }

    const char *direccion_archivos = datos_espliteados[0];
    const char *agregando = "";
    const char *nom_columnas_si_no_existe_archivo = "";

    if (n_datos >= 2 && datos_espliteados[1] && datos_espliteados[1][0])
        agregando = datos_espliteados[1];

    if (n_datos >= 3 && datos_espliteados[2] && datos_espliteados[2][0])
        nom_columnas_si_no_existe_archivo = datos_espliteados[2];

    int estado_creacion_metadata = crear_archivo_info_dividida(direccion_archivos,
                                                               nom_columnas_si_no_existe_archivo);

    if (estado_creacion_metadata < 0)
    {
        free_split(datos_espliteados);
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror no pudo crear metadata", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }

    int n_lineas = 0;
    char **lineas = leer_archivo(direccion_archivos, &n_lineas);
    if (!lineas || n_lineas <= 0)
    {
        free_split(datos_espliteados);
        if (lineas)
            free_lineas(lineas, n_lineas);
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror no pudo leer metadata", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }

    long id_total = 0;
    long cantidad_filas_por_archivo = atol(GG_cantidado_por_archivo);
    char *columnas = NULL;

    if (cantidad_filas_por_archivo <= 0)
        cantidad_filas_por_archivo = 100;

    for (int i = 0; i < n_lineas; i++)
    {
        char **partes = NULL;
        int n_partes = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n_partes >= 2 && partes)
        {
            if (strcmp(partes[0], "ID_TOT") == 0)
                id_total = atol(partes[1]);
            else if (strcmp(partes[0], "COLUMNAS") == 0)
            {
                char *tmp_col = (char *)malloc(strlen(partes[1]) + 1);
                if (!tmp_col)
                {
                    free_split(partes);
                    free_lineas(lineas, n_lineas);
                    free_split(datos_espliteados);
                    concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]);
                    return respuesta;
                }
                strcpy(tmp_col, partes[1]);
                if (columnas)
                    free(columnas);
                columnas = tmp_col;
            }
            else if (strcmp(partes[0], "CANT_POR_ARCH") == 0)
            {
                long tmp = atol(partes[1]);
                if (tmp > 0)
                    cantidad_filas_por_archivo = tmp;
            }
        }

        if (partes)
            free_split(partes);
    }

    char *ruta_base_sin_ext = NULL;
    if (concatenar_formato_separado_por_variable(&ruta_base_sin_ext, NULL, "%s", direccion_archivos) < 0)
    {
        if (columnas)
            free(columnas);
        free_lineas(lineas, n_lineas);
        free_split(datos_espliteados);
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }

    char *sep = buscar_ultimo_separador(ruta_base_sin_ext);
    char *punto = strrchr(ruta_base_sin_ext, '.');
    if (punto && (!sep || punto > sep))
        *punto = '\0';

    char *carpeta_data = NULL;
    if (concatenar_formato_separado_por_variable(&carpeta_data, NULL, "%s_DAT", ruta_base_sin_ext) < 0)
    {
        free(ruta_base_sin_ext);
        if (columnas)
            free(columnas);
        free_lineas(lineas, n_lineas);
        free_split(datos_espliteados);
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }
    free(ruta_base_sin_ext);

    size_t tam_ruta_data = strlen(carpeta_data) + 128;
    char *ruta_data = (char *)malloc(tam_ruta_data);
    if (!ruta_data)
    {
        free(carpeta_data);
        if (columnas)
            free(columnas);
        free_lineas(lineas, n_lineas);
        free_split(datos_espliteados);
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }

    generar_ruta_archivo(carpeta_data, id_total, cantidad_filas_por_archivo, ruta_data, tam_ruta_data);
    free(carpeta_data);

    int estado_creacion_data = crearArchivo(ruta_data, columnas ? columnas : nom_columnas_si_no_existe_archivo);
    if (estado_creacion_data < 0)
    {
        free(ruta_data);
        if (columnas)
            free(columnas);
        free_lineas(lineas, n_lineas);
        free_split(datos_espliteados);
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror no pudo crear archivo de datos", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }

    char *fila_nueva = NULL;
    if (concatenar_formato_separado_por_variable(&fila_nueva, NULL, "%ld%s%s",
                                                 id_total + 1,
                                                 GG_caracter_separacion[0],
                                                 agregando) < 0)
    {
        free(ruta_data);
        if (columnas)
            free(columnas);
        free_lineas(lineas, n_lineas);
        free_split(datos_espliteados);
        concatenar_formato_separado_por_variable(&respuesta, NULL, "0%serror de memoria", GG_caracter_para_confirmacion_o_error[0]);
        return respuesta;
    }

    agregar_fila(ruta_data, fila_nueva);

    char nuevo_id_total[64];
    snprintf(nuevo_id_total, sizeof(nuevo_id_total), "%ld", id_total + 1);
    editar_celda_por_celda(direccion_archivos, 0, "ID_TOT", 1, nuevo_id_total);

    concatenar_formato_separado_por_variable(&respuesta, NULL, "1%s%s",
                                             GG_caracter_para_confirmacion_o_error[0], fila_nueva);

    free(fila_nueva);
    free(ruta_data);
    if (columnas)
        free(columnas);
    free_lineas(lineas, n_lineas);
    free_split(datos_espliteados);
    return respuesta;

#elif defined(__XC)
    (void)datos;
    return NULL;

#endif
}

int incrementa_celda_solo_prog(const char *ruta, const char *id_principal,
                               const char *programa_id, int col_editar, double incremento)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return 0;

    int encontrados = 0;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        /* Verificación: col 0 == id_principal Y col 2 == programa_id */
        if (n > 0 && strcmp(partes[0], id_principal) != 0)
        {
            free_split(partes);
            continue;
        }
        if (n <= 2 || strcmp(partes[2], programa_id) != 0)
        {
            free_split(partes);
            continue;
        }
        if (col_editar >= n)
        {
            free_split(partes);
            continue;
        }

        double valor_actual = atof(partes[col_editar]);
        char nuevo[64];
        snprintf(nuevo, sizeof(nuevo), "%g", valor_actual + incremento);

        char *nueva_linea = (char *)malloc(8192);
        if (!nueva_linea)
        {
            free_split(partes);
            free_lineas(lineas, total);
            return encontrados;
        }
        nueva_linea[0] = '\0';

        for (int j = 0; j < n; j++)
        {
            if (j > 0)
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
            const char *celda = (j == col_editar) ? nuevo : partes[j];
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
        }

        if (lineas[i])
            free(lineas[i]);
        lineas[i] = nueva_linea;
        free_split(partes);
        encontrados++;
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);
    return encontrados;

#elif defined(__XC)
    (void)ruta;
    (void)id_principal;
    (void)programa_id;
    (void)col_editar;
    (void)incremento;
    return 0;

#endif
}

void eliminar_fila_para_multiples_programas_solo_prog(const char *ruta,
                                                      const char *id_a_eliminar,
                                                      const char *programa_id)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    char **resultado = NULL;
    int n_resultado = 0;
    int capacidad = 10;
    resultado = (char **)malloc(capacidad * sizeof(char *));
    if (!resultado)
    {
        free_lineas(lineas, total);
        return;
    }

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);

        int eliminar = 0;
        if (n > 0 && strcmp(partes[0], id_a_eliminar) == 0 &&
            n > 2 && strcmp(partes[2], programa_id) == 0)
            eliminar = 1;

        if (n > 0)
            free_split(partes);

        if (!eliminar)
        {
            if (n_resultado >= capacidad)
            {
                capacidad *= 2;
                char **temp = (char **)realloc(resultado, capacidad * sizeof(char *));
                if (!temp)
                {
                    free_lineas(resultado, n_resultado);
                    free_lineas(lineas, total);
                    return;
                }
                resultado = temp;
            }

            resultado[n_resultado] = (char *)malloc(strlen(lineas[i]) + 1);
            if (!resultado[n_resultado])
            {
                free_lineas(resultado, n_resultado);
                free_lineas(lineas, total);
                return;
            }
            strcpy(resultado[n_resultado], lineas[i]);
            n_resultado++;
        }
    }

    free_lineas(lineas, total);
    guardar_archivo(ruta, resultado, n_resultado);
    free_lineas(resultado, n_resultado);

#elif defined(__XC)
    (void)ruta;
    (void)id_a_eliminar;
    (void)programa_id;

#endif
}

int editar_fila_espesifica_sin_arreglo_gg(const char *ruta, const char *id_fila,
                                          int col_editar, const char *nuevo_valor)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return 0;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        if (strcmp(partes[0], id_fila) != 0 || col_editar >= n)
        {
            free_split(partes);
            continue;
        }

        char *nueva_linea = (char *)malloc(8192);
        if (!nueva_linea)
        {
            free_split(partes);
            free_lineas(lineas, total);
            return 0;
        }
        nueva_linea[0] = '\0';

        for (int j = 0; j < n; j++)
        {
            if (j > 0)
                strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
            const char *celda = (j == col_editar) ? nuevo_valor : partes[j];
            strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
        }

        if (lineas[i])
            free(lineas[i]);
        lineas[i] = nueva_linea;
        free_split(partes);

        guardar_archivo(ruta, lineas, total);
        free_lineas(lineas, total);
        return 1;
    }

    free_lineas(lineas, total);
    return 0;

#elif defined(__XC)
    (void)ruta;
    (void)id_fila;
    (void)col_editar;
    (void)nuevo_valor;
    return 0;

#endif
}

int leer_solo_prog(const char *ruta, const char *programa_id, char ***salida_out)
{
#if defined(_WIN32) || defined(__linux__)
    if (salida_out == NULL)
        return 0;

    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
    {
        *salida_out = NULL;
        return 0;
    }

    char **resultado = NULL;
    int encontrados = 0;
    int capacidad = 10;
    resultado = (char **)malloc(capacidad * sizeof(char *));
    if (!resultado)
    {
        free_lineas(lineas, total);
        *salida_out = NULL;
        return 0;
    }

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        if (n <= 2 || strcmp(partes[2], programa_id) != 0)
        {
            free_split(partes);
            continue;
        }

        if (encontrados >= capacidad)
        {
            capacidad *= 2;
            char **temp = (char **)realloc(resultado, capacidad * sizeof(char *));
            if (!temp)
            {
                free_split(partes);
                free_lineas(resultado, encontrados);
                free_lineas(lineas, total);
                *salida_out = NULL;
                return 0;
            }
            resultado = temp;
        }

        resultado[encontrados] = (char *)malloc(strlen(lineas[i]) + 1);
        if (!resultado[encontrados])
        {
            free_split(partes);
            free_lineas(resultado, encontrados);
            free_lineas(lineas, total);
            *salida_out = NULL;
            return 0;
        }
        strcpy(resultado[encontrados], lineas[i]);
        encontrados++;
        free_split(partes);
    }

    free_lineas(lineas, total);
    *salida_out = resultado;
    return encontrados;

#elif defined(__XC)
    (void)ruta;
    (void)programa_id;
    (void)salida_out;
    return 0;

#endif
}

int editar_celda_id_fila_solo_prog(const char *ruta, int id_fila,
                                   int col_editar, const char *nuevo_valor,
                                   const char *programa_id)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return 0;

    if (id_fila < 0 || id_fila >= total)
    {
        free_lineas(lineas, total);
        return 0;
    }

    char **partes = NULL;
    int n = split(lineas[id_fila], GG_caracter_separacion[0], &partes);
    if (n <= 0 || col_editar >= n || (n <= 2 || strcmp(partes[2], programa_id) != 0))
    {
        if (n > 0)
            free_split(partes);
        free_lineas(lineas, total);
        return 0;
    }

    char *nueva_linea = (char *)malloc(8192);
    if (!nueva_linea)
    {
        free_split(partes);
        free_lineas(lineas, total);
        return 0;
    }
    nueva_linea[0] = '\0';

    for (int j = 0; j < n; j++)
    {
        if (j > 0)
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
        const char *celda = (j == col_editar) ? nuevo_valor : partes[j];
        strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
    }

    if (lineas[id_fila])
        free(lineas[id_fila]);
    lineas[id_fila] = nueva_linea;
    free_split(partes);

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);
    return 1;

#elif defined(__XC)
    (void)ruta;
    (void)id_fila;
    (void)col_editar;
    (void)nuevo_valor;
    (void)programa_id;
    return 0;

#endif
}

int incrementa_celda_id_fila_solo_prog(const char *ruta, int id_fila, int col,
                                       double incremento, const char *programa_id)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return 0;

    if (id_fila < 0 || id_fila >= total)
    {
        free_lineas(lineas, total);
        return 0;
    }

    char **partes = NULL;
    int n = split(lineas[id_fila], GG_caracter_separacion[0], &partes);
    if (n <= 0 || col >= n || (n <= 2 || strcmp(partes[2], programa_id) != 0))
    {
        if (n > 0)
            free_split(partes);
        free_lineas(lineas, total);
        return 0;
    }

    double valor_actual = atof(partes[col]);
    char nuevo[64];
    snprintf(nuevo, sizeof(nuevo), "%g", valor_actual + incremento);

    char *nueva_linea = (char *)malloc(8192);
    if (!nueva_linea)
    {
        free_split(partes);
        free_lineas(lineas, total);
        return 0;
    }
    nueva_linea[0] = '\0';

    for (int j = 0; j < n; j++)
    {
        if (j > 0)
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
        const char *celda = (j == col) ? nuevo : partes[j];
        strncat(nueva_linea, celda, 8192 - strlen(nueva_linea) - 1);
    }

    if (lineas[id_fila])
        free(lineas[id_fila]);
    lineas[id_fila] = nueva_linea;
    free_split(partes);

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);
    return 1;

#elif defined(__XC)
    (void)ruta;
    (void)id_fila;
    (void)col;
    (void)incremento;
    (void)programa_id;
    return 0;

#endif
}

void borrar_contenido_excepto_id(const char *ruta, const char *id_fila)
{
#if defined(_WIN32) || defined(__linux__)
    int total = 0;
    char **lineas = leer_archivo(ruta, &total);
    if (lineas == NULL)
        return;

    for (int i = 0; i < total; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], GG_caracter_separacion[0], &partes);
        if (n <= 0)
            continue;

        if (strcmp(partes[0], id_fila) != 0)
        {
            free_split(partes);
            continue;
        }

        char *nueva_linea = (char *)malloc(8192);
        if (!nueva_linea)
        {
            free_split(partes);
            free_lineas(lineas, total);
            return;
        }
        nueva_linea[0] = '\0';

        strncat(nueva_linea, partes[0], 8191);
        for (int j = 1; j < n; j++)
        {
            strncat(nueva_linea, GG_caracter_separacion[0], 8192 - strlen(nueva_linea) - 1);
        }

        if (lineas[i])
            free(lineas[i]);
        lineas[i] = nueva_linea;
        free_split(partes);
    }

    guardar_archivo(ruta, lineas, total);
    free_lineas(lineas, total);

#elif defined(__XC)
    (void)ruta;
    (void)id_fila;

#endif
}
