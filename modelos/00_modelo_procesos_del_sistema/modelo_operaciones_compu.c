#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"


void modelo_fechaActual(char* texto) 
{
	
	modelo_split(texto,"|");
    fechaActual(texto, "%Y-%m-%d %H:%M:%S");
}