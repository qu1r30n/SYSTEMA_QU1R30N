#ifndef MODELO_GESTOR_DE_PERMISOS_H
#define MODELO_GESTOR_DE_PERMISOS_H

/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - modelo_var_fun_GG.h: Dependencia interna del proyecto
 */
#include "modelo_var_fun_GG.h"

/*
 * Uso: Ejecuta modelo_checar_permiso de forma segura.
 * Entrada ejemplo: modelo_checar_permiso(texto, retorna_direccion_espacio_negocio, retornar_nivel)
 */
int modelo_checar_permiso(char *texto, char **retorna_direccion_espacio_negocio, int *retornar_nivel);

/*
 * Uso: Verifica permiso del negocio sin retornar directorio (ya se tiene la ruta).
 * Entrada ejemplo: modelo_checar_permiso_negocios(texto, retornar_nivel)
 */
int modelo_checar_permiso_negocios(char *texto, int *retornar_nivel);

#endif /* MODELO_GESTOR_DE_PERMISOS_H */
