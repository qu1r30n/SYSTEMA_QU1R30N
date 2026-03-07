#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_renta_equipos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

static const char *ARCH_RENTA_EQUIPOS = "renta_equipos.txt";
static const char *ARCH_RENTA_MOV = "renta_alquileres.txt";

static void renta_asegurar_archivos(void)
{
    crearArchivo(ARCH_RENTA_EQUIPOS, "codigo|nombre|costo_dia|stock|fecha");
    crearArchivo(ARCH_RENTA_MOV, "cliente|codigo|dias|cantidad|total|fecha");
}

static int renta_buscar_equipo(char lineas[][MAX_LINEA], int n, const char *codigo)
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

int renta_registrar_equipo(const char *codigo, const char *nombre, float costo_por_dia, int stock)
{
    if (!codigo || !nombre || costo_por_dia < 0.0f || stock < 0)
    {
        return -1;
    }

    renta_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_RENTA_EQUIPOS, lineas);
    if (n <= 0)
    {
        snprintf(lineas[0], MAX_LINEA, "codigo|nombre|costo_dia|stock|fecha");
        n = 1;
    }

    if (renta_buscar_equipo(lineas, n, codigo) != -1)
    {
        return -2;
    }

    char fecha[20];
    char fila[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(fila, sizeof(fila), "%s|%s|%.2f|%d|%s", codigo, nombre, costo_por_dia, stock, fecha);
    agregar_fila(ARCH_RENTA_EQUIPOS, fila);
    return 0;
}

int renta_registrar_alquiler(const char *cliente, const char *codigo, int dias, int cantidad)
{
    if (!cliente || !codigo || dias <= 0 || cantidad <= 0)
    {
        return -1;
    }

    renta_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_RENTA_EQUIPOS, lineas);
    int idx = renta_buscar_equipo(lineas, n, codigo);
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

    float costo_dia = (float)atof(partes[2]);
    int stock = atoi(partes[3]);
    if (stock < cantidad)
    {
        free_split(partes);
        return -4;
    }
    stock -= cantidad;

    char fecha[20];
    char movimiento[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(lineas[idx], MAX_LINEA, "%s|%s|%.2f|%d|%s", partes[0], partes[1] ? partes[1] : "", costo_dia, stock, fecha);
    free_split(partes);

    guardar_archivo(ARCH_RENTA_EQUIPOS, lineas, n);

    snprintf(movimiento, sizeof(movimiento), "%s|%s|%d|%d|%.2f|%s", cliente, codigo, dias, cantidad, costo_dia * (float)dias * (float)cantidad, fecha);
    agregar_fila(ARCH_RENTA_MOV, movimiento);
    return 0;
}

int renta_consultar_equipo(const char *codigo, float *costo_por_dia, int *stock)
{
    if (!codigo || !costo_por_dia || !stock)
    {
        return -1;
    }

    renta_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_RENTA_EQUIPOS, lineas);
    int idx = renta_buscar_equipo(lineas, n, codigo);
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

    *costo_por_dia = (float)atof(partes[2]);
    *stock = atoi(partes[3]);
    free_split(partes);
    return 0;
}
