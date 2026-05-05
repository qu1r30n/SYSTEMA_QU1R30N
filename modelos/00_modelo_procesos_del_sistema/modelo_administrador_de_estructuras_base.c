/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - ../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_administrador_de_estructuras_base.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administrador_de_estructuras_base.h: Dependencia interna del proyecto
 */
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_administrador_de_estructuras_base.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/administrador_de_estructuras_base.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

/*
 * Uso: Ejecuta modelo_creacion_de_estructura_base de forma segura.
 * Entrada ejemplo: modelo_creacion_de_estructura_base(nombre_de_structura, direccion_del_espacio)
 */
int modelo_creacion_de_estructura_base(char *nombre_de_structura, char *direccion_del_espacio)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    RETORNAR_MODELO_ESTANDAR(creacion_de_estructura_base(nombre_de_structura, direccion_del_espacio));
}