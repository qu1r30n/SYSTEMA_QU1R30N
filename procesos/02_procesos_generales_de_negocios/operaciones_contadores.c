#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/02_cabeceras_procesos_generales_de_negocios/operaciones_contadores.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

static int texto_valido_contador(const char *txt)
{
    return (txt && txt[0] != '\0');
}

static void contador_asegurar_archivo_libro(const char *ruta_libro)
{
    crearArchivo(ruta_libro, "id|tipo|monto|quien|negocio|concepto|item_tipo|item_nombre|medio_pago|fecha");
}

int pg_contador_resumen_general(const char *ruta_libro,
                                float *entradas,
                                float *salidas,
                                float *saldo)
{
    if (!texto_valido_contador(ruta_libro) || !entradas || !salidas || !saldo)
    {
        return -1;
    }

    contador_asegurar_archivo_libro(ruta_libro);

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta_libro, lineas);

    *entradas = 0.0f;
    *salidas = 0.0f;

    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int cols = split(lineas[i], G_caracter_separacion[0], &partes);
        if (cols >= 3 && partes && partes[1] && partes[2])
        {
            float monto = (float)atof(partes[2]);
            if (strcmp(partes[1], "ENTRADA") == 0)
            {
                *entradas += monto;
            }
            else if (strcmp(partes[1], "SALIDA") == 0)
            {
                *salidas += monto;
            }
        }
        if (partes)
        {
            free_split(partes);
        }
    }

    *saldo = *entradas - *salidas;
    return 0;
}

int pg_contador_resumen_negocio(const char *ruta_libro,
                                const char *negocio,
                                float *entradas,
                                float *salidas,
                                float *saldo)
{
    if (!texto_valido_contador(ruta_libro) || !texto_valido_contador(negocio) || !entradas || !salidas || !saldo)
    {
        return -1;
    }

    contador_asegurar_archivo_libro(ruta_libro);

    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta_libro, lineas);

    *entradas = 0.0f;
    *salidas = 0.0f;

    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int cols = split(lineas[i], G_caracter_separacion[0], &partes);
        if (cols >= 6 && partes && partes[1] && partes[2] && partes[4] && strcmp(partes[4], negocio) == 0)
        {
            float monto = (float)atof(partes[2]);
            if (strcmp(partes[1], "ENTRADA") == 0)
            {
                *entradas += monto;
            }
            else if (strcmp(partes[1], "SALIDA") == 0)
            {
                *salidas += monto;
            }
        }
        if (partes)
        {
            free_split(partes);
        }
    }

    *saldo = *entradas - *salidas;
    return 0;
}
