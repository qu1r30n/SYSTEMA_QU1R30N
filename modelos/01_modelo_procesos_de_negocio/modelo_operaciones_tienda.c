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
#include "../../cabeceras/codigos_retorno.h"

/* las cabeceras de procesos que se invocan */
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

// char **G_caracter_separacion = GG_caracter_separacion;//dice que ya no por que ya fue definido en el main

/* Helper reutilizable: parsea `texto` usando el separador indicado (índice)
   y devuelve el array `parts`. Las conversiones seguras a entero/float se
   realizan con `texto_a_int_seguro` / `texto_a_float_seguro` de
   `operaciones_textos.c`. El array retornado debe liberarse con
   `modelo_free_split(parts)` cuando ya no se necesite. */
static char **modelo_parse_split(char *texto, int sep_index)
{
    if (texto == NULL)
        return NULL;
    char **parts = NULL;
    int n = split(texto, G_caracter_separacion_funciones_espesificas[sep_index], &parts);
    (void)n; /* el llamador valida la cantidad */
    return parts;
}

// Leer inventario completo
int modelo_leerInventario(char *texto)
{
    // texto: "maxProductos"
    int maxProductos = (texto && texto[0]) ? atoi(texto) : MAX_PRODUCTOS;

    // Para solo conexión: crea un inventario local y llama al proceso.
    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int cantidad = leerInventario(inventario_local, maxProductos);
    return cantidad;
}

// Guardar inventario
void modelo_guardarInventario(char *texto)
{
    // En el proceso: guardarInventario(inventario, n) requiere inventario[][][]
    // Con solo "texto" no podemos pasar el inventario real todavía.
    // Conexión mínima: no-op funcional (queda para estructura).
    (void)texto;
    // (Aquí se conectará cuando tengas estructura/estado del inventario en modelo o controlador)
}

// Buscar producto
int modelo_buscarProducto(char *texto)
{
    // texto: "codigo"
    if (!texto)
        return -1;

    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario_local, MAX_PRODUCTOS);

    return buscarProducto(inventario_local, n, texto);
}

// Agregar producto
void modelo_agregarProducto(char *texto)
{
    if (!texto)
        return;

    /* parsear parámetros: direccion, fila, editar_info, etc. */
    char **partes = modelo_parse_split(texto, 2);
    if (!partes)
        return;
    int n = 0;
    while (partes[n])
        n++;
    if (n < 9)
    {
        modelo_free_split(partes);
        return;
    }

    agregarProducto(
        partes[0], partes[1], partes[2],
        partes[3], partes[4], partes[5],
        partes[6], partes[7], partes[8]);

    modelo_free_split(partes);
}

// Venta simple
int modelo_venta(char *texto)
{
    // texto: "codigo|cantidad|sucursal"
    if (!texto)
        return RET_INVALID_ARG;

    char **partes = modelo_parse_split(texto, 0);
    int n = 0;
    if (partes)
    {
        while (partes[n])
            n++;
    }
    if (n < 3 || !partes)
    {
        if (partes)
            modelo_free_split(partes);
        return RET_INVALID_ARG;
    }

    const char *codigo = partes[0];
    int cantidad = 0;
    if (texto_a_int_seguro(partes[1], &cantidad) != RET_OK)
        cantidad = atoi(partes[1]);
    const char *sucursal = partes[2];

    int ok = venta(codigo, cantidad, sucursal);

    modelo_free_split(partes);
    return ok;
}

// Compra simple
int modelo_compra(char *texto)
{
    // texto: "codigo|cantidad|proveedor"
    if (!texto)
        return RET_INVALID_ARG;

    char **partes = NULL;
    int n = split(texto, G_caracter_separacion_funciones_espesificas[0], &partes);
    if (n < 3 || !partes)
        return RET_INVALID_ARG;

    const char *codigo = partes[0];
    int cantidad = atoi(partes[1]);
    const char *proveedor = partes[2];

    int ok = compra(codigo, cantidad, proveedor);

    modelo_free_split(partes);
    return ok;
}
