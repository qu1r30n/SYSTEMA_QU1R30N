#ifdef _WIN32
#include <stdio.h>  // Librería estándar para entrada y salida (printf, etc.)
#include <stdlib.h> // Librería estándar para memoria dinámica (malloc, realloc, free)
#include <string.h> // Librería para manejo de cadenas (strlen, strcmp, strcpy)
#endif

#ifdef __linux__
#include <stdio.h>  // Librería estándar para entrada y salida (printf, etc.)
#include <stdlib.h> // Librería estándar para memoria dinámica (malloc, realloc, free)
#include <string.h> // Librería para manejo de cadenas (strlen, strcmp, strcpy)
#endif

#ifdef __XC
#include <stdio.h>  // Librería estándar para entrada y salida (printf, etc.)
#include <string.h> // Librería para manejo de cadenas (strlen, strcmp, strcpy)
#endif

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
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
    StructurasDinamicas s; // Variable local tipo StructurasDinamicas. Valor inicial = basura (memoria no inicializada)

    s.arreglo_char = NULL;  // Arreglo de strings. Valor = NULL porque aún no hay memoria reservada
    s.arreglo_int = NULL;   // Arreglo de enteros. Valor = NULL
    s.arreglo_float = NULL; // Arreglo de floats. Valor = NULL

    s.orden_tipo = NULL;   // Arreglo que guarda el tipo de cada campo (0,1,2). Valor = NULL
    s.orden_indice = NULL; // Arreglo que guarda el índice dentro del arreglo real. Valor = NULL
    s.nombres = NULL;      // Arreglo de nombres de campos (char**). Valor = NULL

    s.total = 0;        // Número total de campos en la estructura. Valor = 0
    s.count_string = 0; // Cantidad de campos tipo string. Valor = 0
    s.count_int = 0;    // Cantidad de campos tipo int. Valor = 0
    s.count_float = 0;  // Cantidad de campos tipo float. Valor = 0

    return s; // Se regresa la estructura inicializada
}

/* ============================================= */
/* AGREGAR CAMPO DINÁMICO                       */
/* ============================================= */
void agregarCampo(StructurasDinamicas *s, const char *nombre, const char *tipo)
{
    imprimirMensaje_para_depurar("-------------------------------------------------------------------------------------------\n");
    imprimirMensaje_para_depurar("%s|%s\n", nombre, tipo); // Imprime el nombre y valor que se van a asignar (para depuración)

    if (!s || !nombre || !tipo) // Verifica si algún puntero es NULL
    {
        return; // Si alguno es NULL se sale de la función
    }

    /* Incrementar total y reallocar arreglos de metadata */
    imprimirMensaje_para_depurar("ANTES total: %d\n", s->total);           // Imprime el total de campos antes de agregar el nuevo campo (para depuración)
    s->total += 1;                                                         // Incrementa el número total de campos. Ejemplo: si era 0 ahora es 1
    imprimirMensaje_para_depurar("Nuevo total de campos: %d\n", s->total); // Imprime el nuevo total de campos (para depuración)

    imprimirMensaje_para_depurar("ANTES orden_tipo: %p\n", (void *)s->orden_tipo);                // Imprime la dirección del arreglo de tipos antes del realloc (para depuración)
    s->orden_tipo = (int *)realloc(s->orden_tipo, sizeof(int) * s->total);                        // realloc aumenta o crea el arreglo de tipos para que tenga espacio para el nuevo campo
    imprimirMensaje_para_depurar("Realloc orden_tipo -> direccion: %p\n", (void *)s->orden_tipo); // Imprime la dirección del arreglo de tipos después del realloc (para depuración)

    imprimirMensaje_para_depurar("ANTES orden_indice: %p\n", (void *)s->orden_indice);                // Imprime la dirección del arreglo de índices antes del realloc (para depuración)
    s->orden_indice = (int *)realloc(s->orden_indice, sizeof(int) * s->total);                        // guarda la posición dentro del arreglo real
    imprimirMensaje_para_depurar("Realloc orden_indice -> direccion: %p\n", (void *)s->orden_indice); // Imprime la dirección del arreglo de índices después del realloc (para depuración)

    imprimirMensaje_para_depurar("ANTES nombres: %p\n", (void *)s->nombres);                // Imprime la dirección del arreglo de nombres antes del realloc (para depuración)
    s->nombres = (char **)realloc(s->nombres, sizeof(char *) * s->total);                   // arreglo de punteros a char para los nombres de los campos
    imprimirMensaje_para_depurar("Realloc nombres -> direccion: %p\n", (void *)s->nombres); // Imprime la dirección del arreglo de nombres después del realloc (para depuración)

    imprimirMensaje_para_depurar("ANTES nombres[%d]: %p\n", s->total - 1, (void *)s->nombres[s->total - 1]);                   // Imprime la dirección del nombre del campo antes del malloc (para depuración)
    s->nombres[s->total - 1] = (char *)malloc(strlen(nombre) + 1);                                                             // reserva memoria para el nombre del campo
    imprimirMensaje_para_depurar("Malloc para nombre[%d] -> direccion: %p\n", s->total - 1, (void *)s->nombres[s->total - 1]); // Imprime la dirección del nombre del campo después del malloc (para depuración)

    imprimirMensaje_para_depurar("ANTES nombres[%d]: %p\n", s->total - 1, (void *)s->nombres[s->total - 1]); // Imprime la dirección del nombre del campo antes del strcpy (para depuración)
    if (s->nombres[s->total - 1])                                                                            // verifica que malloc no haya devuelto NULL (que la memoria se reservó correctamente)
    {
        strcpy(s->nombres[s->total - 1], nombre); // copia el nombre al espacio reservado
    }
    imprimirMensaje_para_depurar("DESPUES nombres[%d]: %p -> %s\n", s->total - 1, (void *)s->nombres[s->total - 1], s->nombres[s->total - 1]);

    /* Agregar campo según tipo */
    if (strcmp(tipo, "string") == 0)
    {
        imprimirMensaje_para_depurar("ANTES arreglo_char: %p, count_string: %d\n", (void *)s->arreglo_char, s->count_string); // Imprime la dirección del arreglo de strings y el contador de strings antes del realloc (para depuración)
        // aumenta el arreglo de strings para que tenga espacio para el nuevo campo
        s->arreglo_char = (char **)realloc(s->arreglo_char, sizeof(char *) * (s->count_string + 1));
        s->arreglo_char[s->count_string] = NULL;                                                                                                                                              // valor inicial = NULL
        imprimirMensaje_para_depurar("DESPUES arreglo_char: %p, count_string: %d, nuevo elemento: %p\n", (void *)s->arreglo_char, s->count_string, (void *)s->arreglo_char[s->count_string]); // Imprime la dirección del arreglo de strings, el contador de strings y la dirección del nuevo elemento después del realloc (para depuración)

        imprimirMensaje_para_depurar("ANTES: orden_tipo[%d]=%d\norden_indice[%d]=%d\ncount_string=%d\n", s->total - 1, s->orden_tipo[s->total - 1], s->total - 1, s->orden_indice[s->total - 1], s->count_string);   // Imprime el tipo y el índice que se van a asignar antes de asignarlos (para depuración)
        s->orden_tipo[s->total - 1] = TIPO_STRING;                                                                                                                                                                   // guarda tipo = 0
        s->orden_indice[s->total - 1] = s->count_string;                                                                                                                                                             // índice dentro del arreglo de strings
        s->count_string++;                                                                                                                                                                                           // aumenta contador de strings
        imprimirMensaje_para_depurar("DESPUES: orden_tipo[%d]=%d\norden_indice[%d]=%d\ncount_string=%d\n", s->total - 1, s->orden_tipo[s->total - 1], s->total - 1, s->orden_indice[s->total - 1], s->count_string); // Imprime el tipo y el índice que se asigno (para depuración)
    }
    else if (strcmp(tipo, "int") == 0)
    {
        imprimirMensaje_para_depurar("ANTES arreglo_int: %p, count_int: %d\n", (void *)s->arreglo_int, s->count_int);
        s->arreglo_int = (int *)realloc(s->arreglo_int, sizeof(int) * (s->count_int + 1));                                                                                // aumenta el arreglo de enteros para que tenga espacio para el nuevo campo
        s->arreglo_int[s->count_int] = 0;                                                                                                                                 // valor inicial = 0
        imprimirMensaje_para_depurar("DESPUES arreglo_int: %p, count_int: %d, nuevo elemento: %d\n", (void *)s->arreglo_int, s->count_int, s->arreglo_int[s->count_int]); // Imprime la dirección del arreglo de enteros, el contador de enteros y el valor del nuevo elemento después del realloc (para depuración)

        imprimirMensaje_para_depurar("ANTES: orden_tipo[%d]=%d\norden_indice[%d]=%d\ncount_string=%d\n", s->total - 1, s->orden_tipo[s->total - 1], s->total - 1, s->orden_indice[s->total - 1], s->count_string); // Imprime el tipo y el índice que se van a asignar antes de asignarlos (para depuración)
        s->orden_tipo[s->total - 1] = TIPO_INT;                                                                                                                                                                    // índice dentro del arreglo de int
        s->orden_indice[s->total - 1] = s->count_int;                                                                                                                                                              // índice dentro del arreglo de enteros
        s->count_int++;                                                                                                                                                                                            // aumenta contador de enteros
        imprimirMensaje_para_depurar("DESPUES arreglo_int: %p, count_int: %d, nuevo elemento: %d\n", (void *)s->arreglo_int, s->count_int, s->arreglo_int[s->count_int]);                                          // Imprime la dirección del arreglo de enteros, el contador de enteros y el valor del nuevo elemento después del realloc (para depuración)
    }
    else if (strcmp(tipo, "float") == 0)
    {
        imprimirMensaje_para_depurar("ANTES arreglo_float: %p, count_float: %d\n", (void *)s->arreglo_float, s->count_float);                                                           // Imprime la dirección del arreglo de floats y el contador de floats antes del realloc (para depuración)
        s->arreglo_float = (float *)realloc(s->arreglo_float, sizeof(float) * (s->count_float + 1));                                                                                    // aumenta el arreglo de floats para que tenga espacio para el nuevo campo
        s->arreglo_float[s->count_float] = 0.0f;                                                                                                                                        // valor inicial = 0.0f
        imprimirMensaje_para_depurar("DESPUES arreglo_float: %p, count_float: %d, nuevo elemento: %.2f\n", (void *)s->arreglo_float, s->count_float, s->arreglo_float[s->count_float]); // Imprime la dirección del arreglo de floats, el contador de floats y el valor del nuevo elemento después del realloc (para depuración)

        imprimirMensaje_para_depurar("ANTES: orden_tipo[%d]=%d\norden_indice[%d]=%d\ncount_string=%d\n", s->total - 1, s->orden_tipo[s->total - 1], s->total - 1, s->orden_indice[s->total - 1], s->count_string); // Imprime el tipo y el índice que se van a asignar antes de asignarlos (para depuración)
        s->orden_tipo[s->total - 1] = TIPO_FLOAT;                                                                                                                                                                  // índice dentro del arreglo de float
        s->orden_indice[s->total - 1] = s->count_float;                                                                                                                                                            // índice dentro del arreglo de floats
        s->count_float++;                                                                                                                                                                                          // aumenta contador de floats
        imprimirMensaje_para_depurar("DESPUES arreglo_float: %p, count_float: %d, nuevo elemento: %.2f\n", (void *)s->arreglo_float, s->count_float, s->arreglo_float[s->count_float]);                            // Imprime la dirección del arreglo de floats, el contador de floats y el valor del nuevo elemento después del realloc (para depuración)
    }
    imprimirMensaje_para_depurar("--------------------------------------------------------------------------------------------------\n");
}

/* ============================================= */
/* IMPRIMIR ESTRUCTURA DINÁMICA                  */
/* ============================================= */
void imprimirStructura(StructurasDinamicas *s)
{
    if (!s)
    {
        imprimirMensaje_para_depurar("imprimirStructura: estructura NULL\n");
        return;
    }

    for (int i = 0; i < s->total; i++)
    {
        imprimirMensaje_para_depurar("%s = ", s->nombres[i]); // Imprime el nombre del campo

        if (s->orden_tipo[i] == TIPO_STRING) // Si el tipo es string, imprime el valor del arreglo de strings en la posición indicada por orden_indice
        {
            char *valor = s->arreglo_char[s->orden_indice[i]];            // valor del campo (string)
            imprimirMensaje_para_depurar("%s\n", valor ? valor : "NULL"); // Imprime el valor del campo o "NULL" si es NULL
        }
        else if (s->orden_tipo[i] == TIPO_INT) // Si el tipo es int, imprime el valor del arreglo de enteros en la posición indicada por orden_indice
        {
            imprimirMensaje_para_depurar("%d\n", s->arreglo_int[s->orden_indice[i]]); // Imprime el valor del campo (int)
        }
        else if (s->orden_tipo[i] == TIPO_FLOAT) // Si el tipo es float, imprime el valor del arreglo de floats en la posición indicada por orden_indice
        {
            imprimirMensaje_para_depurar("%.2f\n", s->arreglo_float[s->orden_indice[i]]); // Imprime el valor del campo (float)
        }
    }
}

/* ============================================= */
/* ASIGNAR VALOR STRING POR NOMBRE              */
/* ============================================= */
void asignarValorString(StructurasDinamicas *s, const char *nombre, const char *valor)
{
    imprimirMensaje_para_depurar("%s|%s\n", nombre, valor); // Imprime el nombre y valor que se van a asignar (para depuración)

    if (!s || !nombre) // Verifica si el puntero a la estructura o el nombre es NULL
    {
        imprimirMensaje_para_depurar("asignarValorString: parametros invalidos\n");
        return;
    }

    for (int i = 0; i < s->total; i++) // Recorre los campos de la estructura para encontrar el que coincide con el nombre y es de tipo string
    {
        imprimirMensaje_para_depurar("%d | %s | %s\n", i, s->nombres[i], nombre); // Imprime el índice, el nombre del campo actual y el nombre que se busca (para depuración)

        if (strcmp(s->nombres[i], nombre) == 0 && s->orden_tipo[i] == TIPO_STRING) // Si encuentra el campo con el nombre y tipo string
        {
            /* Liberar valor anterior si existe */
            if (s->arreglo_char[s->orden_indice[i]]) // Si el campo ya tiene un valor asignado (no es NULL), libera la memoria para evitar fugas
            {
                free(s->arreglo_char[s->orden_indice[i]]); // Libera la memoria del valor anterior
            }
            /* Asignar nuevo valor */
            s->arreglo_char[s->orden_indice[i]] = (char *)malloc(strlen(valor) + 1);
            if (s->arreglo_char[s->orden_indice[i]]) // Verifica que malloc no haya devuelto NULL (que la memoria se reservó correctamente)
            {
                strcpy(s->arreglo_char[s->orden_indice[i]], valor); // Copia el nuevo valor al espacio reservado
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
    imprimirMensaje_para_depurar("asignarValorInt: %s=%d\n", nombre ? nombre : "(null)", valor);

    if (!s || !nombre) // Verifica si el puntero a la estructura o el nombre es NULL
    {
        imprimirMensaje_para_depurar("asignarValorInt: parametros invalidos\n");
        return;
    }

    for (int i = 0; i < s->total; i++) // Recorre los campos de la estructura para encontrar el que coincide con el nombre y es de tipo int
    {
        imprimirMensaje_para_depurar("asignarValorInt revisando: i=%d, campo=%s\n", i, s->nombres[i]);

        if (strcmp(s->nombres[i], nombre) == 0 && s->orden_tipo[i] == TIPO_INT) // Si encuentra el campo con el nombre y tipo int
        {
            s->arreglo_int[s->orden_indice[i]] = valor; // Asigna el valor al campo (int)
            imprimirMensaje_para_depurar("asignarValorInt aplicado: %s=%d\n", nombre, s->arreglo_int[s->orden_indice[i]]);
            return;
        }
    }

    imprimirMensaje_para_depurar("asignarValorInt: campo no encontrado o tipo incorrecto (%s)\n", nombre);
}

/* ============================================= */
/* ASIGNAR VALOR FLOAT POR NOMBRE               */
/* ============================================= */
void asignarValorFloat(StructurasDinamicas *s, const char *nombre, float valor)
{
    imprimirMensaje_para_depurar("asignarValorFloat: %s=%.2f\n", nombre ? nombre : "(null)", valor);

    if (!s || !nombre) // Verifica si el puntero a la estructura o el nombre es NULL
    {
        imprimirMensaje_para_depurar("asignarValorFloat: parametros invalidos\n");
        return;
    }

    for (int i = 0; i < s->total; i++) // Recorre los campos de la estructura para encontrar el que coincide con el nombre y es de tipo float
    {
        imprimirMensaje_para_depurar("asignarValorFloat revisando: i=%d, campo=%s\n", i, s->nombres[i]);

        if (strcmp(s->nombres[i], nombre) == 0 && s->orden_tipo[i] == TIPO_FLOAT) // Si encuentra el campo con el nombre y tipo float
        {
            s->arreglo_float[s->orden_indice[i]] = valor; // Asigna el valor al campo (float)
            imprimirMensaje_para_depurar("asignarValorFloat aplicado: %s=%.2f\n", nombre, s->arreglo_float[s->orden_indice[i]]);
            return;
        }
    }

    imprimirMensaje_para_depurar("asignarValorFloat: campo no encontrado o tipo incorrecto (%s)\n", nombre);
}

/* ============================================= */
/* LIBERAR MEMORIA DE LA ESTRUCTURA              */
/* ============================================= */
void liberarStructura(StructurasDinamicas *s)
{
    if (!s) // Verifica si el puntero a la estructura es NULL
    {
        return;
    }

    /* Liberar nombres */
    if (s->nombres) // Si el arreglo de nombres no es NULL, libera cada nombre y luego el arreglo de nombres
    {
        for (int i = 0; i < s->total; i++) // Recorre los nombres de los campos
        {
            if (s->nombres[i]) // Si el nombre del campo no es NULL, libera la memoria
            {
                free(s->nombres[i]); // Libera la memoria del nombre del campo
            }
        }
        free(s->nombres);  // Libera la memoria del arreglo de nombres
        s->nombres = NULL; // Establece el puntero a NULL para evitar accesos a memoria liberada
    }

    /* Liberar strings de valores */
    if (s->arreglo_char) // Si el arreglo de strings no es NULL, libera cada string y luego el arreglo de strings
    {
        for (int i = 0; i < s->count_string; i++) // Recorre los campos de tipo string
        {
            if (s->arreglo_char[i]) // Si el campo de tipo string no es NULL, libera la memoria
            {
                free(s->arreglo_char[i]); // Libera la memoria del campo de tipo string
            }
        }
        free(s->arreglo_char);  // Libera la memoria del arreglo de strings
        s->arreglo_char = NULL; // Establece el puntero a NULL para evitar accesos a memoria liberada
    }

    /* Liberar arreglos de tipos */
    if (s->orden_tipo) // Si el arreglo de tipos no es NULL, libera la memoria
    {
        free(s->orden_tipo);  // Libera la memoria del arreglo de tipos
        s->orden_tipo = NULL; // Establece el puntero a NULL para evitar accesos a memoria liberada
    }

    if (s->orden_indice) // Si el arreglo de índices no es NULL, libera la memoria
    {
        free(s->orden_indice);  // Libera la memoria del arreglo de índices
        s->orden_indice = NULL; // Establece el puntero a NULL para evitar accesos a memoria liberada
    }

    if (s->arreglo_int) // Si el arreglo de enteros no es NULL, libera la memoria
    {
        free(s->arreglo_int);  // Libera la memoria del arreglo de enteros
        s->arreglo_int = NULL; // Establece el puntero a NULL para evitar accesos a memoria liberada
    }

    if (s->arreglo_float) // Si el arreglo de floats no es NULL, libera la memoria
    {
        free(s->arreglo_float);  // Libera la memoria del arreglo de floats
        s->arreglo_float = NULL; // Establece el puntero a NULL para evitar accesos a memoria liberada
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
    for (size_t i = 0; nombres_variables[i][0] != NULL; i++) // Recorre el arreglo de nombres de variables hasta encontrar un NULL(para depuración)
    {
        printf("Fila %zu:\n", i);

        for (size_t j = 0; j < 4; j++)
        {
            if (nombres_variables[i][j] != NULL)
            {
                printf("Elemento [%zu][%zu]: %s\n", i, j, nombres_variables[i][j]);
            }
        }
    }

    StructurasDinamicas datos = crearStructuraVacia();
    int cuantos_parametros_hay = 0;

    while (nombres_variables[cuantos_parametros_hay][0] != NULL) // Recorre el arreglo de nombres de variables hasta encontrar un NULL
    {
        agregarCampo(&datos,                                        // Agrega un campo a la estructura con el nombre y tipo especificados en el arreglo de nombres de variables
                     nombres_variables[cuantos_parametros_hay][0],  // nombre del campo
                     nombres_variables[cuantos_parametros_hay][1]); // tipo del campo (string, int, float)

        if (strcmp(nombres_variables[cuantos_parametros_hay][1], "string") == 0) // Si el tipo del campo es string
        {
            asignarValorString(&datos,                                        // Asigna el valor por defecto al campo de tipo string según lo especificado en el arreglo de nombres de variables
                               nombres_variables[cuantos_parametros_hay][0],  // nombre del campo
                               nombres_variables[cuantos_parametros_hay][2]); // valor por defecto del campo de tipo string
        }
        else if (strcmp(nombres_variables[cuantos_parametros_hay][1], "int") == 0) // Si el tipo del campo es int
        {
            asignarValorInt(&datos,                                              // Asigna el valor por defecto al campo de tipo int según lo especificado en el arreglo de nombres de variables
                            nombres_variables[cuantos_parametros_hay][0],        // nombre del campo
                            atoi(nombres_variables[cuantos_parametros_hay][2])); // valor por defecto del campo de tipo int
        }
        else if (strcmp(nombres_variables[cuantos_parametros_hay][1], "float") == 0) // Si el tipo del campo es float
        {
            asignarValorFloat(&datos,                                                     // Asigna el valor por defecto al campo de tipo float según lo especificado en el arreglo de nombres de variables
                              nombres_variables[cuantos_parametros_hay][0],               // nombre del campo
                              (float)atof(nombres_variables[cuantos_parametros_hay][2])); // valor por defecto del campo de tipo float
        }

        cuantos_parametros_hay++; // Incrementa el contador de parámetros para pasar al siguiente campo en el arreglo de nombres de variables
    }

    return datos;
}

/* Obtener valor de estructura por orden de inserci?n */
void *obtenerValorPorOrden(StructurasDinamicas *datos, int orden)
{

    if (orden < 0 || orden >= datos->total) // Verifica que el orden solicitado esté dentro del rango de campos existentes en la estructura
    {
        return NULL;
    }

    int tipo = datos->orden_tipo[orden];     // Obtiene el tipo del campo según el orden de inserción
    int indice = datos->orden_indice[orden]; // Obtiene el índice del campo según el orden de inserción

    if (tipo == TIPO_STRING) // Si el tipo del campo es string
    {
        return (void *)datos->arreglo_char[indice]; // Retorna el valor del campo de tipo string en la posición indicada por el índice
    }
    else if (tipo == TIPO_INT) // Si el tipo del campo es int
    {
        return (void *)&datos->arreglo_int[indice]; // Retorna el valor del campo de tipo int en la posición indicada por el índice
    }
    else if (tipo == TIPO_FLOAT) // Si el tipo del campo es float
    {
        return (void *)&datos->arreglo_float[indice]; // Retorna el valor del campo de tipo float en la posición indicada por el índice
    }

    return NULL;
}

/* Procesar partes de texto y cargar en estructura */
StructurasDinamicas procesar_partes_del_texto(char **partes, char *nombres_variables[][4], const char *separador)
{
    StructurasDinamicas datos = cargarDesdeArreglo(nombres_variables);

    int i = 0;
    while (partes[i]) // Recorre las partes del texto hasta encontrar un NULL
    {
        char **nom_parametro_dato = modelo_split(partes[i], separador); // Divide cada parte del texto en nombre de parámetro y valor usando el separador especificado
        for (int j = 0; nom_parametro_dato[j] != NULL; j++)
        {
            imprimirMensaje_para_depurar("nom_parametro_dato[%d]: %s  separador:%s\n", j, nom_parametro_dato[j], separador);
        }

        if (nom_parametro_dato && nom_parametro_dato[0] && nom_parametro_dato[1]) // Verifica que la división haya sido exitosa y que ambos elementos existan
        {
            int j = 0;
            while (nombres_variables[j][0]) // Recorre el arreglo de nombres de variables hasta encontrar un NULL
            {
                if (strcmp(nombres_variables[j][0], nom_parametro_dato[0]) == 0) // Compara el nombre del parámetro con el nombre de la variable
                {
                    if (strcmp(nombres_variables[j][1], "string") == 0) // Si el tipo del campo es string
                    {
                        asignarValorString(&datos,                  // Asigna el valor al campo de tipo string
                                           nombres_variables[j][0], // nombre del campo
                                           nom_parametro_dato[1]);  // valor del campo de tipo string
                    }
                    else if (strcmp(nombres_variables[j][1], "int") == 0) // Si el tipo del campo es int
                    {
                        asignarValorInt(&datos,                       // Asigna el valor al campo de tipo int
                                        nombres_variables[j][0],      // nombre del campo
                                        atoi(nom_parametro_dato[1])); // valor del campo de tipo int
                    }
                    else if (strcmp(nombres_variables[j][1], "float") == 0) // Si el tipo del campo es float
                    {
                        asignarValorFloat(&datos,                              // Asigna el valor al campo de tipo float
                                          nombres_variables[j][0],             // nombre del campo
                                          (float)atof(nom_parametro_dato[1])); // valor del campo de tipo float
                    }
                    break;
                }
                j++;
            }
        }

        if (nom_parametro_dato) // Si la división del texto en nombre de parámetro y valor fue exitosa, libera la memoria del arreglo resultante para evitar fugas
        {
            modelo_free_split(nom_parametro_dato); // Libera la memoria del arreglo resultante de la división del texto en nombre de parámetro y valor
        }

        i++;
    }

    return datos;
}
