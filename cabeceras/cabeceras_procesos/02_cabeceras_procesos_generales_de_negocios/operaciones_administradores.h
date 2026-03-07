#ifndef OPERACIONES_ADMINISTRADORES_H
#define OPERACIONES_ADMINISTRADORES_H

/* Clase de procesos: Administradores */
int pg_administrador_configurar_presupuesto(const char *ruta_presupuestos,
                                            const char *negocio,
                                            const char *rubro,
                                            float limite);

int pg_administrador_verificar_presupuesto(const char *ruta_libro,
                                           const char *ruta_presupuestos,
                                           const char *negocio,
                                           const char *rubro,
                                           float *gastado,
                                           float *limite,
                                           float *disponible,
                                           int *excedido);

#endif
