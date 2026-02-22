#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"


// Leer inventario completo
void modelo_leerInventario(char* texto)
{
    // texto: "maxProductos"
    int maxProductos = (texto && texto[0]) ? atoi(texto) : MAX_PRODUCTOS;

    // Para solo conexión: crea un inventario local y llama al proceso.
    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    (void)leerInventario(inventario_local, maxProductos);
}

// Guardar inventario
void modelo_guardarInventario(char* texto)
{
    // En el proceso: guardarInventario(inventario, n) requiere inventario[][][]
    // Con solo "texto" no podemos pasar el inventario real todavía.
    // Conexión mínima: no-op funcional (queda para estructura).
    (void)texto;
    // (Aquí se conectará cuando tengas estructura/estado del inventario en modelo o controlador)
}

// Buscar producto
void modelo_buscarProducto(char* texto)
{
    // texto: "codigo"
    if (!texto) return;

    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario_local, MAX_PRODUCTOS);

    (void)buscarProducto(inventario_local, n, texto);
}

// Agregar producto
void modelo_agregarProducto(char* texto)
{
    if (!texto) return;

    char** partes = NULL;
    int n = split(texto, G_caracter_separacion, &partes);
    if (n < 9 || !partes) return;

    agregarProducto(
        partes[0], partes[1], partes[2],
        partes[3], partes[4], partes[5],
        partes[6], partes[7], partes[8]
    );

    modelo_free_split(partes);
}

// Venta simple
void modelo_venta(char* texto)
{
    // texto: "codigo|cantidad|sucursal"
    if (!texto) return;

    char** partes = NULL;
    int n = split(texto, G_caracter_separacion[0], &partes);
    if (n < 3 || !partes) return;

    const char* codigo = partes[0];
    int cantidad = atoi(partes[1]);
    const char* sucursal = partes[2];

    (void)venta(codigo, cantidad, sucursal);

    modelo_free_split(partes);
}

// Compra simple
void modelo_compra(char* texto)
{
    // texto: "codigo|cantidad|proveedor"
    if (!texto) return;

    char** partes = NULL;
    int n = split(texto, G_caracter_separacion[0], &partes);
    if (n < 3 || !partes) return;

    const char* codigo = partes[0];
    int cantidad = atoi(partes[1]);
    const char* proveedor = partes[2];

    (void)compra(codigo, cantidad, proveedor);

    modelo_free_split(partes);
}