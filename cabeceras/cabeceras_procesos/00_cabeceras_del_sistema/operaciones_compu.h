#ifndef OPERACIONES_COMPU_H
#define OPERACIONES_COMPU_H

void delay_ms(unsigned int ms);

void fechaActual(char *b, const char *f);

void imprimirMensaje_para_depurar(const char *format, ...);

/* Retorna un texto formateado en heap. El caller debe liberarlo con free(). */
char *variable_string(const char *format, ...);

#endif
