#ifndef CONTROLADOR_MONITOREO_ARCHIVO_H
#define CONTROLADOR_MONITOREO_ARCHIVO_H

/*
 * Uso: Ejecuta monitoreo_archivo_entrada de forma segura.
 * Entrada ejemplo: monitoreo_archivo_entrada(retorno_comando, retorno_numero_lineas)
 */
int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas);
/*
 * Uso: Ejecuta respuesta de forma segura.
 * Entrada ejemplo: respuesta(info, programa_enviar, info_espejo)
 */
void respuesta(const char *info, const char *programa_enviar, const char *info_espejo);
/*
 * Uso: Ejecuta datos_recibidos_a_procesar_y_borrar de forma segura.
 * Entrada ejemplo: datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas)
 */
int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas);
/*
 * Uso: Ejecuta finalizar_comando_procesado de forma segura.
 * Entrada ejemplo: finalizar_comando_procesado(linea_original, estado_ejecucion)
 */
int finalizar_comando_procesado(const char *linea_original, int estado_ejecucion);
/*
 * Uso: Ejecuta cambiar_id_programa_al_siguiente de forma segura.
 * Entrada ejemplo: cambiar_id_programa_al_siguiente(usuarios, total_usuarios)
 */
int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios);
/*
 * Uso: Ejecuta quitar_id_prog_del_archivo de forma segura.
 * Entrada ejemplo: quitar_id_prog_del_archivo()
 */
int quitar_id_prog_del_archivo(void);
/*
 * Uso: Ejecuta checar_numero_de_direccion_de_archivo_atras_actual_adelante de forma segura.
 * Entrada ejemplo: checar_numero_de_direccion_de_archivo_atras_actual_adelante(posicion_bandera, numero_actual_posicion, arr_devolver)
 */
int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera, int numero_actual_posicion, int arr_devolver[3]);

#endif
