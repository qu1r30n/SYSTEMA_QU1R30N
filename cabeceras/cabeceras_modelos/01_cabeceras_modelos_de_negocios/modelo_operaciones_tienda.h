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
void modelo_crearDirectorio(char *texto);
void modelo_crearArchivo(char *texto);

// Archivos (filas y columnas)
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

// Inicialización
void modelo_inicializacion(char *texto);

// Inventario
int modelo_leerInventario(char *texto);
void modelo_guardarInventario(char *texto);
int modelo_buscarProducto(char *texto);
int modelo_agregarProducto(char *texto);
int modelo_editarPrecio(char *texto);
int modelo_venta(char *texto);
int modelo_compra(char *texto);

// Fecha
void modelo_fechaActual(char *texto);

#endif // MODELOS_H
