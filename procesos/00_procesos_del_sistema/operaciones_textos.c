/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - stdarg.h: Argumentos variables de funciones tipo printf
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h: Dependencia interna del proyecto
 * - stdlib.h: Memoria dinamica, conversiones y utilidades generales
 * - xc.h: Cabecera del compilador para microcontroladores PIC
 */
#include <string.h> // strlen, memcpy, strstr
#include <stdio.h>  // snprintf
#include <stdarg.h> // va_list, va_start, va_end
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"

#ifdef _WIN32
#include <stdlib.h> // malloc, realloc, free

#elif defined(__linux__)
#include <stdlib.h> // malloc, realloc, free

#elif defined(__XC)
#define _XTAL_FREQ 4000000
#include <xc.h>
/* PIC16F: Sin malloc disponible. Las funciones son stubs limitadas. */

#else
#include <stdlib.h>
#endif

/*
===============================================================================
 CORE_STRING_SPLIT
===============================================================================

 FUNCIÓN: core_split

 Divide un texto usando un separador (string completo).
 ------------------------------------------------------------------------------

 EJEMPLO DE ENTRADA:

     txt = "7501020304050|5|SucursalNorte"
     sep = "|"

 RESULTADO EN MEMORIA:

     resultado[0] = "7501020304050"
     resultado[1] = "5"
     resultado[2] = "SucursalNorte"
     resultado[3] = NULL

 RETORNO:
     3

===============================================================================
*/

int split(const char *txt, const char *sep, char ***salida)
{

    /* -----------------------------------------------------------------------
       VALIDACIÓN DE PARÁMETROS
       -----------------------------------------------------------------------

       txt     -> texto original (ej: "A|B|C")
       sep     -> separador (ej: "|")
       salida  -> dirección donde se guardará el arreglo resultante

       Si alguno es NULL → error inmediato
    ----------------------------------------------------------------------- */
    if (txt == NULL || sep == NULL || salida == NULL)
    {
        return -1;
    }

    /* Obtener longitud del separador */
    size_t len_sep = strlen(sep);

    /* Si el separador está vacío, no tiene sentido dividir */
    if (len_sep == 0)
    {
        return -1;
    }

    /* Capacidad inicial del arreglo dinámico
       Significa que inicialmente podemos guardar 4 fragmentos */
    int capacidad = 4;

    /* Cantidad real de fragmentos encontrados */
    int cantidad = 0;

    /* Reservar memoria para arreglo de punteros (char*) */
    char **resultado = malloc(sizeof(char *) * capacidad);

    /* Si falla malloc → error */
    if (resultado == NULL)
    {
        return -1;
    }

    /* inicio apunta al comienzo del fragmento actual */
    const char *inicio = txt;

    /* Buscar primera aparición del separador */
    const char *pos = strstr(inicio, sep);

    /* -----------------------------------------------------------------------
       BUCLE PRINCIPAL
       Mientras encontremos el separador en el texto
    ----------------------------------------------------------------------- */
    while (pos != NULL)
    {
        /* Calcular longitud del fragmento actual */
        size_t len_fragmento = (size_t)(pos - inicio);

        /* Reservar memoria para el fragmento (+1 para '\0') */
        char *fragmento = malloc(len_fragmento + 1);

        if (fragmento == NULL)
        {
            /* Liberar todo lo previamente reservado */
            for (int i = 0; i < cantidad; i++)
                free(resultado[i]);

            free(resultado);
            return -1;
        }

        /* Copiar contenido del fragmento */
        memcpy(fragmento, inicio, len_fragmento);

        /* Agregar terminador de cadena */
        fragmento[len_fragmento] = '\0';

        /* Si el arreglo está lleno, duplicar capacidad */
        if (cantidad >= capacidad)
        {
            capacidad *= 2;

            char **temp = realloc(resultado, sizeof(char *) * capacidad);

            if (temp == NULL)
            {
                free(fragmento);

                for (int i = 0; i < cantidad; i++)
                    free(resultado[i]);

                free(resultado);
                return -1;
            }

            resultado = temp;
        }

        /* Guardar fragmento */
        resultado[cantidad] = fragmento;
        cantidad++;

        /* Avanzar inicio después del separador */
        inicio = pos + len_sep;

        /* Buscar siguiente separador */
        pos = strstr(inicio, sep);
    }

    /* -----------------------------------------------------------------------
       ÚLTIMO FRAGMENTO
       (lo que queda después del último separador)
    ----------------------------------------------------------------------- */

    size_t len_final = strlen(inicio);

    char *fragmento_final = malloc(len_final + 1);

    if (fragmento_final == NULL)
    {
        for (int i = 0; i < cantidad; i++)
            free(resultado[i]);

        free(resultado);
        return -1;
    }

    /* Copiar último fragmento incluyendo '\0' */
    memcpy(fragmento_final, inicio, len_final + 1);

    /* Expandir si es necesario */
    if (cantidad >= capacidad)
    {
        char **temp = realloc(resultado, sizeof(char *) * (capacidad + 1));

        if (temp == NULL)
        {
            free(fragmento_final);

            for (int i = 0; i < cantidad; i++)
                free(resultado[i]);

            free(resultado);
            return -1;
        }

        resultado = temp;
    }

    /* Guardar último fragmento */
    resultado[cantidad] = fragmento_final;
    cantidad++;

    /* -----------------------------------------------------------------------
       AGREGAR NULL FINAL (estilo argv)
       Permite recorrer así:
           while(resultado[i] != NULL)
    ----------------------------------------------------------------------- */

    char **temp = realloc(resultado, sizeof(char *) * (cantidad + 1));

    if (temp == NULL)
    {
        for (int i = 0; i < cantidad; i++)
            free(resultado[i]);

        free(resultado);
        return -1;
    }

    resultado = temp;
    resultado[cantidad] = NULL;

    /* Guardar arreglo final en parámetro de salida */
    *salida = resultado;

    /* Retornar cantidad de fragmentos encontrados */
    return cantidad;
}

/*
===============================================================================
 FUNCIÓN: free_split
-------------------------------------------------------------------------------

 Libera completamente la memoria creada por core_split.

 Parámetro:
     arreglo -> arreglo dinámico terminado en NULL

 Ejemplo interno:

     arreglo[0] = "7501020304050"
     arreglo[1] = "5"
     arreglo[2] = "SucursalNorte"
     arreglo[3] = NULL

 Esta función:
     ✔ Libera cada fragmento
     ✔ Libera el arreglo principal
     ✔ No deja memoria colgada
===============================================================================
*/

void free_split(char **arreglo)
{
    /* Si es NULL, no hacer nada */
    if (arreglo == NULL)
    {
        return;
    }

    int i = 0;

    /* Recorrer hasta encontrar NULL */
    while (arreglo[i] != NULL)
    {
        free(arreglo[i]);
        i++;
    }

    /* Liberar arreglo principal */
    free(arreglo);
}

/*
===============================================================================
 EJEMPLO DE USO EN main
===============================================================================

#include <stdio.h>

int main()
{
    const char* linea = "7501020304050|5|SucursalNorte";

    char** partes;

    int n = split(linea, "|", &partes);

    if (n == -1)
    {
        printf("Error al dividir\n");
        return 1;
    }

    printf("Fragmentos encontrados: %d\n", n);

    int i = 0;
    while (partes[i] != NULL)
    {
        printf("Parte %d: %s\n", i, partes[i]);
        i++;
    }

    free_split(partes);

    return 0;
}

===============================================================================
*/

int texto_a_int_seguro(const char *texto, int *var_a_retornar)
{
    int signo = 1;
    long temp = 0; // usamos long para detectar overflow

    if (texto == 0 || var_a_retornar == 0)
        return -1;

    if (*texto == '-')
    {
        signo = -1;
        texto++;
    }
    else if (*texto == '+')
    {
        texto++;
    }

    if (*texto < '0' || *texto > '9')
    {
        return -1; // no empieza con número
    }

    while (*texto >= '0' && *texto <= '9')
    {

        temp = temp * 10 + (*texto - '0');

        /* Detectar overflow para int 16-bit (PIC16F) */
        if (temp > 32767)
        {
            return -1;
        }

        texto++;
    }

    if (*texto != '\0')
    {
        return -1; // caracteres inválidos al final
    }

    *var_a_retornar = (int)(temp * signo);
    return 0;
}

int texto_a_float_seguro(const char *texto, float *var_a_retornar)
{
    float valor = 0.0f;
    float decimal = 0.1f;
    int signo = 1;
    int tiene_decimal = 0;

    if (texto == 0 || var_a_retornar == 0)
        return -1;

    if (*texto == '-')
    {
        signo = -1;
        texto++;
    }
    else if (*texto == '+')
    {
        texto++;
    }

    if ((*texto < '0' || *texto > '9') && *texto != '.')
    {
        return -1;
    }

    while (*texto != '\0')
    {

        if (*texto >= '0' && *texto <= '9')
        {

            if (!tiene_decimal)
            {
                valor = valor * 10.0f + (*texto - '0');
            }
            else
            {
                valor += (*texto - '0') * decimal;
                decimal *= 0.1f;
            }
        }
        else if (*texto == '.')
        {

            if (tiene_decimal)
            {
                return -1; // dos puntos decimales
            }

            tiene_decimal = 1;
        }
        else
        {
            return -1; // carácter inválido
        }

        texto++;
    }

    *var_a_retornar = valor * signo;
    return 0;
}

/*
Ejemplo:
    char salida[128] = "";
    concatenar_formato(salida, NULL, "%s", "producto");
    concatenar_formato(salida, "|", "%d", 5);
    concatenar_formato(salida, "|", "%.2f", 12.5f);

Resultado en salida:
    "producto|5|12.50"
*/
int concatenar_formato_separado_por_variable(char **destino, const char *separador, const char *formato, ...)
{
    if (destino == NULL || formato == NULL)
    {
        return -1;
    }

    if (*destino == NULL)
    {
        *destino = malloc(1);
        if (*destino == NULL)
        {
            return -1;
        }
        (*destino)[0] = '\0';
    }

    size_t largo_actual = strlen(*destino);

    const char *formato_a_usar = formato;
    char *formato_expandido = NULL;

    if (separador != NULL && separador[0] != '\0')
    {
        size_t len_formato = strlen(formato);
        size_t len_sep = strlen(separador);
        size_t cantidad_specs = 0;

        for (size_t i = 0; i < len_formato; i++)
        {
            if (formato[i] == '%')
            {
                i++;

                if (i >= len_formato)
                {
                    break;
                }

                if (formato[i] == '%')
                {
                    continue;
                }

                while (i < len_formato && strchr("diuoxXfFeEgGaAcspn", formato[i]) == NULL)
                {
                    i++;
                }

                if (i < len_formato)
                {
                    cantidad_specs++;
                }
            }
        }

        if (cantidad_specs > 0)
        {
            size_t len_expandido = len_formato + (cantidad_specs * len_sep) + 1;
            formato_expandido = malloc(len_expandido);

            if (formato_expandido == NULL)
            {
                return -1;
            }

            size_t j = 0;

            for (size_t i = 0; i < len_formato; i++)
            {
                formato_expandido[j++] = formato[i];

                if (formato[i] == '%')
                {
                    i++;

                    if (i >= len_formato)
                    {
                        break;
                    }

                    formato_expandido[j++] = formato[i];

                    if (formato[i] == '%')
                    {
                        continue;
                    }

                    while (i < len_formato && strchr("diuoxXfFeEgGaAcspn", formato[i]) == NULL)
                    {
                        i++;
                        if (i < len_formato)
                        {
                            formato_expandido[j++] = formato[i];
                        }
                    }

                    if (i < len_formato)
                    {
                        memcpy(formato_expandido + j, separador, len_sep);
                        j += len_sep;
                    }
                }
            }

            formato_expandido[j] = '\0';
            formato_a_usar = formato_expandido;
        }
    }

    va_list args;
    va_start(args, formato);

    va_list args_len;
    va_copy(args_len, args);
    int necesarios = vsnprintf(NULL, 0, formato_a_usar, args_len);
    va_end(args_len);

    if (necesarios < 0)
    {
        va_end(args);
        free(formato_expandido);
        return -1;
    }

    char *tmp = realloc(*destino, largo_actual + (size_t)necesarios + 1);
    if (tmp == NULL)
    {
        va_end(args);
        free(formato_expandido);
        return -1;
    }

    *destino = tmp;
    int escritos = vsnprintf(*destino + largo_actual, (size_t)necesarios + 1, formato_a_usar, args);
    va_end(args);

    free(formato_expandido);

    if (escritos < 0)
    {
        return -1;
    }

    return 0;
}

int concatenar_formato(char *destino, const char *separador, const char *formato, ...)
{
    if (destino == NULL || formato == NULL)
    {
        return -1;
    }

    size_t largo_actual = strlen(destino);

    va_list args;
    va_start(args, formato);
    int escritos = vsprintf(destino + largo_actual, formato, args);
    va_end(args);

    if (escritos < 0)
    {
        return -1;
    }

    /* Agregar separador al final del valor recien concatenado. */
    if (separador != NULL)
    {
        strcat(destino, separador);
    }

    return 0;
}
