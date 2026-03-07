#include <string.h> // strlen, memcpy, strstr
#include <stdio.h>  // FILE, fopen, fgetc, fprintf, vsnprintf
#include <stdarg.h> // va_list

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

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

/* Prototipos adelantados para evitar uso antes de definicion */
int split(const char *txt, const char *sep, char ***salida);
void free_split(char **arreglo);

char *texto_copiar_dinamico(const char *texto_origen)
{
    if (!texto_origen)
    {
        return NULL;
    }

    size_t longitud = strlen(texto_origen);
    /* Reserva memoria en heap para devolver una copia independiente */
    char *texto_copia = (char *)malloc(longitud + 1);
    if (!texto_copia)
    {
        return NULL;
    }

    memcpy(texto_copia, texto_origen, longitud + 1);
    return texto_copia;
}

char *texto_formatear_dinamico(const char *formato, ...)
{
    va_list argumentos;
    va_start(argumentos, formato);
    int longitud_necesaria = vsnprintf(NULL, 0, formato, argumentos);
    va_end(argumentos);

    if (longitud_necesaria < 0)
    {
        return NULL;
    }

    char *texto_formateado = (char *)malloc((size_t)longitud_necesaria + 1);
    if (!texto_formateado)
    {
        return NULL;
    }

    va_start(argumentos, formato);
    vsnprintf(texto_formateado, (size_t)longitud_necesaria + 1, formato, argumentos);
    va_end(argumentos);
    return texto_formateado;
}

int texto_leer_linea_dinamica(FILE *archivo, char **linea_salida)
{
    if (!archivo || !linea_salida)
    {
        return -1;
    }

    size_t capacidad = 64;
    size_t longitud = 0;
    /* linea_salida es puntero doble porque devolvemos memoria creada aqui */
    char *linea = (char *)malloc(capacidad);
    if (!linea)
    {
        return -1;
    }

    int caracter = 0;
    while ((caracter = fgetc(archivo)) != EOF)
    {
        if (caracter == '\r')
        {
            continue;
        }
        if (caracter == '\n')
        {
            break;
        }

        if (longitud + 1 >= capacidad)
        {
            size_t nueva_capacidad = capacidad * 2;
            /* realloc puede mover la memoria: por eso usamos temporal */
            char *temporal = (char *)realloc(linea, nueva_capacidad);
            if (!temporal)
            {
                free(linea);
                return -1;
            }
            linea = temporal;
            capacidad = nueva_capacidad;
        }

        linea[longitud++] = (char)caracter;
    }

    if (caracter == EOF && longitud == 0)
    {
        free(linea);
        return 0;
    }

    linea[longitud] = '\0';
    *linea_salida = linea;
    return 1;
}

void texto_liberar_lineas_dinamicas(char **lineas, int cantidad_lineas)
{
    if (!lineas)
    {
        return;
    }

    /* Primero se libera cada fila y al final el arreglo de punteros */
    for (int i = 0; i < cantidad_lineas; i++)
    {
        free(lineas[i]);
    }
    free(lineas);
}

int texto_leer_archivo_dinamico(const char *ruta, char ***lineas_salida)
{
    if (!ruta || !lineas_salida)
    {
        return -1;
    }

    FILE *archivo = fopen(ruta, "r");
    if (!archivo)
    {
        *lineas_salida = NULL;
        return 0;
    }

    int cantidad_lineas = 0;
    int capacidad = 8;
    /* lineas es un arreglo dinamico de punteros a char (char**) */
    char **lineas = (char **)malloc((size_t)capacidad * sizeof(char *));
    if (!lineas)
    {
        fclose(archivo);
        return -1;
    }

    while (1)
    {
        char *linea_leida = NULL;
        int resultado_lectura = texto_leer_linea_dinamica(archivo, &linea_leida);
        if (resultado_lectura == 0)
        {
            break;
        }
        if (resultado_lectura < 0)
        {
            texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
            fclose(archivo);
            return -1;
        }

        if (cantidad_lineas >= capacidad)
        {
            int nueva_capacidad = capacidad * 2;
            /* igual que en char*: usamos temporal por seguridad */
            char **temporal = (char **)realloc(lineas, (size_t)nueva_capacidad * sizeof(char *));
            if (!temporal)
            {
                free(linea_leida);
                texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
                fclose(archivo);
                return -1;
            }
            lineas = temporal;
            capacidad = nueva_capacidad;
        }

        lineas[cantidad_lineas++] = linea_leida;
    }

    fclose(archivo);
    *lineas_salida = lineas;
    return cantidad_lineas;
}

int texto_guardar_archivo_dinamico(const char *ruta, char **lineas, int cantidad_lineas)
{
    if (!ruta || !lineas || cantidad_lineas < 0)
    {
        return -1;
    }

    FILE *archivo = fopen(ruta, "w");
    if (!archivo)
    {
        return -1;
    }

    for (int i = 0; i < cantidad_lineas; i++)
    {
        fprintf(archivo, "%s\n", lineas[i] ? lineas[i] : "");
    }

    fclose(archivo);
    return 0;
}

int texto_buscar_fila_por_columna_en_archivo(const char *ruta,
                                             int columna_busqueda,
                                             const char *valor_buscado,
                                             int omitir_encabezado,
                                             char **fila_encontrada)
{
    if (!ruta || !valor_buscado || !fila_encontrada || columna_busqueda < 0)
    {
        return -1;
    }

    /* inicializamos salida para evitar punteros colgantes */
    *fila_encontrada = NULL;

    char **lineas = NULL;
    int cantidad_lineas = texto_leer_archivo_dinamico(ruta, &lineas);
    if (cantidad_lineas < 0)
    {
        return -2;
    }

    if (cantidad_lineas <= 0)
    {
        return -3;
    }

    int inicio = omitir_encabezado ? 1 : 0;
    if (inicio < 0)
    {
        inicio = 0;
    }

    for (int i = inicio; i < cantidad_lineas; i++)
    {
        char **partes = NULL;
        int columnas = split(lineas[i], G_caracter_separacion[0], &partes);

        int coincide = 0;
        if (columnas > columna_busqueda && partes && partes[columna_busqueda])
        {
            coincide = (strcmp(partes[columna_busqueda], valor_buscado) == 0);
        }

        if (partes)
        {
            free_split(partes);
        }

        if (coincide)
        {
            /* devolvemos una copia para que el caller pueda usarla/liberarla */
            *fila_encontrada = texto_copiar_dinamico(lineas[i]);
            texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
            return (*fila_encontrada != NULL) ? 0 : -2;
        }
    }

    texto_liberar_lineas_dinamicas(lineas, cantidad_lineas);
    return -3;
}

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
