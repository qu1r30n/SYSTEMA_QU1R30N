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
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_arreglos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"

static int construir_datos_desde_texto(
    char *texto,
    char *nombres_variables[][4],
    StructurasDinamicas *datos_out,
    char ***partes_salida)
{
    if (!texto || !nombres_variables || !datos_out || !partes_salida)
    {
        return -1;
    }

    int total_campos = 0;
    while (nombres_variables[total_campos][0])
    {
        total_campos++;
    }

    const char *sep_partes = G_caracter_separacion_nom_parametro_de_valor[1];
    const char *sep_nom_val = G_caracter_separacion_nom_parametro_de_valor[0];

    if (strstr(texto, sep_partes) == NULL && strstr(texto, G_caracter_separacion_funciones_espesificas[1]) != NULL)
    {
        sep_partes = G_caracter_separacion_funciones_espesificas[1];
    }
    if (strstr(texto, sep_nom_val) == NULL && strstr(texto, G_caracter_separacion_funciones_espesificas[2]) != NULL)
    {
        sep_nom_val = G_caracter_separacion_funciones_espesificas[2];
    }

    char **partes = modelo_split(texto, sep_partes);
    if (!partes)
    {
        return -2;
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    if (cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        return -3;
    }

    int formato_con_nombres = 0;
    char **primera_parte = modelo_split(partes[0], sep_nom_val);
    if (primera_parte && primera_parte[0])
    {
        for (int i = 0; i < total_campos; i++)
        {
            if (strcmp(primera_parte[0], nombres_variables[i][0]) == 0)
            {
                formato_con_nombres = 1;
                break;
            }
        }
    }
    if (primera_parte)
    {
        modelo_free_split(primera_parte);
    }

    if (formato_con_nombres)
    {
        *datos_out = procesar_partes_del_texto(partes, nombres_variables, sep_nom_val);
    }
    else
    {
        *datos_out = cargarDesdeArreglo(nombres_variables);

        int indice_valor = 0;
        for (int p = 0; partes[p] != NULL && indice_valor < total_campos; p++)
        {
            char **valores = modelo_split(partes[p], sep_nom_val);
            if (!valores)
            {
                continue;
            }

            for (int t = 0; valores[t] != NULL && indice_valor < total_campos; t++)
            {
                if (strcmp(nombres_variables[indice_valor][1], "string") == 0)
                {
                    asignarValorString(datos_out, nombres_variables[indice_valor][0], valores[t]);
                }
                else if (strcmp(nombres_variables[indice_valor][1], "int") == 0)
                {
                    asignarValorInt(datos_out, nombres_variables[indice_valor][0], atoi(valores[t]));
                }
                else if (strcmp(nombres_variables[indice_valor][1], "float") == 0)
                {
                    asignarValorFloat(datos_out, nombres_variables[indice_valor][0], (float)atof(valores[t]));
                }

                indice_valor++;
            }

            modelo_free_split(valores);
        }
    }

    *partes_salida = partes;
    return 0;
}

// Leer inventario completo
int modelo_leerInventario(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"maxProductos", "int", "0", ""},
            {NULL, NULL, NULL, NULL}};

    char **partes = NULL;
    StructurasDinamicas datos;
    int resultado_parseo = construir_datos_desde_texto(texto, nombres_variables, &datos, &partes);
    if (resultado_parseo != 0)
    {
        return resultado_parseo;
    }

    int maxProductos = 0;
    if (arreglo_obtener_entero_por_orden(&datos, 0, &maxProductos) != 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -4;
    }

    // Para solo conexión: crea un inventario local y llama al proceso.
    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int cantidad = leerInventario(inventario_local, maxProductos);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return cantidad;
}

// Guardar inventario
void modelo_guardarInventario(char *texto)
{
    // En el proceso: guardarInventario(inventario, cuantas_partes) requiere inventario[][][]
    // Con solo "texto" no podemos pasar el inventario real todavía.
    // Conexión mínima: no-op funcional (queda para estructura).
    (void)texto;
    // (Aquí se conectará cuando tengas estructura/estado del inventario en modelo o controlador)
}

// Buscar producto
int modelo_buscarProducto(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"codigo", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}};

    char **partes = NULL;
    StructurasDinamicas datos;
    int resultado_parseo = construir_datos_desde_texto(texto, nombres_variables, &datos, &partes);
    if (resultado_parseo != 0)
    {
        return resultado_parseo;
    }

    char *codigo = NULL;
    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) != 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -4;
    }

    char inventario_local[MAX_PRODUCTOS][COLUMNAS][256];
    int cantidad = leerInventario(inventario_local, MAX_PRODUCTOS);

    int resultado = buscarProducto(inventario_local, cantidad, codigo);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return resultado;
}

// Agregar producto
int modelo_agregarProducto(char *texto)
{
    if (!texto) // Verifica si el texto es NULL
    {
        return -1;
    }

    char *nombres_variables[][4] = // Arreglo de campos esperados con su tipo y valor por defecto
        {
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

    char **partes = NULL;
    StructurasDinamicas datos;
    int resultado_parseo = construir_datos_desde_texto(texto, nombres_variables, &datos, &partes);
    if (resultado_parseo != 0)
    {
        return resultado_parseo;
    }

    int a1 = 0;
    float c1 = 0.0f;
    float e1 = 0.0f;
    float g1 = 0.0f;
    float h1 = 0.0f;
    char *b1 = NULL;
    char *d1 = NULL;
    char *f1 = NULL;
    char *i1 = NULL;

    if (arreglo_obtener_entero_por_orden(&datos, 0, &a1) != 0 ||
        arreglo_obtener_cadena_por_orden(&datos, 1, &b1) != 0 ||
        arreglo_obtener_flotante_por_orden(&datos, 2, &c1) != 0 ||
        arreglo_obtener_cadena_por_orden(&datos, 3, &d1) != 0 ||
        arreglo_obtener_flotante_por_orden(&datos, 4, &e1) != 0 ||
        arreglo_obtener_cadena_por_orden(&datos, 5, &f1) != 0 ||
        arreglo_obtener_flotante_por_orden(&datos, 6, &g1) != 0 ||
        arreglo_obtener_flotante_por_orden(&datos, 7, &h1) != 0 ||
        arreglo_obtener_cadena_por_orden(&datos, 8, &i1) != 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -4;
    }

    REGISTRO_DEPURACION("a1 (int): %d\n", a1);     // checa si todo esta bien (para depuracion)
    REGISTRO_DEPURACION("b1 (string): %s\n", b1);  // checa si todo esta bien (para depuracion)
    REGISTRO_DEPURACION("c1 (float): %.2f\n", c1); // checa si todo esta bien (para depuracion)
    REGISTRO_DEPURACION("d1 (string): %s\n", d1);  // checa si todo esta bien (para depuracion)
    REGISTRO_DEPURACION("e1 (float): %.2f\n", e1); // checa si todo esta bien (para depuracion)
    REGISTRO_DEPURACION("f1 (string): %s\n", f1);  // checa si todo esta bien (para depuracion)
    REGISTRO_DEPURACION("g1 (float): %.2f\n", g1); // checa si todo esta bien (para depuracion)
    REGISTRO_DEPURACION("h1 (float): %.2f\n", h1); // checa si todo esta bien (para depuracion)
    REGISTRO_DEPURACION("i1 (string): %s\n", i1);  // checa si todo esta bien (para depuracion)

    agregarProducto(
        a1,
        b1,
        c1,
        d1,
        e1,
        f1,
        g1,
        h1,
        i1);

    modelo_free_split(partes); // Libera la memoria del arreglo de partes
    liberarStructura(&datos);  // Libera la memoria de la estructura dinámica
    return 0;
}

// Venta simple
int modelo_venta(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"codigo", "string", "nose", ""},
            {"cantidad", "int", "0", ""},
            {"sucursal", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}};

    char **partes = NULL;
    StructurasDinamicas datos;
    int resultado_parseo = construir_datos_desde_texto(texto, nombres_variables, &datos, &partes);
    if (resultado_parseo != 0)
    {
        return resultado_parseo;
    }

    // texto: "codigo|cantidad|sucursal"
    char *codigo = NULL;
    char *sucursal = NULL;
    int cantidad = 0;

    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) != 0 ||
        arreglo_obtener_entero_por_orden(&datos, 1, &cantidad) != 0 ||
        arreglo_obtener_cadena_por_orden(&datos, 2, &sucursal) != 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -4;
    }

    int ok = venta(codigo, cantidad, sucursal);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

// Compra simple
int modelo_compra(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] =
        {
            {"codigo", "string", "nose", ""},
            {"cantidad", "int", "0", ""},
            {"proveedor", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}};

    char **partes = NULL;
    StructurasDinamicas datos;
    int resultado_parseo = construir_datos_desde_texto(texto, nombres_variables, &datos, &partes);
    if (resultado_parseo != 0)
    {
        return resultado_parseo;
    }

    // texto: "codigo|cantidad|proveedor"
    char *codigo = NULL;
    char *proveedor = NULL;
    int cantidad = 0;

    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) != 0 ||
        arreglo_obtener_entero_por_orden(&datos, 1, &cantidad) != 0 ||
        arreglo_obtener_cadena_por_orden(&datos, 2, &proveedor) != 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        return -4;
    }

    int ok = compra(codigo, cantidad, proveedor);

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}

int modelo_tienda_consultar_producto(char *texto)
{
    if (!texto)
    {
        return -1;
    }

    char *nombres_variables[][4] = {
        {"codigo", "string", "nose", ""},
        {NULL, NULL, NULL, NULL}};

    char **partes = NULL;
    StructurasDinamicas datos;
    int resultado_parseo = construir_datos_desde_texto(texto, nombres_variables, &datos, &partes);
    if (resultado_parseo != 0)
    {
        return resultado_parseo;
    }

    char *codigo = NULL;
    float precio_venta = 0.0f;
    float stock = 0.0f;

    int ok = -4;
    if (arreglo_obtener_cadena_por_orden(&datos, 0, &codigo) == 0)
    {
        ok = tienda_consultar_producto(codigo, &precio_venta, &stock);
        if (ok == 0)
        {
            printf("[TIENDA] codigo=%s | precio_venta=%.2f | stock=%.2f\n", codigo, precio_venta, stock);
        }
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    return ok;
}
