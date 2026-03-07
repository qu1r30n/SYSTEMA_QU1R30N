#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_banco.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_banco.h"

static int obtener_flotante(StructurasDinamicas *datos, int orden, float *salida)
{
    float *ptr = (float *)obtenerValorPorOrden(datos, orden);
    if (!ptr || !salida)
    {
        return -1;
    }
    *salida = *ptr;
    return 0;
}

static int obtener_cadena(StructurasDinamicas *datos, int orden, char **salida)
{
    char *ptr = (char *)obtenerValorPorOrden(datos, orden);
    if (!ptr || !salida)
    {
        return -1;
    }
    *salida = ptr;
    return 0;
}

static int parsear(char *texto, char *vars[][4], StructurasDinamicas *datos, char ***partes)
{
    if (!texto)
    {
        return -1;
    }

    char **tmp = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!tmp)
    {
        return -2;
    }

    *datos = procesar_partes_del_texto(tmp, vars, G_caracter_separacion_nom_parametro_de_valor[0]);
    *partes = tmp;
    return 0;
}

int modelo_banco_registrar_cuenta(char *texto)
{
    char *vars[][4] = {
        {"cuenta", "string", "", ""},
        {"titular", "string", "", ""},
        {"saldo_inicial", "float", "0", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *cuenta = NULL;
    char *titular = NULL;
    float saldo = 0.0f;

    int ok = -1;
    if (obtener_cadena(&datos, 0, &cuenta) == 0 &&
        obtener_cadena(&datos, 1, &titular) == 0 &&
        obtener_flotante(&datos, 2, &saldo) == 0)
    {
        ok = banco_registrar_cuenta(cuenta, titular, saldo);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_banco_depositar(char *texto)
{
    char *vars[][4] = {
        {"cuenta", "string", "", ""},
        {"monto", "float", "0", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *cuenta = NULL;
    float monto = 0.0f;

    int ok = -1;
    if (obtener_cadena(&datos, 0, &cuenta) == 0 &&
        obtener_flotante(&datos, 1, &monto) == 0)
    {
        ok = banco_depositar(cuenta, monto);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_banco_retirar(char *texto)
{
    char *vars[][4] = {
        {"cuenta", "string", "", ""},
        {"monto", "float", "0", ""},
        {"motivo", "string", "NA", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *cuenta = NULL;
    char *motivo = NULL;
    float monto = 0.0f;

    int ok = -1;
    if (obtener_cadena(&datos, 0, &cuenta) == 0 &&
        obtener_flotante(&datos, 1, &monto) == 0 &&
        obtener_cadena(&datos, 2, &motivo) == 0)
    {
        ok = banco_retirar(cuenta, monto, motivo);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_banco_consultar_saldo(char *texto)
{
    char *vars[][4] = {
        {"cuenta", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *cuenta = NULL;
    float saldo = 0.0f;

    int ok = -1;
    if (obtener_cadena(&datos, 0, &cuenta) == 0)
    {
        ok = banco_consultar_saldo(cuenta, &saldo);
        if (ok == 0)
        {
            printf("[BANCO] cuenta=%s | saldo=%.2f\n", cuenta, saldo);
        }
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}
