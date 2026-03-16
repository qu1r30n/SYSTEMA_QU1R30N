#ifndef MODELO_TEX_BAS_H
#define MODELO_TEX_BAS_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - modelo_var_fun_GG.h: Dependencia interna del proyecto
 */
#include "modelo_var_fun_GG.h"

#define MAX_LINEA 1024
#define MAX_LINEAS (MAX_PRODUCTOS + 1)

void modelo_crearDirectorio(char *texto);
void modelo_crearArchivo(char *texto);

void modelo_leer_archivo(char *texto);
void modelo_guardar_archivo(char *texto);

void modelo_agregar_fila(char *texto);
void modelo_eliminar_fila(char *texto);
void modelo_editar_fila(char *texto);

void modelo_editar_celda(char *texto);
void modelo_incrementar_celda(char *texto);

void modelo_editar_columna_completa(char *texto);
void modelo_eliminar_columna(char *texto);
void modelo_agregar_columna(char *texto);

#endif // MODELO_TEX_BAS_H
