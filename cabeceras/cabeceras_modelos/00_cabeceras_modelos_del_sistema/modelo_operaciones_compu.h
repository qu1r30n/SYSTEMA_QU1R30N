#ifndef MODELO_OPERACIONES_COMPU_H
#define MODELO_OPERACIONES_COMPU_H

/* Alias del modulo (portabilidad al mover esta clase a otro proyecto). */
extern char *GG_caracter_separacion_nom_parametro_de_valor[];
#ifndef G_caracter_separacion_nom_parametro_de_valor
#define G_caracter_separacion_nom_parametro_de_valor GG_caracter_separacion_nom_parametro_de_valor
#endif

void modelo_fechaActual(char *texto);
void modelo_delay_ms(char *texto);

#endif