#ifndef MODELO_OPERACIONES_TEXTOS_H
#define MODELO_OPERACIONES_TEXTOS_H

char** modelo_split(char *texto, const char* sep);
/* libera un arreglo terminado en NULL, no necesita pasar la longitud */
void modelo_free_split(char** a);

int modelo_texto_a_int_seguro(char *texto);
float modelo_texto_a_float_seguro(char *texto);

#endif // MODELO_OPERACIONES_TEXTOS_H
