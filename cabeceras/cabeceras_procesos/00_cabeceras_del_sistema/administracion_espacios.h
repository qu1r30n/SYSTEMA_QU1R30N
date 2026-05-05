#ifndef ADMINISTRACION_ESPACIOS_H
#define ADMINISTRACION_ESPACIOS_H

/*
 * Uso: Ejecuta crear_espacios de forma segura.
 * Entrada ejemplo: crear_espacios(nom_espacio, usuario, contrasena, retorno_nombre_completo_espacio)
 */
int crear_espacios(char *nom_espacio, char *usuario, char *contrasena, char **retorno_nombre_completo_espacio);
/*
 * Uso: Ejecuta crear_archivos_base_negocio de forma segura.
 * Entrada ejemplo: crear_archivos_base_negocio(id_espacio)
 */
int crear_archivos_base_negocio(const char *id_espacio);

#endif
