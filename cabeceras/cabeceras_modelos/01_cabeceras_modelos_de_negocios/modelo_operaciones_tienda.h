// ============================
// MODELOS - Cabecera (solo prototipos)
// ============================

#ifndef MODELOS_H
#define MODELOS_H

/* Alias del modulo (portabilidad al mover esta clase a otro proyecto). */
extern char *GG_caracter_separacion_nom_parametro_de_valor[];
extern char *GG_caracter_separacion_funciones_espesificas[];

#ifndef G_caracter_separacion_nom_parametro_de_valor
#define G_caracter_separacion_nom_parametro_de_valor GG_caracter_separacion_nom_parametro_de_valor
#endif

#ifndef G_caracter_separacion_funciones_espesificas
#define G_caracter_separacion_funciones_espesificas GG_caracter_separacion_funciones_espesificas
#endif

// Directorios y Archivos
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

// Archivos (filas y columnas)
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

// Inicialización
/*
 * Uso: Ejecuta modelo_inicializacion de forma segura.
 * Entrada ejemplo: modelo_inicializacion(texto)
 */
void modelo_inicializacion(char *texto);

// Inventario
/*
 * Uso: Ejecuta modelo_leerInventario de forma segura.
 * Entrada ejemplo: modelo_leerInventario(texto, dir_espacio, usuario_contraseña_negocio)
 */
int modelo_leerInventario(char *texto, char *dir_espacio, char *usuario_contraseña_negocio);
/*
 * Uso: Ejecuta modelo_guardarInventario de forma segura.
 * Entrada ejemplo: modelo_guardarInventario(texto, dir_espacio, usuario_contraseña_negocio)
 */
void modelo_guardarInventario(char *texto, char *dir_espacio, char *usuario_contraseña_negocio);
/*
 * Uso: Ejecuta modelo_buscarProducto de forma segura.
 * Entrada ejemplo: modelo_buscarProducto(texto, dir_espacio, usuario_contraseña_negocio)
 */
int modelo_buscarProducto(char *texto, char *dir_espacio, char *usuario_contraseña_negocio);
/*
 * Uso: Ejecuta modelo_agregarProducto de forma segura.
 * Entrada ejemplo: modelo_agregarProducto(texto, dir_espacio, usuario_contraseña_negocio)
 */
int modelo_agregarProducto(char *texto, char *dir_espacio, char *usuario_contraseña_negocio);
/*
 * Uso: Ejecuta modelo_editarPrecio de forma segura.
 * Entrada ejemplo: modelo_editarPrecio(texto, dir_espacio, usuario_contraseña_negocio)
 */
int modelo_editarPrecio(char *texto, char *dir_espacio, char *usuario_contraseña_negocio);
/*
 * Uso: Ejecuta modelo_venta de forma segura.
 * Entrada ejemplo: modelo_venta(texto, dir_espacio, usuario_contraseña_negocio)
 */
int modelo_venta(char *texto, char *dir_espacio, char *usuario_contraseña_negocio);
/*
 * Uso: Ejecuta modelo_compra de forma segura.
 * Entrada ejemplo: modelo_compra(texto, dir_espacio, usuario_contraseña_negocio)
 */
int modelo_compra(char *texto, char *dir_espacio, char *usuario_contraseña_negocio);

// Fecha
/*
 * Uso: Ejecuta modelo_fechaActual de forma segura.
 * Entrada ejemplo: modelo_fechaActual(texto)
 */
void modelo_fechaActual(char *texto);

#endif // MODELOS_H
