#ifndef TEX_BAS_H
#define TEX_BAS_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - var_fun_GG.h: Dependencia interna del proyecto
 */
#include "var_fun_GG.h"
#include <stddef.h>

/*
 * Uso: Ejecuta crearDirectorio de forma segura.
 * Entrada ejemplo: crearDirectorio(ruta)
 */
int crearDirectorio(const char *ruta);
/*
 * Uso: Ejecuta crearArchivo de forma segura.
 * Entrada ejemplo: crearArchivo(ruta, cabecera)
 */
int crearArchivo(const char *ruta, const char *cabecera);

/* Lee archivo y retorna arreglo din�mico de strings.
El caller es responsable de llamar a free_lineas() cuando termine. */
char **leer_archivo(const char *ruta, int *n_lineas_out);

/* Guarda arreglo din�mico de strings a archivo. */
/*
 * Uso: Ejecuta guardar_archivo de forma segura.
 * Entrada ejemplo: guardar_archivo(ruta, lineas, n_lineas)
 */
void guardar_archivo(const char *ruta, char **lineas, int n_lineas);

/* Libera memoria de arreglo din�mico retornado por leer_archivo(). */
/*
 * Uso: Ejecuta free_lineas de forma segura.
 * Entrada ejemplo: free_lineas(lineas, n_lineas)
 */
void free_lineas(char **lineas, int n_lineas);

/*
 * Uso: Ejecuta agregar_fila de forma segura.
 * Entrada ejemplo: agregar_fila(ruta, fila)
 */
void agregar_fila(const char *ruta, const char *fila);
/*
 * Uso: Ejecuta eliminar_fila de forma segura.
 * Entrada ejemplo: eliminar_fila(ruta, filaEliminar)
 */
void eliminar_fila(const char *ruta, int filaEliminar);
/*
 * Uso: Ejecuta editar_fila de forma segura.
 * Entrada ejemplo: editar_fila(ruta, fila, nueva)
 */
void editar_fila(const char *ruta, int fila, const char *nueva);

/*
 * Uso: Ejecuta editar_celda de forma segura.
 * Entrada ejemplo: editar_celda(ruta, colBuscar, valorBuscar, colEditar, nuevoValor)
 */
void editar_celda(const char *ruta, int colBuscar, const char *valorBuscar, int colEditar, const char *nuevoValor);

/*
 * Uso: Ejecuta incrementar_celda de forma segura.
 * Entrada ejemplo: incrementar_celda(ruta, colBuscar, valorBuscar, colEditar, inc)
 */
void incrementar_celda(const char *ruta, int colBuscar, const char *valorBuscar, int colEditar, int inc);

/*
 * Uso: Ejecuta editar_columna_completa de forma segura.
 * Entrada ejemplo: editar_columna_completa(ruta, col, nuevo)
 */
void editar_columna_completa(const char *ruta, int col, const char *nuevo);
/*
 * Uso: Ejecuta eliminar_columna de forma segura.
 * Entrada ejemplo: eliminar_columna(ruta, col)
 */
void eliminar_columna(const char *ruta, int col);
/*
 * Uso: Ejecuta agregar_columna de forma segura.
 * Entrada ejemplo: agregar_columna(ruta, nombre)
 */
void agregar_columna(const char *ruta, const char *nombre);

/* Verifica si un archivo existe. Retorna 1 si existe, 0 si no. */
/*
 * Uso: Ejecuta existe_archivo de forma segura.
 * Entrada ejemplo: existe_archivo(ruta)
 */
int existe_archivo(const char *ruta);

/* Busca filas donde la celda[col_buscar] == valor_buscar (split por GG_caracter_separacion[0]).
Retorna arreglo din�mico de filas encontradas y actualiza salida_out.
El caller es responsable de llamar a free_lineas(). */
int seleccionar_fila_por_celda(const char *ruta, int col_buscar, const char *valor_buscar, char ***salida_out);

/* Elimina del archivo todas las filas donde celda[col_buscar] == valor_buscar. */
/*
 * Uso: Ejecuta eliminar_fila_por_celda de forma segura.
 * Entrada ejemplo: eliminar_fila_por_celda(ruta, col_buscar, valor_buscar)
 */
void eliminar_fila_por_celda(const char *ruta, int col_buscar, const char *valor_buscar);

/* En las filas donde celda[col_buscar] == valor_buscar,
reemplaza celda[col_editar] con nuevo_valor. */
/*
 * Uso: Ejecuta editar_celda_por_celda de forma segura.
 * Entrada ejemplo: editar_celda_por_celda(ruta, col_buscar, valor_buscar, col_editar, nuevo_valor)
 */
void editar_celda_por_celda(const char *ruta, int col_buscar, const char *valor_buscar, int col_editar, const char *nuevo_valor);

/* Buscar primera fila donde celda[colBuscar]==valorBuscar.
Retorna el indice de la fila (0-based) o -1 si no se encuentra.
Si salida_out no es NULL, copia la fila encontrada. */
int buscar_fila(const char *ruta, int colBuscar, const char *valorBuscar, char **salida_out);

/* Agregar fila_nueva solo si no existe fila con celda[colBuscar]==valorBuscar.
Retorna 1=agrego, 0=ya existia, -1=error. */
/*
 * Uso: Ejecuta agregar_sino_existe de forma segura.
 * Entrada ejemplo: agregar_sino_existe(ruta, colBuscar, valorBuscar, fila_nueva)
 */
int agregar_sino_existe(const char *ruta, int colBuscar, const char *valorBuscar, const char *fila_nueva);

/* Editar celda[col] en la fila con indice id_fila (0-based).
Retorna 1=exito, 0=fuera de rango. */
/*
 * Uso: Ejecuta editar_celda_id_fila de forma segura.
 * Entrada ejemplo: editar_celda_id_fila(ruta, id_fila, col, nuevo_valor)
 */
int editar_celda_id_fila(const char *ruta, int id_fila, int col, const char *nuevo_valor);

/* Incrementar celda[col] numerica en la fila con indice id_fila.
Retorna 1=exito, 0=fuera de rango. */
/*
 * Uso: Ejecuta incrementar_celda_id_fila de forma segura.
 * Entrada ejemplo: incrementar_celda_id_fila(ruta, id_fila, col, incremento)
 */
int incrementar_celda_id_fila(const char *ruta, int id_fila, int col, double incremento);

/* Borrar celdas[1..n] dejando solo celda[0] en filas donde celda[colBuscar]==valorBuscar. */
/*
 * Uso: Ejecuta borrar_celdas_excepto_primera de forma segura.
 * Entrada ejemplo: borrar_celdas_excepto_primera(ruta, colBuscar, valorBuscar)
 */
void borrar_celdas_excepto_primera(const char *ruta, int colBuscar, const char *valorBuscar);

/* Reescribir el archivo completo con el arreglo din�mico dado. */
/*
 * Uso: Ejecuta reescribir_archivo de forma segura.
 * Entrada ejemplo: reescribir_archivo(ruta, lineas, n_lineas)
 */
void reescribir_archivo(const char *ruta, char **lineas, int n_lineas);

/* Generar ruta completa de archivo distribuido a partir de ruta base, id y cant_por_arch.
Escribe el resultado en salida. */
/*
 * Uso: Ejecuta generar_ruta_archivo de forma segura.
 * Entrada ejemplo: generar_ruta_archivo(ruta, id, cant_por_arch, salida, tam_salida)
 */
void generar_ruta_archivo(const char *ruta, long id, long cant_por_arch, char *salida, size_t tam_salida);

/* =======================
FUNCIONES ADICIONALES DEL C#
======================== */

/* Leer archivo completo en una sola string (para procesos que requieren contenido completo).
El caller debe liberar con free(). */
char *leer_info_dividida(const char *ruta);

/* Agregar informacion en archivo distribuido y actualizar metadata ID_TOT.
Retorna "1<sep_confirmacion>fila" en exito, o "0<sep_confirmacion>mensaje" en error.
El caller debe liberar con free(). */
char *agregar_info_dividida(const char *datos);

/* Incrementar celda solo si el programa (col 2) coincide con programa_id.
Busca por col 0 (ID principal). */
/*
 * Uso: Ejecuta incrementa_celda_solo_prog de forma segura.
 * Entrada ejemplo: incrementa_celda_solo_prog(ruta, id_principal, programa_id, col_editar, incremento)
 */
int incrementa_celda_solo_prog(const char *ruta, const char *id_principal, const char *programa_id, int col_editar, double incremento);

/* Eliminar filas solo para un programa espec�fico. */
/*
 * Uso: Ejecuta eliminar_fila_para_multiples_programas_solo_prog de forma segura.
 * Entrada ejemplo: eliminar_fila_para_multiples_programas_solo_prog(ruta, id_a_eliminar, programa_id)
 */
void eliminar_fila_para_multiples_programas_solo_prog(const char *ruta, const char *id_a_eliminar, const char *programa_id);

/* Editar fila espec�fica sin arreglo GG (alternativa a editar_celda_por_celda). */
/*
 * Uso: Ejecuta editar_fila_espesifica_sin_arreglo_gg de forma segura.
 * Entrada ejemplo: editar_fila_espesifica_sin_arreglo_gg(ruta, id_fila, col_editar, nuevo_valor)
 */
int editar_fila_espesifica_sin_arreglo_gg(const char *ruta, const char *id_fila, int col_editar, const char *nuevo_valor);

/* Leer solo datos de un programa espec�fico (filtro por columna programa). */
/*
 * Uso: Ejecuta leer_solo_prog de forma segura.
 * Entrada ejemplo: leer_solo_prog(ruta, programa_id, salida_out)
 */
int leer_solo_prog(const char *ruta, const char *programa_id, char ***salida_out);

/* Editar celda por ID de fila restringido a un programa. */
/*
 * Uso: Ejecuta editar_celda_id_fila_solo_prog de forma segura.
 * Entrada ejemplo: editar_celda_id_fila_solo_prog(ruta, id_fila, col_editar, nuevo_valor, programa_id)
 */
int editar_celda_id_fila_solo_prog(const char *ruta, int id_fila, int col_editar, const char *nuevo_valor, const char *programa_id);

/* Incrementar celda por ID de fila restringido a un programa. */
/*
 * Uso: Ejecuta incrementa_celda_id_fila_solo_prog de forma segura.
 * Entrada ejemplo: incrementa_celda_id_fila_solo_prog(ruta, id_fila, col, incremento, programa_id)
 */
int incrementa_celda_id_fila_solo_prog(const char *ruta, int id_fila, int col, double incremento, const char *programa_id);

/* Borrar contenido de celdas excepto la primera en filas que coincidan con criterio. */
/*
 * Uso: Ejecuta borrar_contenido_excepto_id de forma segura.
 * Entrada ejemplo: borrar_contenido_excepto_id(ruta, id_fila)
 */
void borrar_contenido_excepto_id(const char *ruta, const char *id_fila);

/* =======================
FUNCIONES INFO_DIVIDIDA PORTADAS DEL C#
======================== */

/* Lee todas las filas de todos los archivos de datos divididos y las retorna unidas con SEP[3].
El caller debe liberar con free(). */
char *leer_todo_info_dividida(const char *ruta);

/* Agrega una nueva fila al almacenamiento dividido y actualiza ID_TOT en el metadata.
 *   direccion    - ruta del archivo metadata
 *   agregando    - fila a insertar (sin ID, campos separados con SEP[0]; puede ser NULL)
 *   nom_columnas - cabecera de columnas si se crea el archivo por primera vez (puede ser NULL)
 * Retorna "1<SEP_C>fila_agregada" o "0<SEP_C>mensaje_error". El caller debe liberar con free(). */
char *agregar_info_dividida(const char *direccion,
                            const char *agregando,
                            const char *nom_columnas);

/* Agrega una fila solo si no existe ya un registro con el mismo valor en la columna indicada.
 *   direccion      - ruta del archivo metadata
 *   col_comp       - indice de columna de comparacion (0 = primera columna)
 *   comparar       - valor a buscar en col_comp
 *   texto_agr      - fila a insertar si no existe (sin ID, separada con SEP[0])
 *   nom_columnas   - cabecera de columnas si se crea el archivo por primera vez
 * Retorna "1<SEP_C>fila" o "0<SEP_C>ya existe...". El caller debe liberar con free(). */
char *agregar_sino_existe_info_dividida(const char *direccion,
                                        long        col_comp,
                                        const char *comparar,
                                        const char *texto_agr,
                                        const char *nom_columnas);

/* Obtiene el registro correspondiente a un ID dentro del almacenamiento dividido.
 *   direccion - ruta del archivo metadata
 *   id        - identificador del registro a buscar
 * Retorna "1<SEP_C>fila" o "0<SEP_C>no_se_encontro_informacion". El caller debe liberar con free(). */
char *seleccionar_id_info_dividida(const char *direccion, const char *id);

/* Igual a seleccionar_id_info_dividida pero también retorna la ruta del archivo y la posición de fila.
 * Retorna "1<SEP_C>fila<SEP_C>ruta<SEP_C>pos" o "0<SEP_C>no_se_encontro_informacion". El caller debe liberar con free(). */
char *seleccionar_id_info_dividida_extrae(const char *direccion, const char *id);

/* Edita una columna en el registro que coincide por columna de búsqueda o por ID.
 *   direccion       - ruta del archivo metadata
 *   id              - identificador del registro objetivo
 *   info_a_comparar - valor de busqueda (NULL = buscar por id)
 *   col_comparar    - columna donde buscar (NULL = buscar por id)
 *   nuevos_datos    - nuevo valor para la celda editada
 *   col_editar      - indice de columna a modificar
 * Retorna "1<SEP_C>informacion_editada" o "0<SEP_C>no_se_encontro_informacion". El caller debe liberar con free(). */
char *editar_id_info_dividida(const char *direccion,
                               const char *id,
                               const char *info_a_comparar,
                               const char *col_comparar,
                               const char *nuevos_datos,
                               int         col_editar);

/* Edita múltiples celdas de un registro por ID usando SEP[4] para separar columnas y valores.
 *   direccion - ruta del archivo metadata
 *   id        - identificador del registro objetivo
 *   cols_str  - columnas a editar separadas con SEP[4]
 *   vals_str  - nuevos valores separados con SEP[4]
 * Retorna "1<SEP_C>fila_editada" o "0<SEP_C>no_se_encontro_informacion". El caller debe liberar con free(). */
char *editar_celda_id_info_dividida(const char *direccion,
                                    const char *id,
                                    const char *cols_str,
                                    const char *vals_str);

/* Incrementa numéricamente múltiples celdas de un registro buscando por ID.
 *   direccion  - ruta del archivo metadata
 *   id         - identificador del registro objetivo
 *   cols_str   - columnas a incrementar separadas con SEP[4] (SEP[5] reemplazado por SEP[0] internamente)
 *   cants_str  - cantidades a sumar separadas con SEP[4] (pueden ser negativas)
 * Retorna "1<SEP_C>fila_editada" o "0<SEP_C>no_se_encontro_informacion". El caller debe liberar con free(). */
char *incrementa_celda_id_info_dividida(const char *direccion,
                                        const char *id,
                                        const char *cols_str,
                                        const char *cants_str);

/* Incrementa celdas por ID; si el resultado es negativo o la celda estaba vacía, copia
 * desde una columna fuente y reporta cuántos paquetes descontar (código de retorno 2).
 *   cols_fuente_str - columnas fuente para copiar cuando hay deficit, separadas con SEP[4]
 * Retorna "2<SEP_C>fila<SEP_C>bultos", "1<SEP_C>fila", o "0<SEP_C>...". El caller debe liberar con free(). */
char *incrementa_celda_id_info_dividida_copia_si_cero(const char *direccion,
                                                       const char *id,
                                                       const char *cols_str,
                                                       const char *cants_str,
                                                       const char *cols_fuente_str);

/* Busca un registro por valor en una columna e incrementa celdas numéricas al encontrarlo.
 *   direccion       - ruta del archivo metadata
 *   dato_a_buscar   - valor a buscar
 *   col_buscar      - indice de columna donde buscar
 *   cols_inc_str    - columnas a incrementar separadas con SEP[4]
 *   cants_inc_str   - cantidades a sumar separadas con SEP[4]
 *   agregar_fallback- fila a agregar si no se encuentra (puede ser NULL o vacío)
 * Retorna "1" si encontró y editó, "0" si no encontró. El caller debe liberar con free(). */
char *incrementa_celda_busqueda_info_dividida(const char *direccion,
                                              const char *dato_a_buscar,
                                              int         col_buscar,
                                              const char *cols_inc_str,
                                              const char *cants_inc_str,
                                              const char *agregar_fallback);

/* Busca un registro por valor en una columna. Con hint de posición para búsqueda rápida.
 *   direccion    - ruta del archivo metadata
 *   dato_buscar  - valor a buscar
 *   col_buscar   - indice de columna donde buscar
 *   id_hint      - posición aproximada donde buscar primero (-1 para búsqueda completa)
 * Retorna "1<SEP_C>fila<SEP_C>id" o "0<SEP_C>no encontro el producto". El caller debe liberar con free(). */
char *buscar_info_dividida(const char *direccion,
                           const char *dato_buscar,
                           int         col_buscar,
                           int         id_hint);

#endif
