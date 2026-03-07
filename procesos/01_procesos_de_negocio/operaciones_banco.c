#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_banco.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

static const char *ARCH_BANCO_CUENTAS = "banco_cuentas.txt";
static const char *ARCH_BANCO_MOV = "banco_movimientos.txt";

static void banco_asegurar_archivos(void)
{
    crearArchivo(ARCH_BANCO_CUENTAS, "cuenta|titular|saldo|fecha");
    crearArchivo(ARCH_BANCO_MOV, "cuenta|tipo|monto|saldo_final|motivo|fecha");
}

static int banco_buscar_cuenta(char lineas[][MAX_LINEA], int n, const char *cuenta)
{
    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int cols = split(lineas[i], G_caracter_separacion[0], &partes);
        int coincide = (cols > 0 && partes[0] && strcmp(partes[0], cuenta) == 0);
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

int banco_registrar_cuenta(const char *cuenta, const char *titular, float saldo_inicial)
{
    if (!cuenta || !titular || saldo_inicial < 0.0f)
    {
        return -1;
    }

    banco_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_BANCO_CUENTAS, lineas);
    if (n <= 0)
    {
        snprintf(lineas[0], MAX_LINEA, "cuenta|titular|saldo|fecha");
        n = 1;
    }

    if (banco_buscar_cuenta(lineas, n, cuenta) != -1)
    {
        return -2;
    }

    char fecha[20];
    char fila[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(fila, sizeof(fila), "%s|%s|%.2f|%s", cuenta, titular, saldo_inicial, fecha);
    agregar_fila(ARCH_BANCO_CUENTAS, fila);

    return 0;
}

int banco_depositar(const char *cuenta, float monto)
{
    if (!cuenta || monto <= 0.0f)
    {
        return -1;
    }

    banco_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_BANCO_CUENTAS, lineas);
    int idx = banco_buscar_cuenta(lineas, n, cuenta);
    if (idx == -1)
    {
        return -2;
    }

    char **partes = NULL;
    int cols = split(lineas[idx], G_caracter_separacion[0], &partes);
    if (cols < 3 || !partes[2])
    {
        if (partes)
        {
            free_split(partes);
        }
        return -3;
    }

    float saldo = (float)atof(partes[2]);
    saldo += monto;

    char fecha[20];
    char movimiento[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(lineas[idx], MAX_LINEA, "%s|%s|%.2f|%s", partes[0], partes[1] ? partes[1] : "", saldo, fecha);
    free_split(partes);

    guardar_archivo(ARCH_BANCO_CUENTAS, lineas, n);

    snprintf(movimiento, sizeof(movimiento), "%s|DEPOSITO|%.2f|%.2f|%s|%s", cuenta, monto, saldo, "NA", fecha);
    agregar_fila(ARCH_BANCO_MOV, movimiento);
    return 0;
}

int banco_retirar(const char *cuenta, float monto, const char *motivo)
{
    if (!cuenta || !motivo || monto <= 0.0f)
    {
        return -1;
    }

    banco_asegurar_archivos();

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ARCH_BANCO_CUENTAS, lineas);
    int idx = banco_buscar_cuenta(lineas, n, cuenta);
    if (idx == -1)
    {
        return -2;
    }

    char **partes = NULL;
    int cols = split(lineas[idx], G_caracter_separacion[0], &partes);
    if (cols < 3 || !partes[2])
    {
        if (partes)
        {
            free_split(partes);
        }
        return -3;
    }

    float saldo = (float)atof(partes[2]);
    if (saldo < monto)
    {
        free_split(partes);
        return -4;
    }
    saldo -= monto;

    char fecha[20];
    char movimiento[MAX_LINEA];
    fechaActual(fecha, "%Y-%m-%d");
    snprintf(lineas[idx], MAX_LINEA, "%s|%s|%.2f|%s", partes[0], partes[1] ? partes[1] : "", saldo, fecha);
    free_split(partes);

    guardar_archivo(ARCH_BANCO_CUENTAS, lineas, n);

    snprintf(movimiento, sizeof(movimiento), "%s|RETIRO|%.2f|%.2f|%s|%s", cuenta, monto, saldo, motivo, fecha);
    agregar_fila(ARCH_BANCO_MOV, movimiento);
    return 0;
}
