#ifndef PROCESOS_OPERACIONES_ARREGLOS_H
#define PROCESOS_OPERACIONES_ARREGLOS_H

/*
 * Uso: Agrega un texto a un arreglo dinamico de punteros char*.
 * No retorna el arreglo porque se modifica por referencia.
 * Entrada ejemplo: agregar_texto_a_arreglo(&mi_arreglo, "hola")
 */
void agregar_texto_a_arreglo(char ***arreglo, const char *texto);

#endif
