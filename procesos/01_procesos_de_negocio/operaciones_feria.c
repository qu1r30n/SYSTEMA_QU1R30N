#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_feria.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

static const char *ARCH_FERIA_PREMIOS = "feria_premios.txt";
static const char *ARCH_FERIA_CANJES = "feria_canjes.txt";

static void feria_asegurar_archivos(void)
{
    crearArchivo(ARCH_FERIA_PREMIOS, "codigo|nombre|puntos|stock|fecha");
    crearArchivo(ARCH_FERIA_CANJES, "usuario|codigo|cantidad|puntos_totales|fecha");
}

static int feria_buscar_premio(char lineas[][MAX_LINEA], int n, const char *codigo)
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

int feria_registrar_premio(const char *codigo, const char *nombre, int puntos, int stock)
{
    if (!codigo || !nombre || puntos < 0 || stock < 0)
    {
        return -1;
    }

    feria_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_FERIA_PREMIOS, lineas);
    if (n <= 0)
    {
        snprintf(lineas[0], MAX_LINEA, "codigo|nombre|puntos|stock|fecha");
        n = 1;
    }

    if (feria_buscar_premio(lineas, n, codigo) != -1)
    {
        return -2;
    }

    char fecha[20];
    char fila[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(fila, sizeof(fila), "%s|%s|%d|%d|%s", codigo, nombre, puntos, stock, fecha);
    agregar_fila(ARCH_FERIA_PREMIOS, fila);
    return 0;
}

int feria_canjear_premio(const char *usuario, const char *codigo, int cantidad)
{
    if (!usuario || !codigo || cantidad <= 0)
    {
        return -1;
    }

    feria_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_FERIA_PREMIOS, lineas);
    int idx = feria_buscar_premio(lineas, n, codigo);
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

    int puntos = atoi(partes[2]);
    int stock = atoi(partes[3]);
    if (stock < cantidad)
    {
        free_split(partes);
        return -4;
    }
    stock -= cantidad;

    char fecha[20];
    char canje[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(lineas[idx], MAX_LINEA, "%s|%s|%d|%d|%s", partes[0], partes[1] ? partes[1] : "", puntos, stock, fecha);
    free_split(partes);

    guardar_archivo(ARCH_FERIA_PREMIOS, lineas, n);

    snprintf(canje, sizeof(canje), "%s|%s|%d|%d|%s", usuario, codigo, cantidad, puntos * cantidad, fecha);
    agregar_fila(ARCH_FERIA_CANJES, canje);
    return 0;
}
