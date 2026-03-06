#ifndef CLASE_QU1R30N_H
#define CLASE_QU1R30N_H

// -----------------------------
// Cabeceras de modelos de negocio
// -----------------------------
#include "cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"

// -----------------------------
// Cabeceras de modelos del sistema
// -----------------------------
#include "cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_compu.h"
#include "cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h"
#include "cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_tex_bas.h"
#include "cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_var_fun_GG.h"

// también incluimos algunos encabezados de procesos comunes
#include "cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

// Declaraciones externas de variables globales de procesos
extern char *GG_caracter_separacion[];
extern char *GG_caracter_separacion_2[];
extern char *GG_caracter_separacion_funciones_espesificas[];
extern char *GG_caracter_separacion_funciones_espesificas_2[];
extern char *GG_archivos[][2];
extern char *GG_archivos_registros[][2];

// Puedes agregar nuevas cabeceras de modelos aquí en el futuro

/* aliases globales visibles en todo el proyecto (definidas en un único TU) */
extern char **G_caracter_separacion;
extern char **G_caracter_separacion_funciones_espesificas;
extern char *(*G_archivos)[2];
extern char *(*G_archivos_registros)[2];

#endif // CLASE_QU1R30N_H