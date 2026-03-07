#ifndef PROCESOS_OPERACIONES_TEXTOS_H
#define PROCESOS_OPERACIONES_TEXTOS_H

#include <stdio.h>

int split(const char *txt, const char *sep, char ***salida);

/* libera el arreglo terminado en NULL (no necesita longitud) */
void free_split(char **a);

int texto_a_float_seguro(const char *texto, float *var_a_retornar);

int texto_a_int_seguro(const char *texto, int *var_a_retornar);

/* utilidades dinamicas de texto */
char *texto_copiar_dinamico(const char *texto_origen);
char *texto_formatear_dinamico(const char *formato, ...);

/* utilidades dinamicas de archivo de texto */
int texto_leer_linea_dinamica(FILE *archivo, char **linea_salida);
void texto_liberar_lineas_dinamicas(char **lineas, int cantidad_lineas);
int texto_leer_archivo_dinamico(const char *ruta, char ***lineas_salida);
int texto_guardar_archivo_dinamico(const char *ruta, char **lineas, int cantidad_lineas);

/*
 * Busca una fila por valor de columna en un archivo de texto separado por '|'.
 * - columna_busqueda: indice de columna (0 = primera).
 * - omitir_encabezado: 1 para empezar en la fila 1, 0 para incluir fila 0.
 * - fila_encontrada: retorna una copia dinamica de la fila encontrada (liberar con free).
 * Retorna 0 si encuentra, -1 parametros invalidos, -2 error de lectura/memoria, -3 no encontrado.
 */
int texto_buscar_fila_por_columna_en_archivo(const char *ruta,
                                             int columna_busqueda,
                                             const char *valor_buscado,
                                             int omitir_encabezado,
                                             char **fila_encontrada);

#endif // PROCESOS_OPERACIONES_TEXTOS_H
