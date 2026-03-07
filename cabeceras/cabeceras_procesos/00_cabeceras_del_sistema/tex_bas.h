#ifndef TEX_BAS_H
#define TEX_BAS_H

#include "var_fun_GG.h"

#define MAX_LINEA 1024
#define MAX_LINEAS (MAX_PRODUCTOS + 1)

/*
 * Regla de arquitectura (importante):
 * - "modelos" define el proceso, aplica defaults y parsea el comando.
 * - "procesos" recibe solo los parametros necesarios para ejecutar.
 * - En este modulo (tex_bas), como trabaja con archivos, "ruta" si es necesaria.
 * - La ruta nunca debe estar hardcodeada en procesos.
 *
 * Esto permite reutilizar el mismo proceso con diferentes archivos.
 */

void crearDirectorio(const char *ruta);
void crearArchivo(const char *ruta, const char *cabecera);

int leer_archivo(const char *ruta, char l[][MAX_LINEA]);
void guardar_archivo(const char *ruta, char l[][MAX_LINEA], int n);

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

#endif
