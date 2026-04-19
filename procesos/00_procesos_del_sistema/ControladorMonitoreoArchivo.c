/*
 * Modulo: ControladorMonitoreoArchivo
 * Lee la ruta definida en GG_archivos y detecta si existe una linea extra.
 *
 * NOTA: Este módulo SOLO compila en Windows y Linux.
 *       En PIC no hay sistema de archivos disponible.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/ControladorMonitoreoArchivo.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

#if defined(_WIN32) || defined(__linux__)
/* ============================================================
   COMPILACIÓN PARA WINDOWS Y LINUX
   ============================================================ */

static int construir_ruta_transferencia(int indice_archivo, char **ruta_out)
{
    if (ruta_out == NULL)
    {
        return -1;
    }

    *ruta_out = NULL;

    if (indice_archivo < 0 ||
        GG_archivos[indice_archivo][0] == NULL ||
        GG_archivos[indice_archivo][2] == NULL)
    {
        return -1;
    }

    if (concatenar_formato_separado_por_variable(ruta_out, NULL, "%s%s",
                                                 GG_archivos[indice_archivo][0],
                                                 GG_archivos[indice_archivo][2]) < 0)
    {
        free(*ruta_out);
        *ruta_out = NULL;
        return -1;
    }

    return 0;
}

void respuesta(const char *folio_o_palabra_clave_a_del_que_lo_recibira,
               const char *info,
               const char *programa_enviar)
{
    const char *programa = programa_enviar;
    char *ruta = NULL;
    char *info_a_enviar = NULL;

    if (programa == NULL || programa[0] == '\0')
    {
        programa = "NEXOPORTALARCANO";
    }

    if (folio_o_palabra_clave_a_del_que_lo_recibira == NULL ||
        folio_o_palabra_clave_a_del_que_lo_recibira[0] == '\0' ||
        info == NULL || info[0] == '\0')
    {
        return;
    }

    if (construir_ruta_transferencia(2, &ruta) < 0)
    {
        return;
    }

    if (concatenar_formato_separado_por_variable(
            &info_a_enviar,
            NULL,
            "%s%s%s%s%s%s%s",
            programa,
            GG_caracter_para_transferencia_entre_archivos[0],
            GG_id_programa,
            GG_caracter_para_transferencia_entre_archivos[1],
            folio_o_palabra_clave_a_del_que_lo_recibira,
            GG_caracter_para_transferencia_entre_archivos[1],
            info) < 0)
    {
        free(info_a_enviar);
        free(ruta);
        return;
    }

    agregar_fila(ruta, info_a_enviar);
    free(info_a_enviar);
    free(ruta);
}

int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    const char *directorio = GG_archivos[1][0];
    const char *archivo = GG_archivos[1][2];
    char *ruta = NULL;
    char **lineas_archivo = NULL;
    int total_lineas_archivo = 0;
    int cantidad_comandos = 0;

    if (retorno_comando == NULL || retorno_numero_lineas == NULL)
    {
        return -1;
    }

    *retorno_comando = NULL;
    *retorno_numero_lineas = 0;

    if (directorio == NULL || archivo == NULL)
    {
        return -1;
    }

    if (concatenar_formato_separado_por_variable(&ruta, NULL, "%s%s", directorio, archivo) < 0)
    {
        free(ruta);
        return -1;
    }

    lineas_archivo = leer_archivo(ruta, &total_lineas_archivo);
    free(ruta);
    if (lineas_archivo == NULL)
    {
        return -1;
    }

    if (total_lineas_archivo <= GG_indice_donde_comensar)
    {
        free_lineas(lineas_archivo, total_lineas_archivo);
        return 0;
    }

    for (int i = GG_indice_donde_comensar; i < total_lineas_archivo; i++)
    {
        imprimirMensaje_para_depurar("Leyendo linea %d: %s", i, lineas_archivo[i] ? lineas_archivo[i] : "(vacia)");
        char **partes_transferencia = NULL;
        int n_partes_transferencia = 0;

        if (lineas_archivo[i] == NULL || lineas_archivo[i][0] == '\0')
        {
            continue;
        }

        n_partes_transferencia = split(lineas_archivo[i], GG_caracter_para_transferencia_entre_archivos[0], &partes_transferencia);
        if (n_partes_transferencia >= 2 &&
            partes_transferencia != NULL &&
            partes_transferencia[0] != NULL &&
            partes_transferencia[1] != NULL &&
            strcmp(partes_transferencia[0], GG_id_programa) == 0)
        {
            char **partes_comando = NULL;
            int n_partes_comando = split(partes_transferencia[1], GG_caracter_para_transferencia_entre_archivos[1], &partes_comando);
            char *comando_final = NULL;

            if (n_partes_comando >= 3 && partes_comando != NULL && partes_comando[1] != NULL && partes_comando[2] != NULL)
            {
                if (concatenar_formato_separado_por_variable(&comando_final, NULL, "%s%s%s",
                                                             partes_comando[1],
                                                             GG_caracter_para_transferencia_entre_archivos[1],
                                                             partes_comando[2]) < 0)
                {
                    free_split(partes_comando);
                    free_split(partes_transferencia);
                    for (int j = 0; j < cantidad_comandos; j++)
                    {
                        free((*retorno_comando)[j]);
                    }
                    free(*retorno_comando);
                    *retorno_comando = NULL;
                    *retorno_numero_lineas = 0;
                    free_lineas(lineas_archivo, total_lineas_archivo);
                    return -1;
                }
            }
            else
            {
                comando_final = (char *)malloc(strlen(partes_transferencia[1]) + 1);
                if (comando_final == NULL)
                {
                    free_split(partes_comando);
                    free_split(partes_transferencia);
                    for (int j = 0; j < cantidad_comandos; j++)
                    {
                        free((*retorno_comando)[j]);
                    }
                    free(*retorno_comando);
                    *retorno_comando = NULL;
                    *retorno_numero_lineas = 0;
                    free_lineas(lineas_archivo, total_lineas_archivo);
                    return -1;
                }

                strcpy(comando_final, partes_transferencia[1]);
            }

            free_split(partes_comando);

            char **tmp = (char **)realloc(*retorno_comando, sizeof(char *) * (cantidad_comandos + 1));
            if (tmp == NULL)
            {
                free(comando_final);
                free_split(partes_transferencia);
                for (int j = 0; j < cantidad_comandos; j++)
                {
                    free((*retorno_comando)[j]);
                }
                free(*retorno_comando);
                *retorno_comando = NULL;
                *retorno_numero_lineas = 0;
                free_lineas(lineas_archivo, total_lineas_archivo);
                return -1;
            }

            *retorno_comando = tmp;
            (*retorno_comando)[cantidad_comandos] = comando_final;
            cantidad_comandos++;
        }

        free_split(partes_transferencia);
    }

    free_lineas(lineas_archivo, total_lineas_archivo);

    if (cantidad_comandos == 0)
    {
        return 0;
    }

    *retorno_numero_lineas = cantidad_comandos;
    return 1;
}

int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    char **comandos = NULL;
    int total_comandos = 0;
    int estado = 0;

    if (retorno_comando == NULL || retorno_numero_lineas == NULL)
    {
        return -1;
    }

    *retorno_comando = NULL;
    *retorno_numero_lineas = 0;

    estado = monitoreo_archivo_entrada(&comandos, &total_comandos);

    if (estado <= 0)
    {
        return estado;
    }

    char *ruta_entrada = NULL;
    if (construir_ruta_transferencia(1, &ruta_entrada) == 0)
    {
        eliminar_fila_para_multiples_programas_solo_prog(ruta_entrada, "0", GG_id_programa);
    }

    free(ruta_entrada);

    *retorno_comando = comandos;
    *retorno_numero_lineas = total_comandos;
    return 1;
}

int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    if (usuarios == NULL || total_usuarios <= GG_indice_donde_comensar)
    {
        return 0;
    }

    if (usuarios[0] == NULL || strcmp(usuarios[0], GG_id_programa) != 0)
    {
        return 0;
    }

    int id_nuevo = GG_indice_donde_comensar;
    for (int i = GG_indice_donde_comensar; i < total_usuarios; i++)
    {
        if (usuarios[i] != NULL && strcmp(usuarios[i], GG_id_programa) == 0)
        {
            if (i >= total_usuarios - 1)
            {
                id_nuevo = GG_indice_donde_comensar;
            }
            else
            {
                id_nuevo = i + 1;
            }
            break;
        }
    }

    if (usuarios[id_nuevo] == NULL || usuarios[id_nuevo][0] == '\0')
    {
        return 0;
    }

    char *ruta_entrada = NULL;
    if (construir_ruta_transferencia(1, &ruta_entrada) < 0)
    {
        return -1;
    }

    int resultado = editar_fila_espesifica_sin_arreglo_gg(ruta_entrada, "0", 0, usuarios[id_nuevo]);
    free(ruta_entrada);
    return resultado ? 1 : 0;
}

int quitar_id_prog_del_archivo(void)
{
    char *ruta_entrada = NULL;
    if (construir_ruta_transferencia(1, &ruta_entrada) < 0)
    {
        return -1;
    }

    eliminar_fila_para_multiples_programas_solo_prog(ruta_entrada, "0", GG_id_programa);
    free(ruta_entrada);
    return 1;
}

int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera,
                                                                int numero_actual_posicion,
                                                                int arr_devolver[3])
{
    if (arr_devolver == NULL)
    {
        return -1;
    }

    const int total_direcciones = 3;
    int numero_adelante_posicion = numero_actual_posicion + total_direcciones;
    int numero_atras_posicion = numero_actual_posicion - total_direcciones;

    if (numero_adelante_posicion >= total_direcciones)
    {
        numero_adelante_posicion = posicion_bandera;
    }

    if (numero_atras_posicion < 0)
    {
        numero_atras_posicion = (total_direcciones - 1) + posicion_bandera;
    }

    arr_devolver[0] = numero_atras_posicion;
    arr_devolver[1] = numero_actual_posicion;
    arr_devolver[2] = numero_adelante_posicion;
    return 0;
}

#elif defined(__XC)
/* ============================================================
   COMPILACIÓN PARA PIC16/18 CON COMUNICACIÓN USB

   NOTA: En PIC usamos comunicación USB en lugar de sistema
   de archivos. Las funciones USB se implementarán en futuro.
   ============================================================ */

/* ============================================================
   FUNCIONES USB STUB - A IMPLEMENTAR EN FUTURO
   ============================================================

   Estas funciones serán implementadas cuando se agregue
   soporte para comunicación USB en PIC.
*/

/* Lee comandos desde USB/puerto serie.
   Retorna: 1=hay comandos, 0=sin comandos, -1=error
   A IMPLEMENTAR: usb_leer_comandos() */
static int usb_monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* TODO: Implementar lectura desde USB/UART
       - Leer buffer de USB
       - Parsear comandos
       - Llenar retorno_comando
       - Retornar cantidad de comandos
    */
    if (retorno_comando)
        *retorno_comando = NULL;
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0;
    return 0; /* Sin comandos (implementar en futuro) */
}

/* Envía respuesta por USB/puerto serie.
   A IMPLEMENTAR: usb_enviar_respuesta() */
static void usb_respuesta(const char *folio, const char *info, const char *programa)
{
    /* TODO: Implementar envío por USB/UART
       - Construir payload: programa | ID | folio | info
       - Enviar por USB/puerto serie
       - Manejar timeouts y errores
    */
    (void)folio;
    (void)info;
    (void)programa;
}

/* Procesa y limpia comandos recibidos por USB.
   A IMPLEMENTAR: usb_limpiar_comandos() */
static int usb_datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* TODO: Implementar limpieza de buffer USB
       - Leer comandos del buffer USB
       - Limpiar después de procesar
       - Retornar estado
    */
    if (retorno_comando)
        *retorno_comando = NULL;
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0;
    return 0;
}

/* Cambia ID del programa en buffer USB.
   A IMPLEMENTAR: usb_cambiar_id_programa() */
static int usb_cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* TODO: Implementar rotación de ID en buffer USB */
    (void)usuarios;
    (void)total_usuarios;
    return 0;
}

/* Elimina ID del programa desde buffer USB.
   A IMPLEMENTAR: usb_quitar_id_programa() */
static int usb_quitar_id_prog_del_archivo(void)
{
    /* TODO: Implementar eliminación de ID en buffer USB */
    return 0;
}

/* ============================================================
   FUNCIONES PÚBLICAS - Delegan a USB
   ============================================================ */

int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* En PIC, leer desde USB en lugar de archivo */
    return usb_monitoreo_archivo_entrada(retorno_comando, retorno_numero_lineas);
}

void respuesta(const char *folio_o_palabra_clave_a_del_que_lo_recibira,
               const char *info,
               const char *programa_enviar)
{
    /* En PIC, enviar por USB en lugar de archivo */
    usb_respuesta(folio_o_palabra_clave_a_del_que_lo_recibira, info, programa_enviar);
}

int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* En PIC, procesar desde USB en lugar de archivo */
    return usb_datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas);
}

int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* En PIC, cambiar ID en buffer USB */
    return usb_cambiar_id_programa_al_siguiente(usuarios, total_usuarios);
}

int quitar_id_prog_del_archivo(void)
{
    /* En PIC, quitar ID de buffer USB */
    return usb_quitar_id_prog_del_archivo();
}

int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera,
                                                                int numero_actual_posicion,
                                                                int arr_devolver[3])
{
    if (arr_devolver == NULL)
        return -1;
    arr_devolver[0] = 0;
    arr_devolver[1] = numero_actual_posicion;
    arr_devolver[2] = 0;
    return 0;
}

#else
/* ============================================================
   COMPILACIÓN POR DEFECTO (stubs básicos)
   ============================================================ */

int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    if (retorno_comando)
        *retorno_comando = NULL;
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0;
    return 0;
}

void respuesta(const char *folio_o_palabra_clave_a_del_que_lo_recibira,
               const char *info,
               const char *programa_enviar)
{
    (void)folio_o_palabra_clave_a_del_que_lo_recibira;
    (void)info;
    (void)programa_enviar;
}

int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    if (retorno_comando)
        *retorno_comando = NULL;
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0;
    return 0;
}

int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    (void)usuarios;
    (void)total_usuarios;
    return 0;
}

int quitar_id_prog_del_archivo(void)
{
    return 0;
}

int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera,
                                                                int numero_actual_posicion,
                                                                int arr_devolver[3])
{
    if (arr_devolver == NULL)
        return -1;
    arr_devolver[0] = 0;
    arr_devolver[1] = numero_actual_posicion;
    arr_devolver[2] = 0;
    return 0;
}

#endif /* Fin compilación condicional */
