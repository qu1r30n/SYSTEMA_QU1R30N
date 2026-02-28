#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* prototipos del modelo para validar firmas y ajustar retornos */
#include "../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"

/* las cabeceras de procesos que se invocan */
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

static const char** G_caracter_separacion = GG_caracter_separacion;
static const char* (*G_archivos)[2] = GG_archivos;
static const char* (*G_archivos_registros)[2] = GG_archivos_registros;



// Leer inventario completo
int modelo_leerInventario(char* texto)
{
    // texto: "maxProductos"
    int maxProductos = (texto && texto[0]) ? atoi(texto) : MAX_PRODUCTOS;

    // Para solo conexión: crea un inventario local y llama al proceso.
    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int cantidad = leerInventario(inventario_local, MAX_PRODUCTOS);
    return cantidad;
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
int modelo_buscarProducto(char* texto)
{
    // texto: "codigo"
    if (!texto) return -1;

    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario_local, MAX_PRODUCTOS);

    return buscarProducto(inventario_local, n, texto);
}

// Agregar producto
void modelo_agregarProducto(char* texto)
{
    if (!texto) return;

    char** partes = NULL;
    int n = split(texto, G_caracter_separacion[0], &partes);
    if (n < 9 || !partes) return;

    agregarProducto(
        partes[0], partes[1], partes[2],
        partes[3], partes[4], partes[5],
        partes[6], partes[7], partes[8]
    );

    modelo_free_split(partes);
}

// Venta simple
int modelo_venta(char* texto)
{
    // texto: "codigo|cantidad|sucursal"
    if (!texto) return 0;

    char** partes = NULL;
    int n = split(texto, G_caracter_separacion[0], &partes);
    if (n < 3 || !partes) return 0;

    const char* codigo = partes[0];
    int cantidad = atoi(partes[1]);
    const char* sucursal = partes[2];

    int ok = venta(codigo, cantidad, sucursal);

    modelo_free_split(partes);
    return ok;
}

// Compra simple
int modelo_compra(char* texto)
{
    // texto: "codigo|cantidad|proveedor"
    if (!texto) return 0;

    char** partes = NULL;
    int n = split(texto, G_caracter_separacion[0], &partes);
    if (n < 3 || !partes) return 0;

    const char* codigo = partes[0];
    int cantidad = atoi(partes[1]);
    const char* proveedor = partes[2];

    int ok = compra(codigo, cantidad, proveedor);

    modelo_free_split(partes);
    return ok;
}

