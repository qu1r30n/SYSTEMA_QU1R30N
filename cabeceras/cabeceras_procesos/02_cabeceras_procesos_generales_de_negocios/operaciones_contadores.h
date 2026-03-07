#ifndef OPERACIONES_CONTADORES_H
#define OPERACIONES_CONTADORES_H

/* Clase de procesos: Contadores */
int pg_contador_resumen_general(const char *ruta_libro,
                                float *entradas,
                                float *salidas,
                                float *saldo);

int pg_contador_resumen_negocio(const char *ruta_libro,
                                const char *negocio,
                                float *entradas,
                                float *salidas,
                                float *saldo);

#endif
