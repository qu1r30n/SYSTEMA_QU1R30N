#ifndef GESTOR_DE_PERMISOS_H
#define GESTOR_DE_PERMISOS_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - var_fun_GG.h: Dependencia interna del proyecto
 */
#include "var_fun_GG.h"

/* Verifica si el usuario con la contrasena dada tiene permiso sobre ruta_archivo e id_de_espacio,
   y además que su nivel sea mayor o igual a nivel_minimo.
   Si retorna_direccion_espacio_negocio no es NULL, devuelve por salida una copia de columnas[3].
    Si retornar_nivel no es NULL, devuelve por salida el nivel leido de columnas[4].
    Retorna 0 si tiene permiso, 1 si no lo tiene, -1 si ocurre un error. */
int checar_permiso(int nivel_minimo, const char *ruta_archivo, const char *id_de_espacio, const char *usuario, const char *contrasena, char **retorna_direccion_espacio_negocio, int *retornar_nivel);

#endif /* GESTOR_DE_PERMISOS_H */
