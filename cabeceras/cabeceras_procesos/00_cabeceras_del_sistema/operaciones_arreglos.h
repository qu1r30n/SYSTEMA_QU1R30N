#ifndef PROCESOS_OPERACIONES_ARREGLOS_H
#define PROCESOS_OPERACIONES_ARREGLOS_H

#include "estructuras_dinamicas.h"

/*
 * Utilidades generales para leer datos desde StructurasDinamicas
 * por posicion (orden) sin duplicar codigo en cada modulo de negocio.
 */
int arreglo_obtener_entero_por_orden(StructurasDinamicas *datos, int orden, int *salida);
int arreglo_obtener_flotante_por_orden(StructurasDinamicas *datos, int orden, float *salida);
int arreglo_obtener_cadena_por_orden(StructurasDinamicas *datos, int orden, char **salida);

#endif
