#ifndef OPERACIONES_TIENDA_H
#define OPERACIONES_TIENDA_H

#include "../00_cabeceras_del_sistema/var_fun_GG.h" //NECESARIO para COLUMNAS y MAX_PRODUCTOS

int leerInventario(char inventario[][COLUMNAS][256], int maxProductos);
void guardarInventario(char inventario[][COLUMNAS][256], int n);
int buscarProducto(char inventario[][COLUMNAS][256], int n, char *codigo);

void agregarProducto(int id, char *producto, float contenido,
                     char *tipo_medida, float precio_venta,
                     char *cod_barras, float cantidad,
                     float costo_compra, char *proveedor);

int editarPrecio(char *codigo, char *precio, char *proveedor);
int venta(char *codigo, int cantidad, char *sucursal);
int compra(char *codigo, int cantidad, char *proveedor);
int tienda_consultar_producto(const char *codigo, float *precio_venta, float *stock);

#endif
