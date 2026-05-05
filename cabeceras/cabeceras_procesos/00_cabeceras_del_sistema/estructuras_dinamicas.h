#ifndef ESTRUCTURAS_DINAMICAS_H
#define ESTRUCTURAS_DINAMICAS_H
/* Macros para tipos */
#define TIPO_STRING 0 /* string */
#define TIPO_INT 1    /* int */
#define TIPO_FLOAT 2  /* float */
typedef struct
{
    char **arreglo_char;
    int *arreglo_int;
    float *arreglo_float;

    int *orden_tipo;   // 0=string,1=int,2=float
    int *orden_indice; // índice dentro de su arreglo
    char **nombres;    // nombre del campo

    int total; // total de campos
    int count_string;
    int count_int;
    int count_float;

} StructurasDinamicas;

/* Crear una estructura vacía */
/*
 * Uso: Ejecuta crearStructuraVacia de forma segura.
 * Entrada ejemplo: crearStructuraVacia()
 */
StructurasDinamicas crearStructuraVacia(void);

/* Agregar un campo a la estructura (tipo: "string", "int" o "float") */
/*
 * Uso: Ejecuta agregarCampo de forma segura.
 * Entrada ejemplo: agregarCampo(s, nombre, tipo)
 */
void agregarCampo(StructurasDinamicas *s, const char *nombre, const char *tipo);

/* Imprimir todos los campos y sus valores */
/*
 * Uso: Ejecuta imprimirStructura de forma segura.
 * Entrada ejemplo: imprimirStructura(s)
 */
void imprimirStructura(StructurasDinamicas *s);

/* Asignar valor a un campo string */
/*
 * Uso: Ejecuta asignarValorString de forma segura.
 * Entrada ejemplo: asignarValorString(s, nombre, valor)
 */
void asignarValorString(StructurasDinamicas *s, const char *nombre, const char *valor);

/* Asignar valor a un campo int */
/*
 * Uso: Ejecuta asignarValorInt de forma segura.
 * Entrada ejemplo: asignarValorInt(s, nombre, valor)
 */
void asignarValorInt(StructurasDinamicas *s, const char *nombre, int valor);

/* Asignar valor a un campo float */
/*
 * Uso: Ejecuta asignarValorFloat de forma segura.
 * Entrada ejemplo: asignarValorFloat(s, nombre, valor)
 */
void asignarValorFloat(StructurasDinamicas *s, const char *nombre, float valor);

/* Liberar toda la memoria de la estructura */
/*
 * Uso: Ejecuta liberarStructura de forma segura.
 * Entrada ejemplo: liberarStructura(s)
 */
void liberarStructura(StructurasDinamicas *s);

/* Cargar estructura desde arreglo bidimensional */
/*
 * Uso: Ejecuta cargarDesdeArreglo de forma segura.
 * Entrada ejemplo: cargarDesdeArreglo(nombres_variables)
 */
StructurasDinamicas cargarDesdeArreglo(char *nombres_variables[][4]);

/* Obtener valor de estructura por orden de inserción */
/*
 * Uso: Ejecuta obtenerValorPorOrden de forma segura.
 * Entrada ejemplo: obtenerValorPorOrden(datos, orden)
 */
void *obtenerValorPorOrden(StructurasDinamicas *datos, int orden);

/* Procesar partes de texto y cargar en estructura. Retorna 0 si todo salio bien, <0 si hubo error. */
/*
 * Uso: Ejecuta procesar_partes_del_texto de forma segura.
 * Entrada ejemplo: procesar_partes_del_texto(partes, nombres_variables, separador, a_retornar)
 */
int procesar_partes_del_texto(char **partes, char *nombres_variables[][4], const char *separador, StructurasDinamicas *a_retornar);

#endif
