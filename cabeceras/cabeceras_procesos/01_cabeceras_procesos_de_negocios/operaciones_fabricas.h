#ifndef OPERACIONES_FABRICAS_H
#define OPERACIONES_FABRICAS_H

int fabrica_registrar_producto(const char *codigo, const char *nombre, float costo_unitario, int stock);
int fabrica_producir_lote(const char *codigo, int cantidad, const char *responsable);
int fabrica_despachar_producto(const char *codigo, int cantidad, const char *destino);
int fabrica_consultar_producto(const char *codigo, float *costo_unitario, int *stock);
int fabrica_buscar_producto_en_archivo(const char *ruta_inventario,
                                       const char *codigo,
                                       char **fila_producto);

#endif
