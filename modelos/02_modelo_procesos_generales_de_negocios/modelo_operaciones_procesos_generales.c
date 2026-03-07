#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "../../cabeceras/cabeceras_modelos/02_cabeceras_modelos_generales_de_negocios/modelo_operaciones_procesos_generales.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/02_cabeceras_procesos_generales_de_negocios/operaciones_procesos_generales.h"
#include "../../cabeceras/cabeceras_procesos/02_cabeceras_procesos_generales_de_negocios/operaciones_contadores.h"
#include "../../cabeceras/cabeceras_procesos/02_cabeceras_procesos_generales_de_negocios/operaciones_administradores.h"

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

int modelo_pg_registrar_movimiento(char *texto)
{
    char *vars[][4] = {
        {"ruta_libro", "string", "contabilidad_libro.txt", ""},
        {"tipo", "string", "SALIDA", ""},
        {"monto", "float", "0", ""},
        {"quien", "string", "NA", ""},
        {"negocio", "string", "GENERAL", ""},
        {"concepto", "string", "OPERACION", ""},
        {"item_tipo", "string", "SERVICIO", ""},
        {"item_nombre", "string", "NA", ""},
        {"medio_pago", "string", "NA", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *ruta_libro = NULL;
    char *tipo = NULL;
    char *quien = NULL;
    char *negocio = NULL;
    char *concepto = NULL;
    char *item_tipo = NULL;
    char *item_nombre = NULL;
    char *medio_pago = NULL;
    float monto = 0.0f;

    int resultado = -1;
    if (obtener_cadena(&datos, 0, &ruta_libro) == 0 &&
        obtener_cadena(&datos, 1, &tipo) == 0 &&
        obtener_flotante(&datos, 2, &monto) == 0 &&
        obtener_cadena(&datos, 3, &quien) == 0 &&
        obtener_cadena(&datos, 4, &negocio) == 0 &&
        obtener_cadena(&datos, 5, &concepto) == 0 &&
        obtener_cadena(&datos, 6, &item_tipo) == 0 &&
        obtener_cadena(&datos, 7, &item_nombre) == 0 &&
        obtener_cadena(&datos, 8, &medio_pago) == 0)
    {
        resultado = pg_registrar_movimiento(ruta_libro, tipo, monto, quien, negocio, concepto, item_tipo, item_nombre, medio_pago);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return resultado;
}

int modelo_pg_contador_resumen_general(char *texto)
{
    char *vars[][4] = {
        {"ruta_libro", "string", "contabilidad_libro.txt", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *ruta_libro = NULL;
    float entradas = 0.0f;
    float salidas = 0.0f;
    float saldo = 0.0f;

    int resultado = -1;
    if (obtener_cadena(&datos, 0, &ruta_libro) == 0)
    {
        resultado = pg_contador_resumen_general(ruta_libro, &entradas, &salidas, &saldo);
        if (resultado == 0)
        {
            printf("[CONTADOR] Resumen general -> entradas: %.2f | salidas: %.2f | saldo: %.2f\n", entradas, salidas, saldo);
        }
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return resultado;
}

int modelo_pg_contador_resumen_negocio(char *texto)
{
    char *vars[][4] = {
        {"ruta_libro", "string", "contabilidad_libro.txt", ""},
        {"negocio", "string", "GENERAL", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *ruta_libro = NULL;
    char *negocio = NULL;
    float entradas = 0.0f;
    float salidas = 0.0f;
    float saldo = 0.0f;

    int resultado = -1;
    if (obtener_cadena(&datos, 0, &ruta_libro) == 0 &&
        obtener_cadena(&datos, 1, &negocio) == 0)
    {
        resultado = pg_contador_resumen_negocio(ruta_libro, negocio, &entradas, &salidas, &saldo);
        if (resultado == 0)
        {
            printf("[CONTADOR] Negocio %s -> entradas: %.2f | salidas: %.2f | saldo: %.2f\n", negocio, entradas, salidas, saldo);
        }
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return resultado;
}

int modelo_pg_admin_configurar_presupuesto(char *texto)
{
    char *vars[][4] = {
        {"ruta_presupuestos", "string", "contabilidad_presupuestos.txt", ""},
        {"negocio", "string", "GENERAL", ""},
        {"rubro", "string", "OPERACION", ""},
        {"limite", "float", "0", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *ruta_presupuestos = NULL;
    char *negocio = NULL;
    char *rubro = NULL;
    float limite = 0.0f;

    int resultado = -1;
    if (obtener_cadena(&datos, 0, &ruta_presupuestos) == 0 &&
        obtener_cadena(&datos, 1, &negocio) == 0 &&
        obtener_cadena(&datos, 2, &rubro) == 0 &&
        obtener_flotante(&datos, 3, &limite) == 0)
    {
        resultado = pg_administrador_configurar_presupuesto(ruta_presupuestos, negocio, rubro, limite);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return resultado;
}

int modelo_pg_admin_verificar_presupuesto(char *texto)
{
    char *vars[][4] = {
        {"ruta_libro", "string", "contabilidad_libro.txt", ""},
        {"ruta_presupuestos", "string", "contabilidad_presupuestos.txt", ""},
        {"negocio", "string", "GENERAL", ""},
        {"rubro", "string", "OPERACION", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos;
    char **partes = NULL;
    if (parsear(texto, vars, &datos, &partes) != 0)
    {
        return -1;
    }

    char *ruta_libro = NULL;
    char *ruta_presupuestos = NULL;
    char *negocio = NULL;
    char *rubro = NULL;

    float gastado = 0.0f;
    float limite = 0.0f;
    float disponible = 0.0f;
    int excedido = 0;

    int resultado = -1;
    if (obtener_cadena(&datos, 0, &ruta_libro) == 0 &&
        obtener_cadena(&datos, 1, &ruta_presupuestos) == 0 &&
        obtener_cadena(&datos, 2, &negocio) == 0 &&
        obtener_cadena(&datos, 3, &rubro) == 0)
    {
        resultado = pg_administrador_verificar_presupuesto(ruta_libro, ruta_presupuestos, negocio, rubro,
                                                           &gastado, &limite, &disponible, &excedido);

        if (resultado == 0)
        {
            printf("[ADMIN] Presupuesto %s/%s -> gastado: %.2f | limite: %.2f | disponible: %.2f | excedido: %s\n",
                   negocio, rubro, gastado, limite, disponible, excedido ? "SI" : "NO");
        }
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return resultado;
}
