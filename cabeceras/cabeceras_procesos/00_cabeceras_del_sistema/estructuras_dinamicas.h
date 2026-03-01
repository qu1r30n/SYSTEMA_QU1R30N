#ifndef ESTRUCTURAS_DINAMICAS_H
#define ESTRUCTURAS_DINAMICAS_H
/* Macros para tipos */
#define TIPO_STRING 0
#define TIPO_INT 1
#define TIPO_FLOAT 2
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
StructurasDinamicas crearStructuraVacia(void);

/* Agregar un campo a la estructura (tipo: "string", "int" o "float") */
void agregarCampo(StructurasDinamicas *s, const char *nombre, const char *tipo);

/* Imprimir todos los campos y sus valores */
void imprimirStructura(StructurasDinamicas *s);

/* Asignar valor a un campo string */
void asignarValorString(StructurasDinamicas *s, const char *nombre, const char *valor);

/* Asignar valor a un campo int */
void asignarValorInt(StructurasDinamicas *s, const char *nombre, int valor);

/* Asignar valor a un campo float */
void asignarValorFloat(StructurasDinamicas *s, const char *nombre, float valor);

/* Liberar toda la memoria de la estructura */
void liberarStructura(StructurasDinamicas *s);

/* Cargar estructura desde arreglo bidimensional */
StructurasDinamicas cargarDesdeArreglo(char *nombres_variables[][4]);

/* Obtener valor de estructura por orden de inserción */
void *obtenerValorPorOrden(StructurasDinamicas *datos, int orden);

#endif
