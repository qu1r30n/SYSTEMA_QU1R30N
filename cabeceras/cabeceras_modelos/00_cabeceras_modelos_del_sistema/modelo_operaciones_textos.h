#ifndef OPERACIONES_TEXTOS_H
#define OPERACIONES_TEXTOS_H

char** modelo_split(char *texto, const char* sep);
void modelo_free_split(char** a, int n);

int modelo_texto_a_int_seguro(char *texto);
float modelo_texto_a_float_seguro(char *texto);

#endif
