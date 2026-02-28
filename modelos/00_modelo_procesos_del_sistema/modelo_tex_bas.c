#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <stdlib.h>
#include <sys/stat.h>
#include <direct.h>

#elif defined(__linux__)
#include <stdlib.h>
#include <sys/stat.h>

#elif defined(__XC)
#define _XTAL_FREQ 4000000
#include <xc.h>
/* PIC16F: Sin archivos. Las funciones son stubs. */

#else
#include <stdlib.h>
#include <sys/stat.h>
#endif

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"

/* ===== MODELO DE PROCESOS DEL SISTEMA: OPERACIONES DE TEXTOS ===== */
// Crear directorio
void modelo_crearDirectorio(char *texto)
{
    char **texto_espliteado = modelo_split(texto, G_caracter_separacion_funciones_espesificas[0]);
    if (texto_espliteado && texto_espliteado[0])
    {
        crearDirectorio(texto_espliteado[0]);
    }
    free_split(texto_espliteado);
}

// Crear archivo
void modelo_crearArchivo(char *texto)
{
    char **texto_espliteado = modelo_split(texto, G_caracter_separacion_funciones_espesificas[0]);

    crearArchivo(texto_espliteado[0], texto_espliteado[1]);
    free_split(texto_espliteado);
}

// Leer archivo
void modelo_leer_archivo(char *texto)
{
    char **texto_espliteado = modelo_split(texto, G_caracter_separacion_funciones_espesificas[0]);
    if (texto_espliteado && texto_espliteado[0])
    {
        char lineas[MAX_LINEAS][MAX_LINEA];
        leer_archivo(texto_espliteado[0], lineas);
    }
    free_split(texto_espliteado);
}

// Guardar archivo
void modelo_guardar_archivo(char *texto)
{
    char **texto_espliteado = modelo_split(texto, G_caracter_separacion_funciones_espesificas[0]);
    if (texto_espliteado && texto_espliteado[0])
    {
        char lineas[MAX_LINEAS][MAX_LINEA];
        guardar_archivo(texto_espliteado[0], lineas, 0);
    }
    free_split(texto_espliteado);
}

// Agregar fila
void modelo_agregar_fila(char *texto)
{
    char **texto_espliteado = modelo_split(texto, G_caracter_separacion_funciones_espesificas[0]);
    if (texto_espliteado && texto_espliteado[0])
    {
        agregar_fila(texto_espliteado[0], texto_espliteado[1]);
    }
    free_split(texto_espliteado);
}
