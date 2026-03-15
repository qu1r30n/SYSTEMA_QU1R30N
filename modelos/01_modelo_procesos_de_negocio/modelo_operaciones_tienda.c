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

// char **G_caracter_separacion = G_caracter_separacion;//dice que ya no por que ya fue definido en el main

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

    StructurasDinamicas datos = crearStructuraVacia();
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return (ret_parse < 0) ? ret_parse : -3;
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

    StructurasDinamicas datos = crearStructuraVacia();
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return (ret_parse < 0) ? ret_parse : -3;
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
    if (!texto) // Verifica si el texto es NULL
    {
        return -1;
    }

    char *nombres_variables[][4] = // Arreglo de campos esperados con su tipo y valor por defecto
        {
            {"producto", "string", "NOSE", ""},
            {"contenido", "float", "-0", ""},
            {"tipo_medida", "string", "NOSE", ""},
            {"precio_venta", "float", "-0", ""},
            {"cod_barras", "string", "NOSE", ""},
            {"cantidad", "float", "-0", ""},
            {"costo_comp", "float", "-0", ""},
            {"provedor", "string", "NOSE¬0", ""},
            {"grupo", "string", "PRODUCTO_PIEZA", ""},
            {"cant_x_paquet", "float", "-0", ""},
            {"es_paquete", "string", "INDIVIDUAL", ""},
            {"codbar_paquete_e_id", "string", "NOSE_2", ""},
            {"cod_bar_individual_es_paq_e_id", "string", "NOSE_3¬1", ""},
            {"ligar_prod_sab", "string", "NOSE", ""},
            {"impuestos", "string", "NOSE", ""},
            {"ingredientes", "string", "NOSE", ""},
            {"caducidad", "string", "-0", ""},
            {"ultimo_mov", "string", "-0", ""},
            {"sucur_vent", "string", "NOSE¬0", ""},
            {"claf_prod", "float", "-0", ""},
            {"dir_img_inter", "string", "NOSE", ""},
            {"dir_img_comp", "string", "NOSE", ""},
            {"info_extra", "string", "NOSE", ""},
            {"proceso_crear", "string", "NOSE", ""},
            {"dir_vid_proc_crear", "string", "NOSE", ""},
            {"tiempo_fabricacion", "float", "-0", ""},
            {"indices_dia_registro_produc_vendido", "string", "0", ""},
            {"indices_mes_registro_produc_vendido", "string", "0", ""},
            {"indices_anio_registro_produc_vendido", "string", "0", ""},
            {"ultima_venta", "string", "", ""},
            {"indices_total_registro_produc_vendido", "string", "0", ""},
            {"no_poner_nada", "string", "", ""},
            {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0]) // Cuenta cuántos campos hay en el arreglo de nombres_variables
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[2]);
    if (!partes)
    {
        return -2;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes]) // Cuenta cuántas partes del texto que se reccibio en el parametro hay en el arreglo de partes
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = crearStructuraVacia();
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return (ret_parse < 0) ? ret_parse : -3;
    }

    agregarProducto(
        (char *)obtenerValorPorOrden(&datos, 0),
        *(float *)obtenerValorPorOrden(&datos, 1),
        (char *)obtenerValorPorOrden(&datos, 2),
        *(float *)obtenerValorPorOrden(&datos, 3),
        (char *)obtenerValorPorOrden(&datos, 4),
        *(float *)obtenerValorPorOrden(&datos, 5),
        *(float *)obtenerValorPorOrden(&datos, 6),
        (char *)obtenerValorPorOrden(&datos, 7),
        (char *)obtenerValorPorOrden(&datos, 8),
        *(float *)obtenerValorPorOrden(&datos, 9),
        (char *)obtenerValorPorOrden(&datos, 10),
        (char *)obtenerValorPorOrden(&datos, 11),
        (char *)obtenerValorPorOrden(&datos, 12),
        (char *)obtenerValorPorOrden(&datos, 13),
        (char *)obtenerValorPorOrden(&datos, 14),
        (char *)obtenerValorPorOrden(&datos, 15),
        (char *)obtenerValorPorOrden(&datos, 16),
        (char *)obtenerValorPorOrden(&datos, 17),
        (char *)obtenerValorPorOrden(&datos, 18),
        *(float *)obtenerValorPorOrden(&datos, 19),
        (char *)obtenerValorPorOrden(&datos, 20),
        (char *)obtenerValorPorOrden(&datos, 21),
        (char *)obtenerValorPorOrden(&datos, 22),
        (char *)obtenerValorPorOrden(&datos, 23),
        (char *)obtenerValorPorOrden(&datos, 24),
        *(float *)obtenerValorPorOrden(&datos, 25),
        (char *)obtenerValorPorOrden(&datos, 26),
        (char *)obtenerValorPorOrden(&datos, 27),
        (char *)obtenerValorPorOrden(&datos, 28),
        (char *)obtenerValorPorOrden(&datos, 29),
        (char *)obtenerValorPorOrden(&datos, 30),
        (char *)obtenerValorPorOrden(&datos, 31));

    modelo_free_split(partes); // Libera la memoria del arreglo de partes
    liberarStructura(&datos);  // Libera la memoria de la estructura dinámica
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

    StructurasDinamicas datos = crearStructuraVacia();
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[2], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return (ret_parse < 0) ? ret_parse : -3;
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

    StructurasDinamicas datos = crearStructuraVacia();
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return (ret_parse < 0) ? ret_parse : -3;
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
