#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_fabricas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

static const char *ARCH_FAB_PRODUCTOS = "fabrica_productos.txt";
static const char *ARCH_FAB_MOV = "fabrica_movimientos.txt";

static void fabrica_asegurar_archivos(void)
{
    crearArchivo(ARCH_FAB_PRODUCTOS, "_00_CODIGO|_01_NOMBRE|_02_COSTO_UNITARIO|_03_STOCK|_04_FECHA");
    crearArchivo(ARCH_FAB_MOV, "_00_CODIGO|_01_OPERACION|_02_CANTIDAD|_03_RESPONSABLE_DESTINO|_04_STOCK_FINAL|_05_FECHA");
}

static int fabrica_buscar_producto(char lineas[][MAX_LINEA], int n, const char *codigo)
{
    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int cols = split(lineas[i], G_caracter_separacion[0], &partes);
        int coincide = (cols > 0 && partes && partes[0] && strcmp(partes[0], codigo) == 0);

        if (partes)
        {
            free_split(partes);
        }

        if (coincide)
        {
            return i;
        }
    }

    return -1;
}

int fabrica_buscar_producto_en_archivo(const char *ruta_inventario,
                                       const char *codigo,
                                       char **fila_producto)
{
    return texto_buscar_fila_por_columna_en_archivo(ruta_inventario, 0, codigo, 1, fila_producto);
}

int fabrica_registrar_producto(const char *codigo, const char *nombre, float costo_unitario, int stock)
{
    if (!codigo || !nombre || costo_unitario < 0.0f || stock < 0)
    {
        return -1;
    }

    fabrica_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_FAB_PRODUCTOS, lineas);
    if (n <= 0)
    {
        snprintf(lineas[0], MAX_LINEA, "codigo|nombre|costo_unitario|stock|fecha");
        n = 1;
    }

    if (fabrica_buscar_producto(lineas, n, codigo) != -1)
    {
        return -2;
    }

    char fila[MAX_LINEA];
    char fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(fila, sizeof(fila), "%s|%s|%.2f|%d|%s", codigo, nombre, costo_unitario, stock, fecha);
    agregar_fila(ARCH_FAB_PRODUCTOS, fila);
    return 0;
}

int fabrica_producir_lote(const char *codigo, int cantidad, const char *responsable)
{
    if (!codigo || !responsable || cantidad <= 0)
    {
        return -1;
    }

    fabrica_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_FAB_PRODUCTOS, lineas);
    int idx = fabrica_buscar_producto(lineas, n, codigo);
    if (idx == -1)
    {
        return -2;
    }

    char **partes = NULL;
    int cols = split(lineas[idx], G_caracter_separacion[0], &partes);
    if (cols < 4 || !partes || !partes[2] || !partes[3])
    {
        if (partes)
        {
            free_split(partes);
        }
        return -3;
    }

    int stock = atoi(partes[3]);
    stock += cantidad;

    char fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(lineas[idx], MAX_LINEA, "%s|%s|%.2f|%d|%s", partes[0], partes[1] ? partes[1] : "", (float)atof(partes[2]), stock, fecha);
    free_split(partes);

    guardar_archivo(ARCH_FAB_PRODUCTOS, lineas, n);

    {
        char mov[MAX_LINEA];
        snprintf(mov, sizeof(mov), "%s|PRODUCCION|%d|%s|%d|%s", codigo, cantidad, responsable, stock, fecha);
        agregar_fila(ARCH_FAB_MOV, mov);
    }

    return 0;
}

int fabrica_despachar_producto(const char *codigo, int cantidad, const char *destino)
{
    if (!codigo || !destino || cantidad <= 0)
    {
        return -1;
    }

    fabrica_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_FAB_PRODUCTOS, lineas);
    int idx = fabrica_buscar_producto(lineas, n, codigo);
    if (idx == -1)
    {
        return -2;
    }

    char **partes = NULL;
    int cols = split(lineas[idx], G_caracter_separacion[0], &partes);
    if (cols < 4 || !partes || !partes[2] || !partes[3])
    {
        if (partes)
        {
            free_split(partes);
        }
        return -3;
    }

    int stock = atoi(partes[3]);
    if (stock < cantidad)
    {
        free_split(partes);
        return -4;
    }
    stock -= cantidad;

    char fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(lineas[idx], MAX_LINEA, "%s|%s|%.2f|%d|%s", partes[0], partes[1] ? partes[1] : "", (float)atof(partes[2]), stock, fecha);
    free_split(partes);

    guardar_archivo(ARCH_FAB_PRODUCTOS, lineas, n);

    {
        char mov[MAX_LINEA];
        snprintf(mov, sizeof(mov), "%s|DESPACHO|%d|%s|%d|%s", codigo, cantidad, destino, stock, fecha);
        agregar_fila(ARCH_FAB_MOV, mov);
    }

    return 0;
}

int fabrica_consultar_producto(const char *codigo, float *costo_unitario, int *stock)
{
    if (!codigo || !costo_unitario || !stock)
    {
        return -1;
    }

    fabrica_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_FAB_PRODUCTOS, lineas);
    int idx = fabrica_buscar_producto(lineas, n, codigo);
    if (idx == -1)
    {
        return -2;
    }

    char **partes = NULL;
    int cols = split(lineas[idx], G_caracter_separacion[0], &partes);
    if (cols < 4 || !partes || !partes[2] || !partes[3])
    {
        if (partes)
        {
            free_split(partes);
        }
        return -3;
    }

    *costo_unitario = (float)atof(partes[2]);
    *stock = atoi(partes[3]);
    free_split(partes);
    return 0;
}
