/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - stdarg.h: Argumentos variables de funciones tipo printf
 * - time.h: Funciones de fecha y hora
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h: Dependencia interna del proyecto
 * - stdlib.h: Memoria dinamica, conversiones y utilidades generales
 * - xc.h: Cabecera del compilador para microcontroladores PIC
 */
#include <string.h> // strlen, memcpy, strstr
#include <stdio.h>  // snprintf
#include <stdarg.h> // va_list, va_start, va_end
#include <time.h>   // time, localtime, strftime
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

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

/* =======================
   FUNCIONES NUEVAS DEL C#
   ======================== */

char *join_paresido_simple(char caracter_union_filas, char **texto, int n_texto,
                           const char *columnas_extraer, const char *caracter_union_columnas)
{
    if (!texto || n_texto <= 0)
        return calloc(1, 1);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    if (columnas_extraer != NULL && strlen(columnas_extraer) > 0)
    {
        for (int i = 0; i < n_texto; i++)
        {
            char **partes = NULL;
            int n = split(texto[i], caracter_union_columnas, &partes);
            if (n > 0)
            {
                char **cols_extraer = NULL;
                int n_cols = split(columnas_extraer, caracter_union_columnas, &cols_extraer);

                for (int j = 0; j < n_cols; j++)
                {
                    int col_idx = atoi(cols_extraer[j]);
                    if (col_idx < n && col_idx >= 0 && partes[col_idx])
                    {
                        if (j > 0)
                            strncat(resultado, caracter_union_columnas, 65535 - strlen(resultado) - 1);
                        strncat(resultado, partes[col_idx], 65535 - strlen(resultado) - 1);
                    }
                }
                free_split(cols_extraer);
                strncat(resultado, &caracter_union_filas, 65535 - strlen(resultado) - 1);
            }
            free_split(partes);
        }
    }
    else
    {
        for (int i = 0; i < n_texto; i++)
        {
            if (i > 0)
                strncat(resultado, &caracter_union_filas, 65535 - strlen(resultado) - 1);
            if (texto[i])
                strncat(resultado, texto[i], 65535 - strlen(resultado) - 1);
        }
    }

    size_t len = strlen(resultado);
    if (len > 0 && resultado[len - 1] == caracter_union_filas)
    {
        resultado[len - 1] = '\0';
    }

    return resultado;
}

char *joineada_paraesida_y_quitador_de_extremos(const char *data,
                                                int restar_cuantas,
                                                int restar_primera_celda)
{
    if (!data)
        return calloc(1, 1);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    char **partes = NULL;
    int n = split(data, GG_caracter_separacion[0], &partes);
    if (n <= 0)
    {
        free_split(partes);
        return resultado;
    }

    if (restar_primera_celda)
    {
        for (int i = restar_cuantas; i < n; i++)
        {
            if (i > restar_cuantas)
                strncat(resultado, GG_caracter_separacion[0], 65535 - strlen(resultado) - 1);
            if (partes[i])
                strncat(resultado, partes[i], 65535 - strlen(resultado) - 1);
        }
    }
    else
    {
        int cantidad_retornar = n - restar_cuantas;
        for (int i = 0; i < cantidad_retornar; i++)
        {
            if (i > 0)
                strncat(resultado, GG_caracter_separacion[0], 65535 - strlen(resultado) - 1);
            if (partes[i])
                strncat(resultado, partes[i], 65535 - strlen(resultado) - 1);
        }
    }

    free_split(partes);
    return resultado;
}

char *Trimend_paresido(const char *texto)
{
    if (!texto)
        return calloc(1, 1);

    char *resultado = malloc(strlen(texto) + 1);
    if (!resultado)
        return NULL;

    char **partes = NULL;
    int n = split(texto, GG_caracter_separacion[0], &partes);
    if (n <= 0)
    {
        free_split(partes);
        strcpy(resultado, texto);
        return resultado;
    }

    resultado[0] = '\0';
    int hasta = n;
    if (n > 0 && partes[n - 1] && strlen(partes[n - 1]) == 0)
        hasta = n - 1;

    for (int i = 0; i < hasta; i++)
    {
        if (i > 0)
            strncat(resultado, GG_caracter_separacion[0], strlen(texto) - 1);
        if (partes[i])
            strncat(resultado, partes[i], strlen(texto) - 1);
    }

    free_split(partes);
    return resultado;
}

char *concatenacion_filas_de_un_archivo(const char *ruta_archivo, int poner_num_fila)
{
    int n_lineas = 0;
    char **lineas = leer_archivo(ruta_archivo, &n_lineas);
    if (!lineas)
        return calloc(1, 1);

    char *resultado = malloc(65536);
    if (!resultado)
    {
        free_lineas(lineas, n_lineas);
        return NULL;
    }
    resultado[0] = '\0';

    for (int i = 0; i < n_lineas; i++)
    {
        char prefijo[32] = "";
        if (poner_num_fila)
            snprintf(prefijo, sizeof(prefijo), "%d) ", i);

        if (strlen(resultado) > 0)
            strncat(resultado, GG_caracter_separacion[0], 65535 - strlen(resultado) - 1);
        strncat(resultado, prefijo, 65535 - strlen(resultado) - 1);
        strncat(resultado, lineas[i], 65535 - strlen(resultado) - 1);
    }

    free_lineas(lineas, n_lineas);
    return resultado;
}

char *concatenacion_filas_de_un_arreglo(char **arreglo, int n_arreglo, int poner_num_fila)
{
    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    for (int i = 0; i < n_arreglo; i++)
    {
        if (!arreglo[i])
            continue;

        char prefijo[32] = "";
        if (poner_num_fila)
            snprintf(prefijo, sizeof(prefijo), "%d) ", i);

        if (strlen(resultado) > 0)
            strncat(resultado, GG_caracter_separacion[0], 65535 - strlen(resultado) - 1);
        strncat(resultado, prefijo, 65535 - strlen(resultado) - 1);
        strncat(resultado, arreglo[i], 65535 - strlen(resultado) - 1);
    }

    return resultado;
}

char *concatenacion_caracter_separacion(const char *texto_actual,
                                        const char *texto_agregar,
                                        const char *separador)
{
    if (!texto_agregar)
        return calloc(1, 1);

    size_t len_actual = texto_actual ? strlen(texto_actual) : 0;
    size_t len_agregar = strlen(texto_agregar);
    size_t len_sep = separador ? strlen(separador) : 0;

    char *resultado = malloc(len_actual + len_agregar + len_sep + 10);
    if (!resultado)
        return NULL;

    resultado[0] = '\0';

    if (texto_actual != NULL && strlen(texto_actual) > 0)
    {
        strcpy(resultado, texto_actual);
        if (separador)
            strncat(resultado, separador, len_sep);
    }

    strncat(resultado, texto_agregar, len_agregar);
    return resultado;
}

char *generar_folio(const char *formato_fecha_hora)
{
    char *folio = malloc(256);
    if (!folio)
        return NULL;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    if (formato_fecha_hora == NULL)
    {
        strftime(folio, 256, "%y%m%d%H%M%S", tm_info);
    }
    else
    {
        strftime(folio, 256, formato_fecha_hora, tm_info);
    }

    return folio;
}

char **extraer_separado_carpetas_nombreArchivo_extencion(const char *direccion_archivo)
{
    char **resultado = malloc(3 * sizeof(char *));
    if (!resultado)
        return NULL;

    for (int i = 0; i < 3; i++)
    {
        resultado[i] = malloc(512);
        if (resultado[i])
            resultado[i][0] = '\0';
    }

    if (!direccion_archivo)
        return resultado;

    char **partes = NULL;
    int n = split(direccion_archivo, "\\", &partes);
    if (n > 0)
    {
        for (int i = 0; i < n - 1; i++)
        {
            strncat(resultado[0], partes[i], 510 - strlen(resultado[0]));
            if (i < n - 2)
                strncat(resultado[0], "\\", 510 - strlen(resultado[0]));
        }

        char **nom_ext = NULL;
        int n_ne = split(partes[n - 1], ".", &nom_ext);
        if (n_ne > 0)
        {
            strncpy(resultado[1], nom_ext[0], 511);
            if (n_ne > 1)
                strncpy(resultado[2], nom_ext[1], 511);
            free_split(nom_ext);
        }
        free_split(partes);
    }

    return resultado;
}

char *ReemplazarCaracteres_de_texto_arreglo(const char *info,
                                            char **caracteres_sep, int n_sep,
                                            char **caracteres_sustitucion)
{
    if (!info)
        return calloc(1, 1);

    char *resultado = malloc(strlen(info) * 2 + 1);
    if (!resultado)
        return NULL;
    strcpy(resultado, info);

    for (int i = 0; i < n_sep; i++)
    {
        if (!caracteres_sep[i] || !caracteres_sustitucion[i])
            continue;

        char *temp = malloc(strlen(resultado) * 2 + 1024);
        if (!temp)
        {
            free(resultado);
            return NULL;
        }
        temp[0] = '\0';

        const char *pos = resultado;
        const char *found;
        int sep_len = strlen(caracteres_sep[i]);

        while ((found = strstr(pos, caracteres_sep[i])) != NULL)
        {
            strncat(temp, pos, found - pos);
            strcat(temp, caracteres_sustitucion[i]);
            pos = found + sep_len;
        }
        strcat(temp, pos);

        free(resultado);
        resultado = temp;
    }

    return resultado;
}

/* =========================================================================
   BÚSQUEDA PROFUNDA - Buscar en estructuras anidadas por columnas
   ========================================================================= */

char *busqueda_profunda_string(const char *texto, const char *columnas_recorrer,
                               const char *comparar)
{
    if (!texto || !columnas_recorrer || !comparar)
        return calloc(1, 1);

    /* Usar split para acceder a filas usando separador primario */
    char **filas = NULL;
    int n_filas = split(texto, GG_caracter_separacion[0], &filas);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    int encontrado = 0;
    for (int i = 0; i < n_filas; i++)
    {
        if (!filas[i])
            continue;

        /* Split la fila por segundo separador para acceder a columnas */
        char **columnas = NULL;
        int n_cols = split(filas[i], GG_caracter_separacion[1], &columnas);

        /* Recorrer columnas según índices especificados */
        const char *pos = columnas_recorrer;
        while (pos && *pos)
        {
            int col_idx = atoi(pos);
            if (col_idx >= 0 && col_idx < n_cols && columnas[col_idx])
            {
                if (strcmp(columnas[col_idx], comparar) == 0)
                {
                    if (encontrado)
                        strcat(resultado, GG_caracter_separacion[0]);
                    strcat(resultado, filas[i]);
                    encontrado = 1;
                    break;
                }
            }
            /* Buscar siguiente índice separado por '|' */
            while (pos && *pos && *pos != '|')
                pos++;
            if (*pos == '|')
                pos++;
        }

        free_split(columnas);
    }

    free_split(filas);
    return resultado;
}

/* =========================================================================
   BÚSQUEDA PROFUNDA CON FORMATO FINAL
   ========================================================================= */

char *busqueda_profunda_comparacion_final_string(const char *texto,
                                                 const char *columnas_recorrer,
                                                 const char *comparar)
{
    if (!texto || !columnas_recorrer || !comparar)
        return calloc(1, 1);

    /* Similar a busqueda_profunda_string pero retorna con formato especial */
    char **filas = NULL;
    int n_filas = split(texto, GG_caracter_separacion[0], &filas);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    int encontrado = 0;
    const char *ultima_fila = NULL;

    for (int i = 0; i < n_filas; i++)
    {
        if (!filas[i])
            continue;

        char **columnas = NULL;
        int n_cols = split(filas[i], GG_caracter_separacion[1], &columnas);

        const char *pos = columnas_recorrer;
        while (pos && *pos)
        {
            int col_idx = atoi(pos);
            if (col_idx >= 0 && col_idx < n_cols && columnas[col_idx])
            {
                if (strcmp(columnas[col_idx], comparar) == 0)
                {
                    ultima_fila = filas[i];
                    encontrado = 1;
                    break;
                }
            }
            while (pos && *pos && *pos != '|')
                pos++;
            if (*pos == '|')
                pos++;
        }

        free_split(columnas);
    }

    if (encontrado && ultima_fila)
        strcpy(resultado, ultima_fila);

    free_split(filas);
    return resultado;
}

/* =========================================================================
   BÚSQUEDA CON MÚLTIPLES CONDICIONES (YY)
   ========================================================================= */

char *busqueda_con_YY_profunda_texto_id_archivo(const char *texto,
                                                const char *columnas_recorrer,
                                                const char *comparaciones)
{
    if (!texto || !columnas_recorrer || !comparaciones)
        return calloc(1, 1);

    char **filas = NULL;
    int n_filas = split(texto, GG_caracter_separacion[0], &filas);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    /* Parsear comparaciones múltiples (separadas por algún delimitador) */
    char **comparaciones_arr = NULL;
    int n_comparaciones = split(comparaciones, "|", &comparaciones_arr);

    int encontrado = 0;
    for (int i = 0; i < n_filas; i++)
    {
        if (!filas[i])
            continue;

        char **columnas = NULL;
        int n_cols = split(filas[i], GG_caracter_separacion[1], &columnas);

        int todas_coinciden = 1;

        /* Verificar todas las condiciones */
        for (int j = 0; j < n_comparaciones && todas_coinciden; j++)
        {
            if (!comparaciones_arr[j])
                continue;

            /* Parsear "col_idx:valor" */
            char temp[1024];
            strcpy(temp, comparaciones_arr[j]);
            char *colon = strchr(temp, ':');

            if (colon)
            {
                *colon = '\0';
                int col_idx = atoi(temp);
                const char *valor_esperado = colon + 1;

                if (col_idx < 0 || col_idx >= n_cols || !columnas[col_idx] ||
                    strcmp(columnas[col_idx], valor_esperado) != 0)
                {
                    todas_coinciden = 0;
                }
            }
        }

        if (todas_coinciden)
        {
            if (encontrado)
                strcat(resultado, GG_caracter_separacion[0]);
            strcat(resultado, filas[i]);
            encontrado = 1;
        }

        free_split(columnas);
    }

    free_split(comparaciones_arr);
    free_split(filas);
    return resultado;
}

/* =========================================================================
   EDICIÓN CON INCREMENTO RECURSIVO
   ========================================================================= */

char *editar_incr_string_funcion_recursiva(const char *texto,
                                           const char *columnas_recorrer,
                                           const char *info_sustituir,
                                           const char *edit_0_increm_1)
{
    if (!texto || !columnas_recorrer)
        return calloc(1, 1);

    int es_incremento = edit_0_increm_1 && strcmp(edit_0_increm_1, "1") == 0;

    char **filas = NULL;
    int n_filas = split(texto, GG_caracter_separacion[0], &filas);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    for (int i = 0; i < n_filas; i++)
    {
        if (i > 0)
            strcat(resultado, GG_caracter_separacion[0]);

        if (!filas[i])
            continue;

        char **columnas = NULL;
        int n_cols = split(filas[i], GG_caracter_separacion[1], &columnas);

        /* Parsear índices de columnas a editar */
        const char *pos = columnas_recorrer;
        while (pos && *pos)
        {
            int col_idx = atoi(pos);
            if (col_idx >= 0 && col_idx < n_cols)
            {
                if (es_incremento && columnas[col_idx])
                {
                    /* Incrementar valor numérico */
                    int val = atoi(columnas[col_idx]);
                    char new_val[64];
                    snprintf(new_val, sizeof(new_val), "%d", val + 1);
                    strcpy(columnas[col_idx], new_val);
                }
                else if (info_sustituir && columnas[col_idx])
                {
                    /* Reemplazar con nuevo valor */
                    strcpy(columnas[col_idx], info_sustituir);
                }
            }
            while (pos && *pos && *pos != '|')
                pos++;
            if (*pos == '|')
                pos++;
        }

        /* Reconstruir fila */
        for (int j = 0; j < n_cols; j++)
        {
            if (j > 0)
                strcat(resultado, GG_caracter_separacion[1]);
            if (columnas[j])
                strcat(resultado, columnas[j]);
        }

        free_split(columnas);
    }

    free_split(filas);
    return resultado;
}

/* =========================================================================
   EDICIÓN PROFUNDA MÚLTIPLE CON COMPARACIÓN FINAL
   ========================================================================= */

char *editar_inc_agregar_edicion_profunda_multiple_comparacion_final_string(
    const char *texto,
    const char *indices_editar,
    const char *info_editar,
    const char *comparacion,
    const char *edit_0_increm_1)
{
    if (!texto || !indices_editar)
        return calloc(1, 1);

    /* Combina búsqueda con comparación y edición */
    char *encontrado = busqueda_profunda_comparacion_final_string(texto, indices_editar, comparacion);

    if (encontrado && strlen(encontrado) > 0)
    {
        char *editado = editar_incr_string_funcion_recursiva(encontrado, indices_editar,
                                                             info_editar, edit_0_increm_1);
        free(encontrado);
        return editado;
    }

    free(encontrado);
    return calloc(1, 1);
}

/* =========================================================================
   WRAPPER ARR_FUN - Edición con estructura simplificada
   ========================================================================= */

char *ARR_FUN_SOLO_TEXTO_editar_inc_agregar_edicion_profunda_multiple(const char *datos)
{
    if (!datos)
        return calloc(1, 1);

    /* Parsear estructura: "texto|indices|info|edit_mode" */
    char **partes = NULL;
    int n_partes = split(datos, "|", &partes);

    char *resultado = calloc(1, 1);

    if (n_partes >= 3)
    {
        resultado = editar_incr_string_funcion_recursiva(partes[0], partes[1],
                                                         partes[2],
                                                         n_partes > 3 ? partes[3] : "0");
    }

    free_split(partes);
    return resultado;
}

/* =========================================================================
   EDICIÓN CON MÚLTIPLES CHEQUEOS
   ========================================================================= */

char *editar_inc_agregar_edicion_profunda_multiple_comparacion_MULTIPLE_A_CHECAR(
    const char *texto,
    const char *indices_editar,
    const char *comparacion_con_edicion,
    const char *edit_0_increm_1)
{
    if (!texto || !indices_editar || !comparacion_con_edicion)
        return calloc(1, 1);

    /* Parsear comparación_con_edicion para extraer comparación e info_editar */
    char temp[1024];
    strcpy(temp, comparacion_con_edicion);
    char *coma = strchr(temp, ',');

    char *comparar_val = temp;
    char *editar_val = "";

    if (coma)
    {
        *coma = '\0';
        editar_val = coma + 1;
    }

    /* Buscar filas que coincidan y editarlas */
    char **filas = NULL;
    int n_filas = split(texto, GG_caracter_separacion[0], &filas);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    for (int i = 0; i < n_filas; i++)
    {
        if (i > 0)
            strcat(resultado, GG_caracter_separacion[0]);

        if (!filas[i])
            continue;

        /* Verificar si esta fila coincide con la búsqueda */
        char **columnas = NULL;
        int n_cols = split(filas[i], GG_caracter_separacion[1], &columnas);

        int debe_editar = 0;
        const char *pos = indices_editar;
        while (pos && *pos)
        {
            int col_idx = atoi(pos);
            if (col_idx >= 0 && col_idx < n_cols && columnas[col_idx] &&
                strcmp(columnas[col_idx], comparar_val) == 0)
            {
                debe_editar = 1;
                break;
            }
            while (pos && *pos && *pos != '|')
                pos++;
            if (*pos == '|')
                pos++;
        }

        if (debe_editar)
        {
            pos = indices_editar;
            while (pos && *pos)
            {
                int col_idx = atoi(pos);
                if (col_idx >= 0 && col_idx < n_cols)
                {
                    int es_incremento = edit_0_increm_1 && strcmp(edit_0_increm_1, "1") == 0;
                    if (columnas[col_idx] && strcmp(columnas[col_idx], comparar_val) == 0)
                    {
                        if (es_incremento)
                        {
                            int val = atoi(columnas[col_idx]);
                            snprintf(columnas[col_idx], 64, "%d", val + 1);
                        }
                        else if (*editar_val)
                        {
                            strcpy(columnas[col_idx], editar_val);
                        }
                    }
                }
                while (pos && *pos && *pos != '|')
                    pos++;
                if (*pos == '|')
                    pos++;
            }
        }

        for (int j = 0; j < n_cols; j++)
        {
            if (j > 0)
                strcat(resultado, GG_caracter_separacion[1]);
            if (columnas[j])
                strcat(resultado, columnas[j]);
        }

        free_split(columnas);
    }

    free_split(filas);
    return resultado;
}

/* =========================================================================
   EDICIÓN PROFUNDA MÚLTIPLE SIMPLE
   ========================================================================= */

char *editar_inc_edicion_profunda_multiple_string(const char *texto,
                                                  const char *indices_editar,
                                                  const char *info_editar,
                                                  const char *edit_0_increm_1)
{
    /* Simplemente aplica la edición a todas las filas en los índices especificados */
    char **filas = NULL;
    int n_filas = split(texto, GG_caracter_separacion[0], &filas);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    int es_incremento = edit_0_increm_1 && strcmp(edit_0_increm_1, "1") == 0;

    for (int i = 0; i < n_filas; i++)
    {
        if (i > 0)
            strcat(resultado, GG_caracter_separacion[0]);

        if (!filas[i])
            continue;

        char **columnas = NULL;
        int n_cols = split(filas[i], GG_caracter_separacion[1], &columnas);

        const char *pos = indices_editar;
        while (pos && *pos)
        {
            int col_idx = atoi(pos);
            if (col_idx >= 0 && col_idx < n_cols && columnas[col_idx])
            {
                if (es_incremento)
                {
                    int val = atoi(columnas[col_idx]);
                    snprintf(columnas[col_idx], 64, "%d", val + 1);
                }
                else if (info_editar)
                {
                    strcpy(columnas[col_idx], info_editar);
                }
            }
            while (pos && *pos && *pos != '|')
                pos++;
            if (*pos == '|')
                pos++;
        }

        for (int j = 0; j < n_cols; j++)
        {
            if (j > 0)
                strcat(resultado, GG_caracter_separacion[1]);
            if (columnas[j])
                strcat(resultado, columnas[j]);
        }

        free_split(columnas);
    }

    free_split(filas);
    return resultado;
}

/* =========================================================================
   EDICIÓN PROFUNDA AL FINAL
   ========================================================================= */

char *editar_inc_edicion_profunda_multiple_AL_FINAL_string(const char *texto,
                                                           const char *indices_editar,
                                                           const char *info_editar,
                                                           const char *edit_0_increm_1)
{
    /* Edita solo la última fila que coincide */
    char **filas = NULL;
    int n_filas = split(texto, GG_caracter_separacion[0], &filas);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    int es_incremento = edit_0_increm_1 && strcmp(edit_0_increm_1, "1") == 0;

    /* Primera pasada: copiar todas las filas */
    for (int i = 0; i < n_filas; i++)
    {
        if (i > 0)
            strcat(resultado, GG_caracter_separacion[0]);

        if (!filas[i])
            continue;

        /* En la última iteración, editar */
        if (i == n_filas - 1)
        {
            char **columnas = NULL;
            int n_cols = split(filas[i], GG_caracter_separacion[1], &columnas);

            const char *pos = indices_editar;
            while (pos && *pos)
            {
                int col_idx = atoi(pos);
                if (col_idx >= 0 && col_idx < n_cols && columnas[col_idx])
                {
                    if (es_incremento)
                    {
                        int val = atoi(columnas[col_idx]);
                        snprintf(columnas[col_idx], 64, "%d", val + 1);
                    }
                    else if (info_editar)
                    {
                        strcpy(columnas[col_idx], info_editar);
                    }
                }
                while (pos && *pos && *pos != '|')
                    pos++;
                if (*pos == '|')
                    pos++;
            }

            for (int j = 0; j < n_cols; j++)
            {
                if (j > 0)
                    strcat(resultado, GG_caracter_separacion[1]);
                if (columnas[j])
                    strcat(resultado, columnas[j]);
            }

            free_split(columnas);
        }
        else
        {
            strcat(resultado, filas[i]);
        }
    }

    free_split(filas);
    return resultado;
}

/* =========================================================================
   RECORRER CARACTERES DE SEPARACIÓN
   ========================================================================= */

char *recorrer_caracter_separacion(const char *contenidoFila,
                                   const char *izquierda_o_derecha,
                                   int numero_veses)
{
    if (!contenidoFila)
        return calloc(1, 1);

    char **partes = NULL;
    int n_partes = split(contenidoFila, GG_caracter_separacion[0], &partes);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    int es_izquierda = izquierda_o_derecha && strcmp(izquierda_o_derecha, "izq") == 0;

    if (es_izquierda)
    {
        /* Saltar primeros 'numero_veses' elementos */
        for (int i = numero_veses; i < n_partes; i++)
        {
            if (i > numero_veses)
                strcat(resultado, GG_caracter_separacion[0]);
            if (partes[i])
                strcat(resultado, partes[i]);
        }
    }
    else
    {
        /* Tomar hasta 'n - numero_veses' elementos */
        int hasta = n_partes - numero_veses;
        for (int i = 0; i < hasta && i < n_partes; i++)
        {
            if (i > 0)
                strcat(resultado, GG_caracter_separacion[0]);
            if (partes[i])
                strcat(resultado, partes[i]);
        }
    }

    free_split(partes);
    return resultado;
}

/* =========================================================================
   RECORRER CARACTERES DE SEPARACIÓN - FUNCIÓN ESPECÍFICA
   ========================================================================= */

char *recorrer_caracter_separacion_funciones_espesificas(const char *contenidoFila,
                                                         const char *izquierda_o_derecha,
                                                         int numero_veses)
{
    if (!contenidoFila)
        return calloc(1, 1);

    /* Usar separador específico si está disponible */
    char separador[16];
    if (GG_caracter_separacion_funciones_espesificas[0])
        strcpy(separador, GG_caracter_separacion_funciones_espesificas[0]);
    else
        strcpy(separador, GG_caracter_separacion[0]);

    char **partes = NULL;
    int n_partes = split(contenidoFila, separador, &partes);

    char *resultado = malloc(65536);
    if (!resultado)
        return NULL;
    resultado[0] = '\0';

    int es_izquierda = izquierda_o_derecha && strcmp(izquierda_o_derecha, "izq") == 0;

    if (es_izquierda)
    {
        for (int i = numero_veses; i < n_partes; i++)
        {
            if (i > numero_veses)
                strcat(resultado, separador);
            if (partes[i])
                strcat(resultado, partes[i]);
        }
    }
    else
    {
        int hasta = n_partes - numero_veses;
        for (int i = 0; i < hasta && i < n_partes; i++)
        {
            if (i > 0)
                strcat(resultado, separador);
            if (partes[i])
                strcat(resultado, partes[i]);
        }
    }

    free_split(partes);
    return resultado;
}
