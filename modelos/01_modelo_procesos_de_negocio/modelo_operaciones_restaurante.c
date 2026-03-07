#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_restaurante.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_restaurante.h"

static int obtener_entero(StructurasDinamicas *datos, int orden, int *salida)
{
    int *ptr = (int *)obtenerValorPorOrden(datos, orden);
    if (!ptr || !salida)
    {
        return -1;
    }
    *salida = *ptr;
    return 0;
}

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

int modelo_restaurante_registrar_platillo(char *texto)
{
    char *vars[][4] = {
        {"codigo", "string", "NOSE", ""},
        {"nombre", "string", "NOSE", ""},
        {"precio", "float", "0", ""},
        {"stock", "int", "0", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *codigo = NULL;
    char *nombre = NULL;
    float precio = 0.0f;
    int stock = 0;

    int ok = -1;
    if (obtener_cadena(&datos, 0, &codigo) == 0 &&
        obtener_cadena(&datos, 1, &nombre) == 0 &&
        obtener_flotante(&datos, 2, &precio) == 0 &&
        obtener_entero(&datos, 3, &stock) == 0)
    {
        ok = restaurante_registrar_platillo(codigo, nombre, precio, stock);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_restaurante_registrar_pedido(char *texto)
{
    char *vars[][4] = {
        {"mesa", "string", "MESA1", ""},
        {"codigo", "string", "NOSE", ""},
        {"cantidad", "int", "1", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *mesa = NULL;
    char *codigo = NULL;
    int cantidad = 0;

    int ok = -1;
    if (obtener_cadena(&datos, 0, &mesa) == 0 &&
        obtener_cadena(&datos, 1, &codigo) == 0 &&
        obtener_entero(&datos, 2, &cantidad) == 0)
    {
        ok = restaurante_registrar_pedido(mesa, codigo, cantidad);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_restaurante_consultar_platillo(char *texto)
{
    char *vars[][4] = {
        {"codigo", "string", "NOSE", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *codigo = NULL;
    float precio = 0.0f;
    int stock = 0;
    int ok = -1;

    if (obtener_cadena(&datos, 0, &codigo) == 0)
    {
        ok = restaurante_consultar_platillo(codigo, &precio, &stock);
        if (ok == 0)
        {
            printf("[RESTAURANTE] codigo=%s | precio=%.2f | stock=%d\n", codigo, precio, stock);
        }
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}
