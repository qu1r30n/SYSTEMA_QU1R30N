#ifndef CONTROLADOR_MONITOREO_ARCHIVO_H
#define CONTROLADOR_MONITOREO_ARCHIVO_H

int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas);
void respuesta(const char *folio_o_palabra_clave_a_del_que_lo_recibira,
               const char *info,
               const char *programa_enviar);
int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas);
int finalizar_comando_procesado(const char *comando, int estado_ejecucion);
int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios);
int quitar_id_prog_del_archivo(void);
int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera,
                                                                int numero_actual_posicion,
                                                                int arr_devolver[3]);

#endif
