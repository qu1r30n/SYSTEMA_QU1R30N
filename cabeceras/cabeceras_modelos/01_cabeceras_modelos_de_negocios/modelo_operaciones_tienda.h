// ============================
// MODELOS - Cabecera (solo prototipos)
// ============================

#ifndef MODELOS_H
#define MODELOS_H

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
void modelo_agregarProducto(char *texto);
int modelo_editarPrecio(char *texto);
int modelo_venta(char *texto);
int modelo_compra(char *texto);

// Fecha
void modelo_fechaActual(char *texto);

#endif // MODELOS_H
