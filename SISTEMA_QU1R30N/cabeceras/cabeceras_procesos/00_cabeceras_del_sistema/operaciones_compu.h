#ifndef OPERACIONES_COMPU_H
#define OPERACIONES_COMPU_H

/*
 * Uso: Ejecuta delay_ms de forma segura.
 * Entrada ejemplo: delay_ms(ms)
 */
void delay_ms(unsigned int ms);

/*
 * Uso: Ejecuta fechaActual de forma segura.
 * Entrada ejemplo: fechaActual(b, f)
 */
void fechaActual(char *b, const char *f);

/*
 * Uso: Ejecuta imprimirMensaje_para_depurar de forma segura.
 * Entrada ejemplo: imprimirMensaje_para_depurar(format, arg2)
 */
void imprimirMensaje_para_depurar(const char *format, ...);

/*
 * Uso: Ejecuta imprimirMensaje_para_depurar_arreglo de forma segura.
 * Entrada ejemplo: imprimirMensaje_para_depurar_arreglo(arreglo, "celda", total)
 * Si total > 0, la función imprimirá exactamente total celdas.
 * Si total <= 0, la función buscará la celda NULL que termina el arreglo.
 * El texto se usa como prefijo antes del índice: <texto>[i]: valor.
 */
void imprimirMensaje_para_depurar_arreglo(char **contenido, const char *texto, int total);

#endif
