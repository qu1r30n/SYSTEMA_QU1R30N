#include <stdlib.h>
#include <string.h>
#include "../../cabeceras/operaciones_textos.h"

int split(const char* txt, const char* sep, char*** out) {
    char* c = strdup(txt);
    char* tok;
    int count = 0;
    char** result = malloc(sizeof(char*) * 64);

    tok = strtok(c, sep);
    while (tok) {
        result[count++] = strdup(tok);
        tok = strtok(NULL, sep);
    }
    *out = result;
    free(c);
    return count;
}

void free_split(char** a, int n) {
    for(int i=0; i<n; i++) free(a[i]);
    free(a);
}
