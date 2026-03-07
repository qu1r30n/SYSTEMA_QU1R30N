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
static const char *ARCH_BANCO_INVENTARIO = "banco_inventario_productos_servicios.txt";

static void banco_asegurar_archivos(void)
{
    crearArchivo(ARCH_BANCO_CUENTAS, "_00_CUENTA|_01_TITULAR|_02_SALDO|_03_FECHA");
    crearArchivo(ARCH_BANCO_MOV, "_00_CUENTA|_01_OPERACION|_02_MONTO|_03_SALDO_FINAL|_04_CONCEPTO|_05_FECHA");
    crearArchivo(ARCH_BANCO_INVENTARIO, "_00_CODIGO|_01_PRODUCTO_SERVICIO|_02_TIPO_PRODUCTO|_03_PRECIO_REFERENCIA|_04_FECHA");
}

static int banco_buscar_cuenta(char **lineas, int n, const char *cuenta)
{
    /* lineas es un arreglo de punteros: cada elemento apunta a una fila */
    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int columnas = split(lineas[i], G_caracter_separacion[0], &partes);
        int es_coincidencia = (columnas > 0 && partes[0] && strcmp(partes[0], cuenta) == 0);
        if (partes)
        {
            free_split(partes);
        }
        if (es_coincidencia)
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

    /* Leemos el archivo en memoria dinamica: lineas -> char** */
    char **lineas = NULL;
    int cantidad_lineas = texto_leer_archivo_dinamico(ARCH_BANCO_CUENTAS, &lineas);
    if (cantidad_lineas < 0)
    {
        return -3;
    }

    if (cantidad_lineas <= 0)
    {
        /* Si no hay archivo/filas, creamos un arreglo de 1 puntero (encabezado) */
        lineas = (char **)malloc(sizeof(char *));
        if (!lineas)
        {
            return -3;
        }
        lineas[0] = texto_copiar_dinamico("cuenta|titular|saldo|fecha");
        if (!lineas[0])
        {
            free(lineas);
            return -3;
        }
        cantidad_lineas = 1;
    }

    if (banco_buscar_cuenta(lineas, cantidad_lineas, cuenta) != -1)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -2;
    }

    char fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    char *fila = texto_formatear_dinamico("%s|%s|%.2f|%s", cuenta, titular, saldo_inicial, fecha);
    if (!fila)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -3;
    }
    agregar_fila(ARCH_BANCO_CUENTAS, fila);
    free(fila);
    texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);

    return 0;
}

int banco_depositar(const char *cuenta, float monto)
{
    if (!cuenta || monto <= 0.0f)
    {
        return -1;
    }

    banco_asegurar_archivos();

    char **lineas = NULL;
    int cantidad_lineas = texto_leer_archivo_dinamico(ARCH_BANCO_CUENTAS, &lineas);
    if (cantidad_lineas < 0)
    {
        return -4;
    }

    int indice_cuenta = banco_buscar_cuenta(lineas, cantidad_lineas, cuenta);
    if (indice_cuenta == -1)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -2;
    }

    char **partes = NULL;
    /* split crea partes como char** y luego se libera con free_split */
    int columnas = split(lineas[indice_cuenta], G_caracter_separacion[0], &partes);
    if (columnas < 3 || !partes[2])
    {
        if (partes)
        {
            free_split(partes);
        }
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -3;
    }

    float saldo = (float)atof(partes[2]);
    saldo += monto;

    char fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    char *cuenta_copiada = texto_copiar_dinamico(partes[0]);
    char *titular_copiado = texto_copiar_dinamico(partes[1] ? partes[1] : "");
    free_split(partes);
    if (!cuenta_copiada || !titular_copiado)
    {
        free(cuenta_copiada);
        free(titular_copiado);
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -4;
    }

    free(lineas[indice_cuenta]);
    /* Reemplazamos la fila anterior por una nueva fila dinamica ya actualizada */
    lineas[indice_cuenta] = texto_formatear_dinamico("%s|%s|%.2f|%s", cuenta_copiada, titular_copiado, saldo, fecha);
    free(cuenta_copiada);
    free(titular_copiado);
    if (!lineas[indice_cuenta])
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -4;
    }

    if (texto_guardar_archivo_dinamico(ARCH_BANCO_CUENTAS, lineas, cantidad_lineas) != 0)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -4;
    }

    char *movimiento = texto_formatear_dinamico("%s|DEPOSITO|%.2f|%.2f|%s|%s", cuenta, monto, saldo, "NA", fecha);
    if (!movimiento)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -4;
    }

    agregar_fila(ARCH_BANCO_MOV, movimiento);
    free(movimiento);
    /* Liberar al final evita fugas de memoria */
    texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
    return 0;
}

int banco_retirar(const char *cuenta, float monto, const char *motivo)
{
    if (!cuenta || !motivo || monto <= 0.0f)
    {
        return -1;
    }

    banco_asegurar_archivos();

    char **lineas = NULL;
    int cantidad_lineas = texto_leer_archivo_dinamico(ARCH_BANCO_CUENTAS, &lineas);
    if (cantidad_lineas < 0)
    {
        return -5;
    }

    int indice_cuenta = banco_buscar_cuenta(lineas, cantidad_lineas, cuenta);
    if (indice_cuenta == -1)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -2;
    }

    char **partes = NULL;
    int columnas = split(lineas[indice_cuenta], G_caracter_separacion[0], &partes);
    if (columnas < 3 || !partes[2])
    {
        if (partes)
        {
            free_split(partes);
        }
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -3;
    }

    float saldo = (float)atof(partes[2]);
    if (saldo < monto)
    {
        free_split(partes);
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -4;
    }
    saldo -= monto;

    char fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    char *cuenta_copiada = texto_copiar_dinamico(partes[0]);
    char *titular_copiado = texto_copiar_dinamico(partes[1] ? partes[1] : "");
    free_split(partes);
    if (!cuenta_copiada || !titular_copiado)
    {
        free(cuenta_copiada);
        free(titular_copiado);
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -5;
    }

    free(lineas[indice_cuenta]);
    lineas[indice_cuenta] = texto_formatear_dinamico("%s|%s|%.2f|%s", cuenta_copiada, titular_copiado, saldo, fecha);
    free(cuenta_copiada);
    free(titular_copiado);
    if (!lineas[indice_cuenta])
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -5;
    }

    if (texto_guardar_archivo_dinamico(ARCH_BANCO_CUENTAS, lineas, cantidad_lineas) != 0)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -5;
    }

    char *movimiento = texto_formatear_dinamico("%s|RETIRO|%.2f|%.2f|%s|%s", cuenta, monto, saldo, motivo, fecha);
    if (!movimiento)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -5;
    }

    agregar_fila(ARCH_BANCO_MOV, movimiento);
    free(movimiento);
    texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
    return 0;
}

int banco_consultar_saldo(const char *cuenta, float *saldo)
{
    if (!cuenta || !saldo)
    {
        return -1;
    }

    banco_asegurar_archivos();

    char **lineas = NULL;
    int cantidad_lineas = texto_leer_archivo_dinamico(ARCH_BANCO_CUENTAS, &lineas);
    if (cantidad_lineas < 0)
    {
        return -4;
    }

    int indice_cuenta = banco_buscar_cuenta(lineas, cantidad_lineas, cuenta);
    if (indice_cuenta == -1)
    {
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -2;
    }

    char **partes = NULL;
    int columnas = split(lineas[indice_cuenta], G_caracter_separacion[0], &partes);
    if (columnas < 3 || !partes || !partes[2])
    {
        if (partes)
        {
            free_split(partes);
        }
        texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
        return -3;
    }

    *saldo = (float)atof(partes[2]);
    free_split(partes);
    texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
    return 0;
}

int banco_buscar_producto_en_archivo(const char *ruta_inventario,
                                     const char *codigo,
                                     char **fila_producto)
{
    return texto_buscar_fila_por_columna_en_archivo(ruta_inventario, 0, codigo, 1, fila_producto);
}

int banco_buscar_producto_servicio(const char *codigo, char **fila_producto)
{
    if (!codigo || !fila_producto)
    {
        return -1;
    }

    banco_asegurar_archivos();
    return banco_buscar_producto_en_archivo(ARCH_BANCO_INVENTARIO, codigo, fila_producto);
}

int banco_registrar_producto_servicio(const char *codigo,
                                      const char *producto_servicio,
                                      const char *tipo,
                                      float precio_referencia)
{
    if (!codigo || !producto_servicio || !tipo || precio_referencia < 0.0f)
    {
        return -1;
    }

    banco_asegurar_archivos();

    char *fila_existente = NULL;
    int existe = banco_buscar_producto_en_archivo(ARCH_BANCO_INVENTARIO, codigo, &fila_existente);
    if (fila_existente)
    {
        free(fila_existente);
    }
    if (existe == 0)
    {
        return -2;
    }

    char fecha[20];
    fechaActual(fecha, "%Y-%m-%d");
    char *fila_nueva = texto_formatear_dinamico("%s|%s|%s|%.2f|%s",
                                                codigo,
                                                producto_servicio,
                                                tipo,
                                                precio_referencia,
                                                fecha);
    if (!fila_nueva)
    {
        return -3;
    }

    agregar_fila(ARCH_BANCO_INVENTARIO, fila_nueva);
    free(fila_nueva);
    return 0;
}
