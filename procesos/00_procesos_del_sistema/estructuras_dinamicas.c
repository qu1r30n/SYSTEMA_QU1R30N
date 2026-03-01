#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifdef __XC
#include <stdio.h>
#include <string.h>
#endif

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"

/* ============================================= */
/* EJEMPLO DE USO                                */
/* ============================================= */

/*
    int main() {

        StructurasDinamicas s = crearStructuraVacia();

        // Agregar campos en tiempo de ejecuci??n
        agregarCampo(&s, "producto", "string");
        agregarCampo(&s, "precio", "float");
        agregarCampo(&s, "stock", "int");
        agregarCampo(&s, "proveedor", "string");

        // Asignar valores
        asignarValorString(&s, "producto", "Leche");
        asignarValorFloat(&s, "precio", 1.5);
        asignarValorInt(&s, "stock", 20);
        asignarValorString(&s, "proveedor", "ProveedorX");

        imprimirStructura(&s);

        liberarStructura(&s);

        return 0;
    }
*/

/* Macros para tipos */
#define TIPO_STRING 0
#define TIPO_INT 1
#define TIPO_FLOAT 2

/* ============================================= */
/* CREAR ESTRUCTURA DIN??MICA VAC??A              */
/* ============================================= */
StructurasDinamicas crearStructuraVacia(void)
{
    StructurasDinamicas s;

    s.arreglo_char = NULL;
    s.arreglo_int = NULL;
    s.arreglo_float = NULL;

    s.orden_tipo = NULL;
    s.orden_indice = NULL;
    s.nombres = NULL;

    s.total = 0;
    s.count_string = 0;
    s.count_int = 0;
    s.count_float = 0;

    return s;
}

/* ============================================= */
/* AGREGAR CAMPO DIN??MICO                        */
/* ============================================= */
void agregarCampo(StructurasDinamicas *s, const char *nombre, const char *tipo)
{
    if (!s || !nombre || !tipo)
    {
        return;
    }

    /* Incrementar total y reallocar arreglos de metadata */
    s->total += 1;
    s->orden_tipo = (int *)realloc(s->orden_tipo, sizeof(int) * s->total);
    s->orden_indice = (int *)realloc(s->orden_indice, sizeof(int) * s->total);
    s->nombres = (char **)realloc(s->nombres, sizeof(char *) * s->total);
    s->nombres[s->total - 1] = (char *)malloc(strlen(nombre) + 1);
    if (s->nombres[s->total - 1])
    {
        strcpy(s->nombres[s->total - 1], nombre);
    }

    /* Agregar campo seg??n tipo */
    if (strcmp(tipo, "string") == 0)
    {
        s->arreglo_char = (char **)realloc(s->arreglo_char, sizeof(char *) * (s->count_string + 1));
        s->arreglo_char[s->count_string] = NULL;

        s->orden_tipo[s->total - 1] = TIPO_STRING;
        s->orden_indice[s->total - 1] = s->count_string;
        s->count_string++;
    }
    else if (strcmp(tipo, "int") == 0)
    {
        s->arreglo_int = (int *)realloc(s->arreglo_int, sizeof(int) * (s->count_int + 1));
        s->arreglo_int[s->count_int] = 0;

        s->orden_tipo[s->total - 1] = TIPO_INT;
        s->orden_indice[s->total - 1] = s->count_int;
        s->count_int++;
    }
    else if (strcmp(tipo, "float") == 0)
    {
        s->arreglo_float = (float *)realloc(s->arreglo_float, sizeof(float) * (s->count_float + 1));
        s->arreglo_float[s->count_float] = 0.0f;

        s->orden_tipo[s->total - 1] = TIPO_FLOAT;
        s->orden_indice[s->total - 1] = s->count_float;
        s->count_float++;
    }
}

/* ============================================= */
/* IMPRIMIR ESTRUCTURA DIN??MICA                  */
/* ============================================= */
void imprimirStructura(StructurasDinamicas *s)
{
    if (!s)
    {
        return;
    }

    for (int i = 0; i < s->total; i++)
    {
        printf("%s = ", s->nombres[i]);

        if (s->orden_tipo[i] == TIPO_STRING)
        {
            char *valor = s->arreglo_char[s->orden_indice[i]];
            printf("%s\n", valor ? valor : "NULL");
        }
        else if (s->orden_tipo[i] == TIPO_INT)
        {
            printf("%d\n", s->arreglo_int[s->orden_indice[i]]);
        }
        else if (s->orden_tipo[i] == TIPO_FLOAT)
        {
            printf("%.2f\n", s->arreglo_float[s->orden_indice[i]]);
        }
    }
}

/* ============================================= */
/* ASIGNAR VALOR STRING POR NOMBRE              */
/* ============================================= */
void asignarValorString(StructurasDinamicas *s, const char *nombre, const char *valor)
{
    if (!s || !nombre)
    {
        return;
    }

    for (int i = 0; i < s->total; i++)
    {
        if (strcmp(s->nombres[i], nombre) == 0 && s->orden_tipo[i] == TIPO_STRING)
        {
            /* Liberar valor anterior si existe */
            if (s->arreglo_char[s->orden_indice[i]])
            {
                free(s->arreglo_char[s->orden_indice[i]]);
            }
            /* Asignar nuevo valor */
            s->arreglo_char[s->orden_indice[i]] = (char *)malloc(strlen(valor) + 1);
            if (s->arreglo_char[s->orden_indice[i]])
            {
                strcpy(s->arreglo_char[s->orden_indice[i]], valor);
            }
            return;
        }
    }
}

/* ============================================= */
/* ASIGNAR VALOR INT POR NOMBRE                 */
/* ============================================= */
void asignarValorInt(StructurasDinamicas *s, const char *nombre, int valor)
{
    if (!s || !nombre)
    {
        return;
    }

    for (int i = 0; i < s->total; i++)
    {
        if (strcmp(s->nombres[i], nombre) == 0 && s->orden_tipo[i] == TIPO_INT)
        {
            s->arreglo_int[s->orden_indice[i]] = valor;
            return;
        }
    }
}

/* ============================================= */
/* ASIGNAR VALOR FLOAT POR NOMBRE               */
/* ============================================= */
void asignarValorFloat(StructurasDinamicas *s, const char *nombre, float valor)
{
    if (!s || !nombre)
    {
        return;
    }

    for (int i = 0; i < s->total; i++)
    {
        if (strcmp(s->nombres[i], nombre) == 0 && s->orden_tipo[i] == TIPO_FLOAT)
        {
            s->arreglo_float[s->orden_indice[i]] = valor;
            return;
        }
    }
}

/* ============================================= */
/* LIBERAR MEMORIA DE LA ESTRUCTURA              */
/* ============================================= */
void liberarStructura(StructurasDinamicas *s)
{
    if (!s)
    {
        return;
    }

    /* Liberar nombres */
    if (s->nombres)
    {
        for (int i = 0; i < s->total; i++)
        {
            if (s->nombres[i])
            {
                free(s->nombres[i]);
            }
        }
        free(s->nombres);
        s->nombres = NULL;
    }

    /* Liberar strings de valores */
    if (s->arreglo_char)
    {
        for (int i = 0; i < s->count_string; i++)
        {
            if (s->arreglo_char[i])
            {
                free(s->arreglo_char[i]);
            }
        }
        free(s->arreglo_char);
        s->arreglo_char = NULL;
    }

    /* Liberar arreglos de tipos */
    if (s->orden_tipo)
    {
        free(s->orden_tipo);
        s->orden_tipo = NULL;
    }

    if (s->orden_indice)
    {
        free(s->orden_indice);
        s->orden_indice = NULL;
    }

    if (s->arreglo_int)
    {
        free(s->arreglo_int);
        s->arreglo_int = NULL;
    }

    if (s->arreglo_float)
    {
        free(s->arreglo_float);
        s->arreglo_float = NULL;
    }

    /* Reinicializar estructura */
    s->total = 0;
    s->count_string = 0;
    s->count_int = 0;
    s->count_float = 0;
    s->count_float = 0;
}

/* Cargar estructura desde arreglo bidimensional */
StructurasDinamicas cargarDesdeArreglo(char *nombres_variables[][4])
{
    StructurasDinamicas datos = crearStructuraVacia();
    int cuantos_parametros_hay = 0;

    while (nombres_variables[cuantos_parametros_hay][0] != NULL)
    {
        agregarCampo(&datos,
                     nombres_variables[cuantos_parametros_hay][0],
                     nombres_variables[cuantos_parametros_hay][1]);

        if (strcmp(nombres_variables[cuantos_parametros_hay][1], "string") == 0)
        {
            asignarValorString(&datos,
                               nombres_variables[cuantos_parametros_hay][0],
                               nombres_variables[cuantos_parametros_hay][2]);
        }
        else if (strcmp(nombres_variables[cuantos_parametros_hay][1], "int") == 0)
        {
            asignarValorInt(&datos,
                            nombres_variables[cuantos_parametros_hay][0],
                            atoi(nombres_variables[cuantos_parametros_hay][2]));
        }
        else if (strcmp(nombres_variables[cuantos_parametros_hay][1], "float") == 0)
        {
            asignarValorFloat(&datos,
                              nombres_variables[cuantos_parametros_hay][0],
                              (float)atof(nombres_variables[cuantos_parametros_hay][2]));
        }

        cuantos_parametros_hay++;
    }

    return datos;
}

/* Obtener valor de estructura por orden de inserci?n */
void *obtenerValorPorOrden(StructurasDinamicas *datos, int orden)
{
    if (orden < 0 || orden >= datos->total)
    {
        return NULL;
    }

    int tipo = datos->orden_tipo[orden];
    int indice = datos->orden_indice[orden];

    if (tipo == TIPO_STRING)
    {
        return (void *)datos->arreglo_char[indice];
    }
    else if (tipo == TIPO_INT)
    {
        return (void *)&datos->arreglo_int[indice];
    }
    else if (tipo == TIPO_FLOAT)
    {
        return (void *)&datos->arreglo_float[indice];
    }

    return NULL;
}

/* Procesar partes de texto y cargar en estructura */
StructurasDinamicas procesar_partes_del_texto(char **partes, char *nombres_variables[][4], const char *separador)
{
    StructurasDinamicas datos = cargarDesdeArreglo(nombres_variables);

    int i = 0;
    while (partes[i])
    {
        char **nom_parametro_dato = modelo_split(partes[i], separador);

        if (nom_parametro_dato && nom_parametro_dato[0] && nom_parametro_dato[1])
        {
            int j = 0;
            while (nombres_variables[j][0])
            {
                if (strcmp(nombres_variables[j][0], nom_parametro_dato[0]) ==  0)
                {
                    if (strcmp(nombres_variables[j][1], "string") == 0)
                    {
                        asignarValorString(&datos,
                                           nombres_variables[j][0],
                                           nom_parametro_dato[1]);
                    }
                    else if (strcmp(nombres_variables[j][1], "int") == 0)
                    {
                        asignarValorInt(&datos,
                                        nombres_variables[j][0],
                                        atoi(nom_parametro_dato[1]));
                    }
                    else if (strcmp(nombres_variables[j][1], "float") == 0)
                    {
                        asignarValorFloat(&datos,
                                          nombres_variables[j][0],
                                          (float)atof(nom_parametro_dato[1]));
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

    return datos;
}
