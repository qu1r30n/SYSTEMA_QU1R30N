#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <stdlib.h>

#elif defined(__linux__)
#include <stdlib.h>

#elif defined(__XC)
#define _XTAL_FREQ 4000000
#include <xc.h>
/* PIC16F: Sin malloc. Las funciones son stubs. */

#else
#include <stdlib.h>
#endif

/* prototipos del modelo para validar firmas y ajustar retornos */
#include "../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"
#include "../../CLASE_QU1R30N.h"
/* usar el split del modelo de textos */
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"

/* las cabeceras de procesos que se invocan */
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"

// char **G_caracter_separacion = GG_caracter_separacion;//dice que ya no por que ya fue definido en el main

// Leer inventario completo
int modelo_leerInventario(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"maxProductos", "int", "0", ""},
            {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return -2;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0]);

    if (cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -3;
    }

    // texto: "maxProductos"
    int maxProductos = *(int *)obtenerValorPorOrden(&datos, 0);

    // Para solo conexión: crea un inventario local y llama al proceso.
    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int cantidad = leerInventario(inventario_local, maxProductos);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return cantidad;
}

// Guardar inventario
void modelo_guardarInventario(char *texto)
{
    // En el proceso: guardarInventario(inventario, cuantas_partes) requiere inventario[][][]
    // Con solo "texto" no podemos pasar el inventario real todavía.
    // Conexión mínima: no-op funcional (queda para estructura).
    (void)texto;
    // (Aquí se conectará cuando tengas estructura/estado del inventario en modelo o controlador)
}

// Buscar producto
int modelo_buscarProducto(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"codigo", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return -2;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0]);

    if (cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -3;
    }

    // texto: "codigo"
    char *codigo = (char *)obtenerValorPorOrden(&datos, 0);

    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int cantidad = leerInventario(inventario_local, MAX_PRODUCTOS);

    int resultado = buscarProducto(inventario_local, cantidad, codigo);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return resultado;
}

// Agregar producto
int modelo_agregarProducto(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"id", "int", "0", ""},
            {"producto", "string", "nose", ""},
            {"contenido", "float", "0", ""},
            {"tipo_medida", "string", "nose", ""},
            {"precio_venta", "float", "0", ""},
            {"cod_barras", "string", "nose", ""},
            {"cantidad", "float", "0", ""},
            {"costo_compra", "float", "0", ""},
            {"proveedor", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return -2;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0]);

    if (cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -3;
    }

    int a1 = *(int *)obtenerValorPorOrden(&datos, 0);
    char *b1 = (char *)obtenerValorPorOrden(&datos, 1);
    float c1 = *(float *)obtenerValorPorOrden(&datos, 2);
    char *d1 = (char *)obtenerValorPorOrden(&datos, 3);
    float e1 = *(float *)obtenerValorPorOrden(&datos, 4);
    char *f1 = (char *)obtenerValorPorOrden(&datos, 5);
    float g1 = *(float *)obtenerValorPorOrden(&datos, 6);
    float h1 = *(float *)obtenerValorPorOrden(&datos, 7);
    char *i1 = (char *)obtenerValorPorOrden(&datos, 8);

    printf("a1 (int): %d\n", a1);
    printf("b1 (string): %s\n", b1);
    printf("c1 (float): %.2f\n", c1);
    printf("d1 (string): %s\n", d1);
    printf("e1 (float): %.2f\n", e1);
    printf("f1 (string): %s\n", f1);
    printf("g1 (float): %.2f\n", g1);
    printf("h1 (float): %.2f\n", h1);
    printf("i1 (string): %s\n", i1);

    agregarProducto(
        a1,
        b1,
        c1,
        d1,
        e1,
        f1,
        g1,
        h1,
        i1);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return 0;
}

// Venta simple
int modelo_venta(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"codigo", "string", "nose", ""},
            {"cantidad", "int", "0", ""},
            {"sucursal", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return -2;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0]);

    if (cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -3;
    }

    // texto: "codigo|cantidad|sucursal"
    char *codigo = (char *)obtenerValorPorOrden(&datos, 0);
    int cantidad = *(int *)obtenerValorPorOrden(&datos, 1);
    char *sucursal = (char *)obtenerValorPorOrden(&datos, 2);

    int ok = venta(codigo, cantidad, sucursal);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

// Compra simple
int modelo_compra(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"codigo", "string", "nose", ""},
            {"cantidad", "int", "0", ""},
            {"proveedor", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        return -2;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0]);

    if (cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -3;
    }

    // texto: "codigo|cantidad|proveedor"
    char *codigo = (char *)obtenerValorPorOrden(&datos, 0);
    int cantidad = *(int *)obtenerValorPorOrden(&datos, 1);
    char *proveedor = (char *)obtenerValorPorOrden(&datos, 2);

    int ok = compra(codigo, cantidad, proveedor);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}
