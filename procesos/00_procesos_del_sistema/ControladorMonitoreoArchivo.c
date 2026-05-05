/*
 * Modulo: ControladorMonitoreoArchivo
 * Lee la ruta definida en GG_archivos y detecta si existe una linea extra.
 *
 * NOTA: Este mÃ³dulo SOLO compila en Windows y Linux.
 *       En PIC no hay sistema de archivos disponible.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cabeceras/codigos_retorno.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/ControladorMonitoreoArchivo.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

#if defined(_WIN32) || defined(__linux__)
/* ============================================================
   COMPILACIÃ“N PARA WINDOWS Y LINUX
   ============================================================ */

/*
 * Uso: Ejecuta construir_ruta_transferencia de forma segura.
 * Entrada ejemplo: construir_ruta_transferencia(indice_archivo, ruta_out)
 */
static int construir_ruta_transferencia(int indice_archivo, char **ruta_out)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (ruta_out == NULL) // si el puntero de salida no existe, no se puede guardar la ruta
    {
        return -1; // retorna error: puntero de salida inválido
    }

    *ruta_out = NULL; // inicializa el puntero de salida a NULL por seguridad; ejemplo: *ruta_out = NULL

    if (indice_archivo < 0 ||                     // si el índice es negativo, es inválido
        GG_archivos[indice_archivo][0] == NULL || // si no hay directorio definido para ese índice
        GG_archivos[indice_archivo][2] == NULL)   // si no hay nombre de archivo definido para ese índice
    {
        return -1; // retorna error: datos del archivo no disponibles en GG_archivos
    }

    if (concatenar_formato_separado_por_variable(ruta_out, NULL, "%s%s",
                                                 GG_archivos[indice_archivo][0],
                                                 GG_archivos[indice_archivo][2]) < 0) // construye la ruta completa concatenando directorio + nombre del archivo
    {
        free(*ruta_out);  // libera memoria si concatenar asignó algo antes de fallar
        *ruta_out = NULL; // deja el puntero limpio para no dejar basura
        return -1;        // retorna error: fallo al construir la ruta
    }

    return 0; // retorna éxito: la ruta fue construida y almacenada en *ruta_out
}

/*
 * Uso: Ejecuta duplicar_texto_local de forma segura.
 * Entrada ejemplo: duplicar_texto_local(texto)
 */
static char *duplicar_texto_local(const char *texto)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char *copia = NULL; // puntero donde se guardará la copia del texto; ejemplo: "NEXOPORTALARCANO"

    if (texto == NULL) // si el texto de entrada es NULL, no hay nada que copiar
    {
        return NULL; // retorna NULL indicando que no se puede duplicar
    }

    copia = (char *)malloc(strlen(texto) + 1); // reserva memoria exacta: longitud del texto más el terminador '\0'
    if (copia == NULL)                         // si malloc falló por falta de memoria disponible
    {
        return NULL; // retorna NULL indicando fallo de memoria
    }

    strcpy(copia, texto); // copia el contenido del texto original byte a byte en la nueva memoria
    return copia;         // retorna el puntero a la copia creada
}

/*
 * Uso: Ejecuta extraer_comando_de_linea_transferencia de forma segura.
 * Entrada ejemplo: extraer_comando_de_linea_transferencia(linea_transferencia, comando_out)
 */
static int extraer_comando_de_linea_transferencia(const char *linea_transferencia, char **comando_out)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char **partes_transferencia = NULL; // arreglo con las partes de la línea dividida por el separador de transferencia
    int n_partes_transferencia = 0;     // cantidad de partes encontradas al dividir la línea
    char *comando_final = NULL;         // puntero donde se guardará el comando extraído; ejemplo: "op_tienda~agregar"

    if (comando_out == NULL) // si el puntero de salida es NULL, no se puede devolver el comando
    {
        return RET_INVALID_ARG; // retorna error: argumento inválido
    }

    *comando_out = NULL; // inicializa el puntero de salida a NULL por seguridad

    if (linea_transferencia == NULL || linea_transferencia[0] == '\0') // si la línea es NULL o está vacía, no hay comando que extraer
    {
        return RET_NOT_FOUND; // retorna "no encontrado": línea inválida o vacía
    }

    n_partes_transferencia = split(linea_transferencia, GG_caracter_para_transferencia_entre_archivos[0], &partes_transferencia); // divide la línea usando el separador principal de transferencia
    if (n_partes_transferencia < 3 ||                                                                                             // se esperan al menos 3 partes: destino, comando y espejo
        partes_transferencia == NULL ||                                                                                           // si split falló y no devolvió arreglo
        partes_transferencia[0] == NULL ||                                                                                        // si la parte de destino está vacía
        partes_transferencia[1] == NULL ||                                                                                        // si la parte de comando está vacía
        partes_transferencia[2] == NULL)                                                                                          // si la parte de espejo está vacía
    {
        free_split(partes_transferencia); // libera el arreglo aunque esté incompleto
        return RET_NOT_FOUND;             // retorna "no encontrado": formato de línea incorrecto
    }

    {
        /* Separar "ID_DESTINOâ”´ID_ORIGEN" y verificar que el destino sea este programa */
        char **partes_destino = NULL;                                                                                             // arreglo para separar destino y origen dentro de la primera parte
        int n_partes_destino = split(partes_transferencia[0], GG_caracter_para_transferencia_entre_archivos[1], &partes_destino); // divide "ID_DESTINO┴ID_ORIGEN" por el separador secundario
        int es_para_mi = (n_partes_destino >= 1 && partes_destino != NULL &&                                                      // verifica que el split haya funcionado
                          partes_destino[0] != NULL &&                                                                            // verifica que el destino no sea NULL
                          strcmp(partes_destino[0], GG_id_programa) == 0);                                                        // compara el destino con el ID de este programa
        free_split(partes_destino);                                                                                               // libera las partes de destino, ya no se necesitan
        if (!es_para_mi)                                                                                                          // si el mensaje no es para este programa, ignorarlo
        {
            free_split(partes_transferencia); // libera las partes de la línea completa
            return RET_NOT_FOUND;             // retorna "no encontrado": el mensaje es para otro programa
        }
    }

    comando_final = duplicar_texto_local(partes_transferencia[1]); // duplica el comando (segunda parte) en memoria propia
    if (comando_final == NULL)                                     // si la duplicación falló por memoria insuficiente
    {
        free_split(partes_transferencia); // libera las partes antes de salir con error
        return RET_ERROR_GENERIC;         // retorna error genérico: fallo de memoria
    }

    free_split(partes_transferencia); // libera el arreglo de partes, ya se copió lo necesario
    *comando_out = comando_final;     // entrega el comando extraído al caller
    return RET_OK;                    // retorna éxito: comando extraído correctamente
}

/*
 * Uso: Ejecuta quitar_linea_exacta_del_archivo de forma segura.
 * Entrada ejemplo: quitar_linea_exacta_del_archivo(ruta, linea_a_quitar)
 */
static int quitar_linea_exacta_del_archivo(const char *ruta, const char *linea_a_quitar)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char **lineas = NULL;    // arreglo con todas las líneas leídas del archivo
    char **resultado = NULL; // arreglo con las líneas que se conservarán (sin la eliminada)
    int total_lineas = 0;    // cantidad total de líneas leídas del archivo
    int total_resultado = 0; // cantidad de líneas que se guardarán (resultado final)
    int eliminado = 0;       // bandera: 1 si ya se encontró y eliminó la línea buscada

    if (ruta == NULL || linea_a_quitar == NULL) // si alguno de los parámetros de entrada es NULL
    {
        return RET_INVALID_ARG; // retorna error: argumento inválido
    }

    lineas = leer_archivo(ruta, &total_lineas); // lee todas las líneas del archivo en memoria
    if (lineas == NULL)                         // si no se pudo leer el archivo (no existe o error de lectura)
    {
        return RET_NOT_FOUND; // retorna "no encontrado": archivo inaccesible
    }

    resultado = (char **)malloc(sizeof(char *) * ((total_lineas > 0) ? total_lineas : 1)); // reserva memoria para el arreglo resultado (mínimo 1 para evitar malloc(0))
    if (resultado == NULL)                                                                 // si malloc falló por falta de memoria
    {
        free_lineas(lineas, total_lineas); // libera las líneas antes de salir
        return RET_ERROR_GENERIC;          // retorna error genérico: fallo de memoria
    }

    for (int i = 0; i < total_lineas; i++) // recorre cada línea del archivo
    {
        if (!eliminado && lineas[i] != NULL && strcmp(lineas[i], linea_a_quitar) == 0) // si aún no se eliminó y esta línea coincide exactamente con la buscada
        {
            eliminado = 1; // marca que ya se encontró la línea a eliminar
            continue;      // salta esta línea sin agregarla al resultado
        }

        resultado[total_resultado] = duplicar_texto_local(lineas[i] ? lineas[i] : ""); // copia la línea actual al arreglo resultado
        if (resultado[total_resultado] == NULL)                                        // si la copia falló por memoria
        {
            free_lineas(resultado, total_resultado); // libera el resultado parcial
            free_lineas(lineas, total_lineas);       // libera las líneas originales
            return RET_ERROR_GENERIC;                // retorna error genérico: fallo de memoria
        }
        total_resultado++; // incrementa el contador de líneas en el resultado
    }

    if (!eliminado) // si se recorrieron todas las líneas y nunca se encontró la buscada
    {
        free_lineas(resultado, total_resultado); // libera el resultado (no se usará)
        free_lineas(lineas, total_lineas);       // libera las líneas originales
        return RET_NOT_FOUND;                    // retorna "no encontrado": la línea no existía en el archivo
    }

    guardar_archivo(ruta, resultado, total_resultado); // sobreescribe el archivo con las líneas restantes
    free_lineas(resultado, total_resultado);           // libera el arreglo resultado
    free_lineas(lineas, total_lineas);                 // libera las líneas originales
    return RET_OK;                                     // retorna éxito: la línea fue eliminada y el archivo fue actualizado
}

/*
 * Uso: Ejecuta respuesta de forma segura.
 * Entrada ejemplo: respuesta(info, programa_enviar, info_espejo)
 */
void respuesta(const char *info,
               const char *programa_enviar,
               const char *info_espejo)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    imprimirMensaje_para_depurar("parametros recibidos en respuesta(): \n\nprograma_enviar='%s', \ninfo='%s', \ninfo_espejo='%s'\n", programa_enviar ? programa_enviar : "(null)", info ? info : "(null)", info_espejo ? info_espejo : "(null)");

    const char *programa = programa_enviar; // alias local al nombre del programa destino; ejemplo: "NEXOPORTALARCANO"
    const char *texto_info = info;          // alias local al texto de información a enviar
    const char *texto_espejo = info_espejo; // alias local al texto espejo (copia de confirmación)
    char *ruta = NULL;                      // ruta del archivo de salida donde se escribirá la respuesta
    char *info_a_enviar = NULL;             // cadena completa formateada lista para agregar al archivo

    if (programa == NULL || programa[0] == '\0') // si no se especificó programa destino, usar el predeterminado
    {
        programa = "NEXOPORTALARCANO"; // asigna el programa destino por defecto
    }

    if (texto_info == NULL) // si el texto de info es NULL, usar cadena vacía para evitar puntero nulo
    {
        texto_info = ""; // reemplaza NULL por cadena vacía
    }

    if (texto_espejo == NULL) // si el texto espejo es NULL, usar cadena vacía
    {
        texto_espejo = ""; // reemplaza NULL por cadena vacía
    }

    if (texto_info[0] == '\0' && texto_espejo[0] == '\0') // si ambos textos están vacíos, no hay nada que enviar
    {
        return; // sale sin hacer nada: respuesta vacía no tiene sentido
    }

    if (construir_ruta_transferencia(2, &ruta) < 0) // intenta construir la ruta del archivo de salida (posición 2 en GG_archivos)
    {
        return; // sale si no se pudo construir la ruta de transferencia
    }

    if (concatenar_formato_separado_por_variable(
            &info_a_enviar,
            NULL,
            "%s%s%s%s%s%s%s",
            programa,
            GG_caracter_para_transferencia_entre_archivos[1],
            GG_id_programa,
            GG_caracter_para_transferencia_entre_archivos[0],
            texto_info,
            GG_caracter_para_transferencia_entre_archivos[0],
            texto_espejo) < 0) // construye la línea de respuesta con formato: destino┴origen│info│espejo
    {
        free(info_a_enviar); // libera por si concatenar asignó algo parcial
        free(ruta);          // libera la ruta antes de salir
        return;              // sale con error silencioso: fallo al construir la respuesta
    }

    agregar_fila(ruta, info_a_enviar); // escribe la línea de respuesta al final del archivo de salida
    free(info_a_enviar);               // libera la cadena de respuesta, ya fue escrita
    free(ruta);                        // libera la ruta del archivo, ya no se necesita
}

// FunciÃ³n que lee un archivo, extrae comandos y los devuelve en un arreglo dinÃ¡mico
/*
 * Uso: Ejecuta monitoreo_archivo_entrada de forma segura.
 * Entrada ejemplo: monitoreo_archivo_entrada(retorno_comando, retorno_numero_lineas)
 */
int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */

    const char *directorio = GG_archivos[1][0]; // Obtiene el directorio desde una variable global
    const char *archivo = GG_archivos[1][2];    // Obtiene el nombre del archivo desde una variable global

    char *ruta = NULL;            // AquÃ­ se construirÃ¡ la ruta completa (directorio + archivo)
    char **lineas_archivo = NULL; // Arreglo donde se guardarÃ¡n las lÃ­neas del archivo
    int total_lineas_archivo = 0; // NÃºmero total de lÃ­neas leÃ­das del archivo
    int cantidad_comandos = 0;    // NÃºmero de comandos vÃ¡lidos encontrados

    // ValidaciÃ³n de parÃ¡metros de salida
    if (retorno_comando == NULL || retorno_numero_lineas == NULL)
    {
        return -1; // Error si los punteros son invÃ¡lidos
    }

    *retorno_comando = NULL;    // Inicializa el arreglo de salida
    *retorno_numero_lineas = 0; // Inicializa el contador de salida

    // Validar que existan directorio y archivo
    if (directorio == NULL || archivo == NULL)
    {
        return -1;
    }

    // Construye la ruta completa usando formato (tipo sprintf dinÃ¡mico)
    if (concatenar_formato_separado_por_variable(&ruta, NULL, "%s%s", directorio, archivo) < 0)
    {
        free(ruta); // Libera por si algo se alcanzÃ³ a asignar
        return -1;
    }

    // Lee todas las lÃ­neas del archivo
    lineas_archivo = leer_archivo(ruta, &total_lineas_archivo);
    free(ruta); // Ya no se necesita la ruta

    if (lineas_archivo == NULL)
    {
        return -1; // Error al leer archivo
    }

    // Si no hay suficientes lÃ­neas (por ejemplo, encabezado o Ã­ndice inicial)
    if (total_lineas_archivo <= GG_indice_donde_comensar)
    {
        free_lineas(lineas_archivo, total_lineas_archivo); // Libera memoria
        return 0;                                          // No hay comandos que procesar
    }

    // Recorre las lÃ­neas desde cierto Ã­ndice
    for (int i = GG_indice_donde_comensar; i < total_lineas_archivo; i++)
    {
        // Mensaje de depuraciÃ³n
        imprimirMensaje_para_depurar("\nLeyendo linea %d: %s", i,
                                     lineas_archivo[i] ? lineas_archivo[i] : "(vacia)");

        // Si la lÃ­nea es NULL o estÃ¡ vacÃ­a, se ignora
        if (lineas_archivo[i] == NULL || lineas_archivo[i][0] == '\0')
        {
            continue;
        }

        char *comando_final = NULL;  // AquÃ­ se guardarÃ¡ el comando extraÃ­do
        char *linea_original = NULL; // puntero a la copia de la línea completa para usarla como clave de eliminación; ejemplo: "NEXOPORTALARCANO┴ID│op_tienda§agregar│espejo"

        // Intenta extraer un comando de la lÃ­nea
        int resultado_extraer = extraer_comando_de_linea_transferencia(
            lineas_archivo[i], &comando_final); // intenta extraer el comando de la línea actual; ejemplo: resultado_extraer = RET_OK (0)

        // Si se extrajo correctamente un comando
        if (RET_IS_OK(resultado_extraer) && comando_final != NULL)
        {
            // Aumenta el tamaÃ±o del arreglo de comandos
            char **tmp = (char **)realloc(
                *retorno_comando, sizeof(char *) * (cantidad_comandos + 1));

            if (tmp == NULL) // Si falla realloc
            {
                free(comando_final);  // Libera el comando actual
                free(linea_original); // libera la copia de la línea original antes de salir con error

                // Libera todos los comandos ya guardados
                for (int j = 0; j < cantidad_comandos; j++) // recorre los comandos ya guardados para liberarlos; ejemplo: j de 0 a 2
                {
                    free((*retorno_comando)[j]); // libera cada string de comando almacenado en el arreglo
                }

                free(*retorno_comando);     // Libera el arreglo
                *retorno_comando = NULL;    // deja el puntero del arreglo en NULL para evitar dangling pointer
                *retorno_numero_lineas = 0; // reinicia el contador de comandos a 0

                free_lineas(lineas_archivo, total_lineas_archivo); // Libera lÃ­neas
                return -1;                                         // Error
            }

            *retorno_comando = tmp; // Actualiza el arreglo

            linea_original = duplicar_texto_local(lineas_archivo[i]); // duplica la línea entera para usarla como clave de eliminación posterior; ejemplo: "NEXOPORTALARCANO┴ID│op_tienda§agregar│espejo"
            if (linea_original == NULL)                               // si la duplicación falló por falta de memoria disponible
            {
                free(comando_final); // libera el comando extraído antes de salir con error

                for (int j = 0; j < cantidad_comandos; j++) // recorre los comandos ya guardados para liberarlos todos
                {
                    free((*retorno_comando)[j]); // libera cada string del arreglo de comandos
                }

                free(*retorno_comando);     // libera el arreglo de punteros de comandos
                *retorno_comando = NULL;    // deja el puntero limpio para no tener dangling pointer
                *retorno_numero_lineas = 0; // reinicia el contador de comandos a 0

                free_lineas(lineas_archivo, total_lineas_archivo); // libera las líneas del archivo leídas en memoria
                return -1;                                         // retorna error: fallo de memoria al duplicar la línea original
            }

            // Guarda la linea completa para que el caller pueda separar origen, comando y espejo.
            (*retorno_comando)[cantidad_comandos] = linea_original; // guarda la línea completa en el índice actual del arreglo; ejemplo: (*retorno_comando)[0] = "NEXOPORTALARCANO┴ID│op_tienda§agregar│espejo"

            cantidad_comandos++; // Incrementa contador
            free(comando_final); // libera el string de comando extraído, ya se guardó la línea completa
        }
    }

    // Libera las lÃ­neas del archivo (ya no se necesitan)
    free_lineas(lineas_archivo, total_lineas_archivo);

    // Si no se encontrÃ³ ningÃºn comando
    if (cantidad_comandos == 0)
    {
        return 0;
    }

    *retorno_numero_lineas = cantidad_comandos; // Devuelve cuÃ¡ntos comandos hay
    return 1;                                   // Indica Ã©xito con comandos encontrados
}

/*
 * Uso: Ejecuta datos_recibidos_a_procesar_y_borrar de forma segura.
 * Entrada ejemplo: datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas)
 */
int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char **comandos = NULL; // arreglo que se llenará con las líneas de comando encontradas
    int total_comandos = 0; // cantidad de comandos encontrados en el archivo de entrada
    int estado = 0;         // resultado de la llamada a monitoreo_archivo_entrada; ejemplo: 1=hay comandos

    if (retorno_comando == NULL || retorno_numero_lineas == NULL) // si los punteros de salida son NULL, no se puede continuar
    {
        return -1; // retorna error: parámetros de salida inválidos
    }

    *retorno_comando = NULL;    // inicializa el arreglo de salida a NULL
    *retorno_numero_lineas = 0; // inicializa el contador de salida a 0

    estado = monitoreo_archivo_entrada(&comandos, &total_comandos); // lee el archivo de entrada y extrae los comandos pendientes

    if (estado <= 0) // si no hay comandos (0) o hubo error (-1)
    {
        return estado; // propaga el resultado (0=vacío, -1=error)
    }

    *retorno_comando = comandos;             // entrega al caller el arreglo de comandos encontrados
    *retorno_numero_lineas = total_comandos; // entrega al caller la cantidad de comandos
    return 1;                                // retorna 1 indicando que hay comandos disponibles para procesar
}

/*
 * Uso: Ejecuta finalizar_comando_procesado de forma segura.
 * Entrada ejemplo: finalizar_comando_procesado(linea_original, estado_ejecucion)
 */
int finalizar_comando_procesado(const char *linea_original, int estado_ejecucion)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char *ruta_entrada = NULL;         // ruta del archivo de entrada donde está la línea a eliminar
    int mandar_a_errores = 0;          // bandera: 1 si el comando falló y debe guardarse en el archivo de errores
    int resultado = RET_ERROR_GENERIC; // resultado de la operación, inicializado como error por defecto

    if (linea_original == NULL || linea_original[0] == '\0') // si la línea es NULL o vacía, no hay nada que finalizar
    {
        return RET_INVALID_ARG; // retorna error: argumento inválido
    }

    if (construir_ruta_transferencia(1, &ruta_entrada) < 0) // construye la ruta del archivo de entrada (posición 1 en GG_archivos)
    {
        return RET_ERROR_GENERIC; // retorna error: no se pudo obtener la ruta del archivo de entrada
    }

    if (RET_IS_ERROR(estado_ejecucion)) // si el estado del comando procesado es un código de error
    {
        mandar_a_errores = 1; // activa la bandera para registrar el fallo en el archivo de errores
    }

    if (mandar_a_errores) // si el comando falló, hay que guardarlo en el archivo de errores
    {
        char *ruta_errores = NULL; // ruta del archivo donde se guardan los comandos fallidos

        if (construir_ruta_transferencia(4, &ruta_errores) < 0) // construye la ruta del archivo de errores (posición 4 en GG_archivos)
        {
            free(ruta_entrada);       // libera la ruta de entrada antes de salir
            return RET_ERROR_GENERIC; // retorna error: no se pudo obtener la ruta del archivo de errores
        }

        crearArchivo(ruta_errores, GG_archivos[4][1]); // crea el archivo de errores si no existe
        agregar_fila(ruta_errores, linea_original);    // agrega la línea del comando fallido al archivo de errores
        free(ruta_errores);                            // libera la ruta de errores, ya no se necesita
    }

    resultado = quitar_linea_exacta_del_archivo(ruta_entrada, linea_original); // elimina la línea del archivo de entrada (marca el comando como procesado)
    free(ruta_entrada);                                                        // libera la ruta de entrada
    return resultado;                                                          // retorna el resultado de la eliminación
}

/*
 * Uso: Ejecuta cambiar_id_programa_al_siguiente de forma segura.
 * Entrada ejemplo: cambiar_id_programa_al_siguiente(usuarios, total_usuarios)
 */
int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (usuarios == NULL || total_usuarios <= GG_indice_donde_comensar) // si el arreglo es NULL o no hay suficientes usuarios
    {
        return 0; // retorna 0: no hay cambio posible
    }

    if (usuarios[0] == NULL || strcmp(usuarios[0], GG_id_programa) != 0) // si el primer usuario no es este programa
    {
        return 0; // retorna 0: este programa no está en turno, no corresponde cambiar
    }

    int id_nuevo = GG_indice_donde_comensar;                        // índice del siguiente usuario al que ceder el turno; ejemplo: 1
    for (int i = GG_indice_donde_comensar; i < total_usuarios; i++) // recorre la lista de usuarios desde el inicio
    {
        if (usuarios[i] != NULL && strcmp(usuarios[i], GG_id_programa) == 0) // busca la posición actual de este programa en la lista
        {
            if (i >= total_usuarios - 1) // si es el último de la lista, el siguiente es el primero (circular)
            {
                id_nuevo = GG_indice_donde_comensar; // vuelve al inicio de la lista
            }
            else
            {
                id_nuevo = i + 1; // avanza al siguiente en la lista
            }
            break; // sale del bucle al encontrar este programa
        }
    }

    if (usuarios[id_nuevo] == NULL || usuarios[id_nuevo][0] == '\0') // si el siguiente ID es NULL o vacío, no se puede cambiar
    {
        return 0; // retorna 0: no hay un ID válido al que ceder el turno
    }

    char *ruta_entrada = NULL;                              // ruta del archivo de entrada donde se editará el ID activo
    if (construir_ruta_transferencia(1, &ruta_entrada) < 0) // construye la ruta del archivo de entrada
    {
        return -1; // retorna error: no se pudo construir la ruta
    }

    int resultado = editar_fila_espesifica_sin_arreglo_gg(ruta_entrada, "0", 0, usuarios[id_nuevo]); // edita la fila 0 del archivo con el nuevo ID de programa
    free(ruta_entrada);                                                                              // libera la ruta de entrada
    return resultado ? 1 : 0;                                                                        // retorna 1 si la edición fue exitosa, 0 si falló
}

/*
 * Uso: Ejecuta quitar_id_prog_del_archivo de forma segura.
 * Entrada ejemplo: quitar_id_prog_del_archivo()
 */
int quitar_id_prog_del_archivo(void)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char *ruta_entrada = NULL;                              // ruta del archivo de entrada donde se eliminará el ID de este programa
    if (construir_ruta_transferencia(1, &ruta_entrada) < 0) // construye la ruta del archivo de entrada
    {
        return -1; // retorna error: no se pudo construir la ruta
    }

    eliminar_fila_para_multiples_programas_solo_prog(ruta_entrada, "0", GG_id_programa); // elimina la fila que contiene el ID de este programa del archivo
    free(ruta_entrada);                                                                  // libera la ruta de entrada
    return 1;                                                                            // retorna 1 indicando que la operación fue completada
}

/*
 * Uso: Ejecuta checar_numero_de_direccion_de_archivo_atras_actual_adelante de forma segura.
 * Entrada ejemplo: checar_numero_de_direccion_de_archivo_atras_actual_adelante(posicion_bandera, numero_actual_posicion, arr_devolver)
 */
int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera,
                                                                int numero_actual_posicion,
                                                                int arr_devolver[3])
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (arr_devolver == NULL) // si el arreglo de salida es NULL, no se puede escribir el resultado
    {
        return -1; // retorna error: arreglo de salida inválido
    }

    const int total_direcciones = 3;                                           // número fijo de direcciones: atrás, actual, adelante
    int numero_adelante_posicion = numero_actual_posicion + total_direcciones; // calcula la posición adelante sumando el paso
    int numero_atras_posicion = numero_actual_posicion - total_direcciones;    // calcula la posición atrás restando el paso

    if (numero_adelante_posicion >= total_direcciones) // si la posición adelante supera el límite, volver al inicio
    {
        numero_adelante_posicion = posicion_bandera; // usa la posición de bandera como referencia de inicio
    }

    if (numero_atras_posicion < 0) // si la posición atrás es negativa, ir al final de la lista
    {
        numero_atras_posicion = (total_direcciones - 1) + posicion_bandera; // calcula la última posición válida
    }

    arr_devolver[0] = numero_atras_posicion;    // guarda la posición anterior en el primer elemento
    arr_devolver[1] = numero_actual_posicion;   // guarda la posición actual en el segundo elemento
    arr_devolver[2] = numero_adelante_posicion; // guarda la posición siguiente en el tercer elemento
    return 0;                                   // retorna éxito: las tres posiciones fueron calculadas y almacenadas
}

#elif defined(__XC)
/* ============================================================
   COMPILACIÃ“N PARA PIC16/18 CON COMUNICACIÃ“N USB

   NOTA: En PIC usamos comunicaciÃ³n USB en lugar de sistema
   de archivos. Las funciones USB se implementarÃ¡n en futuro.
   ============================================================ */

/* ============================================================
   FUNCIONES USB STUB - A IMPLEMENTAR EN FUTURO
   ============================================================

   Estas funciones serÃ¡n implementadas cuando se agregue
   soporte para comunicaciÃ³n USB en PIC.
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
        *retorno_comando = NULL; // inicializa el arreglo de salida a NULL
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0; // inicializa el contador de salida a 0
    return 0;                       /* Sin comandos (implementar en futuro) */
}

/* EnvÃ­a respuesta por USB/puerto serie.
   A IMPLEMENTAR: usb_enviar_respuesta() */
static void usb_respuesta(const char *folio, const char *info, const char *programa)
{
    /* TODO: Implementar envÃ­o por USB/UART
       - Construir payload: programa | ID | folio | info
       - Enviar por USB/puerto serie
       - Manejar timeouts y errores
    */
    (void)folio;    // suprime advertencia: folio no se usa hasta implementar el envío USB
    (void)info;     // suprime advertencia: info no se usa hasta implementar el envío USB
    (void)programa; // suprime advertencia: programa no se usa hasta implementar el envío USB
}

/* Procesa y limpia comandos recibidos por USB.
   A IMPLEMENTAR: usb_limpiar_comandos() */
static int usb_datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* TODO: Implementar limpieza de buffer USB
       - Leer comandos del buffer USB
       - Limpiar despuÃ©s de procesar
       - Retornar estado
    */
    if (retorno_comando)
        *retorno_comando = NULL; // inicializa el arreglo de salida a NULL
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0; // inicializa el contador de salida a 0
    return 0;
}

/* Cambia ID del programa en buffer USB.
   A IMPLEMENTAR: usb_cambiar_id_programa() */
static int usb_cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* TODO: Implementar rotaciÃ³n de ID en buffer USB */
    (void)usuarios;       // suprime advertencia: parámetro no usado hasta implementación
    (void)total_usuarios; // suprime advertencia: parámetro no usado hasta implementación
    return 0;             // retorna 0: sin operación (stub pendiente)
}

/* Elimina ID del programa desde buffer USB.
   A IMPLEMENTAR: usb_quitar_id_programa() */
static int usb_quitar_id_prog_del_archivo(void)
{
    /* TODO: Implementar eliminaciÃ³n de ID en buffer USB */
    return 0; // retorna 0: stub pendiente, sin operación real en PIC
}

/* ============================================================
   FUNCIONES PÃšBLICAS - Delegan a USB
       ============================================================ */

/*
 * Uso: Ejecuta monitoreo_archivo_entrada de forma segura.
 * Entrada ejemplo: monitoreo_archivo_entrada(retorno_comando, retorno_numero_lineas)
 */
int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* En PIC, leer desde USB en lugar de archivo */
    return usb_monitoreo_archivo_entrada(retorno_comando, retorno_numero_lineas); // delega a la función USB correspondiente
}

/*
 * Uso: Ejecuta respuesta de forma segura.
 * Entrada ejemplo: respuesta(info, programa_enviar, info_espejo)
 */
void respuesta(const char *info,
               const char *programa_enviar,
               const char *info_espejo)
{
    /* En PIC, enviar por USB en lugar de archivo */
    usb_respuesta(info, info_espejo, programa_enviar); // delega el envío a la función USB correspondiente
    (void)info_espejo;                                 // suprime advertencia: ya fue pasado a usb_respuesta
}

/*
 * Uso: Ejecuta datos_recibidos_a_procesar_y_borrar de forma segura.
 * Entrada ejemplo: datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas)
 */
int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* En PIC, procesar desde USB en lugar de archivo */
    return usb_datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas); // delega a la función USB correspondiente
}

/*
 * Uso: Ejecuta finalizar_comando_procesado de forma segura.
 * Entrada ejemplo: finalizar_comando_procesado(linea_original, estado_ejecucion)
 */
int finalizar_comando_procesado(const char *linea_original, int estado_ejecucion)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    (void)linea_original;   // suprime advertencia: en PIC no se usa sistema de archivos
    (void)estado_ejecucion; // suprime advertencia: en PIC no se registran errores en archivo
    return 0;               // retorna 0: stub sin operación
}

/*
 * Uso: Ejecuta cambiar_id_programa_al_siguiente de forma segura.
 * Entrada ejemplo: cambiar_id_programa_al_siguiente(usuarios, total_usuarios)
 */
int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* En PIC, cambiar ID en buffer USB */
    return usb_cambiar_id_programa_al_siguiente(usuarios, total_usuarios); // delega a la función USB correspondiente
}

/*
 * Uso: Ejecuta quitar_id_prog_del_archivo de forma segura.
 * Entrada ejemplo: quitar_id_prog_del_archivo()
 */
int quitar_id_prog_del_archivo(void)
{
    /* En PIC, quitar ID de buffer USB */
    return usb_quitar_id_prog_del_archivo(); // delega a la función USB correspondiente
}

/*
 * Uso: Ejecuta checar_numero_de_direccion_de_archivo_atras_actual_adelante de forma segura.
 * Entrada ejemplo: checar_numero_de_direccion_de_archivo_atras_actual_adelante(posicion_bandera, numero_actual_posicion, arr_devolver)
 */
int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera,
                                                                int numero_actual_posicion,
                                                                int arr_devolver[3])
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (arr_devolver == NULL)
        return -1;                            // retorna error: arreglo de salida inválido
    arr_devolver[0] = 0;                      // en PIC no hay navegación atrás, se devuelve 0
    arr_devolver[1] = numero_actual_posicion; // posición actual del archivo
    arr_devolver[2] = 0;                      // en PIC no hay navegación adelante, se devuelve 0
    return 0;                                 // retorna éxito: stub con valores por defecto
}

#else
/* ============================================================
   COMPILACIÃ“N POR DEFECTO (stubs bÃ¡sicos)
   ============================================================ */

int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (retorno_comando)
        *retorno_comando = NULL; // inicializa el arreglo de salida a NULL
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0; // inicializa el contador de salida a 0
    return 0;                       // retorna 0: plataforma no soportada, sin comandos
}

/*
 * Uso: Ejecuta respuesta de forma segura.
 * Entrada ejemplo: respuesta(info, programa_enviar, info_espejo)
 */
void respuesta(const char *info,
               const char *programa_enviar,
               const char *info_espejo)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    (void)info;            // suprime advertencia: parámetro no usado en plataforma por defecto
    (void)programa_enviar; // suprime advertencia: parámetro no usado en plataforma por defecto
    (void)info_espejo;     // suprime advertencia: parámetro no usado en plataforma por defecto
}

/*
 * Uso: Ejecuta datos_recibidos_a_procesar_y_borrar de forma segura.
 * Entrada ejemplo: datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas)
 */
int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (retorno_comando)
        *retorno_comando = NULL; // inicializa el arreglo de salida a NULL
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0; // inicializa el contador de salida a 0
    return 0;                       // retorna 0: plataforma no soportada, sin datos
}

/*
 * Uso: Ejecuta finalizar_comando_procesado de forma segura.
 * Entrada ejemplo: finalizar_comando_procesado(linea_original, estado_ejecucion)
 */
int finalizar_comando_procesado(const char *linea_original, int estado_ejecucion)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    (void)linea_original;   // suprime advertencia: parámetro no usado en plataforma por defecto
    (void)estado_ejecucion; // suprime advertencia: parámetro no usado en plataforma por defecto
    return 0;               // retorna 0: stub sin operación
}

/*
 * Uso: Ejecuta cambiar_id_programa_al_siguiente de forma segura.
 * Entrada ejemplo: cambiar_id_programa_al_siguiente(usuarios, total_usuarios)
 */
int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    (void)usuarios;       // suprime advertencia: parámetro no usado en plataforma por defecto
    (void)total_usuarios; // suprime advertencia: parámetro no usado en plataforma por defecto
    return 0;             // retorna 0: stub sin operación
}

/*
 * Uso: Ejecuta quitar_id_prog_del_archivo de forma segura.
 * Entrada ejemplo: quitar_id_prog_del_archivo()
 */
int quitar_id_prog_del_archivo(void)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    return 0; // retorna 0: stub sin operación
}

/*
 * Uso: Ejecuta checar_numero_de_direccion_de_archivo_atras_actual_adelante de forma segura.
 * Entrada ejemplo: checar_numero_de_direccion_de_archivo_atras_actual_adelante(posicion_bandera, numero_actual_posicion, arr_devolver)
 */
int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera,
                                                                int numero_actual_posicion,
                                                                int arr_devolver[3])
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (arr_devolver == NULL)
        return -1;                            // retorna error: arreglo de salida inválido
    arr_devolver[0] = 0;                      // plataforma por defecto no tiene navegación atrás
    arr_devolver[1] = numero_actual_posicion; // posición actual recibida como parámetro
    arr_devolver[2] = 0;                      // plataforma por defecto no tiene navegación adelante
    return 0;                                 // retorna éxito: stub con valores por defecto
}

#endif /* Fin compilaciÃ³n condicional */
