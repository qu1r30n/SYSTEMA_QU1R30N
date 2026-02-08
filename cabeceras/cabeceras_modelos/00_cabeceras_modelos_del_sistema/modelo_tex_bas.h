#ifndef TEX_BAS_H
#define TEX_BAS_H

#define MAX_LINEA 1024

void crearDirectorio(const char* ruta);
void crearArchivo(const char* ruta, const char* cabecera);

int leer_archivo(const char* ruta, char l[][MAX_LINEA]);
void guardar_archivo(const char* ruta, char l[][MAX_LINEA], int n);

void agregar_fila(const char* ruta, const char* fila);
void eliminar_fila(const char* ruta, int filaEliminar);
void editar_fila(const char* ruta, int fila, const char* nueva);

void editar_celda(const char* ruta,int colBuscar,const char* valorBuscar,
                  int colEditar,const char* nuevoValor);

void incrementar_celda(const char* ruta,int colBuscar,const char* valorBuscar,
                       int colEditar,int inc);

void editar_columna_completa(const char* ruta,int col,const char* nuevo);
void eliminar_columna(const char* ruta,int col);
void agregar_columna(const char* ruta,const char* nombre);

void inicializacion();

#endif
