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
#include "../../cabeceras/codigos_retorno.h"

#if defined(_WIN32) || defined(__linux__)
/* ============================================================
   COMPILACIÓN PARA WINDOWS Y LINUX
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
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: puntero de salida inv�lido
    }

    *ruta_out = NULL; // inicializa el puntero de salida a NULL por seguridad; ejemplo: *ruta_out = NULL

    if (indice_archivo < 0 ||                     // si el �ndice es negativo, es inv�lido
        GG_archivos[indice_archivo][0] == NULL || // si no hay directorio definido para ese �ndice
        GG_archivos[indice_archivo][2] == NULL)   // si no hay nombre de archivo definido para ese �ndice
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: datos del archivo no disponibles en GG_archivos
    }

    if (concatenar_formato_separado_por_variable(ruta_out, NULL, "%s%s", GG_archivos[indice_archivo][0], GG_archivos[indice_archivo][2]) < 0) // construye la ruta completa concatenando directorio + nombre del archivo
    {
        free(*ruta_out);               // libera memoria si concatenar asign� algo antes de fallar
        *ruta_out = NULL;              // deja el puntero limpio para no dejar basura
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: fallo al construir la ruta
    }

    RETORNAR_PROCESO_ESTANDAR(0); // retorna �xito: la ruta fue construida y almacenada en *ruta_out
}

/*
 * Uso: Ejecuta extraer_comando_de_linea_transferencia de forma segura.
 * Entrada ejemplo: extraer_comando_de_linea_transferencia(linea_transferencia, comando_out)
 */
static int extraer_comando_de_linea_transferencia(const char *linea_transferencia, char **comando_out)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char **partes_transferencia = NULL; // arreglo con las partes de la l�nea dividida por el separador de transferencia
    int n_partes_transferencia = 0;     // cantidad de partes encontradas al dividir la l�nea
    char *comando_final = NULL;         // puntero donde se guardar� el comando extra�do; ejemplo: "op_tienda~agregar"

    if (comando_out == NULL) // si el puntero de salida es NULL, no se puede devolver el comando
    {
        RETORNAR_PROCESO_ESTANDAR(RET_INVALID_ARG); // retorna error: argumento inv�lido
    }

    *comando_out = NULL; // inicializa el puntero de salida a NULL por seguridad

    if (linea_transferencia == NULL || linea_transferencia[0] == '\0') // si la l�nea es NULL o est� vac�a, no hay comando que extraer
    {
        RETORNAR_PROCESO_ESTANDAR(RET_NOT_FOUND); // retorna "no encontrado": l�nea inv�lida o vac�a
    }

    n_partes_transferencia = split(linea_transferencia, GG_caracter_para_transferencia_entre_archivos[0], &partes_transferencia); // divide la l�nea usando el separador principal de transferencia
    if (n_partes_transferencia < 3 ||                                                                                             // se esperan al menos 3 partes: destino, comando y espejo
        partes_transferencia == NULL ||                                                                                           // si split fall� y no devolvi� arreglo
        partes_transferencia[0] == NULL ||                                                                                        // si la parte de destino est� vac�a
        partes_transferencia[1] == NULL ||                                                                                        // si la parte de comando est� vac�a
        partes_transferencia[2] == NULL)                                                                                          // si la parte de espejo est� vac�a
    {
        free_split(partes_transferencia);         // libera el arreglo aunque est� incompleto
        RETORNAR_PROCESO_ESTANDAR(RET_NOT_FOUND); // retorna "no encontrado": formato de l�nea incorrecto
    }

    {
        /* Separar "ID_DESTINO┴ID_ORIGEN" y verificar que el destino sea este programa */
        char **partes_destino = NULL;                                                                                             // arreglo para separar destino y origen dentro de la primera parte
        int n_partes_destino = split(partes_transferencia[0], GG_caracter_para_transferencia_entre_archivos[1], &partes_destino); // divide "ID_DESTINO-ID_ORIGEN" por el separador secundario
        int es_para_mi = (n_partes_destino >= 1 && partes_destino != NULL &&                                                      // verifica que el split haya funcionado
                          partes_destino[0] != NULL &&                                                                            // verifica que el destino no sea NULL
                          strcmp(partes_destino[0], GG_id_programa) == 0);                                                        // compara el destino con el ID de este programa
        free_split(partes_destino);                                                                                               // libera las partes de destino, ya no se necesitan
        if (!es_para_mi)                                                                                                          // si el mensaje no es para este programa, ignorarlo
        {
            free_split(partes_transferencia);         // libera las partes de la l�nea completa
            RETORNAR_PROCESO_ESTANDAR(RET_NOT_FOUND); // retorna "no encontrado": el mensaje es para otro programa
        }
    }

    comando_final = variable_string("%s", partes_transferencia[1]); // duplica el comando (segunda parte) en memoria propia
    if (comando_final == NULL)                                      // si la duplicaci�n fall� por memoria insuficiente
    {
        free_split(partes_transferencia);             // libera las partes antes de salir con error
        RETORNAR_PROCESO_ESTANDAR(RET_ERROR_GENERIC); // retorna error gen�rico: fallo de memoria
    }

    free_split(partes_transferencia);  // libera el arreglo de partes, ya se copi� lo necesario
    *comando_out = comando_final;      // entrega el comando extra�do al caller
    RETORNAR_PROCESO_ESTANDAR(RET_OK); // retorna �xito: comando extra�do correctamente
}

/*
 * Uso: Ejecuta quitar_linea_exacta_del_archivo de forma segura.
 * Entrada ejemplo: quitar_linea_exacta_del_archivo(ruta, linea_a_quitar)
 */
static int quitar_linea_exacta_del_archivo(const char *ruta, const char *linea_a_quitar)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char **lineas = NULL;    // arreglo con todas las l�neas le�das del archivo
    char **resultado = NULL; // arreglo con las l�neas que se conservar�n (sin la eliminada)
    int total_lineas = 0;    // cantidad total de l�neas le�das del archivo
    int total_resultado = 0; // cantidad de l�neas que se guardar�n (resultado final)
    int eliminado = 0;       // bandera: 1 si ya se encontr� y elimin� la l�nea buscada

    if (ruta == NULL || linea_a_quitar == NULL) // si alguno de los par�metros de entrada es NULL
    {
        RETORNAR_PROCESO_ESTANDAR(RET_INVALID_ARG); // retorna error: argumento inv�lido
    }

    lineas = leer_archivo(ruta, &total_lineas); // lee todas las l�neas del archivo en memoria
    if (lineas == NULL)                         // si no se pudo leer el archivo (no existe o error de lectura)
    {
        RETORNAR_PROCESO_ESTANDAR(RET_NOT_FOUND); // retorna "no encontrado": archivo inaccesible
    }

    resultado = (char **)malloc(sizeof(char *) * ((total_lineas > 0) ? total_lineas : 1)); // reserva memoria para el arreglo resultado (m�nimo 1 para evitar malloc(0))
    if (resultado == NULL)                                                                 // si malloc fall� por falta de memoria
    {
        free_lineas(lineas, total_lineas);            // libera las l�neas antes de salir
        RETORNAR_PROCESO_ESTANDAR(RET_ERROR_GENERIC); // retorna error gen�rico: fallo de memoria
    }

    for (int i = 0; i < total_lineas; i++) // recorre cada l�nea del archivo
    {
        if (!eliminado && lineas[i] != NULL && strcmp(lineas[i], linea_a_quitar) == 0) // si a�n no se elimin� y esta l�nea coincide exactamente con la buscada
        {
            eliminado = 1; // marca que ya se encontr� la l�nea a eliminar
            continue;      // salta esta l�nea sin agregarla al resultado
        }

        resultado[total_resultado] = variable_string("%s", lineas[i] ? lineas[i] : ""); // copia la l�nea actual al arreglo resultado
        if (resultado[total_resultado] == NULL)                                         // si la copia fall� por memoria
        {
            free_lineas(resultado, total_resultado);      // libera el resultado parcial
            free_lineas(lineas, total_lineas);            // libera las l�neas originales
            RETORNAR_PROCESO_ESTANDAR(RET_ERROR_GENERIC); // retorna error gen�rico: fallo de memoria
        }
        total_resultado++; // incrementa el contador de l�neas en el resultado
    }

    if (!eliminado) // si se recorrieron todas las l�neas y nunca se encontr� la buscada
    {
        free_lineas(resultado, total_resultado);  // libera el resultado (no se usar�)
        free_lineas(lineas, total_lineas);        // libera las l�neas originales
        RETORNAR_PROCESO_ESTANDAR(RET_NOT_FOUND); // retorna "no encontrado": la l�nea no exist�a en el archivo
    }

    guardar_archivo(ruta, resultado, total_resultado); // sobreescribe el archivo con las l�neas restantes
    free_lineas(resultado, total_resultado);           // libera el arreglo resultado
    free_lineas(lineas, total_lineas);                 // libera las l�neas originales
    RETORNAR_PROCESO_ESTANDAR(RET_OK);                 // retorna �xito: la l�nea fue eliminada y el archivo fue actualizado
}

/*
 * Uso: Ejecuta respuesta de forma segura.
 * Entrada ejemplo: respuesta(info, programa_enviar, info_espejo)
 */
void respuesta(const char *info, const char *programa_enviar, const char *info_espejo)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    imprimirMensaje_para_depurar("parametros recibidos en respuesta(): \n\nprograma_enviar='%s', \ninfo='%s', \ninfo_espejo='%s'\n", programa_enviar ? programa_enviar : "(null)", info ? info : "(null)", info_espejo ? info_espejo : "(null)");

    const char *programa = programa_enviar; // alias local al nombre del programa destino; ejemplo: "NEXOPORTALARCANO"
    const char *texto_info = info;          // alias local al texto de informaci�n a enviar
    const char *texto_espejo = info_espejo; // alias local al texto espejo (copia de confirmaci�n)
    char *ruta = NULL;                      // ruta del archivo de salida donde se escribir� la respuesta
    char *info_a_enviar = NULL;             // cadena completa formateada lista para agregar al archivo

    if (programa == NULL || programa[0] == '\0') // si no se especific� programa destino, usar el predeterminado
    {
        programa = "NEXOPORTALARCANO"; // asigna el programa destino por defecto
    }

    if (texto_info == NULL) // si el texto de info es NULL, usar cadena vac�a para evitar puntero nulo
    {
        texto_info = ""; // reemplaza NULL por cadena vac�a
    }

    if (texto_espejo == NULL) // si el texto espejo es NULL, usar cadena vac�a
    {
        texto_espejo = ""; // reemplaza NULL por cadena vac�a
    }

    if (texto_info[0] == '\0' && texto_espejo[0] == '\0') // si ambos textos est�n vac�os, no hay nada que enviar
    {
        return; // sale sin hacer nada: respuesta vac�a no tiene sentido
    }

    if (construir_ruta_transferencia(2, &ruta) < 0) // intenta construir la ruta del archivo de salida (posici�n 2 en GG_archivos)
    {
        return; // sale si no se pudo construir la ruta de transferencia
    }

    if (concatenar_formato_separado_por_variable(&info_a_enviar, NULL, "%s%s%s%s%s%s%s", programa, GG_caracter_para_transferencia_entre_archivos[1], GG_id_programa, GG_caracter_para_transferencia_entre_archivos[0], texto_info, GG_caracter_para_transferencia_entre_archivos[0],
                                                 texto_espejo) < 0) // construye la l�nea de respuesta con formato: destino-origen�info�espejo
    {
        free(info_a_enviar); // libera por si concatenar asign� algo parcial
        free(ruta);          // libera la ruta antes de salir
        return;              // sale con error silencioso: fallo al construir la respuesta
    }

    agregar_fila(ruta, info_a_enviar); // escribe la l�nea de respuesta al final del archivo de salida
    free(info_a_enviar);               // libera la cadena de respuesta, ya fue escrita
    free(ruta);                        // libera la ruta del archivo, ya no se necesita
}

// Función que lee un archivo, extrae comandos y los devuelve en un arreglo dinámico
/*
 * Uso: Ejecuta monitoreo_archivo_entrada de forma segura.
 * Entrada ejemplo: monitoreo_archivo_entrada(retorno_comando, retorno_numero_lineas)
 */
int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */

    const char *directorio = GG_archivos[1][0]; // Obtiene el directorio desde una variable global
    const char *archivo = GG_archivos[1][2];    // Obtiene el nombre del archivo desde una variable global

    imprimirMensaje_para_depurar("Directorio obtenido: '%s', Archivo obtenido: '%s'", directorio ? directorio : "(null)", archivo ? archivo : "(null)");

    char *ruta = NULL;            // Aquí se construirá la ruta completa (directorio + archivo)
    char **lineas_archivo = NULL; // Arreglo donde se guardarán las líneas del archivo
    int total_lineas_archivo = 0; // Número total de líneas leídas del archivo
    int cantidad_comandos = 0;    // Número de comandos válidos encontrados

    // Validación de parámetros de salida
    if (retorno_comando == NULL || retorno_numero_lineas == NULL)
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // Error si los punteros son inválidos
    }

    *retorno_comando = NULL;    // Inicializa el arreglo de salida
    *retorno_numero_lineas = 0; // Inicializa el contador de salida

    // Validar que existan directorio y archivo
    if (directorio == NULL || archivo == NULL)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // Construye la ruta completa usando formato (tipo sprintf dinámico)
    if (concatenar_formato_separado_por_variable(&ruta, NULL, "%s%s", directorio, archivo) < 0)
    {
        free(ruta); // Libera por si algo se alcanzó a asignar
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // Lee todas las líneas del archivo
    lineas_archivo = leer_archivo(ruta, &total_lineas_archivo);
    free(ruta); // Ya no se necesita la ruta

    if (lineas_archivo == NULL)
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // Error al leer archivo
    }

    // Si no hay suficientes líneas (por ejemplo, encabezado o índice inicial)
    if (total_lineas_archivo <= GG_indice_donde_comensar)
    {
        free_lineas(lineas_archivo, total_lineas_archivo); // Libera memoria
        RETORNAR_PROCESO_ESTANDAR(0);                      // No hay comandos que procesar
    }

    // Recorre las líneas desde cierto índice
    for (int i = GG_indice_donde_comensar; i < total_lineas_archivo; i++)
    {
        // Mensaje de depuración
        imprimirMensaje_para_depurar("\nLeyendo linea %d: %s", i, lineas_archivo[i] ? lineas_archivo[i] : "(vacia)");

        // Si la línea es NULL o está vacía, se ignora
        if (lineas_archivo[i] == NULL || lineas_archivo[i][0] == '\0')
        {
            continue;
        }

        char *comando_final = NULL;  // Aquí se guardará el comando extraído
        char *linea_original = NULL; // puntero a la copia de la l�nea completa para usarla como clave de eliminaci�n; ejemplo: "NEXOPORTALARCANO-ID�op_tienda�agregar�espejo"

        // Intenta extraer un comando de la línea
        int resultado_extraer = extraer_comando_de_linea_transferencia(lineas_archivo[i], &comando_final); // intenta extraer el comando de la l�nea actual; ejemplo: resultado_extraer = RET_OK (0)

        // Si se extrajo correctamente un comando
        if (RET_IS_OK(resultado_extraer) && comando_final != NULL)
        {
            // Aumenta el tamaño del arreglo de comandos
            char **tmp = (char **)realloc(*retorno_comando, sizeof(char *) * (cantidad_comandos + 1));

            if (tmp == NULL) // Si falla realloc
            {
                free(comando_final);  // Libera el comando actual
                free(linea_original); // libera la copia de la l�nea original antes de salir con error

                // Libera todos los comandos ya guardados
                for (int j = 0; j < cantidad_comandos; j++) // recorre los comandos ya guardados para liberarlos; ejemplo: j de 0 a 2
                {
                    free((*retorno_comando)[j]); // libera cada string de comando almacenado en el arreglo
                }

                free(*retorno_comando);     // Libera el arreglo
                *retorno_comando = NULL;    // deja el puntero del arreglo en NULL para evitar dangling pointer
                *retorno_numero_lineas = 0; // reinicia el contador de comandos a 0

                free_lineas(lineas_archivo, total_lineas_archivo); // Libera líneas
                RETORNAR_PROCESO_ESTANDAR(-1);                     // Error
            }

            *retorno_comando = tmp; // Actualiza el arreglo

            linea_original = variable_string("%s", lineas_archivo[i]); // duplica la l�nea entera para usarla como clave de eliminaci�n posterior; ejemplo: "NEXOPORTALARCANO-ID�op_tienda�agregar�espejo"
            if (linea_original == NULL)                                // si la duplicaci�n fall� por falta de memoria disponible
            {
                free(comando_final); // libera el comando extra�do antes de salir con error

                for (int j = 0; j < cantidad_comandos; j++) // recorre los comandos ya guardados para liberarlos todos
                {
                    free((*retorno_comando)[j]); // libera cada string del arreglo de comandos
                }

                free(*retorno_comando);     // libera el arreglo de punteros de comandos
                *retorno_comando = NULL;    // deja el puntero limpio para no tener dangling pointer
                *retorno_numero_lineas = 0; // reinicia el contador de comandos a 0

                free_lineas(lineas_archivo, total_lineas_archivo); // libera las l�neas del archivo le�das en memoria
                RETORNAR_PROCESO_ESTANDAR(-1);                     // retorna error: fallo de memoria al duplicar la l�nea original
            }

            // Guarda la linea completa para que el caller pueda separar origen, comando y espejo.
            (*retorno_comando)[cantidad_comandos] = linea_original; // guarda la l�nea completa en el �ndice actual del arreglo; ejemplo: (*retorno_comando)[0] = "NEXOPORTALARCANO-ID�op_tienda�agregar�espejo"

            cantidad_comandos++; // Incrementa contador
            free(comando_final); // libera el string de comando extra�do, ya se guard� la l�nea completa
        }
    }

    // Libera las líneas del archivo (ya no se necesitan)
    free_lineas(lineas_archivo, total_lineas_archivo);

    // Si no se encontró ningún comando
    if (cantidad_comandos == 0)
    {
        RETORNAR_PROCESO_ESTANDAR(0);
    }

    *retorno_numero_lineas = cantidad_comandos; // Devuelve cuántos comandos hay
    RETORNAR_PROCESO_ESTANDAR(1);               // Indica éxito con comandos encontrados
}

/*
 * Uso: Ejecuta datos_recibidos_a_procesar_y_borrar de forma segura.
 * Entrada ejemplo: datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas)
 */
int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char **comandos = NULL; // arreglo que se llenar� con las l�neas de comando encontradas
    int total_comandos = 0; // cantidad de comandos encontrados en el archivo de entrada
    int estado = 0;         // resultado de la llamada a monitoreo_archivo_entrada; ejemplo: 1=hay comandos

    if (retorno_comando == NULL || retorno_numero_lineas == NULL) // si los punteros de salida son NULL, no se puede continuar
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: par�metros de salida inv�lidos
    }

    *retorno_comando = NULL;    // inicializa el arreglo de salida a NULL
    *retorno_numero_lineas = 0; // inicializa el contador de salida a 0

    estado = monitoreo_archivo_entrada(&comandos, &total_comandos); // lee el archivo de entrada y extrae los comandos pendientes

    if (estado <= 0) // si no hay comandos (0) o hubo error (-1)
    {
        RETORNAR_PROCESO_ESTANDAR(estado); // propaga el resultado (0=vac�o, -1=error)
    }

    *retorno_comando = comandos;             // entrega al caller el arreglo de comandos encontrados
    *retorno_numero_lineas = total_comandos; // entrega al caller la cantidad de comandos
    RETORNAR_PROCESO_ESTANDAR(1);            // retorna 1 indicando que hay comandos disponibles para procesar
}

/*
 * Uso: Ejecuta finalizar_comando_procesado de forma segura.
 * Entrada ejemplo: finalizar_comando_procesado(linea_original, estado_ejecucion)
 */
int finalizar_comando_procesado(const char *linea_original, int estado_ejecucion)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char *ruta_entrada = NULL;         // ruta del archivo de entrada donde est� la l�nea a eliminar
    int mandar_a_errores = 0;          // bandera: 1 si el comando fall� y debe guardarse en el archivo de errores
    int resultado = RET_ERROR_GENERIC; // resultado de la operaci�n, inicializado como error por defecto

    if (linea_original == NULL || linea_original[0] == '\0') // si la l�nea es NULL o vac�a, no hay nada que finalizar
    {
        RETORNAR_PROCESO_ESTANDAR(RET_INVALID_ARG); // retorna error: argumento inv�lido
    }

    if (construir_ruta_transferencia(1, &ruta_entrada) < 0) // construye la ruta del archivo de entrada (posici�n 1 en GG_archivos)
    {
        RETORNAR_PROCESO_ESTANDAR(RET_ERROR_GENERIC); // retorna error: no se pudo obtener la ruta del archivo de entrada
    }

    if (RET_IS_ERROR(estado_ejecucion)) // si el estado del comando procesado es un c�digo de error
    {
        mandar_a_errores = 1; // activa la bandera para registrar el fallo en el archivo de errores
    }

    if (mandar_a_errores) // si el comando fall�, hay que guardarlo en el archivo de errores
    {
        char *ruta_errores = NULL; // ruta del archivo donde se guardan los comandos fallidos

        if (construir_ruta_transferencia(4, &ruta_errores) < 0) // construye la ruta del archivo de errores (posici�n 4 en GG_archivos)
        {
            free(ruta_entrada);                           // libera la ruta de entrada antes de salir
            RETORNAR_PROCESO_ESTANDAR(RET_ERROR_GENERIC); // retorna error: no se pudo obtener la ruta del archivo de errores
        }

        crearArchivo(ruta_errores, GG_archivos[4][1]); // crea el archivo de errores si no existe
        agregar_fila(ruta_errores, linea_original);    // agrega la l�nea del comando fallido al archivo de errores
        free(ruta_errores);                            // libera la ruta de errores, ya no se necesita
    }

    resultado = quitar_linea_exacta_del_archivo(ruta_entrada, linea_original); // elimina la l�nea del archivo de entrada (marca el comando como procesado)
    free(ruta_entrada);                                                        // libera la ruta de entrada
    RETORNAR_PROCESO_ESTANDAR(resultado);                                      // retorna el resultado de la eliminaci�n
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
        RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: no hay cambio posible
    }

    if (usuarios[0] == NULL || strcmp(usuarios[0], GG_id_programa) != 0) // si el primer usuario no es este programa
    {
        RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: este programa no est� en turno, no corresponde cambiar
    }

    int id_nuevo = GG_indice_donde_comensar;                        // �ndice del siguiente usuario al que ceder el turno; ejemplo: 1
    for (int i = GG_indice_donde_comensar; i < total_usuarios; i++) // recorre la lista de usuarios desde el inicio
    {
        if (usuarios[i] != NULL && strcmp(usuarios[i], GG_id_programa) == 0) // busca la posici�n actual de este programa en la lista
        {
            if (i >= total_usuarios - 1) // si es el �ltimo de la lista, el siguiente es el primero (circular)
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

    if (usuarios[id_nuevo] == NULL || usuarios[id_nuevo][0] == '\0') // si el siguiente ID es NULL o vac�o, no se puede cambiar
    {
        RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: no hay un ID v�lido al que ceder el turno
    }

    char *ruta_entrada = NULL;                              // ruta del archivo de entrada donde se editar� el ID activo
    if (construir_ruta_transferencia(1, &ruta_entrada) < 0) // construye la ruta del archivo de entrada
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo construir la ruta
    }

    int resultado = editar_fila_espesifica_sin_arreglo_gg(ruta_entrada, "0", 0, usuarios[id_nuevo]); // edita la fila 0 del archivo con el nuevo ID de programa
    free(ruta_entrada);                                                                              // libera la ruta de entrada
    RETORNAR_PROCESO_ESTANDAR(resultado ? 1 : 0);                                                    // retorna 1 si la edici�n fue exitosa, 0 si fall�
}

/*
 * Uso: Ejecuta quitar_id_prog_del_archivo de forma segura.
 * Entrada ejemplo: quitar_id_prog_del_archivo()
 */
int quitar_id_prog_del_archivo(void)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    char *ruta_entrada = NULL;                              // ruta del archivo de entrada donde se eliminar� el ID de este programa
    if (construir_ruta_transferencia(1, &ruta_entrada) < 0) // construye la ruta del archivo de entrada
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: no se pudo construir la ruta
    }

    eliminar_fila_para_multiples_programas_solo_prog(ruta_entrada, "0", GG_id_programa); // elimina la fila que contiene el ID de este programa del archivo
    free(ruta_entrada);                                                                  // libera la ruta de entrada
    RETORNAR_PROCESO_ESTANDAR(1);                                                        // retorna 1 indicando que la operaci�n fue completada
}

/*
 * Uso: Ejecuta checar_numero_de_direccion_de_archivo_atras_actual_adelante de forma segura.
 * Entrada ejemplo: checar_numero_de_direccion_de_archivo_atras_actual_adelante(posicion_bandera, numero_actual_posicion, arr_devolver)
 */
int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera, int numero_actual_posicion, int arr_devolver[3])
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (arr_devolver == NULL) // si el arreglo de salida es NULL, no se puede escribir el resultado
    {
        RETORNAR_PROCESO_ESTANDAR(-1); // retorna error: arreglo de salida inv�lido
    }

    const int total_direcciones = 3;                                           // n�mero fijo de direcciones: atr�s, actual, adelante
    int numero_adelante_posicion = numero_actual_posicion + total_direcciones; // calcula la posici�n adelante sumando el paso
    int numero_atras_posicion = numero_actual_posicion - total_direcciones;    // calcula la posici�n atr�s restando el paso

    if (numero_adelante_posicion >= total_direcciones) // si la posici�n adelante supera el l�mite, volver al inicio
    {
        numero_adelante_posicion = posicion_bandera; // usa la posici�n de bandera como referencia de inicio
    }

    if (numero_atras_posicion < 0) // si la posici�n atr�s es negativa, ir al final de la lista
    {
        numero_atras_posicion = (total_direcciones - 1) + posicion_bandera; // calcula la �ltima posici�n v�lida
    }

    arr_devolver[0] = numero_atras_posicion;    // guarda la posici�n anterior en el primer elemento
    arr_devolver[1] = numero_actual_posicion;   // guarda la posici�n actual en el segundo elemento
    arr_devolver[2] = numero_adelante_posicion; // guarda la posici�n siguiente en el tercer elemento
    RETORNAR_PROCESO_ESTANDAR(0);               // retorna �xito: las tres posiciones fueron calculadas y almacenadas
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
        *retorno_comando = NULL; // inicializa el arreglo de salida a NULL
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0; // inicializa el contador de salida a 0
    RETORNAR_PROCESO_ESTANDAR(0);   /* Sin comandos (implementar en futuro) */
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
    (void)folio;    // suprime advertencia: folio no se usa hasta implementar el env�o USB
    (void)info;     // suprime advertencia: info no se usa hasta implementar el env�o USB
    (void)programa; // suprime advertencia: programa no se usa hasta implementar el env�o USB
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
        *retorno_comando = NULL; // inicializa el arreglo de salida a NULL
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0; // inicializa el contador de salida a 0
    RETORNAR_PROCESO_ESTANDAR(0);
}

/* Cambia ID del programa en buffer USB.
   A IMPLEMENTAR: usb_cambiar_id_programa() */
static int usb_cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* TODO: Implementar rotación de ID en buffer USB */
    (void)usuarios;               // suprime advertencia: par�metro no usado hasta implementaci�n
    (void)total_usuarios;         // suprime advertencia: par�metro no usado hasta implementaci�n
    RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: sin operaci�n (stub pendiente)
}

/* Elimina ID del programa desde buffer USB.
   A IMPLEMENTAR: usb_quitar_id_programa() */
static int usb_quitar_id_prog_del_archivo(void)
{
    /* TODO: Implementar eliminación de ID en buffer USB */
    RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: stub pendiente, sin operaci�n real en PIC
}

/* ============================================================
   FUNCIONES PÚBLICAS - Delegan a USB
       ============================================================ */

/*
 * Uso: Ejecuta monitoreo_archivo_entrada de forma segura.
 * Entrada ejemplo: monitoreo_archivo_entrada(retorno_comando, retorno_numero_lineas)
 */
int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* En PIC, leer desde USB en lugar de archivo */
    RETORNAR_PROCESO_ESTANDAR(usb_monitoreo_archivo_entrada(retorno_comando, retorno_numero_lineas)); // delega a la funci�n USB correspondiente
}

/*
 * Uso: Ejecuta respuesta de forma segura.
 * Entrada ejemplo: respuesta(info, programa_enviar, info_espejo)
 */
void respuesta(const char *info, const char *programa_enviar, const char *info_espejo)
{
    /* En PIC, enviar por USB en lugar de archivo */
    usb_respuesta(info, info_espejo, programa_enviar); // delega el env�o a la funci�n USB correspondiente
    (void)info_espejo;                                 // suprime advertencia: ya fue pasado a usb_respuesta
}

/*
 * Uso: Ejecuta datos_recibidos_a_procesar_y_borrar de forma segura.
 * Entrada ejemplo: datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas)
 */
int datos_recibidos_a_procesar_y_borrar(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* En PIC, procesar desde USB en lugar de archivo */
    RETORNAR_PROCESO_ESTANDAR(usb_datos_recibidos_a_procesar_y_borrar(retorno_comando, retorno_numero_lineas)); // delega a la funci�n USB correspondiente
}

/*
 * Uso: Ejecuta finalizar_comando_procesado de forma segura.
 * Entrada ejemplo: finalizar_comando_procesado(linea_original, estado_ejecucion)
 */
int finalizar_comando_procesado(const char *linea_original, int estado_ejecucion)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    (void)linea_original;         // suprime advertencia: en PIC no se usa sistema de archivos
    (void)estado_ejecucion;       // suprime advertencia: en PIC no se registran errores en archivo
    RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: stub sin operaci�n
}

/*
 * Uso: Ejecuta cambiar_id_programa_al_siguiente de forma segura.
 * Entrada ejemplo: cambiar_id_programa_al_siguiente(usuarios, total_usuarios)
 */
int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* En PIC, cambiar ID en buffer USB */
    RETORNAR_PROCESO_ESTANDAR(usb_cambiar_id_programa_al_siguiente(usuarios, total_usuarios)); // delega a la funci�n USB correspondiente
}

/*
 * Uso: Ejecuta quitar_id_prog_del_archivo de forma segura.
 * Entrada ejemplo: quitar_id_prog_del_archivo()
 */
int quitar_id_prog_del_archivo(void)
{
    /* En PIC, quitar ID de buffer USB */
    RETORNAR_PROCESO_ESTANDAR(usb_quitar_id_prog_del_archivo()); // delega a la funci�n USB correspondiente
}

/*
 * Uso: Ejecuta checar_numero_de_direccion_de_archivo_atras_actual_adelante de forma segura.
 * Entrada ejemplo: checar_numero_de_direccion_de_archivo_atras_actual_adelante(posicion_bandera, numero_actual_posicion, arr_devolver)
 */
int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera, int numero_actual_posicion, int arr_devolver[3])
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (arr_devolver == NULL)
        RETORNAR_PROCESO_ESTANDAR(-1);        // retorna error: arreglo de salida inv�lido
    arr_devolver[0] = 0;                      // en PIC no hay navegaci�n atr�s, se devuelve 0
    arr_devolver[1] = numero_actual_posicion; // posici�n actual del archivo
    arr_devolver[2] = 0;                      // en PIC no hay navegaci�n adelante, se devuelve 0
    RETORNAR_PROCESO_ESTANDAR(0);             // retorna �xito: stub con valores por defecto
}

#else
/* ============================================================
   COMPILACIÓN POR DEFECTO (stubs básicos)
   ============================================================ */

int monitoreo_archivo_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (retorno_comando)
        *retorno_comando = NULL; // inicializa el arreglo de salida a NULL
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0; // inicializa el contador de salida a 0
    RETORNAR_PROCESO_ESTANDAR(0);   // retorna 0: plataforma no soportada, sin comandos
}

/*
 * Uso: Ejecuta respuesta de forma segura.
 * Entrada ejemplo: respuesta(info, programa_enviar, info_espejo)
 */
void respuesta(const char *info, const char *programa_enviar, const char *info_espejo)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    (void)info;            // suprime advertencia: par�metro no usado en plataforma por defecto
    (void)programa_enviar; // suprime advertencia: par�metro no usado en plataforma por defecto
    (void)info_espejo;     // suprime advertencia: par�metro no usado en plataforma por defecto
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
    RETORNAR_PROCESO_ESTANDAR(0);   // retorna 0: plataforma no soportada, sin datos
}

/*
 * Uso: Ejecuta finalizar_comando_procesado de forma segura.
 * Entrada ejemplo: finalizar_comando_procesado(linea_original, estado_ejecucion)
 */
int finalizar_comando_procesado(const char *linea_original, int estado_ejecucion)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    (void)linea_original;         // suprime advertencia: par�metro no usado en plataforma por defecto
    (void)estado_ejecucion;       // suprime advertencia: par�metro no usado en plataforma por defecto
    RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: stub sin operaci�n
}

/*
 * Uso: Ejecuta cambiar_id_programa_al_siguiente de forma segura.
 * Entrada ejemplo: cambiar_id_programa_al_siguiente(usuarios, total_usuarios)
 */
int cambiar_id_programa_al_siguiente(char **usuarios, int total_usuarios)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    (void)usuarios;               // suprime advertencia: par�metro no usado en plataforma por defecto
    (void)total_usuarios;         // suprime advertencia: par�metro no usado en plataforma por defecto
    RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: stub sin operaci�n
}

/*
 * Uso: Ejecuta quitar_id_prog_del_archivo de forma segura.
 * Entrada ejemplo: quitar_id_prog_del_archivo()
 */
int quitar_id_prog_del_archivo(void)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    RETORNAR_PROCESO_ESTANDAR(0); // retorna 0: stub sin operaci�n
}

/*
 * Uso: Ejecuta checar_numero_de_direccion_de_archivo_atras_actual_adelante de forma segura.
 * Entrada ejemplo: checar_numero_de_direccion_de_archivo_atras_actual_adelante(posicion_bandera, numero_actual_posicion, arr_devolver)
 */
int checar_numero_de_direccion_de_archivo_atras_actual_adelante(int posicion_bandera, int numero_actual_posicion, int arr_devolver[3])
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
    if (arr_devolver == NULL)
        RETORNAR_PROCESO_ESTANDAR(-1);        // retorna error: arreglo de salida inv�lido
    arr_devolver[0] = 0;                      // plataforma por defecto no tiene navegaci�n atr�s
    arr_devolver[1] = numero_actual_posicion; // posici�n actual recibida como par�metro
    arr_devolver[2] = 0;                      // plataforma por defecto no tiene navegaci�n adelante
    RETORNAR_PROCESO_ESTANDAR(0);             // retorna �xito: stub con valores por defecto
}

#endif /* Fin compilación condicional */
