#ifndef OPERACIONES_TIENDA_H
#define OPERACIONES_TIENDA_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - ../00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 */
#include "../00_cabeceras_del_sistema/var_fun_GG.h" //NECESARIO para COLUMNAS y MAX_PRODUCTOS

/*
 * Uso: Ejecuta leerInventario de forma segura.
 * Entrada ejemplo: leerInventario(inventario, maxProductos)
 */
/*
 * Uso: Ejecuta leerInventario de forma segura.
 * Entrada ejemplo: leerInventario(inventario, maxProductos, dir_espacio)
 */
int leerInventario(char inventario[][COLUMNAS][256], int maxProductos, char *dir_espacio);
/*
 * Uso: Ejecuta guardarInventario de forma segura.
 * Entrada ejemplo: guardarInventario(inventario, n, dir_espacio)
 */
void guardarInventario(char inventario[][COLUMNAS][256], int n, char *dir_espacio);
/*
 * Uso: Ejecuta buscarProducto de forma segura.
 * Entrada ejemplo: buscarProducto(inventario, n, codigo, dir_espacio)
 */
int buscarProducto(char inventario[][COLUMNAS][256], int n, char *codigo, char *dir_espacio);

/*
 * Uso: Ejecuta agregarProducto de forma segura.
 * Entrada ejemplo: agregarProducto(producto, ..., dir_espacio)
 */
void agregarProducto(char *producto, float contenido, char *tipo_medida, float precio_venta, char *cod_barras, float cantidad, float costo_compra, char *proveedor, char *grupo, float cant_x_paquet, char *es_paquete, char *codbar_paquete_e_id, char *cod_bar_individual_es_paq_e_id, char *ligar_prod_sab, char *impuestos, char *ingredientes, char *caducidad, char *ultimo_mov, char *sucur_vent, float claf_prod, char *dir_img_inter, char *dir_img_comp, char *info_extra, char *proceso_crear, char *dir_vid_proc_crear, float tiempo_fabricacion, char *indices_dia_registro_produc_vendido, char *indices_mes_registro_produc_vendido, char *indices_anio_registro_produc_vendido, char *ultima_venta, char *indices_total_registro_produc_vendido, char *dir_espacio);

/*
 * Uso: Ejecuta editarPrecio de forma segura.
 * Entrada ejemplo: editarPrecio(codigo, precio, proveedor, dir_espacio)
 */
int editarPrecio(char *codigo, char *precio, char *proveedor, char *dir_espacio);
/*
 * Uso: Ejecuta venta de forma segura.
 * Entrada ejemplo: venta(codigo, cantidad, sucursal, dir_espacio)
 */
int venta(char *codigo, int cantidad, char *sucursal, char *dir_espacio);
/*
 * Uso: Ejecuta compra de forma segura.
 * Entrada ejemplo: compra(codigo, cantidad, proveedor, dir_espacio)
 */
int compra(char *codigo, int cantidad, char *proveedor, char *dir_espacio);

#endif
