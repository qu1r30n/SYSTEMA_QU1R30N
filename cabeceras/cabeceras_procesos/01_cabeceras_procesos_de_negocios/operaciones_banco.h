#ifndef OPERACIONES_BANCO_H
#define OPERACIONES_BANCO_H

int banco_registrar_cuenta(const char *cuenta, const char *titular, float saldo_inicial);
int banco_depositar(const char *cuenta, float monto);
int banco_retirar(const char *cuenta, float monto, const char *motivo);
int banco_consultar_saldo(const char *cuenta, float *saldo);

/* Inventario de servicios bancarios (ejemplo: PRESTAMO, TARJETA, SEGURO) */
int banco_registrar_producto_servicio(const char *codigo,
                                      const char *producto_servicio,
                                      const char *tipo,
                                      float precio_referencia);
int banco_buscar_producto_en_archivo(const char *ruta_inventario,
                                     const char *codigo,
                                     char **fila_producto);
int banco_buscar_producto_servicio(const char *codigo, char **fila_producto);

#endif
