#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

// Leer inventario
int leerInventario(char inventario[][COLUMNAS][256], int maxProductos)
{
    return 0;
}

// Guardar inventario
void guardarInventario(char inventario[][COLUMNAS][256], int n)
{
}

// Buscar producto
int buscarProducto(char inventario[][COLUMNAS][256], int n, char *codigo)
{
    return -1;
}

// Agregar producto
void agregarProducto(int id,
                     char *producto,
                     float contenido,
                     char *tipo_medida,
                     float precio_venta,
                     char *cod_barras,
                     float cantidad,
                     float costo_compra,
                     char *proveedor)
{
    printf("ENTRO A agregarProducto\n");
}

// Venta
int venta(char *codigo, int cantidad, char *sucursal)
{
    return 0;
}

// Compra
int compra(char *codigo, int cantidad, char *proveedor)
{
    return 0;
}