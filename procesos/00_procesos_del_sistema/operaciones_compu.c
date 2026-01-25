#include <time.h>
#include "../../cabeceras/operaciones_compu.h"

void fechaActual(char* b, const char* f) {
    time_t t = time(NULL);
    strftime(b, 20, f, localtime(&t));
}
