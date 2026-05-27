#ifndef OPERACIONES_TIENDA_H
#define OPERACIONES_TIENDA_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - ../00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 */
#include "../00_cabeceras_del_sistema/var_fun_GG.h" //NECESARIO para COLUMNAS y MAX_PRODUCTOS

/*
 * Uso: Ejecuta leerInventario de forma segura.
 * Entrada ejemplo: leerInventario(&retorno_inventario, dir_espacio)
 * retorno_inventario: salida en texto con el inventario completo del archivo.
 */
int leerInventario(char **retorno_inventario, char *dir_espacio);
/*
 * Uso: Ejecuta liberarInventario de forma segura.
 * Entrada ejemplo: liberarInventario(inventario, n)
 */
void liberarInventario(char ***inventario, int n);
/*
 * Uso: Ejecuta guardarInventario de forma segura.
 * Entrada ejemplo: guardarInventario(inventario, n, dir_espacio)
 */
void guardarInventario(char ***inventario, int n, char *dir_espacio);
/*
 * Uso: Ejecuta hacerInventario de forma segura.
 * Entrada ejemplo: hacerInventario(inv_a_checar, &retorno_inv_revisado, dir_espacio)
 * inv_a_checar: lista "codigo⛪cantidad⊔codigo⛪cantidad".
 * retorno_inv_revisado: salida "codigo⛪delta|no_se_checo⊔...".
 */
int hacerInventario(char *inv_a_checar, char **retorno_inv_revisado, char *dir_espacio);
/*
 * Uso: Ejecuta buscarProducto de forma segura.
 * Entrada ejemplo: buscarProducto(inventario, n, codigo, dir_espacio)
 */
int buscarProducto(char ***inventario, int n, char *codigo, char *dir_espacio);

/*
 * Uso: Ejecuta agregarProducto de forma segura.
 * Entrada ejemplo: agregarProducto(producto, ..., dir_espacio)
 */
void agregarProducto(char *producto, float contenido, char *tipo_medida, float precio_venta, char *cod_barras, float cantidad, float costo_compra, char *proveedor, char *grupo, float cant_x_paquet, char *es_paquete, char *codbar_paquete_e_id, char *cod_bar_individual_es_paq_e_id, char *ligar_prod_sab, char *impuestos, char *ingredientes, char *caducidad, char *ultimo_mov, char *sucur_vent, float claf_prod, char *dir_img_inter, char *dir_img_comp, char *info_extra, char *proceso_crear, char *dir_vid_proc_crear, float tiempo_fabricacion, char *indices_dia_registro_produc_vendido, char *indices_mes_registro_produc_vendido, char *indices_anio_registro_produc_vendido, char *ultima_venta, char *indices_total_registro_produc_vendido, char *dir_espacio);

/*
 * Uso: Ejecuta editarPrecio de forma segura.
 * Entrada ejemplo: editarPrecio(codigo, precio, proveedor, id, dir_espacio)
 * id: si no es NULL ni vacio, verifica que el registro con ese id tenga el mismo codigo;
 *     si coincide se usa directo; si no, se cae a busqueda por codigo de barras.
 */
int editarPrecio(char *codigo, char *precio, char *proveedor, char *id, char *dir_espacio);
/*
 * Uso: Ejecuta venta de forma segura.
 * Entrada ejemplo: venta(codigo, cantidad, sucursal, id, dir_espacio)
 * id: si no es NULL ni vacio, verifica que el registro con ese id tenga el mismo codigo;
 *     si coincide se usa directo; si no, se cae a busqueda por codigo de barras.
 */
int venta(char *codigo, float cantidad, char *sucursal, char *id, char *dir_espacio);
/*
 * Uso: Ejecuta compra de forma segura.
 * Entrada ejemplo: compra(codigo, cantidad, sucursal, id, dir_espacio)
 * id: si no es NULL ni vacio, verifica que el registro con ese id tenga el mismo codigo;
 *     si coincide se usa directo; si no, se cae a busqueda por codigo de barras.
 */
int compra(char *codigo, float cantidad, char *sucursal, char *id, char *dir_espacio);

#endif
