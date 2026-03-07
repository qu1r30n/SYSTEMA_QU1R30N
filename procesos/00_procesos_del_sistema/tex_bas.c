#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int total_columnas_objetivo(int columnas_actuales, int columna_minima)
{
    if (columna_minima + 1 > columnas_actuales)
    {
        return columna_minima + 1;
    }
    return columnas_actuales;
}

static void construir_linea_desde_partes(char *destino, size_t tam_destino,
                                         char **partes, int columnas,
                                         const char *valor_defecto)
{
    const char *separador = G_caracter_separacion[0];
    destino[0] = '\0';

    for (int i = 0; i < columnas; i++)
    {
        const char *valor = valor_defecto;
        if (partes && partes[i] != NULL)
        {
            valor = partes[i];
        }

        size_t usados = strlen(destino);
        if (usados + 1 >= tam_destino)
        {
            break;
        }

        snprintf(destino + usados, tam_destino - usados, "%s%s", (i == 0) ? "" : separador, valor ? valor : "");
    }
}

// Crear directorio
void crearDirectorio(const char *ruta)
{
#if defined(_WIN32) || defined(__linux__)
    char tmp[512];
    strcpy(tmp, ruta);

    char *p =
#ifdef _WIN32 // si windows
        strrchr(tmp, '\\');
#else // si es linux o otro
        strrchr(tmp, '/');
#endif

    if (p)
    {
        *p = 0;

#ifdef _WIN32 // si windows
        mkdir(tmp);
#else // si es linux o otro
        mkdir(tmp, 0777);
#endif
    }

#elif defined(__XC)
    /* PIC16F: Sin sistema de archivos. No se crea nada. */
    (void)ruta;

#endif
}

// Crear archivo
void crearArchivo(const char *ruta, const char *cabecera)
{
#if defined(_WIN32) || defined(__linux__)
    crearDirectorio(ruta);
    FILE *f = fopen(ruta, "r");
    if (!f)
    {
        f = fopen(ruta, "w");
        if (f && cabecera)
        {
            fprintf(f, "%s\n", cabecera);
        }
    }
    if (f)
    {
        fclose(f);
    }

#elif defined(__XC)
    (void)ruta;
    (void)cabecera;

#endif
}

// Leer archivo
int leer_archivo(const char *ruta, char l[][MAX_LINEA])
{
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "r");
    if (!f)
    {
        return 0;
    }
    int n = 0;
    while (fgets(l[n], MAX_LINEA, f))
    {
        l[n][strcspn(l[n], "\n")] = 0;
        n++;
    }
    fclose(f);
    return n;

#elif defined(__XC)
    (void)ruta;
    (void)l;
    return 0;

#endif
}

// Guardar archivo
void guardar_archivo(const char *ruta, char l[][MAX_LINEA], int n)
{
#if defined(_WIN32) || defined(__linux__)
    FILE *f = fopen(ruta, "w");
    for (int i = 0; i < n; i++)
        fprintf(f, "%s\n", l[i]);
    fclose(f);

#elif defined(__XC)
    (void)ruta;
    (void)l;
    (void)n;

#endif
}

// Agregar fila
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

void eliminar_fila(const char *ruta, int filaEliminar)
{
#if defined(_WIN32) || defined(__linux__)
    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta, lineas);
    if (n <= 0 || filaEliminar <= 0 || filaEliminar >= n)
    {
        return;
    }

    for (int i = filaEliminar; i < n - 1; i++)
    {
        strcpy(lineas[i], lineas[i + 1]);
    }
    guardar_archivo(ruta, lineas, n - 1);

#elif defined(__XC)
    (void)ruta;
    (void)filaEliminar;

#endif
}

void editar_fila(const char *ruta, int fila, const char *nueva)
{
#if defined(_WIN32) || defined(__linux__)
    if (!nueva)
    {
        return;
    }

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta, lineas);
    if (n <= 0 || fila <= 0 || fila >= n)
    {
        return;
    }

    snprintf(lineas[fila], MAX_LINEA, "%s", nueva);
    guardar_archivo(ruta, lineas, n);

#elif defined(__XC)
    (void)ruta;
    (void)fila;
    (void)nueva;

#endif
}

void editar_celda(const char *ruta, int colBuscar, const char *valorBuscar,
                  int colEditar, const char *nuevoValor)
{
#if defined(_WIN32) || defined(__linux__)
    if (!valorBuscar || !nuevoValor || colBuscar < 0 || colEditar < 0)
    {
        return;
    }

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta, lineas);
    if (n <= 1)
    {
        return;
    }

    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int columnas = split(lineas[i], G_caracter_separacion[0], &partes);
        if (columnas <= 0)
        {
            continue;
        }

        if (colBuscar < columnas && partes[colBuscar] && strcmp(partes[colBuscar], valorBuscar) == 0)
        {
            int columnas_finales = total_columnas_objetivo(columnas, colEditar);
            char *partes_ext[MAX_LINEA] = {0};

            for (int c = 0; c < columnas_finales; c++)
            {
                if (c < columnas)
                {
                    partes_ext[c] = partes[c];
                }
                else
                {
                    partes_ext[c] = "";
                }
            }
            partes_ext[colEditar] = (char *)nuevoValor;

            construir_linea_desde_partes(lineas[i], MAX_LINEA, partes_ext, columnas_finales, "");
            free_split(partes);
            guardar_archivo(ruta, lineas, n);
            return;
        }

        free_split(partes);
    }

#elif defined(__XC)
    (void)ruta;
    (void)colBuscar;
    (void)valorBuscar;
    (void)colEditar;
    (void)nuevoValor;

#endif
}

void incrementar_celda(const char *ruta, int colBuscar, const char *valorBuscar,
                       int colEditar, int inc)
{
#if defined(_WIN32) || defined(__linux__)
    if (!valorBuscar || colBuscar < 0 || colEditar < 0)
    {
        return;
    }

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta, lineas);
    if (n <= 1)
    {
        return;
    }

    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int columnas = split(lineas[i], G_caracter_separacion[0], &partes);
        if (columnas <= 0)
        {
            continue;
        }

        if (colBuscar < columnas && partes[colBuscar] && strcmp(partes[colBuscar], valorBuscar) == 0)
        {
            int columnas_finales = total_columnas_objetivo(columnas, colEditar);
            char *partes_ext[MAX_LINEA] = {0};
            char valor_inc[64];

            for (int c = 0; c < columnas_finales; c++)
            {
                if (c < columnas)
                {
                    partes_ext[c] = partes[c];
                }
                else
                {
                    partes_ext[c] = "0";
                }
            }

            int actual = (colEditar < columnas && partes[colEditar]) ? atoi(partes[colEditar]) : 0;
            snprintf(valor_inc, sizeof(valor_inc), "%d", actual + inc);
            partes_ext[colEditar] = valor_inc;

            construir_linea_desde_partes(lineas[i], MAX_LINEA, partes_ext, columnas_finales, "0");
            free_split(partes);
            guardar_archivo(ruta, lineas, n);
            return;
        }

        free_split(partes);
    }

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
    if (col < 0 || !nuevo)
    {
        return;
    }

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta, lineas);
    if (n <= 0)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        char **partes = NULL;
        int columnas = split(lineas[i], G_caracter_separacion[0], &partes);
        if (columnas <= 0)
        {
            continue;
        }

        int columnas_finales = total_columnas_objetivo(columnas, col);
        char *partes_ext[MAX_LINEA] = {0};
        for (int c = 0; c < columnas_finales; c++)
        {
            if (c < columnas)
            {
                partes_ext[c] = partes[c];
            }
            else
            {
                partes_ext[c] = "";
            }
        }
        partes_ext[col] = (char *)nuevo;

        construir_linea_desde_partes(lineas[i], MAX_LINEA, partes_ext, columnas_finales, "");
        free_split(partes);
    }

    guardar_archivo(ruta, lineas, n);

#elif defined(__XC)
    (void)ruta;
    (void)col;
    (void)nuevo;

#endif
}

void eliminar_columna(const char *ruta, int col)
{
#if defined(_WIN32) || defined(__linux__)
    if (col < 0)
    {
        return;
    }

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta, lineas);
    if (n <= 0)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        char **partes = NULL;
        int columnas = split(lineas[i], G_caracter_separacion[0], &partes);
        if (columnas <= 1 || col >= columnas)
        {
            if (partes)
            {
                free_split(partes);
            }
            continue;
        }

        char *partes_filtradas[MAX_LINEA] = {0};
        int k = 0;
        for (int c = 0; c < columnas; c++)
        {
            if (c == col)
            {
                continue;
            }
            partes_filtradas[k++] = partes[c];
        }

        construir_linea_desde_partes(lineas[i], MAX_LINEA, partes_filtradas, k, "");
        free_split(partes);
    }

    guardar_archivo(ruta, lineas, n);

#elif defined(__XC)
    (void)ruta;
    (void)col;

#endif
}

void agregar_columna(const char *ruta, const char *nombre)
{
#if defined(_WIN32) || defined(__linux__)
    if (!nombre)
    {
        return;
    }

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta, lineas);
    if (n <= 0)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        const char *valor_nuevo = (i == 0) ? nombre : "0";
        size_t usados = strlen(lineas[i]);
        const char *sep = G_caracter_separacion[0];

        if (usados < MAX_LINEA - 1)
        {
            strncat(lineas[i], sep, MAX_LINEA - 1 - usados);
            usados = strlen(lineas[i]);
        }
        if (usados < MAX_LINEA - 1)
        {
            strncat(lineas[i], valor_nuevo, MAX_LINEA - 1 - usados);
        }
    }

    guardar_archivo(ruta, lineas, n);

#elif defined(__XC)
    (void)ruta;
    (void)nombre;

#endif
}
