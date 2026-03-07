#ifndef OPERACIONES_RESTAURANTE_H
#define OPERACIONES_RESTAURANTE_H

int restaurante_registrar_platillo(const char *codigo, const char *nombre, float precio, int stock);
int restaurante_registrar_pedido(const char *mesa, const char *codigo, int cantidad);

#endif
