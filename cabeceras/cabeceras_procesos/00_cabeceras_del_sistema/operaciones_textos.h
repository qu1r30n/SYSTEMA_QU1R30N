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

/* =======================
   FUNCIONES NUEVAS DEL C#
   ======================== */

/* Unir filas con carácter separador, extrayendo columnas específicas opcionalmente. */
char *join_paresido_simple(char caracter_union_filas, char **texto, int n_texto,
                           const char *columnas_extraer, const char *caracter_union_columnas);

/* Unir arreglo en string con separador, quitando celdas del inicio o final. */
char *joineada_paraesida_y_quitador_de_extremos(const char *data,
                                                int restar_cuantas,
                                                int restar_primera_celda);

/* Igual a anterior pero omitiendo celdas NULL. */
char *joineada_paraesida_SIN_NULOS_y_quitador_de_extremos(const char *data,
                                                          int restar_cuantas,
                                                          int restar_primera_celda);

/* Quitar separador final duplicado de una string. */
char *Trimend_paresido(const char *texto);

/* Concatenar filas de archivo con separador. */
char *concatenacion_filas_de_un_archivo(const char *ruta_archivo, int poner_num_fila);

/* Concatenar filas de arreglo. */
char *concatenacion_filas_de_un_arreglo(char **arreglo, int n_arreglo, int poner_num_fila);

/* Concatenar arreglo 2D fila por fila. */
char *concatenacion_filas_de_un_arreglo_bidimencional(const char **arreglo_2d,
                                                      int filas, int cols,
                                                      int poner_num_fila);

/* Concatenar dos strings con separador. */
char *concatenacion_caracter_separacion(const char *texto_actual,
                                        const char *texto_agregar,
                                        const char *separador);

/* Búsqueda en estructura profunda (nested) por columnas múltiples. */
char *busqueda_profunda_string(const char *texto, const char *columnas_recorrer,
                               const char *comparar);

/* Búsqueda profunda retornando en formato especial final. */
char *busqueda_profunda_comparacion_final_string(const char *texto,
                                                 const char *columnas_recorrer,
                                                 const char *comparar);

/* Búsqueda profunda con YY (múltiples comparaciones). */
char *busqueda_con_YY_profunda_texto_id_archivo(const char *texto,
                                                const char *columnas_recorrer,
                                                const char *comparaciones);

/* Edición/incremento recursiva en estructura profunda. */
char *editar_incr_string_funcion_recursiva(const char *texto,
                                           const char *columnas_recorrer,
                                           const char *info_sustituir,
                                           const char *edit_0_increm_1);

/* Edición profunda múltiple con comparación final. */
char *editar_inc_agregar_edicion_profunda_multiple_comparacion_final_string(
    const char *texto,
    const char *indices_editar,
    const char *info_editar,
    const char *comparacion,
    const char *edit_0_increm_1);

/* Edición profunda múltiple versión ARR_FUN (wrapper). */
char *ARR_FUN_SOLO_TEXTO_editar_inc_agregar_edicion_profunda_multiple(const char *datos);

/* Edición profunda múltiple con múltiples chequeos. */
char *editar_inc_agregar_edicion_profunda_multiple_comparacion_MULTIPLE_A_CHECAR(
    const char *texto,
    const char *indices_editar,
    const char *comparacion_con_edicion,
    const char *edit_0_increm_1);

/* Edición profunda múltiple simple. */
char *editar_inc_edicion_profunda_multiple_string(const char *texto,
                                                  const char *indices_editar,
                                                  const char *info_editar,
                                                  const char *edit_0_increm_1);

/* Edición profunda múltiple al final. */
char *editar_inc_edicion_profunda_multiple_AL_FINAL_string(const char *texto,
                                                           const char *indices_editar,
                                                           const char *info_editar,
                                                           const char *edit_0_increm_1);

/* Recorrer y reemplazar caracteres de separación izq/dcha. */
char *recorrer_caracter_separacion(const char *contenidoFila,
                                   const char *izquierda_o_derecha,
                                   int numero_veses);

/* Recorrer caracteres de separación para funciones específicas. */
char *recorrer_caracter_separacion_funciones_espesificas(const char *contenidoFila,
                                                         const char *izquierda_o_derecha,
                                                         int numero_veses);

/* Extraer carpeta, nombre y extensión de ruta. */
char **extraer_separado_carpetas_nombreArchivo_extencion(const char *direccion_archivo);

/* Desfragmentar ruta y devolver por salida: directorios, nombre de archivo y extencion. */
int desfragmentar_direccion(const char *direccion,
                            char **retorna_directorios,
                            char **retorna_nom_arch,
                            char **retorna_extencion);

/* Generar folio (ID único con timestamp). */
char *generar_folio(const char *formato_fecha_hora);

/* Reemplazar múltiples caracteres según arreglos paralelos. */
char *ReemplazarCaracteres_de_texto_arreglo(const char *info,
                                            char **caracteres_sep, int n_sep,
                                            char **caracteres_sustitucion);

#endif // PROCESOS_OPERACIONES_TEXTOS_H
