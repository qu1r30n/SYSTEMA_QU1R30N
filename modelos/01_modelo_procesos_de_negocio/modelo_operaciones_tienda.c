/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - stdlib.h: Memoria dinamica, conversiones y utilidades generales
 * - xc.h: Cabecera del compilador para microcontroladores PIC
 * - ../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h: Dependencia interna del proyecto
 * - ../../CLASE_QU1R30N.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h: Dependencia interna del proyecto
 */
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
#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"
/* usar el split del modelo de textos */
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"

/* las cabeceras de procesos que se invocan */
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"

// char **G_caracter_separacion = G_caracter_separacion;//dice que ya no por que ya fue definido en el main

// Leer inventario completo
/*
 * Uso: Ejecuta modelo_leerInventario de forma segura.
 * Entrada ejemplo: modelo_leerInventario(texto, dir_espacio)
 */
int modelo_leerInventario(char *texto, char *dir_espacio, char *usuario_contraseña_negocio)
{
    if (!dir_espacio) // valida que se haya recibido la ruta del espacio de negocio
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    (void)texto; // no se requieren parametros para leer inventario
    (void)usuario_contraseña_negocio; // reservado para validación futura del negocio; ejemplo: "admin⊓pass123"

    char *retorno_inventario = NULL;
    int cantidad = leerInventario(&retorno_inventario, dir_espacio); // lee el inventario completo y lo devuelve en texto

    if (retorno_inventario)
    {
        imprimirMensaje_para_depurar("\nretorno_inventario: %s\n", retorno_inventario);
        free(retorno_inventario);
    }

    RETORNAR_MODELO_ESTANDAR(cantidad);
}

// Guardar inventario
/*
 * Uso: Ejecuta modelo_guardarInventario de forma segura.
 * Entrada ejemplo: modelo_guardarInventario(texto, dir_espacio)
 */
void modelo_guardarInventario(char *texto, char *dir_espacio, char *usuario_contraseña_negocio)
{
    // En el proceso: guardarInventario(inventario, n, dir_espacio) requiere inventario[][][]
    // Con solo "texto" no podemos pasar el inventario real todavía.
    // Conexión mínima: no-op funcional (queda para estructura).
    (void)texto;
    (void)dir_espacio;                // ruta del espacio de negocio; ejemplo: "espacios\\20260330113640_ferreteria_dan\\"
    (void)usuario_contraseña_negocio; // reservado para validación futura del negocio
                                      // (Aquí se conectará cuando tengas estructura/estado del inventario en modelo o controlador)
}

// Buscar producto
/*
 * Uso: Ejecuta modelo_buscarProducto de forma segura.
 * Entrada ejemplo: modelo_buscarProducto(texto, dir_espacio)
 */
int modelo_buscarProducto(char *texto, char *dir_espacio, char *usuario_contraseña_negocio)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (!texto)
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    if (!dir_espacio) // valida que se haya recibido la ruta del espacio de negocio
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    (void)usuario_contraseña_negocio; // reservado para validación futura del negocio; ejemplo: "admin⊓pass123"

    char *nombres_variables[][4] = {{"codigo", "string", "nose", ""}, {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0; // contador de filas en nombres_variables[] hasta encontrar NULL // ejemplo: 1
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++; // avanza al siguiente parametro esperado // ejemplo: 0->1->NULL
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        RETORNAR_MODELO_ESTANDAR(-2);
    }

    int cuantas_partes = 0; // contador de partes resultantes del split // ejemplo: 1
    while (partes[cuantas_partes])
    {
        cuantas_partes++; // incrementa contador de partes // ejemplo: 0->1
    }

    StructurasDinamicas datos = crearStructuraVacia(); // crea estructura dinamica vacia para guardar los valores parseados // ejemplo: datos con 0 campos
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0) // aborta si el parseo fallo o no hay partes para procesar // ejemplo: ret_parse=-1 -> retorna
    {
        modelo_free_split(partes);                                  // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
        liberarStructura(&datos);                                   // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
        RETORNAR_MODELO_ESTANDAR((ret_parse < 0) ? ret_parse : -3); // si el parseo fallo retorna su codigo, si no hay partes retorna -3 // ejemplo: ret_parse=-1
    }

    char *codigo = (char *)obtenerValorPorOrden(&datos, 0); // obtiene el codigo de barras a buscar
    char *retorno_inventario = NULL;
    int cantidad = leerInventario(&retorno_inventario, dir_espacio); // carga el inventario del espacio indicado en texto
    int resultado = -1;

    if (cantidad > 0 && retorno_inventario)
    {
        char **filas = NULL;
        int total_filas = split(retorno_inventario, "\n", &filas);
        int indice_producto = 0;

        if (total_filas > 1 && filas)
        {
            for (int i = 1; i < total_filas; i++)
            {
                if (!filas[i] || !filas[i][0])
                {
                    continue;
                }

                char *fila_limpia = variable_string("%s", filas[i]);
                if (!fila_limpia)
                {
                    continue;
                }

                int largo = (int)strlen(fila_limpia);
                while (largo > 0 && (fila_limpia[largo - 1] == '\r' || fila_limpia[largo - 1] == '\n'))
                {
                    fila_limpia[largo - 1] = '\0';
                    largo--;
                }

                if (largo <= 0)
                {
                    free(fila_limpia);
                    continue;
                }

                char **columnas = NULL;
                int total_columnas = split(fila_limpia, GG_caracter_separacion[0], &columnas);
                free(fila_limpia);

                if (total_columnas > 4 && columnas && columnas[4] && strcmp(columnas[4], codigo) == 0)
                {
                    resultado = indice_producto;
                    free_split(columnas);
                    break;
                }

                if (columnas)
                {
                    free_split(columnas);
                }

                indice_producto++;
            }
        }

        if (filas)
        {
            free_split(filas);
        }
    }

    free(retorno_inventario);

    modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
    liberarStructura(&datos);  // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
    RETORNAR_MODELO_ESTANDAR(resultado);
}

// Agregar producto
/*
 * Uso: Ejecuta modelo_agregarProducto de forma segura.
 * Entrada ejemplo: modelo_agregarProducto(texto, dir_espacio)
 */
int modelo_agregarProducto(char *texto, char *dir_espacio, char *usuario_contraseña_negocio)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (!texto) {RETORNAR_MODELO_ESTANDAR(-1);}

    if (!dir_espacio) {RETORNAR_MODELO_ESTANDAR(-1);}

    (void)usuario_contraseña_negocio; // reservado para validación futura del negocio; ejemplo: "admin⊓pass123"

    char *nombres_variables[][4] = // Arreglo de campos esperados con su tipo y valor por defecto
        {
            {"producto", "string", "NOSE", ""},
            {"contenido", "float", "-0", ""},
            {"tipo_medida", "string", "NOSE", ""},
            {"precio_venta", "float", "-0", ""},
            {"cod_barras", "string", "NOSE", ""},
            {"cantidad", "float", "-0", ""},
            {"costo_comp", "float", "-0", ""},
            {"provedor", "string", "NOSE¬0", ""},
            {"grupo", "string", "PRODUCTO_PIEZA", ""},
            {"cant_x_paquet", "float", "-0", ""},
            {"es_paquete", "string", "INDIVIDUAL", ""},
            {"codbar_paquete_e_id", "string", "NOSE_2", ""},
            {"cod_bar_individual_es_paq_e_id", "string", "NOSE_3¬1", ""},
            {"ligar_prod_sab", "string", "NOSE", ""},
            {"impuestos", "string", "NOSE", ""},
            {"ingredientes", "string", "NOSE", ""},
            {"caducidad", "string", "-0", ""},
            {"ultimo_mov", "string", "-0", ""},
            {"sucur_vent", "string", "NOSE¬0", ""},
            {"claf_prod", "float", "-0", ""},
            {"dir_img_inter", "string", "NOSE", ""},
            {"dir_img_comp", "string", "NOSE", ""},
            {"info_extra", "string", "NOSE", ""},
            {"proceso_crear", "string", "NOSE", ""},
            {"dir_vid_proc_crear", "string", "NOSE", ""},
            {"tiempo_fabricacion", "float", "-0", ""},
            {"indices_dia_registro_produc_vendido", "string", "0", ""},
            {"indices_mes_registro_produc_vendido", "string", "0", ""},
            {"indices_anio_registro_produc_vendido", "string", "0", ""},
            {"ultima_venta", "string", "", ""},
            {"indices_total_registro_produc_vendido", "string", "0", ""},
            {NULL, NULL, NULL, NULL}
        };

    int cuantos_parametros_hay = 0;                      // contador de filas en nombres_variables[] hasta encontrar NULL // ejemplo: 31
    while (nombres_variables[cuantos_parametros_hay][0]) // Cuenta cuántos campos hay en el arreglo de nombres_variables
    {
        cuantos_parametros_hay++; // avanza al siguiente parametro esperado // ejemplo: 0->1->2->NULL
    }

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[2]);
    if (!partes){RETORNAR_MODELO_ESTANDAR(-2);}

    int cuantas_partes = 0; // contador de partes resultantes del split // ejemplo: 31
    imprimirMensaje_para_depurar("\n\n");
    while (partes[cuantas_partes]) // Cuenta cuántas partes del texto que se reccibio en el parametro hay en el arreglo de partes
    {
        imprimirMensaje_para_depurar("partes[%d]: %s\n", cuantas_partes, partes[cuantas_partes]);
        cuantas_partes++; // incrementa contador de partes // ejemplo: 0->1->2
    }

    StructurasDinamicas datos = crearStructuraVacia(); // crea estructura dinamica vacia para guardar los valores parseados // ejemplo: datos con 0 campos
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0) // aborta si el parseo fallo o no hay partes para procesar // ejemplo: ret_parse=-1 -> retorna
    {
        modelo_free_split(partes);                                  // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
        liberarStructura(&datos);                                   // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
        RETORNAR_MODELO_ESTANDAR((ret_parse < 0) ? ret_parse : -3); // si el parseo fallo retorna su codigo, si no hay partes retorna -3 // ejemplo: ret_parse=-1
    }

    agregarProducto((char *)obtenerValorPorOrden(&datos, 0), *(float *)obtenerValorPorOrden(&datos, 1), (char *)obtenerValorPorOrden(&datos, 2), *(float *)obtenerValorPorOrden(&datos, 3), (char *)obtenerValorPorOrden(&datos, 4), *(float *)obtenerValorPorOrden(&datos, 5), *(float *)obtenerValorPorOrden(&datos, 6), (char *)obtenerValorPorOrden(&datos, 7), (char *)obtenerValorPorOrden(&datos, 8), *(float *)obtenerValorPorOrden(&datos, 9), (char *)obtenerValorPorOrden(&datos, 10), (char *)obtenerValorPorOrden(&datos, 11), (char *)obtenerValorPorOrden(&datos, 12), (char *)obtenerValorPorOrden(&datos, 13), (char *)obtenerValorPorOrden(&datos, 14), (char *)obtenerValorPorOrden(&datos, 15), (char *)obtenerValorPorOrden(&datos, 16), (char *)obtenerValorPorOrden(&datos, 17), (char *)obtenerValorPorOrden(&datos, 18), *(float *)obtenerValorPorOrden(&datos, 19), (char *)obtenerValorPorOrden(&datos, 20), (char *)obtenerValorPorOrden(&datos, 21), (char *)obtenerValorPorOrden(&datos, 22),
                    (char *)obtenerValorPorOrden(&datos, 23), (char *)obtenerValorPorOrden(&datos, 24), *(float *)obtenerValorPorOrden(&datos, 25), (char *)obtenerValorPorOrden(&datos, 26), (char *)obtenerValorPorOrden(&datos, 27), (char *)obtenerValorPorOrden(&datos, 28), (char *)obtenerValorPorOrden(&datos, 29), (char *)obtenerValorPorOrden(&datos, 30),
                    dir_espacio); // pasa la ruta del espacio de negocio para que el proceso sepa donde guardar el producto

    modelo_free_split(partes); // Libera la memoria del arreglo de partes
    liberarStructura(&datos);  // Libera la memoria de la estructura dinámica
    RETORNAR_MODELO_ESTANDAR(0);
}

// Venta simple
/*
 * Uso: Ejecuta modelo_venta de forma segura.
 * Entrada ejemplo: modelo_venta(texto, dir_espacio)
 */
int modelo_venta(char *texto, char *dir_espacio, char *usuario_contraseña_negocio)
{
    imprimirMensaje_para_depurar("modelo_venta: \ntexto=%s, \ndir_espacio=%s,\nusuario_contraseña_negocio=%s\n", texto, dir_espacio, usuario_contraseña_negocio);
    
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (!texto){RETORNAR_MODELO_ESTANDAR(-1);}

    // valida que se haya recibido la ruta del espacio de negocio
    if (!dir_espacio){RETORNAR_MODELO_ESTANDAR(-1);}

    (void)usuario_contraseña_negocio; // reservado para validación futura del negocio; ejemplo: "admin⊓pass123"

    char *nombres_variables[][4] = 
    {
        {"codigo",   "string", "nose", ""}, 
        {"cantidad", "float",  "0",    ""}, 
        {"sucursal", "string", "nose", ""}, 
        {"id",       "string", "",     ""}, 
        {NULL, NULL, NULL, NULL}
    };

    int cuantos_parametros_hay = 0; // contador de filas en nombres_variables[] hasta encontrar NULL // ejemplo: 3
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++; // avanza al siguiente parametro esperado // ejemplo: 0->1->2->NULL
    }

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[2]);
    
    if (!partes){RETORNAR_MODELO_ESTANDAR(-2);}

    int cuantas_partes = 0; // contador de partes resultantes del split // ejemplo: 3
    while (partes[cuantas_partes])
    {
        imprimirMensaje_para_depurar("partes[%d]: %s\n", cuantas_partes, partes[cuantas_partes]);
        cuantas_partes++; // incrementa contador de partes // ejemplo: 0->1->2
    }

    StructurasDinamicas datos = crearStructuraVacia(); // crea estructura dinamica vacia para guardar los valores parseados // ejemplo: datos con 0 campos
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0) // aborta si el parseo fallo o no hay partes para procesar // ejemplo: ret_parse=-1 -> retorna
    {
        modelo_free_split(partes);                                  // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
        liberarStructura(&datos);                                   // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
        RETORNAR_MODELO_ESTANDAR((ret_parse < 0) ? ret_parse : -3); // si el parseo fallo retorna su codigo, si no hay partes retorna -3 // ejemplo: ret_parse=-1
    }

    char *codigo   = (char *)obtenerValorPorOrden(&datos, 0); // codigo de barras del producto vendido
    float cantidad = *(float *)obtenerValorPorOrden(&datos, 1); // cantidad de unidades vendidas
    char *sucursal = (char *)obtenerValorPorOrden(&datos, 2); // sucursal donde se realizo la venta
    char *id       = (char *)obtenerValorPorOrden(&datos, 3); // id directo (opcional; vacio = buscar por codigo)

    int ok = venta(codigo, cantidad, sucursal, id, dir_espacio); // ejecuta la venta en el espacio de negocio indicado

    modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
    liberarStructura(&datos);  // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
    RETORNAR_MODELO_ESTANDAR(ok);
}

// Compra simple
/*
 * Uso: Ejecuta modelo_compra de forma segura.
 * Entrada ejemplo: modelo_compra(texto, dir_espacio)
 */
int modelo_compra(char *texto, char *dir_espacio, char *usuario_contraseña_negocio)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (!texto)
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    if (!dir_espacio) // valida que se haya recibido la ruta del espacio de negocio
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    (void)usuario_contraseña_negocio; // reservado para validación futura del negocio; ejemplo: "admin⊓pass123"

    char *nombres_variables[][4] = {{"codigo", "string", "nose", ""}, {"cantidad", "float", "0", ""}, {"proveedor", "string", "nose", ""}, {"id", "string", "", ""}, {NULL, NULL, NULL, NULL}};

    int cuantos_parametros_hay = 0; // contador de filas en nombres_variables[] hasta encontrar NULL // ejemplo: 3
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++; // avanza al siguiente parametro esperado // ejemplo: 0->1->2->NULL
    }

    char **partes = modelo_split(texto, G_caracter_separacion_nom_parametro_de_valor[1]);
    if (!partes)
    {
        RETORNAR_MODELO_ESTANDAR(-2);
    }

    int cuantas_partes = 0; // contador de partes resultantes del split // ejemplo: 4
    while (partes[cuantas_partes])
    {
        cuantas_partes++; // incrementa contador de partes // ejemplo: 0->1->2
    }

    StructurasDinamicas datos = crearStructuraVacia(); // crea estructura dinamica vacia para guardar los valores parseados // ejemplo: datos con 0 campos
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0) // aborta si el parseo fallo o no hay partes para procesar // ejemplo: ret_parse=-1 -> retorna
    {
        modelo_free_split(partes);                                  // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
        liberarStructura(&datos);                                   // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
        RETORNAR_MODELO_ESTANDAR((ret_parse < 0) ? ret_parse : -3); // si el parseo fallo retorna su codigo, si no hay partes retorna -3 // ejemplo: ret_parse=-1
    }

    char *codigo = (char *)obtenerValorPorOrden(&datos, 0); // codigo de barras del producto comprado
    float cantidad = *(float *)obtenerValorPorOrden(&datos, 1); // cantidad de unidades compradas
    char *proveedor = (char *)obtenerValorPorOrden(&datos, 2); // nombre del proveedor
    char *id = (char *)obtenerValorPorOrden(&datos, 3); // id directo (opcional; vacio = buscar por codigo)

    int ok = compra(codigo, cantidad, proveedor, id, dir_espacio); // ejecuta la compra en el espacio de negocio indicado

    modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
    liberarStructura(&datos);  // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.
    RETORNAR_MODELO_ESTANDAR(ok);
}

// Editar precio
/*
 * Uso: Ejecuta modelo_editarPrecio de forma segura.
 * Entrada ejemplo: modelo_editarPrecio(texto, dir_espacio)
 */
int modelo_editarPrecio(char *texto, char *dir_espacio, char *usuario_contraseña_negocio)
{
    // valida entradas obligatorias del modelo
    if (!texto)
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    if (!dir_espacio)
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    (void)usuario_contraseña_negocio; // reservado para validación futura del negocio

    char *nombres_variables[][4] =
    {
        {"codigo", "string", "", ""},
        {"precio", "string", "", ""},
        {"proveedor", "string", "", ""},
        {"id", "string", "", ""},
        {NULL, NULL, NULL, NULL}
    };

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[2]);
    if (!partes)
    {
        RETORNAR_MODELO_ESTANDAR(-2);
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = crearStructuraVacia();
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);

    if (ret_parse < 0 || cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        RETORNAR_MODELO_ESTANDAR((ret_parse < 0) ? ret_parse : -3);
    }

    char *codigo = (char *)obtenerValorPorOrden(&datos, 0);
    char *precio = (char *)obtenerValorPorOrden(&datos, 1);
    char *proveedor = (char *)obtenerValorPorOrden(&datos, 2);
    char *id = (char *)obtenerValorPorOrden(&datos, 3);

    int ok = editarPrecio(codigo, precio, proveedor, id, dir_espacio);

    modelo_free_split(partes);
    liberarStructura(&datos);
    RETORNAR_MODELO_ESTANDAR(ok);
}

// Hacer inventario
/*
 * Uso: Ejecuta modelo_hacerInventario de forma segura.
 * Entrada ejemplo: modelo_hacerInventario(texto, dir_espacio)
 */
int modelo_hacerInventario(char *texto, char *dir_espacio, char *usuario_contraseña_negocio)
{
    if (!texto)
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    if (!dir_espacio)
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    (void)usuario_contraseña_negocio; // reservado para validación futura del negocio

    char *nombres_variables[][4] =
    {
        {"inv_a_checar", "string", "", ""},
        {NULL, NULL, NULL, NULL}
    };

    int cuantos_parametros_hay = 0;
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++;
    }

    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[2]);
    if (!partes)
    {
        RETORNAR_MODELO_ESTANDAR(-2);
    }

    int cuantas_partes = 0;
    while (partes[cuantas_partes])
    {
        cuantas_partes++;
    }

    StructurasDinamicas datos = crearStructuraVacia();
    int ret_parse = procesar_partes_del_texto(partes, nombres_variables, G_caracter_separacion_nom_parametro_de_valor[0], &datos);
    if (ret_parse < 0 || cuantas_partes <= 0)
    {
        modelo_free_split(partes);
        liberarStructura(&datos);
        RETORNAR_MODELO_ESTANDAR((ret_parse < 0) ? ret_parse : -3);
    }

    char *inv_a_checar = (char *)obtenerValorPorOrden(&datos, 0);
    char *retorno_inv_revisado = NULL;
    int ok = hacerInventario(inv_a_checar, &retorno_inv_revisado, dir_espacio);

    if (retorno_inv_revisado)
    {
        imprimirMensaje_para_depurar("\nretorno_inv_revisado: %s\n", retorno_inv_revisado);
        free(retorno_inv_revisado);
    }

    modelo_free_split(partes);
    liberarStructura(&datos);
    RETORNAR_MODELO_ESTANDAR(ok);
}
