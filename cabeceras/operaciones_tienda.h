#ifndef OPERACIONES_TIENDA_H
#define OPERACIONES_TIENDA_H

#include "var_fun_GG.h"   //NECESARIO para COLUMNAS y MAX_PRODUCTOS

int leerInventario(char inventario[][COLUMNAS][256], int maxProductos);
void guardarInventario(char inventario[][COLUMNAS][256], int n);
int buscarProducto(char inventario[][COLUMNAS][256], int n, const char* codigo);

void agregarProducto(const char* id,const char* producto,const char* contenido,
                     const char* tipo_medida,const char* precio_venta,
                     const char* cod_barras,const char* cantidad,
                     const char* costo_compra,const char* proveedor);

int editarPrecio(const char* codigo,const char* precio,const char* proveedor);
int venta(const char* codigo,int cantidad,const char* sucursal);
int compra(const char* codigo,int cantidad,const char* proveedor);

#endif
