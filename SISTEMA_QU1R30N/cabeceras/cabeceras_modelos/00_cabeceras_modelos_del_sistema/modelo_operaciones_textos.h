#ifndef MODELO_OPERACIONES_TEXTOS_H
#define MODELO_OPERACIONES_TEXTOS_H

/*
 * Uso: Ejecuta split de forma segura.
 * Entrada ejemplo: split(texto, sep)
 */
char **split(char *texto, const char *sep);
/* libera un arreglo terminado en NULL, no necesita pasar la longitud */
/*
 * Uso: Ejecuta modelo_free_split_con_numero_de_celdas de forma segura.
 * Entrada ejemplo: modelo_free_split_con_numero_de_celdas(a)
 */
void modelo_free_split_con_numero_de_celdas(char **a);

/*
 * Uso: Ejecuta modelo_texto_a_int_seguro de forma segura.
 * Entrada ejemplo: modelo_texto_a_int_seguro(texto)
 */
int modelo_texto_a_int_seguro(char *texto);
/*
 * Uso: Ejecuta modelo_texto_a_float_seguro de forma segura.
 * Entrada ejemplo: modelo_texto_a_float_seguro(texto)
 */
float modelo_texto_a_float_seguro(char *texto);

#endif // MODELO_OPERACIONES_TEXTOS_H
