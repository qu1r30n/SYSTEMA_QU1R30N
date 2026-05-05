/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - stdlib.h: Memoria dinamica, conversiones y utilidades generales
 * - ../../CLASE_QU1R30N.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_gestor_de_permisos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/gestor_de_permisos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h: Dependencia interna del proyecto
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_gestor_de_permisos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/gestor_de_permisos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/estructuras_dinamicas.h"

/* ===== MODELO DE PROCESOS DEL SISTEMA: GESTOR DE PERMISOS ===== */

// Checar permiso
/*
 * Uso: Ejecuta modelo_checar_permiso de forma segura.
 * Entrada ejemplo: modelo_checar_permiso(texto, retorna_direccion_espacio_negocio, retornar_nivel)
 */
int modelo_checar_permiso(char *texto, char **retorna_direccion_espacio_negocio, int *retornar_nivel)
// Función que recibe un texto con parámetros, los procesa y verifica permisos
{
    // Inicializa el puntero de salida a NULL si existe
    if (retorna_direccion_espacio_negocio)
    {
        *retorna_direccion_espacio_negocio = NULL;
    }

    // Inicializa el nivel de salida en -1 si existe
    if (retornar_nivel)
    {
        *retornar_nivel = -1;
    }

    // Validación: si no hay texto, no se puede procesar
    if (!texto)
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    // Definición de los parámetros esperados:
    // nombre, tipo, valor por defecto, (campo extra vacío)
    char *nombres_variables[][4] =
        {
            {"nivel_minimo", "int", "0", ""},
            {"ruta_archivo", "string", "nose", ""},
            {"id_de_espacio", "string", "nose", ""},
            {"usuario_de_espacio", "string", "nose", ""},
            {"contraseña_de_espacio", "string", "nose", ""},
            {NULL, NULL, NULL, NULL}}; // Marca el final del arreglo

    // Cuenta cuántos parámetros hay definidos
    int cuantos_parametros_hay = 0; // contador de filas en nombres_variables[] hasta encontrar NULL // ejemplo: 3
    while (nombres_variables[cuantos_parametros_hay][0])
    {
        cuantos_parametros_hay++; // avanza al siguiente parametro esperado // ejemplo: 0->1->2->NULL
    }

    // Divide el texto en partes usando un separador global
    char **partes = modelo_split(texto, G_caracter_separacion_funciones_espesificas[1]);

    // Si falla el split → error
    if (!partes)
    {
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    // Imprime las primeras partes para depuración
    imprimirMensaje_para_depurar("%s\n%s\n%s\n%s", partes[0], partes[1], partes[2], partes[3]);

    // Cuenta cuántas partes se generaron
    int cuantas_partes = 0; // contador de partes resultantes del split // ejemplo: 3
    while (partes[cuantas_partes])
    {
        cuantas_partes++; // incrementa contador de partes // ejemplo: 0->1->2
    }

    // Crea una estructura dinámica donde se guardarán los valores parseados
    StructurasDinamicas datos = crearStructuraVacia(); // crea estructura dinamica vacia para guardar los valores parseados // ejemplo: datos con 0 campos

    // Procesa las partes del texto:
    // interpreta "parametro=valor" y llena la estructura
    int ret_parse = procesar_partes_del_texto(
        partes,
        nombres_variables,
        G_caracter_separacion_nom_parametro_de_valor[0],
        &datos);

    // Si falla el parseo o no hay partes → error
    if (ret_parse < 0 || cuantas_partes <= 0) // aborta si el parseo fallo o no hay partes para procesar // ejemplo: ret_parse=-1 -> retorna
    {
        modelo_free_split(partes); // Libera memoria del split
        liberarStructura(&datos);  // Libera estructura dinámica
        RETORNAR_MODELO_ESTANDAR(-1);
    }

    // Obtiene los valores en orden desde la estructura
    int nivel_minimo = *(int *)obtenerValorPorOrden(&datos, 0);
    char *ruta_archivo = (char *)obtenerValorPorOrden(&datos, 1);
    char *id_de_espacio = (char *)obtenerValorPorOrden(&datos, 2);
    char *usuario = (char *)obtenerValorPorOrden(&datos, 3);
    char *contrasena = (char *)obtenerValorPorOrden(&datos, 4);

    // Mensaje de depuración con los valores obtenidos
    imprimirMensaje_para_depurar("%s\n%s\n%s\n%s\n%d",
                                 ruta_archivo, id_de_espacio, usuario, contrasena, nivel_minimo);

    // Llama a la función que realmente valida permisos
    int tiene_permiso = checar_permiso(
        nivel_minimo,
        ruta_archivo,
        id_de_espacio,
        usuario,
        contrasena,
        retorna_direccion_espacio_negocio,
        retornar_nivel);

    // Libera memoria usada
    modelo_free_split(partes); // libera la memoria del arreglo generado por modelo_split // ejemplo: libera partes[0..n]
    liberarStructura(&datos); // libera la memoria interna de la estructura dinamica // ejemplo: libera arreglo_char, nombres, etc.

    // Devuelve el resultado de la validación (1, 0 o -1)
    RETORNAR_MODELO_ESTANDAR(tiene_permiso);
}