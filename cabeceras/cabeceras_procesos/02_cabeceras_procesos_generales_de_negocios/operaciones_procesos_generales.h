#ifndef OPERACIONES_PROCESOS_GENERALES_H
#define OPERACIONES_PROCESOS_GENERALES_H

#include "operaciones_contadores.h"
#include "operaciones_administradores.h"

/*
 * Libro contable general:
 * id|tipo|monto|quien|negocio|concepto|item_tipo|item_nombre|medio_pago|fecha
 *
 * - tipo: ENTRADA o SALIDA
 * - item_tipo: PRODUCTO o SERVICIO
 */
int pg_registrar_movimiento(const char *ruta_libro,
                            const char *tipo,
                            float monto,
                            const char *quien,
                            const char *negocio,
                            const char *concepto,
                            const char *item_tipo,
                            const char *item_nombre,
                            const char *medio_pago);

#endif
