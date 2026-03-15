#ifndef OPERACIONES_TIENDA_H
#define OPERACIONES_TIENDA_H

#include "../00_cabeceras_del_sistema/var_fun_GG.h" //NECESARIO para COLUMNAS y MAX_PRODUCTOS

int leerInventario(char inventario[][COLUMNAS][256], int maxProductos);
void guardarInventario(char inventario[][COLUMNAS][256], int n);
int buscarProducto(char inventario[][COLUMNAS][256], int n, char *codigo);

void agregarProducto(
    char *producto,
    float contenido,
    char *tipo_medida,
    float precio_venta,
    char *cod_barras,
    float cantidad,
    float costo_compra,
    char *proveedor,
    char *grupo,
    float cant_x_paquet,
    char *es_paquete,
    char *codbar_paquete_e_id,
    char *cod_bar_individual_es_paq_e_id,
    char *ligar_prod_sab,
    char *impuestos,
    char *ingredientes,
    char *caducidad,
    char *ultimo_mov,
    char *sucur_vent,
    float claf_prod,
    char *dir_img_inter,
    char *dir_img_comp,
    char *info_extra,
    char *proceso_crear,
    char *dir_vid_proc_crear,
    float tiempo_fabricacion,
    char *indices_dia_registro_produc_vendido,
    char *indices_mes_registro_produc_vendido,
    char *indices_anio_registro_produc_vendido,
    char *ultima_venta,
    char *indices_total_registro_produc_vendido,
    char *no_poner_nada);

int editarPrecio(char *codigo, char *precio, char *proveedor);
int venta(char *codigo, int cantidad, char *sucursal);
int compra(char *codigo, int cantidad, char *proveedor);

#endif
