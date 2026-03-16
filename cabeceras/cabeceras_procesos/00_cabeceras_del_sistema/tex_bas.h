#ifndef TEX_BAS_H
#define TEX_BAS_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - var_fun_GG.h: Dependencia interna del proyecto
 */
#include "var_fun_GG.h"
#include <stddef.h>

void crearDirectorio(const char *ruta);
void crearArchivo(const char *ruta, const char *cabecera);

/* Lee archivo y retorna arreglo dinámico de strings.
   El caller es responsable de llamar a free_lineas() cuando termine. */
char **leer_archivo(const char *ruta, int *n_lineas_out);

/* Guarda arreglo dinámico de strings a archivo. */
void guardar_archivo(const char *ruta, char **lineas, int n_lineas);

/* Libera memoria de arreglo dinámico retornado por leer_archivo(). */
void free_lineas(char **lineas, int n_lineas);

void agregar_fila(const char *ruta, const char *fila);
void eliminar_fila(const char *ruta, int filaEliminar);
void editar_fila(const char *ruta, int fila, const char *nueva);

void editar_celda(const char *ruta, int colBuscar, const char *valorBuscar,
                  int colEditar, const char *nuevoValor);

void incrementar_celda(const char *ruta, int colBuscar, const char *valorBuscar,
                       int colEditar, int inc);

void editar_columna_completa(const char *ruta, int col, const char *nuevo);
void eliminar_columna(const char *ruta, int col);
void agregar_columna(const char *ruta, const char *nombre);

/* Verifica si un archivo existe. Retorna 1 si existe, 0 si no. */
int existe_archivo(const char *ruta);

/* Busca filas donde la celda[col_buscar] == valor_buscar (split por GG_caracter_separacion[0]).
   Retorna arreglo dinámico de filas encontradas y actualiza salida_out.
   El caller es responsable de llamar a free_lineas(). */
int seleccionar_fila_por_celda(const char *ruta, int col_buscar,
                               const char *valor_buscar,
                               char ***salida_out);

/* Elimina del archivo todas las filas donde celda[col_buscar] == valor_buscar. */
void eliminar_fila_por_celda(const char *ruta, int col_buscar,
                             const char *valor_buscar);

/* En las filas donde celda[col_buscar] == valor_buscar,
   reemplaza celda[col_editar] con nuevo_valor. */
void editar_celda_por_celda(const char *ruta, int col_buscar,
                            const char *valor_buscar,
                            int col_editar, const char *nuevo_valor);

/* Buscar primera fila donde celda[colBuscar]==valorBuscar.
   Retorna el indice de la fila (0-based) o -1 si no se encuentra.
   Si salida_out no es NULL, copia la fila encontrada. */
int buscar_fila(const char *ruta, int colBuscar, const char *valorBuscar,
                char **salida_out);

/* Agregar fila_nueva solo si no existe fila con celda[colBuscar]==valorBuscar.
   Retorna 1=agrego, 0=ya existia, -1=error. */
int agregar_sino_existe(const char *ruta, int colBuscar, const char *valorBuscar,
                        const char *fila_nueva);

/* Editar celda[col] en la fila con indice id_fila (0-based).
   Retorna 1=exito, 0=fuera de rango. */
int editar_celda_id_fila(const char *ruta, int id_fila, int col,
                         const char *nuevo_valor);

/* Incrementar celda[col] numerica en la fila con indice id_fila.
   Retorna 1=exito, 0=fuera de rango. */
int incrementar_celda_id_fila(const char *ruta, int id_fila, int col,
                              double incremento);

/* Borrar celdas[1..n] dejando solo celda[0] en filas donde celda[colBuscar]==valorBuscar. */
void borrar_celdas_excepto_primera(const char *ruta, int colBuscar,
                                   const char *valorBuscar);

/* Reescribir el archivo completo con el arreglo dinámico dado. */
void reescribir_archivo(const char *ruta, char **lineas, int n_lineas);

/* Generar ruta completa de archivo distribuido a partir de ruta base, id y cant_por_arch.
   Escribe el resultado en salida. */
void generar_ruta_archivo(const char *ruta, long id, long cant_por_arch,
                          char *salida, size_t tam_salida);

/* =======================
   FUNCIONES ADICIONALES DEL C#
   ======================== */

/* Leer archivo completo en una sola string (para procesos que requieren contenido completo).
   El caller debe liberar con free(). */
char *leer_info_dividida(const char *ruta);

/* Incrementar celda solo si el programa (col 2) coincide con programa_id.
   Busca por col 0 (ID principal). */
int incrementa_celda_solo_prog(const char *ruta, const char *id_principal,
                               const char *programa_id, int col_editar, double incremento);

/* Eliminar filas solo para un programa específico. */
void eliminar_fila_para_multiples_programas_solo_prog(const char *ruta,
                                                      const char *id_a_eliminar,
                                                      const char *programa_id);

/* Editar fila específica sin arreglo GG (alternativa a editar_celda_por_celda). */
int editar_fila_espesifica_sin_arreglo_gg(const char *ruta, const char *id_fila,
                                          int col_editar, const char *nuevo_valor);

/* Leer solo datos de un programa específico (filtro por columna programa). */
int leer_solo_prog(const char *ruta, const char *programa_id, char ***salida_out);

/* Editar celda por ID de fila restringido a un programa. */
int editar_celda_id_fila_solo_prog(const char *ruta, int id_fila,
                                   int col_editar, const char *nuevo_valor,
                                   const char *programa_id);

/* Incrementar celda por ID de fila restringido a un programa. */
int incrementa_celda_id_fila_solo_prog(const char *ruta, int id_fila, int col,
                                       double incremento, const char *programa_id);

/* Borrar contenido de celdas excepto la primera en filas que coincidan con criterio. */
void borrar_contenido_excepto_id(const char *ruta, const char *id_fila);

#endif
