#ifndef OPERACIONES_FERIA_H
#define OPERACIONES_FERIA_H

int feria_registrar_premio(const char *codigo, const char *nombre, int puntos, int stock);
int feria_canjear_premio(const char *usuario, const char *codigo, int cantidad);

#endif
