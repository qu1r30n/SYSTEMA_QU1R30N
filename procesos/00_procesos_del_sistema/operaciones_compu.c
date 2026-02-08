#include <time.h>
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

void fechaActual(char* b, const char* f) {
    time_t t = time(NULL);
    strftime(b, 20, f, localtime(&t));
}
