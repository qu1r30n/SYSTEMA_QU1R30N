#ifndef PROCESOS_OPERACIONES_TEXTOS_H
#define PROCESOS_OPERACIONES_TEXTOS_H

#include <stddef.h>

#define CONCAT_TEXTO 0
#define CONCAT_INT 1
#define CONCAT_FLOAT 2

int split(const char *txt, const char *sep, char ***salida);

/* libera el arreglo terminado en NULL (no necesita longitud) */
void free_split(char **a);

int texto_a_float_seguro(const char *texto, float *var_a_retornar);

int texto_a_int_seguro(const char *texto, int *var_a_retornar);

int concatenar(char *destino, size_t capacidad_destino, const void *valor, int tipo_valor, const char *caracter_separacion);

/* Version tipo printf: formatea y concatena al destino. */
int concatenar_formato(char *destino, const char *formato, ...);

#endif // PROCESOS_OPERACIONES_TEXTOS_H
