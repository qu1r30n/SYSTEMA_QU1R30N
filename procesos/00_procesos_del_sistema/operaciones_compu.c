#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>
#include <time.h>

#elif defined(__linux__)
#include <time.h>

#elif defined(__XC)
#define _XTAL_FREQ 4000000
#include <xc.h>
#endif

void imprimirMensaje_para_depurar(const char *format, ...)
{
    // ---------------------------
    // Los "..." significan que la función puede recibir
    // un número indefinido de argumentos adicionales,
    // igual que printf.
    // Por ejemplo:
    // imprimirMensaje_para_depurar("Valor=%d, puntero=%p\n", 42, ptr);
    // El 42 y ptr son los "argumentos variables"
    // ---------------------------

    va_list args;           // Crea una lista que va a contener todos los argumentos variables
    va_start(args, format); // Inicializa la lista de argumentos variables a partir del último parámetro fijo (format)

#ifdef PIC16F
    char buffer[80];
    vsnprintf(buffer, sizeof(buffer), format, args);
    printf("%s", buffer);
#else
    vprintf(format, args); // vprintf es igual que printf, pero toma la lista de argumentos variables // Esto permite imprimir todo lo que se pasó en los "..."
#endif

    va_end(args); // Libera la lista de argumentos variables. Siempre debe llamarse al final// para limpiar cualquier recurso interno usado por la lista.
}

/* =========================
   DELAY PORTABLE
========================= */

void delay_ms(unsigned int ms)
{

#ifdef _WIN32
    Sleep(ms);

#elif defined(__linux__)
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);

#elif defined(__XC)
    while (ms--)
    {
        __delay_ms(1);
    }
#endif
}

/* =========================
   FECHA ACTUAL PORTABLE
========================= */

void fechaActual(char *buffer, const char *formato)
{

#if defined(_WIN32) || defined(__linux__)

    time_t t = time(NULL);
    strftime(buffer, 20, formato, localtime(&t));

#elif defined(__XC)

    /* PIC16F no tiene reloj real.
       Aquí ponemos un placeholder.
       Luego puedes reemplazarlo con un RTC real. */

    const char *fakeDate = "01/01/2000 00:00";

    while (*fakeDate)
    {
        *buffer++ = *fakeDate++;
    }
    *buffer = '\0';

#endif
}