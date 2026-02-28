#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_compu.h"
#include "../../cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"    /* necesitamos la firma de modelo_split */
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"


void modelo_fechaActual(char* texto) 
{
    /* Antes se hacía modelo_split(texto,"|") pero el valor devuelto no
       se utilizaba; quitar la llamada o almacenarla si hace falta.
       El propósito de esta función es simplemente delegar en el proceso. */
    fechaActual(texto, "%Y-%m-%d %H:%M:%S");
}

void modelo_delay_ms(char* texto) 
{
    unsigned int ms = modelo_texto_a_int_seguro(texto);
    delay_ms(ms);
}


