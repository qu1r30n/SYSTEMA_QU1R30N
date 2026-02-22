#include <stdlib.h>   // malloc, realloc, free
#include <string.h>   // strlen, memcpy, strstr

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

int split(const char* txt, const char* sep, char*** salida)
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
        return -1;

    /* Obtener longitud del separador */
    size_t len_sep = strlen(sep);

    /* Si el separador está vacío, no tiene sentido dividir */
    if (len_sep == 0)
        return -1;

    /* Capacidad inicial del arreglo dinámico
       Significa que inicialmente podemos guardar 4 fragmentos */
    int capacidad = 4;

    /* Cantidad real de fragmentos encontrados */
    int cantidad = 0;

    /* Reservar memoria para arreglo de punteros (char*) */
    char** resultado = malloc(sizeof(char*) * capacidad);

    /* Si falla malloc → error */
    if (resultado == NULL)
        return -1;

    /* inicio apunta al comienzo del fragmento actual */
    const char* inicio = txt;

    /* Buscar primera aparición del separador */
    const char* pos = strstr(inicio, sep);

    /* -----------------------------------------------------------------------
       BUCLE PRINCIPAL
       Mientras encontremos el separador en el texto
    ----------------------------------------------------------------------- */
    while (pos != NULL)
    {
        /* Calcular longitud del fragmento actual */
        size_t len_fragmento = (size_t)(pos - inicio);

        /* Reservar memoria para el fragmento (+1 para '\0') */
        char* fragmento = malloc(len_fragmento + 1);

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

            char** temp = realloc(resultado, sizeof(char*) * capacidad);

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

    char* fragmento_final = malloc(len_final + 1);

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
        char** temp = realloc(resultado, sizeof(char*) * (capacidad + 1));

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

    char** temp = realloc(resultado, sizeof(char*) * (cantidad + 1));

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

void free_split(char** arreglo)
{
    /* Si es NULL, no hacer nada */
    if (arreglo == NULL)
        return;

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
