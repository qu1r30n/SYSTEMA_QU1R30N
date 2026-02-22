#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"

#ifdef _WIN32
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif

#define MAX_LINEAS 1024
#define MAX_LINEA 1024

// Crear directorio
void modelo_crearDirectorio(char* texto) {
    crearDirectorio(texto);
}

// Crear archivo
void modelo_crearArchivo(char* texto) {
    crearArchivo(texto, NULL);
}

// Leer archivo
void modelo_leer_archivo(char* texto) 
{
    char lineas[MAX_LINEAS][MAX_LINEA];
    leer_archivo(texto, lineas);
}

// Guardar archivo
void modelo_guardar_archivo(char* texto) {
    char lineas[MAX_LINEAS][MAX_LINEA];
    guardar_archivo(texto, lineas, 0);
}


// Agregar fila
void modelo_agregar_fila(char* texto) {
    agregar_fila(texto, texto);
}



// Inicialización
void modelo_inicializacion(char* texto) {
    inicializacion();
}
