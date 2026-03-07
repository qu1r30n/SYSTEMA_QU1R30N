#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/02_cabeceras_procesos_generales_de_negocios/operaciones_procesos_generales.h"
#include "../../cabeceras/cabeceras_procesos/02_cabeceras_procesos_generales_de_negocios/operaciones_contadores.h"
#include "../../cabeceras/cabeceras_procesos/02_cabeceras_procesos_generales_de_negocios/operaciones_administradores.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

static int texto_valido(const char *txt)
{
    return (txt && txt[0] != '\0');
}

static int tipo_valido(const char *tipo)
{
    return (tipo && (strcmp(tipo, "ENTRADA") == 0 || strcmp(tipo, "SALIDA") == 0));
}

static void pg_asegurar_archivo_libro(const char *ruta_libro)
{
    crearArchivo(ruta_libro, "id|tipo|monto|quien|negocio|concepto|item_tipo|item_nombre|medio_pago|fecha");
}

static int pg_siguiente_id(const char *ruta_libro)
{
    char lineas[MAX_LINEAS][MAX_LINEA];
    int n = leer_archivo(ruta_libro, lineas);
    int ultimo_id = 0;

    for (int i = 1; i < n; i++)
    {
        char **partes = NULL;
        int cols = split(lineas[i], G_caracter_separacion[0], &partes);
        if (cols > 0 && partes && partes[0])
        {
            int id = atoi(partes[0]);
            if (id > ultimo_id)
            {
                ultimo_id = id;
            }
        }
        if (partes)
        {
            free_split(partes);
        }
    }

    return ultimo_id + 1;
}

int pg_registrar_movimiento(const char *ruta_libro,
                            const char *tipo,
                            float monto,
                            const char *quien,
                            const char *negocio,
                            const char *concepto,
                            const char *item_tipo,
                            const char *item_nombre,
                            const char *medio_pago)
{
    if (!texto_valido(ruta_libro) || !tipo_valido(tipo) || monto <= 0.0f ||
        !texto_valido(quien) || !texto_valido(negocio) || !texto_valido(concepto) ||
        !texto_valido(item_tipo) || !texto_valido(item_nombre) || !texto_valido(medio_pago))
    {
        return -1;
    }

    pg_asegurar_archivo_libro(ruta_libro);

    int id = pg_siguiente_id(ruta_libro);
    char fecha[20];
    char fila[MAX_LINEA];

    fechaActual(fecha, "%Y-%m-%d");
    snprintf(fila, sizeof(fila), "%d|%s|%.2f|%s|%s|%s|%s|%s|%s|%s",
             id, tipo, monto, quien, negocio, concepto, item_tipo, item_nombre, medio_pago, fecha);

    agregar_fila(ruta_libro, fila);
    return id;
}
