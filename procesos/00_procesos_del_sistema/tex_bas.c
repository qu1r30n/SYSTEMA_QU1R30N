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
