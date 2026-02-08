#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

// Leer inventario completo
int leerInventario(char inventario[][COLUMNAS][256], int maxProductos){
    char lineas[MAX_PRODUCTOS+1][MAX_LINEA];
    int nLineas = leer_archivo(G_archivos[ARCH_INVENTARIO][0], lineas);

    int fila = 0;
    for(int i=1;i<nLineas && fila<maxProductos;i++){
        char **partes;
        int n = split(lineas[i], G_caracter_separacion[0], &partes);
        for(int j=0;j<COLUMNAS;j++)
            strcpy(inventario[fila][j], (j<n)?partes[j]:"0");
        free_split(partes,n);
        fila++;
    }
    return fila;
}

// Guardar inventario
void guardarInventario(char inventario[][COLUMNAS][256], int n){
    char lineas[MAX_PRODUCTOS+1][MAX_LINEA];
    strcpy(lineas[0], G_archivos[ARCH_INVENTARIO][1]);
    for(int i=0;i<n;i++){
        lineas[i+1][0]=0;
        for(int j=0;j<COLUMNAS;j++){
            strcat(lineas[i+1], inventario[i][j]);
            if(j<COLUMNAS-1) strcat(lineas[i+1], G_caracter_separacion[0]);
        }
    }
    guardar_archivo(G_archivos[ARCH_INVENTARIO][0], lineas, n+1);
}

// Buscar producto
int buscarProducto(char inventario[][COLUMNAS][256], int n, const char* codigo){
    for(int i=0;i<n;i++)
        if(strcmp(inventario[i][5],codigo)==0)
            return i;
    return -1;
}

// Agregar producto
void agregarProducto(const char* id,const char* producto,const char* contenido,
                     const char* tipo_medida,const char* precio_venta,
                     const char* cod_barras,const char* cantidad,
                     const char* costo_compra,const char* proveedor){
    char inventario[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario, MAX_PRODUCTOS);

    for(int i=0;i<COLUMNAS;i++) strcpy(inventario[n][i],"0");
    strcpy(inventario[n][0],id);
    strcpy(inventario[n][1],producto);
    strcpy(inventario[n][2],contenido);
    strcpy(inventario[n][3],tipo_medida);
    strcpy(inventario[n][4],precio_venta);
    strcpy(inventario[n][5],cod_barras);
    strcpy(inventario[n][6],cantidad);
    strcpy(inventario[n][7],costo_compra);
    strcpy(inventario[n][8],proveedor);
    fechaActual(inventario[n][18],"%Y-%m-%d");

    guardarInventario(inventario,n+1);
}

// Venta simple
int venta(const char* codigo,int cantidad,const char* sucursal){
    char inventario[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario, MAX_PRODUCTOS);
    int idx = buscarProducto(inventario,n,codigo);
    if(idx==-1) return 0;
    int stock = atoi(inventario[idx][6]);
    if(stock<cantidad) return 0;
    stock-=cantidad;
    sprintf(inventario[idx][6],"%d",stock);
    fechaActual(inventario[idx][18],"%Y-%m-%d");
    guardarInventario(inventario,n);

    char registro[512], fecha[20];
    fechaActual(fecha,"%Y-%m-%d");
    sprintf(registro,"%s%s%d%s%s%s%s",codigo,G_caracter_separacion[0],cantidad,G_caracter_separacion[0],sucursal,G_caracter_separacion[0],fecha);
    agregar_fila(G_archivos_registros[0][0],registro);
    return 1;
}

// Compra simple
int compra(const char* codigo,int cantidad,const char* proveedor){
    char inventario[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario, MAX_PRODUCTOS);
    int idx = buscarProducto(inventario,n,codigo);
    if(idx==-1) return 0;
    int stock = atoi(inventario[idx][6]);
    stock+=cantidad;
    sprintf(inventario[idx][6],"%d",stock);
    fechaActual(inventario[idx][18],"%Y-%m-%d");
    guardarInventario(inventario,n);

    char registro[512], fecha[20];
    fechaActual(fecha,"%Y-%m-%d");
    sprintf(registro,"%s%s%d%s%s%s%s",codigo,G_caracter_separacion[0],cantidad,G_caracter_separacion[0],proveedor,G_caracter_separacion[0],fecha);
    agregar_fila(G_archivos_registros[1][0],registro);
    return 1;
}
