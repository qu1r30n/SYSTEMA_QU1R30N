#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"

#ifdef _WIN32
    #include <windows.h>
    #include <time.h>

#elif defined(__linux__)
    #include <time.h>

#elif defined(__XC)
    #define _XTAL_FREQ 4000000
    #include <xc.h>
#endif


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
    while(ms--) {
        __delay_ms(1);
    }
#endif
}


/* =========================
   FECHA ACTUAL PORTABLE
========================= */

void fechaActual(char* buffer, const char* formato) {

#if defined(_WIN32) || defined(__linux__)

    time_t t = time(NULL);
    strftime(buffer, 20, formato, localtime(&t));

#elif defined(__XC)

    /* PIC16F no tiene reloj real.
       Aquí ponemos un placeholder.
       Luego puedes reemplazarlo con un RTC real. */

    const char* fakeDate = "01/01/2000 00:00";
    
    while(*fakeDate) {
        *buffer++ = *fakeDate++;
    }
    *buffer = '\0';

#endif
}