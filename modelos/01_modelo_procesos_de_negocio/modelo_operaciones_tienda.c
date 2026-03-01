#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <stdlib.h>

#elif defined(__linux__)
#include <stdlib.h>

#elif defined(__XC)
#define _XTAL_FREQ 4000000
#include <xc.h>
/* PIC16F: Sin malloc. Las funciones son stubs. */

#else
#include <stdlib.h>
#endif

/* prototipos del modelo para validar firmas y ajustar retornos */
#include "../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"
#include "../../CLASE_QU1R30N.h"
/* usar el split del modelo de textos */
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"

/* las cabeceras de procesos que se invocan */
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"

// char **G_caracter_separacion = GG_caracter_separacion;//dice que ya no por que ya fue definido en el main

// Leer inventario completo
int modelo_leerInventario(char *texto)
{
    // texto: "maxProductos"
    int maxProductos = (texto && texto[0]) ? atoi(texto) : MAX_PRODUCTOS;

    // Para solo conexión: crea un inventario local y llama al proceso.
    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int cantidad = leerInventario(inventario_local, maxProductos);
    return cantidad;
}

// Guardar inventario
void modelo_guardarInventario(char *texto)
{
    // En el proceso: guardarInventario(inventario, i) requiere inventario[][][]
    // Con solo "texto" no podemos pasar el inventario real todavía.
    // Conexión mínima: no-op funcional (queda para estructura).
    (void)texto;
    // (Aquí se conectará cuando tengas estructura/estado del inventario en modelo o controlador)
}

// Buscar producto
int modelo_buscarProducto(char *texto)
{
    // texto: "codigo"
    if (!texto)
        return -1;

    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int i = leerInventario(inventario_local, MAX_PRODUCTOS);

    return buscarProducto(inventario_local, i, texto);
}

// Agregar producto
int modelo_agregarProducto(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] = {
        {"id", "int", "0", ""},
        {"producto", "string", "nose", ""},
        {"contenido", "float", "0", ""},
        {"tipo_medida", "string", "nose", ""},
        {"precio_venta", "float", "0", ""},
        {"cod_barras", "string", "nose", ""},
        {"cantidad", "float", "0", ""},
        {"costo_compra", "float", "0", ""},
        {"proveedor", "string", "nose", ""},
        {NULL, NULL, NULL, NULL}};

    StructurasDinamicas datos = cargarDesdeArreglo(nombres_variables);

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);

    if (!partes)
    {
        liberarStructura(&datos);
        return -2;
    }

    int i = 0;
    while (partes[i])
    {
        char **nom_parametro_dato = modelo_split(partes[i], G_caracter_separacion_nom_parametro_de_valor[0]);
        if (nom_parametro_dato && nom_parametro_dato[0] && nom_parametro_dato[1])
        {
            int j = 0;
            while (nombres_variables[j][0])
            {
                if (strcmp(nombres_variables[j][0], nom_parametro_dato[0]) == 0)
                {
                    if (strcmp(nombres_variables[j][1], "string") == 0)
                    {
                        asignarValorString(&datos, nombres_variables[j][0], nom_parametro_dato[1]);
                    }
                    else if (strcmp(nombres_variables[j][1], "int") == 0)
                    {
                        asignarValorInt(&datos, nombres_variables[j][0], atoi(nom_parametro_dato[1]));
                    }
                    else if (strcmp(nombres_variables[j][1], "float") == 0)
                    {
                        asignarValorFloat(&datos, nombres_variables[j][0], (float)atof(nom_parametro_dato[1]));
                    }
                    break;
                }
                j++;
            }
        }
        if (nom_parametro_dato)
        {
            modelo_free_split(nom_parametro_dato);
        }
        i++;
    }

    if (i <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -3;
    }

    agregarProducto(
        *(int *)obtenerValorPorOrden(&datos, 0),
        (char *)obtenerValorPorOrden(&datos, 1),
        *(float *)obtenerValorPorOrden(&datos, 2),
        (char *)obtenerValorPorOrden(&datos, 3),
        *(float *)obtenerValorPorOrden(&datos, 4),
        (const char *)obtenerValorPorOrden(&datos, 5),
        *(float *)obtenerValorPorOrden(&datos, 6),
        *(float *)obtenerValorPorOrden(&datos, 7),
        (const char *)obtenerValorPorOrden(&datos, 8));

    modelo_free_split(partes);
    liberarStructura(&datos);
    return 0;
}

// Venta simple
int modelo_venta(char *texto)
{
    // texto: "codigo|cantidad|sucursal"
    if (!texto)
        return -1;

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[0]);
    int i = 0;
    if (partes)
    {
        while (partes[i])
        {
            i++;
        }
    }
    if (i < 3 || !partes)
    {
        if (partes)
            modelo_free_split(partes);
        return -2;
    }

    const char *codigo = partes[0];
    int cantidad = 0;
    if (texto_a_int_seguro(partes[1], &cantidad) != 0)
    {
        cantidad = atoi(partes[1]);
    }
    const char *sucursal = partes[2];

    int ok = venta(codigo, cantidad, sucursal);

    modelo_free_split(partes);
    return ok;
}

// Compra simple
int modelo_compra(char *texto)
{
    // texto: "codigo|cantidad|proveedor"
    if (!texto)
        return -1;

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[0]);
    if (!partes)
        return -2;
    int i = 0;
    while (partes[i])
        i++;
    if (i < 3)
    {
        modelo_free_split(partes);
        return -2;
    }

    const char *codigo = partes[0];
    int cantidad = atoi(partes[1]);
    const char *proveedor = partes[2];

    int ok = compra(codigo, cantidad, proveedor);

    modelo_free_split(partes);
    return ok;
}
