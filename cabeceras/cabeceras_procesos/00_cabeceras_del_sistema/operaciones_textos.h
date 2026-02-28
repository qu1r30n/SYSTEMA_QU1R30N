#ifndef PROCESOS_OPERACIONES_TEXTOS_H
#define PROCESOS_OPERACIONES_TEXTOS_H

int split(const char* txt, const char* sep, char*** salida);

/* libera el arreglo terminado en NULL (no necesita longitud) */
void free_split(char** a);

int texto_a_float_seguro(const char *texto, float *var_a_retornar);

int texto_a_int_seguro(const char *texto, int *var_a_retornar);

#endif // PROCESOS_OPERACIONES_TEXTOS_H
