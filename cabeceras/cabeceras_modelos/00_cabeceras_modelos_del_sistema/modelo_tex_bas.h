#ifndef TEX_BAS_H
#define TEX_BAS_H

#define MAX_LINEA 1024

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

#endif
