#ifndef OPERACIONES_TEXTOS_H
#define OPERACIONES_TEXTOS_H

int split(const char* txt, const char* sep, char*** out);
void free_split(char** a, int n);

#endif
