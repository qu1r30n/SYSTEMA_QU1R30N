#ifndef OPERACIONES_RENTA_EQUIPOS_H
#define OPERACIONES_RENTA_EQUIPOS_H

int renta_registrar_equipo(const char *codigo, const char *nombre, float costo_por_dia, int stock);
int renta_registrar_alquiler(const char *cliente, const char *codigo, int dias, int cantidad);
int renta_consultar_equipo(const char *codigo, float *costo_por_dia, int *stock);

#endif
