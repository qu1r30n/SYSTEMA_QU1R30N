#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_restaurante.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

static const char *ARCH_REST_MENU = "restaurante_menu.txt";
static const char *ARCH_REST_PEDIDOS = "restaurante_pedidos.txt";

static void restaurante_asegurar_archivos(void)
{
    crearArchivo(ARCH_REST_MENU, "_00_CODIGO|_01_NOMBRE|_02_PRECIO_VENTA|_03_STOCK|_04_FECHA");
    crearArchivo(ARCH_REST_PEDIDOS, "_00_MESA|_01_CODIGO|_02_CANTIDAD|_03_TOTAL_VENTA|_04_FECHA");
}

static int restaurante_buscar_menu(char lineas[][MAX_LINEA], int n, const char *codigo)
{
    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int cols = split(lineas[i], G_caracter_separacion[0], &partes);
        int coincide = (cols > 0 && partes[0] && strcmp(partes[0], codigo) == 0);
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

int restaurante_registrar_platillo(const char *codigo, const char *nombre, float precio, int stock)
{
    if (!codigo || !nombre || stock < 0)
    {
        return -1;
    }

    restaurante_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_REST_MENU, lineas);
    if (n <= 0)
    {
        snprintf(lineas[0], MAX_LINEA, "codigo|nombre|precio|stock|fecha");
        n = 1;
    }

    if (restaurante_buscar_menu(lineas, n, codigo) != -1)
    {
        return -2;
    }

    char fecha[20];
    char fila[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(fila, sizeof(fila), "%s|%s|%.2f|%d|%s", codigo, nombre, precio, stock, fecha);
    agregar_fila(ARCH_REST_MENU, fila);
    return 0;
}

int restaurante_registrar_pedido(const char *mesa, const char *codigo, int cantidad)
{
    if (!mesa || !codigo || cantidad <= 0)
    {
        return -1;
    }

    restaurante_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_REST_MENU, lineas);
    int idx = restaurante_buscar_menu(lineas, n, codigo);
    if (idx == -1)
    {
        return -2;
    }

    char **partes = NULL;
    int cols = split(lineas[idx], G_caracter_separacion[0], &partes);
    if (cols < 4 || !partes[2] || !partes[3])
    {
        if (partes)
        {
            free_split(partes);
        }
        return -3;
    }

    float precio = (float)atof(partes[2]);
    int stock = atoi(partes[3]);
    if (stock < cantidad)
    {
        free_split(partes);
        return -4;
    }

    stock -= cantidad;

    char fecha[20];
    char pedido[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(lineas[idx], MAX_LINEA, "%s|%s|%.2f|%d|%s", partes[0], partes[1] ? partes[1] : "", precio, stock, fecha);
    free_split(partes);

    guardar_archivo(ARCH_REST_MENU, lineas, n);

    snprintf(pedido, sizeof(pedido), "%s|%s|%d|%.2f|%s", mesa, codigo, cantidad, precio * (float)cantidad, fecha);
    agregar_fila(ARCH_REST_PEDIDOS, pedido);
    return 0;
}

int restaurante_consultar_platillo(const char *codigo, float *precio, int *stock)
{
    if (!codigo || !precio || !stock)
    {
        return -1;
    }

    restaurante_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_REST_MENU, lineas);
    int idx = restaurante_buscar_menu(lineas, n, codigo);
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

    *precio = (float)atof(partes[2]);
    *stock = atoi(partes[3]);
    free_split(partes);
    return 0;
}
