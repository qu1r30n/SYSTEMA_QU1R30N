#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_fabricas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_arreglos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_fabricas.h"

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

int modelo_fabrica_registrar_producto(char *texto)
{
    char *vars[][4] = {
        {"codigo", "string", "", ""},
        {"nombre", "string", "", ""},
        {"costo_unitario", "float", "0", ""},
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
    float costo_unitario = 0.0f;
    int stock = 0;

    int ok = -1;
    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) == 0 &&
        arreglo_obtener_cadena_por_orden(&datos, 1, &nombre) == 0 &&
        arreglo_obtener_flotante_por_orden(&datos, 2, &costo_unitario) == 0 &&
        arreglo_obtener_entero_por_orden(&datos, 3, &stock) == 0)
    {
        ok = fabrica_registrar_producto(codigo, nombre, costo_unitario, stock);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_fabrica_producir_lote(char *texto)
{
    char *vars[][4] = {
        {"codigo", "string", "", ""},
        {"cantidad", "int", "1", ""},
        {"responsable", "string", "NA", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *codigo = NULL;
    char *responsable = NULL;
    int cantidad = 0;

    int ok = -1;
    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) == 0 &&
        arreglo_obtener_entero_por_orden(&datos, 1, &cantidad) == 0 &&
        arreglo_obtener_cadena_por_orden(&datos, 2, &responsable) == 0)
    {
        ok = fabrica_producir_lote(codigo, cantidad, responsable);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_fabrica_despachar_producto(char *texto)
{
    char *vars[][4] = {
        {"codigo", "string", "", ""},
        {"cantidad", "int", "1", ""},
        {"destino", "string", "NA", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *codigo = NULL;
    char *destino = NULL;
    int cantidad = 0;

    int ok = -1;
    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) == 0 &&
        arreglo_obtener_entero_por_orden(&datos, 1, &cantidad) == 0 &&
        arreglo_obtener_cadena_por_orden(&datos, 2, &destino) == 0)
    {
        ok = fabrica_despachar_producto(codigo, cantidad, destino);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_fabrica_consultar_producto(char *texto)
{
    char *vars[][4] = {
        {"codigo", "string", "", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *codigo = NULL;
    float costo_unitario = 0.0f;
    int stock = 0;

    int ok = -1;
    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) == 0)
    {
        ok = fabrica_consultar_producto(codigo, &costo_unitario, &stock);
        if (ok == 0)
        {
            printf("[FABRICA] codigo=%s | costo_unitario=%.2f | stock=%d\n", codigo, costo_unitario, stock);
        }
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}
