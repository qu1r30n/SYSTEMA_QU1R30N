#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/02_cabeceras_procesos_generales_de_negocios/operaciones_administradores.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

static int texto_valido_admin(const char *txt)
{
    return (txt && txt[0] != '\0');
}

static void admin_asegurar_archivo_libro(const char *ruta_libro)
{
    crearArchivo(ruta_libro, "id|tipo|monto|quien|negocio|concepto|item_tipo|item_nombre|medio_pago|fecha");
}

static void admin_asegurar_archivo_presupuestos(const char *ruta_presupuestos)
{
    crearArchivo(ruta_presupuestos, "negocio|rubro|limite");
}

int pg_administrador_configurar_presupuesto(const char *ruta_presupuestos,
                                            const char *negocio,
                                            const char *rubro,
                                            float limite)
{
    if (!texto_valido_admin(ruta_presupuestos) || !texto_valido_admin(negocio) || !texto_valido_admin(rubro) || limite < 0.0f)
    {
        return -1;
    }

    admin_asegurar_archivo_presupuestos(ruta_presupuestos);

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta_presupuestos, lineas);
    if (n <= 0)
    {
        snprintf(lineas[0], MAX_LINEA, "negocio|rubro|limite");
        n = 1;
    }

    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int cols = split(lineas[i], G_caracter_separacion[0], &partes);
        int coincide = (cols >= 3 && partes && partes[0] && partes[1] &&
                        strcmp(partes[0], negocio) == 0 && strcmp(partes[1], rubro) == 0);

        if (partes)
        {
            free_split(partes);
        }

        if (coincide)
        {
            snprintf(lineas[i], MAX_LINEA, "%s|%s|%.2f", negocio, rubro, limite);
            guardar_archivo(ruta_presupuestos, lineas, n);
            return 0;
        }
    }

    {
        char fila[MAX_LINEA];
        snprintf(fila, sizeof(fila), "%s|%s|%.2f", negocio, rubro, limite);
        agregar_fila(ruta_presupuestos, fila);
    }

    return 0;
}

int pg_administrador_verificar_presupuesto(const char *ruta_libro,
                                           const char *ruta_presupuestos,
                                           const char *negocio,
                                           const char *rubro,
                                           float *gastado,
                                           float *limite,
                                           float *disponible,
                                           int *excedido)
{
    if (!texto_valido_admin(ruta_libro) || !texto_valido_admin(ruta_presupuestos) || !texto_valido_admin(negocio) || !texto_valido_admin(rubro) ||
        !gastado || !limite || !disponible || !excedido)
    {
        return -1;
    }

    admin_asegurar_archivo_libro(ruta_libro);
    admin_asegurar_archivo_presupuestos(ruta_presupuestos);

    *gastado = 0.0f;
    *limite = 0.0f;
    *disponible = 0.0f;
    *excedido = 0;

    {
        char lineas[MAX_LINEAS][MAX_LINEA];
        int n = leer_archivo(ruta_presupuestos, lineas);
        int encontrado = 0;

        for (int i = 1; i < n; i++)
        {
            char **partes = NULL;
            int cols = split(lineas[i], G_caracter_separacion[0], &partes);
            if (cols >= 3 && partes && partes[0] && partes[1] && partes[2] &&
                strcmp(partes[0], negocio) == 0 && strcmp(partes[1], rubro) == 0)
            {
                *limite = (float)atof(partes[2]);
                encontrado = 1;
            }
            if (partes)
            {
                free_split(partes);
            }
            if (encontrado)
            {
                break;
            }
        }

        if (!encontrado)
        {
            return -2;
        }
    }

    {
        char lineas[MAX_LINEAS][MAX_LINEA];
        int n = leer_archivo(ruta_libro, lineas);

        for (int i = 1; i < n; i++)
        {
            char **partes = NULL;
            int cols = split(lineas[i], G_caracter_separacion[0], &partes);

            if (cols >= 6 && partes && partes[1] && partes[2] && partes[4] && partes[5] &&
                strcmp(partes[1], "SALIDA") == 0 &&
                strcmp(partes[4], negocio) == 0 &&
                strcmp(partes[5], rubro) == 0)
            {
                *gastado += (float)atof(partes[2]);
            }

            if (partes)
            {
                free_split(partes);
            }
        }
    }

    *disponible = *limite - *gastado;
    *excedido = (*gastado > *limite) ? 1 : 0;
    return 0;
}
