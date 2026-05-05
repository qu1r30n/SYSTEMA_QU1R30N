#ifndef MODELO_TEX_BAS_H
#define MODELO_TEX_BAS_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - modelo_var_fun_GG.h: Dependencia interna del proyecto
 */
#include "modelo_var_fun_GG.h"

#define MAX_LINEA 1024
#define MAX_LINEAS (MAX_PRODUCTOS + 1)

/*
 * Uso: Ejecuta modelo_crearDirectorio de forma segura.
 * Entrada ejemplo: modelo_crearDirectorio(texto)
 */
void modelo_crearDirectorio(char *texto);
/*
 * Uso: Ejecuta modelo_crearArchivo de forma segura.
 * Entrada ejemplo: modelo_crearArchivo(texto)
 */
void modelo_crearArchivo(char *texto);

/*
 * Uso: Ejecuta modelo_leer_archivo de forma segura.
 * Entrada ejemplo: modelo_leer_archivo(texto)
 */
void modelo_leer_archivo(char *texto);
/*
 * Uso: Ejecuta modelo_guardar_archivo de forma segura.
 * Entrada ejemplo: modelo_guardar_archivo(texto)
 */
void modelo_guardar_archivo(char *texto);

/*
 * Uso: Ejecuta modelo_agregar_fila de forma segura.
 * Entrada ejemplo: modelo_agregar_fila(texto)
 */
void modelo_agregar_fila(char *texto);
/*
 * Uso: Ejecuta modelo_eliminar_fila de forma segura.
 * Entrada ejemplo: modelo_eliminar_fila(texto)
 */
void modelo_eliminar_fila(char *texto);
/*
 * Uso: Ejecuta modelo_editar_fila de forma segura.
 * Entrada ejemplo: modelo_editar_fila(texto)
 */
void modelo_editar_fila(char *texto);

/*
 * Uso: Ejecuta modelo_editar_celda de forma segura.
 * Entrada ejemplo: modelo_editar_celda(texto)
 */
void modelo_editar_celda(char *texto);
/*
 * Uso: Ejecuta modelo_incrementar_celda de forma segura.
 * Entrada ejemplo: modelo_incrementar_celda(texto)
 */
void modelo_incrementar_celda(char *texto);

/*
 * Uso: Ejecuta modelo_editar_columna_completa de forma segura.
 * Entrada ejemplo: modelo_editar_columna_completa(texto)
 */
void modelo_editar_columna_completa(char *texto);
/*
 * Uso: Ejecuta modelo_eliminar_columna de forma segura.
 * Entrada ejemplo: modelo_eliminar_columna(texto)
 */
void modelo_eliminar_columna(char *texto);
/*
 * Uso: Ejecuta modelo_agregar_columna de forma segura.
 * Entrada ejemplo: modelo_agregar_columna(texto)
 */
void modelo_agregar_columna(char *texto);

#endif // MODELO_TEX_BAS_H
