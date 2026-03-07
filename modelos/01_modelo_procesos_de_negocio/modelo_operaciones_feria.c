#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_feria.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_arreglos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_feria.h"

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

int modelo_feria_registrar_premio(char *texto)
{
    char *vars[][4] = {
        {"codigo", "string", "", ""},
        {"nombre", "string", "", ""},
        {"puntos", "int", "0", ""},
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
    int puntos = 0;
    int stock = 0;

    int ok = -1;
    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) == 0 &&
        arreglo_obtener_cadena_por_orden(&datos, 1, &nombre) == 0 &&
        arreglo_obtener_entero_por_orden(&datos, 2, &puntos) == 0 &&
        arreglo_obtener_entero_por_orden(&datos, 3, &stock) == 0)
    {
        ok = feria_registrar_premio(codigo, nombre, puntos, stock);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_feria_canjear_premio(char *texto)
{
    char *vars[][4] = {
        {"usuario", "string", "", ""},
        {"codigo", "string", "", ""},
        {"cantidad", "int", "1", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *usuario = NULL;
    char *codigo = NULL;
    int cantidad = 0;

    int ok = -1;
    if (arreglo_obtener_cadena_por_orden(&datos, 0, &usuario) == 0 &&
        arreglo_obtener_cadena_por_orden(&datos, 1, &codigo) == 0 &&
        arreglo_obtener_entero_por_orden(&datos, 2, &cantidad) == 0)
    {
        ok = feria_canjear_premio(usuario, codigo, cantidad);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_feria_consultar_premio(char *texto)
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
    int puntos = 0;
    int stock = 0;
    int ok = -1;

    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) == 0)
    {
        ok = feria_consultar_premio(codigo, &puntos, &stock);
        if (ok == 0)
        {
            printf("[FERIA] codigo=%s | puntos=%d | stock=%d\n", codigo, puntos, stock);
        }
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}
