#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

/*
 * Convencion de capas:
 * - MODELOS: interpreta el comando, define defaults y decide parametros.
 * - PROCESOS: ejecuta solo con los parametros necesarios.
 * - En tex_bas, MODELOS obtiene "ruta" y se la pasa a PROCESOS.
 */

static int obtener_entero(StructurasDinamicas *datos, int orden, int *salida)
{
    int *ptr = (int *)obtenerValorPorOrden(datos, orden);
    if (!ptr || !salida)
    {
        return -1;
    }
    *salida = *ptr;
    return 0;
}

static int obtener_cadena(StructurasDinamicas *datos, int orden, char **salida)
{
    char *ptr = (char *)obtenerValorPorOrden(datos, orden);
    if (!ptr || !salida)
    {
        return -1;
    }
    *salida = ptr;
    return 0;
}

static int parsear_datos(char *texto, char *nombres_variables[][4], StructurasDinamicas *datos_out, char ***partes_out)
{
    if (!texto || !nombres_variables || !datos_out || !partes_out)
    {
        return -1;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return -2;
    }

    int cantidad = 0;
    while (partes[cantidad])
    {
        cantidad++;
    }
    if (cantidad <= 0)
    {
        modelo_free_split(partes);
        return -3;
    }

    *datos_out = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0]);
    *partes_out = partes;
    return 0;
}

void modelo_crearDirectorio(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    if (obtener_cadena(&datos, 0, &ruta) == 0)
    {
        crearDirectorio(ruta);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_crearArchivo(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"contenido", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    char *contenido = NULL;
    if (obtener_cadena(&datos, 0, &ruta) == 0 && obtener_cadena(&datos, 1, &contenido) == 0)
    {
        crearArchivo(ruta, contenido);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_leer_archivo(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    if (obtener_cadena(&datos, 0, &ruta) == 0)
    {
        char lineas[MAX_LINEAS][MAX_LINEA];
        (void)leer_archivo(ruta, lineas);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_guardar_archivo(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"contenido", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    char *contenido = NULL;
    if (obtener_cadena(&datos, 0, &ruta) == 0 && obtener_cadena(&datos, 1, &contenido) == 0)
    {
        char lineas[MAX_LINEAS][MAX_LINEA];
        int n = 0;

        char **renglones = modelo_split(contenido, G_caracter_separacion[3]);
        if (renglones)
        {
            while (renglones[n] && n < MAX_LINEAS)
            {
                snprintf(lineas[n], MAX_LINEA, "%s", renglones[n]);
                n++;
            }
            modelo_free_split(renglones);
        }

        if (n == 0)
        {
            snprintf(lineas[0], MAX_LINEA, "%s", contenido);
            n = 1;
        }

        guardar_archivo(ruta, lineas, n);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_agregar_fila(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"fila", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    char *fila = NULL;
    if (obtener_cadena(&datos, 0, &ruta) == 0 && obtener_cadena(&datos, 1, &fila) == 0)
    {
        agregar_fila(ruta, fila);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_eliminar_fila(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"fila", "int", "1", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    int fila = 1;
    if (obtener_cadena(&datos, 0, &ruta) == 0 && obtener_entero(&datos, 1, &fila) == 0)
    {
        eliminar_fila(ruta, fila);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_editar_fila(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"fila", "int", "1", ""},
        {"nueva", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    char *nueva = NULL;
    int fila = 1;
    if (obtener_cadena(&datos, 0, &ruta) == 0 && obtener_entero(&datos, 1, &fila) == 0 && obtener_cadena(&datos, 2, &nueva) == 0)
    {
        editar_fila(ruta, fila, nueva);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_editar_celda(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"col_buscar", "int", "0", ""},
        {"valor_buscar", "string", "", ""},
        {"col_editar", "int", "0", ""},
        {"nuevo", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    char *valor_buscar = NULL;
    char *nuevo = NULL;
    int col_buscar = 0;
    int col_editar = 0;

    if (obtener_cadena(&datos, 0, &ruta) == 0 &&
        obtener_entero(&datos, 1, &col_buscar) == 0 &&
        obtener_cadena(&datos, 2, &valor_buscar) == 0 &&
        obtener_entero(&datos, 3, &col_editar) == 0 &&
        obtener_cadena(&datos, 4, &nuevo) == 0)
    {
        editar_celda(ruta, col_buscar, valor_buscar, col_editar, nuevo);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_incrementar_celda(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"col_buscar", "int", "0", ""},
        {"valor_buscar", "string", "", ""},
        {"col_editar", "int", "0", ""},
        {"incremento", "int", "1", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    char *valor_buscar = NULL;
    int col_buscar = 0;
    int col_editar = 0;
    int incremento = 0;

    if (obtener_cadena(&datos, 0, &ruta) == 0 &&
        obtener_entero(&datos, 1, &col_buscar) == 0 &&
        obtener_cadena(&datos, 2, &valor_buscar) == 0 &&
        obtener_entero(&datos, 3, &col_editar) == 0 &&
        obtener_entero(&datos, 4, &incremento) == 0)
    {
        incrementar_celda(ruta, col_buscar, valor_buscar, col_editar, incremento);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_editar_columna_completa(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"col", "int", "0", ""},
        {"nuevo", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    char *nuevo = NULL;
    int col = 0;

    if (obtener_cadena(&datos, 0, &ruta) == 0 &&
        obtener_entero(&datos, 1, &col) == 0 &&
        obtener_cadena(&datos, 2, &nuevo) == 0)
    {
        editar_columna_completa(ruta, col, nuevo);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_eliminar_columna(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"col", "int", "0", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    int col = 0;
    if (obtener_cadena(&datos, 0, &ruta) == 0 && obtener_entero(&datos, 1, &col) == 0)
    {
        eliminar_columna(ruta, col);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}

void modelo_agregar_columna(char *texto)
{
    char *vars[][4] = {
        {"ruta", "string", "", ""},
        {"nombre", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear_datos(texto, vars, &datos, &partes) != 0)
    {
        return;
    }

    char *ruta = NULL;
    char *nombre = NULL;
    if (obtener_cadena(&datos, 0, &ruta) == 0 && obtener_cadena(&datos, 1, &nombre) == 0)
    {
        agregar_columna(ruta, nombre);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
}
