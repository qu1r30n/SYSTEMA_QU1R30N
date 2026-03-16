#ifndef PROCESOS_OPERACIONES_TEXTOS_H
#define PROCESOS_OPERACIONES_TEXTOS_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stddef.h: Tipos base como size_t y NULL
 */
#include <stddef.h>

#define CONCAT_TEXTO 0
#define CONCAT_INT 1
#define CONCAT_FLOAT 2

int split(const char *txt, const char *sep, char ***salida);

/* libera el arreglo terminado en NULL (no necesita longitud) */
void free_split(char **a);

int texto_a_float_seguro(const char *texto, float *var_a_retornar);

int texto_a_int_seguro(const char *texto, int *var_a_retornar);

/* Version tipo printf: formatea y concatena al destino. */
int concatenar_formato_separado_por_variable(char **destino, const char *separador, const char *formato, ...);
int concatenar_formato(char *destino, const char *separador, const char *formato, ...);

#endif // PROCESOS_OPERACIONES_TEXTOS_H
