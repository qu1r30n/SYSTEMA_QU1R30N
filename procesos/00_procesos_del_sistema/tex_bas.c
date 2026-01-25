#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../../cabeceras/tex_bas.h"
#include "../../cabeceras/var_fun_GG.h"
#include "../../cabeceras/operaciones_textos.h"

#ifdef _WIN32
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif


// Crear directorio
/* Crear directorio linux creo
void crearDirectorio(const char* ruta) {
    char tmp[512];
    strcpy(tmp, ruta);
    char* p = strrchr(tmp, '/');
    if(p) { *p = 0; mkdir(tmp, 0777); }
}
*/
void crearDirectorio(const char* ruta) 
{
    char tmp[512];
    strcpy(tmp, ruta);

    char* p =
#ifdef _WIN32	 //si windows
        strrchr(tmp, '\\');
#else			//si es linux o otro
        strrchr(tmp, '/');
#endif

    if (p) {
        *p = 0;

#ifdef _WIN32
        mkdir(tmp);
#else
        mkdir(tmp, 0777);
#endif
    }
}



// Crear archivo
void crearArchivo(const char* ruta, const char* cabecera) {
    crearDirectorio(ruta);
    FILE* f = fopen(ruta, "r");
    if(!f) {
        f = fopen(ruta, "w");
        if(f && cabecera) fprintf(f, "%s\n", cabecera);
    }
    if(f) fclose(f);
}

// Leer archivo
int leer_archivo(const char* ruta, char l[][MAX_LINEA]) {
    FILE* f = fopen(ruta, "r");
    if(!f) return 0;
    int n = 0;
    while(fgets(l[n], MAX_LINEA, f)) {
        l[n][strcspn(l[n], "\n")] = 0;
        n++;
    }
    fclose(f);
    return n;
}

// Guardar archivo
void guardar_archivo(const char* ruta, char l[][MAX_LINEA], int n) {
    FILE* f = fopen(ruta, "w");
    for(int i=0;i<n;i++)
        fprintf(f,"%s\n",l[i]);
    fclose(f);
}

// Agregar fila
void agregar_fila(const char* ruta, const char* fila) {
    FILE* f = fopen(ruta,"a");
    if(f) {
        fprintf(f,"%s\n",fila);
        fclose(f);
    }
}

// Inicialización
void inicializacion() {
    crearArchivo(G_archivos[ARCH_INVENTARIO][0], G_archivos[ARCH_INVENTARIO][1]);
    for(int i=0;i<2;i++)
        crearArchivo(G_archivos_registros[i][0], G_archivos_registros[i][1]);
}
