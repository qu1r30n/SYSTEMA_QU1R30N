#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"


void modelo_fechaActual(char* texto) 
{
	modelo_split(texto,"|");
    fechaActual(texto, "%Y-%m-%d %H:%M:%S");
}


void modelo_delay_ms(char* texto) 
{
	
	unsigned int ms=modelo_texto_a_int_seguro(texto);
	delay_ms(ms);
}


