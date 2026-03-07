#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

// Leer inventario completo
int leerInventario(char inventario[][COLUMNAS][256], int maxProductos)
{
    char lineas[MAX_PRODUCTOS + 1][MAX_LINEA];
    int nLineas = leer_archivo(G_archivos[ARCH_INVENTARIO][0], lineas);

    if (nLineas <= 1)
    {
        return 0;
    }

    int fila = 0;
    for (int i = 1; i < nLineas && fila < maxProductos; i++)
    {
        char **partes = NULL;
        int n = split(lineas[i], G_caracter_separacion[0], &partes);

        if (n < 0 || partes == NULL)
        {
            continue;
        }

        for (int j = 0; j < COLUMNAS; j++)
        {
            const char *valor = (j < n && partes[j]) ? partes[j] : "0";
            snprintf(inventario[fila][j], sizeof(inventario[fila][j]), "%s", valor);
        }

        free_split(partes);
        fila++;
    }
    return fila;
}

// Guardar inventario
void guardarInventario(char inventario[][COLUMNAS][256], int n)
{
    char lineas[MAX_PRODUCTOS + 1][MAX_LINEA];
    snprintf(lineas[0], sizeof(lineas[0]), "%s", G_archivos[ARCH_INVENTARIO][1]);
    for (int i = 0; i < n; i++)
    {
        lineas[i + 1][0] = '\0';
        size_t usado = 0;
        for (int j = 0; j < COLUMNAS; j++)
        {
            int escritos = snprintf(lineas[i + 1] + usado,
                                    sizeof(lineas[i + 1]) - usado,
                                    "%s",
                                    inventario[i][j]);
            if (escritos < 0)
            {
                break;
            }

            if ((size_t)escritos >= sizeof(lineas[i + 1]) - usado)
            {
                usado = sizeof(lineas[i + 1]) - 1;
                break;
            }

            usado += (size_t)escritos;

            if (j < COLUMNAS - 1)
            {
                escritos = snprintf(lineas[i + 1] + usado,
                                    sizeof(lineas[i + 1]) - usado,
                                    "%s",
                                    G_caracter_separacion[0]);
                if (escritos < 0)
                {
                    break;
                }

                if ((size_t)escritos >= sizeof(lineas[i + 1]) - usado)
                {
                    usado = sizeof(lineas[i + 1]) - 1;
                    break;
                }

                usado += (size_t)escritos;
            }
        }
    }
    guardar_archivo(G_archivos[ARCH_INVENTARIO][0], lineas, n + 1);
}

// Buscar producto
int buscarProducto(char inventario[][COLUMNAS][256], int n, char *codigo)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(inventario[i][5], codigo) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Agregar producto
void agregarProducto(int id,
                     char *producto,
                     float contenido,
                     char *tipo_medida,
                     float precio_venta,
                     char *cod_barras,
                     float cantidad,
                     float costo_compra,
                     char *proveedor)
{
    char inventario[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario, MAX_PRODUCTOS);

    if (n < 0)
    {
        return;
    }

    if (n >= MAX_PRODUCTOS)
    {
        /* No hay espacio para otro producto. */
        return;
    }

    for (int i = 0; i < COLUMNAS; i++)
    {
        snprintf(inventario[n][i], sizeof(inventario[n][i]), "%s", "0");
    }
    sprintf(inventario[n][0], "%d", id);
    snprintf(inventario[n][1], sizeof(inventario[n][1]), "%s", producto ? producto : "");
    sprintf(inventario[n][2], "%.2f", contenido);
    snprintf(inventario[n][3], sizeof(inventario[n][3]), "%s", tipo_medida ? tipo_medida : "");
    sprintf(inventario[n][4], "%.2f", precio_venta);
    snprintf(inventario[n][5], sizeof(inventario[n][5]), "%s", cod_barras ? cod_barras : "");
    sprintf(inventario[n][6], "%.2f", cantidad);
    sprintf(inventario[n][7], "%.2f", costo_compra);
    snprintf(inventario[n][8], sizeof(inventario[n][8]), "%s", proveedor ? proveedor : "");
    fechaActual(inventario[n][18], "%Y-%m-%d");

    guardarInventario(inventario, n + 1);
}

// Venta simple
int venta(char *codigo, int cantidad, char *sucursal)
{
    char inventario[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario, MAX_PRODUCTOS);
    int idx = buscarProducto(inventario, n, codigo);
    if (idx == -1)
    {
        return -2;
    }
    int stock = atoi(inventario[idx][6]);
    if (stock < cantidad)
    {
        return -3;
    }
    stock -= cantidad;
    sprintf(inventario[idx][6], "%d", stock);
    fechaActual(inventario[idx][18], "%Y-%m-%d");
    guardarInventario(inventario, n);

    char registro[512], fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    sprintf(registro, "%s%s%d%s%s%s%s", codigo, G_caracter_separacion[0], cantidad, G_caracter_separacion[0], sucursal, G_caracter_separacion[0], fecha);
    agregar_fila(G_archivos_registros[0][0], registro);
    return 0;
}

// Compra simple
int compra(char *codigo, int cantidad, char *proveedor)
{
    char inventario[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario, MAX_PRODUCTOS);
    int idx = buscarProducto(inventario, n, codigo);
    if (idx == -1)
        return -2;
    int stock = atoi(inventario[idx][6]);
    stock += cantidad;
    sprintf(inventario[idx][6], "%d", stock);
    fechaActual(inventario[idx][18], "%Y-%m-%d");
    guardarInventario(inventario, n);

    char registro[512], fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    sprintf(registro, "%s%s%d%s%s%s%s", codigo, G_caracter_separacion[0], cantidad, G_caracter_separacion[0], proveedor, G_caracter_separacion[0], fecha);
    agregar_fila(G_archivos_registros[1][0], registro);
    return 0;
}

int tienda_consultar_producto(const char *codigo, float *precio_venta, float *stock)
{
    if (!codigo || !precio_venta || !stock)
    {
        return -1;
    }

    char inventario[MAX_PRODUCTOS][COLUMNAS][256];
    int n = leerInventario(inventario, MAX_PRODUCTOS);
    int idx = buscarProducto(inventario, n, (char *)codigo);
    if (idx == -1)
    {
        return -2;
    }

    *precio_venta = (float)atof(inventario[idx][4]);
    *stock = (float)atof(inventario[idx][6]);
    return 0;
}
