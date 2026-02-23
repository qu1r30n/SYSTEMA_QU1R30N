#ifndef OPERACIONES_TEXTOS_H
#define OPERACIONES_TEXTOS_H

int split(const char* txt, const char* sep, char*** salida);

void free_split(char** a, int n);

int texto_a_float_seguro(const char *texto, float *var_a_retornar);

int texto_a_int_seguro(const char *texto, int *var_a_retornar);

#endif
