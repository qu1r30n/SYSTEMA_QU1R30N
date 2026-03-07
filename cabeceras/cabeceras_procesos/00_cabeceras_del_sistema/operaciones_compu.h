#ifndef OPERACIONES_COMPU_H
#define OPERACIONES_COMPU_H

/*
 * Bandera global de logs de depuracion.
 * 0 = desactivado (default), 1 = activado.
 *
 * Para activarlo en build:
 *   gcc ... -DSISTEMA_DEBUG_LOGS=1
 */
#ifndef SISTEMA_DEBUG_LOGS
#define SISTEMA_DEBUG_LOGS 0
#endif

void delay_ms(unsigned int ms);

void fechaActual(char *b, const char *f);

void imprimirMensaje_para_depurar(const char *format, ...);

#if SISTEMA_DEBUG_LOGS
#define REGISTRO_DEPURACION(...) imprimirMensaje_para_depurar(__VA_ARGS__)
#else
#define REGISTRO_DEPURACION(...) ((void)0)
#endif

/* Alias legacy para no romper codigo existente. */
#define DEBUG_LOG(...) REGISTRO_DEPURACION(__VA_ARGS__)

#endif
