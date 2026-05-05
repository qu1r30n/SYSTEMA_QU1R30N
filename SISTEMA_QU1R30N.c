/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - CLASE_QU1R30N.h: Dependencia interna del proyecto
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp, etc. */

#include "cabeceras/codigos_retorno.h"
#include "CLASE_QU1R30N.h"
#include "cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/ControladorMonitoreoArchivo.h"

static char *duplicar_texto_local(const char *texto)
{
    char *copia = NULL;

    if (texto == NULL)
    {
        return NULL;
    }

    copia = (char *)malloc(strlen(texto) + 1);
    if (copia == NULL)
    {
        return NULL;
    }

    strcpy(copia, texto);
    return copia;
}

#if defined(_WIN32) || defined(__linux__)
/* ============================================================
   COMPILACIÓN PARA WINDOWS Y LINUX
   (Sistema de archivos disponible)
   ============================================================ */

// Wrapper para atexit() - se ejecuta automáticamente al cerrar el programa
static void limpieza_al_salir(void)
{
    quitar_id_prog_del_archivo();
}

// Inicialización
void inicializacion()
{
    for (int i = 0; GG_archivos[i][0] != NULL && GG_archivos[i][1] != NULL && GG_archivos[i][2] != NULL; i++)
    {
        char *ruta_archivo = NULL;

        if (concatenar_formato_separado_por_variable(&ruta_archivo, NULL, "%s%s", GG_archivos[i][0], GG_archivos[i][2]) < 0)
        {
            free(ruta_archivo);
            continue;
        }

        crearArchivo(ruta_archivo, GG_archivos[i][1]);
        free(ruta_archivo);
    }

    // aqui_agrega_el_id_al_archivo
    char *ruta_banderas = NULL;
    if (concatenar_formato_separado_por_variable(&ruta_banderas, NULL, "%s%s", GG_archivos[3][0], GG_archivos[3][2]) >= 0)
    {
        int n_lineas_banderas = 0;
        char **lineas_banderas = leer_archivo(ruta_banderas, &n_lineas_banderas);

        if (n_lineas_banderas == 0)
        {
            // archivo vacio: agregar 2 veces porque la linea 0 es la que se checa a quien le toca
            agregar_fila(ruta_banderas, GG_id_programa);
            agregar_fila(ruta_banderas, GG_id_programa);
        }
        else
        {
            agregar_sino_existe(ruta_banderas, 0, GG_id_programa, GG_id_programa);
        }

        if (lineas_banderas)
        {
            free_lineas(lineas_banderas, n_lineas_banderas);
        }
        free(ruta_banderas);
    }

    // Registrar limpieza automática al cerrar el programa
    atexit(limpieza_al_salir);
}

char *conmutador(char *info_a_conmutar, int *estado_out)
{
    return variable_string("prueba de retortno");
    imprimirMensaje_para_depurar("%s", info_a_conmutar);
    int resultado = RET_ERROR_GENERIC;
    const char *detalle_resultado = "No se pudo ejecutar el comando.";
    char **opciones = modelo_split(info_a_conmutar, G_caracter_separacion_funciones_espesificas[0]);
    char **sub_opcion = NULL;

    if (estado_out != NULL)
    {
        *estado_out = RET_ERROR_GENERIC;
    }

    if (!opciones || !opciones[0])
    {
        free_split(opciones);
        if (estado_out != NULL)
        {
            *estado_out = RET_ERROR_GENERIC;
        }
        return duplicar_texto_local("Comando invalido: no se pudo separar la solicitud.");
    }

    imprimirMensaje_para_depurar("\n\n%s\n%s\n%s\n%s", opciones[0], opciones[1], opciones[2], opciones[3]);

    char *texto_permiso = NULL;

    if (concatenar_formato_separado_por_variable(&texto_permiso, NULL, "nivel_minimo%s1%sruta_archivo%s%s\\%s%s%s%s%s", GG_caracter_separacion_nom_parametro_de_valor[0], G_caracter_separacion_funciones_espesificas[1], GG_caracter_separacion_nom_parametro_de_valor[0], GG_archivos[0][0], GG_archivos[0][2], G_caracter_separacion_funciones_espesificas[1], opciones[2], G_caracter_separacion_funciones_espesificas[1], opciones[3]) < 0)
    {
        free(texto_permiso);
        free_split(opciones);
        if (estado_out != NULL)
        {
            *estado_out = RET_ERROR_GENERIC;
        }
        return duplicar_texto_local("Error al construir texto de permiso.");
    }

    imprimirMensaje_para_depurar("\n\n%s\n", texto_permiso);

    // La verificación completa de permisos la maneja modelo_checar_permiso.
    // conmutador recibe la respuesta y la direccion del espacio para usarla en su flujo.
    char *retorna_direccion_espacio_negocio = NULL;
    int nivel_del_usuario_espacio = -1;
    int tiene_permiso_espacio = modelo_checar_permiso(texto_permiso, &retorna_direccion_espacio_negocio, &nivel_del_usuario_espacio);

    imprimirMensaje_para_depurar("tiene_permiso_espacio=%d\n", tiene_permiso_espacio); // si es 0 significa que si lo tiene
    imprimirMensaje_para_depurar("nivel_del_usuario_espacio=%d\n", nivel_del_usuario_espacio);
    if (retorna_direccion_espacio_negocio)
    {
        imprimirMensaje_para_depurar("direccion_espacio_negocio=%s\n", retorna_direccion_espacio_negocio);
        free(retorna_direccion_espacio_negocio);
    }
    free(texto_permiso);

    if (nivel_del_usuario_espacio <= 1 && nivel_del_usuario_espacio > -1)
    {

        if (strcmp(opciones[0], "op_tienda") == 0)
        {
            if (!opciones[1])
            {
                printf("Falta sub-opcion en op_tienda.\n");
                free_split(opciones);
                if (estado_out != NULL)
                {
                    *estado_out = RET_ERROR_GENERIC;
                }
                return duplicar_texto_local("Falta sub-opcion en op_tienda.");
            }

            sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);

            if (sub_opcion && sub_opcion[0] && sub_opcion[1])
            {
                imprimirMensaje_para_depurar("%s\n", sub_opcion[0]);
                imprimirMensaje_para_depurar("%s\n", sub_opcion[1]);

                if (strcmp(sub_opcion[0], "ventas") == 0)
                {
                    resultado = modelo_venta(sub_opcion[1]);
                    detalle_resultado = RET_IS_OK(resultado) ? "Venta procesada." : "Fallo en proceso de venta.";
                }
                else if (strcmp(sub_opcion[0], "compras") == 0)
                {
                    resultado = modelo_compra(sub_opcion[1]);
                    detalle_resultado = RET_IS_OK(resultado) ? "Compra procesada." : "Fallo en proceso de compra.";
                }
                else if (strcmp(sub_opcion[0], "agregar_producto") == 0)
                {
                    resultado = modelo_agregarProducto(sub_opcion[1]);
                    detalle_resultado = RET_IS_OK(resultado) ? "Producto agregado." : "No se pudo agregar producto.";
                }
                else
                {
                    printf("Opción no válida: %s\n", sub_opcion[0]);
                    resultado = RET_ERROR_GENERIC;
                    detalle_resultado = "Sub-opcion de op_tienda no valida.";
                }
            }
            else
            {
                printf("Sub-opcion incompleta en op_tienda.\n");
                resultado = RET_ERROR_GENERIC;
                detalle_resultado = "Sub-opcion incompleta en op_tienda.";
            }

            free_split(sub_opcion);
        }

        // nivel programador aqui se podra usar en un futuro directamente talves el tex_bas o algo asi para hablar directamente con el sistema y hacer cosas que solo el programador puede hacer como revisar errores del sistema o cosas asi
        if (nivel_del_usuario_espacio == 0)
        {

            if (strcmp(opciones[0], "administracion_espacio") == 0)
            {
                if (!opciones[1])
                {
                    printf("Falta sub-opcion en administracion_espacio.\n");
                    free_split(opciones);
                    if (estado_out != NULL)
                    {
                        *estado_out = RET_ERROR_GENERIC;
                    }
                    return duplicar_texto_local("Falta sub-opcion en administracion_espacio.");
                }

                sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);

                if (sub_opcion && sub_opcion[0] && sub_opcion[1])
                {
                    imprimirMensaje_para_depurar("%s\n", sub_opcion[0]);
                    imprimirMensaje_para_depurar("%s\n", sub_opcion[1]);

                    if (strcmp(sub_opcion[0], "crear_espacio") == 0)
                    {
                        char *direccion_archivo_espacios = NULL;
                        if (concatenar_formato_separado_por_variable(&direccion_archivo_espacios, NULL, "%s\\%s", GG_archivos[0][0], GG_archivos[0][2]) < 0)
                        {
                            free_split(sub_opcion);
                            free_split(opciones);
                            if (estado_out != NULL)
                            {
                                *estado_out = RET_ERROR_GENERIC;
                            }
                            return duplicar_texto_local("Error al preparar archivo de espacios.");
                        }

                        imprimirMensaje_para_depurar("%s\n", direccion_archivo_espacios);
                        crearArchivo(direccion_archivo_espacios, GG_archivos[0][1]);
                        imprimirMensaje_para_depurar("%s\n", sub_opcion[1]);
                        resultado = modelo_administracion_espacios_crear_espacio(sub_opcion[1]);
                        detalle_resultado = RET_IS_OK(resultado) ? "Espacio creado correctamente." : "No se pudo crear el espacio.";
                        free(direccion_archivo_espacios);
                    }
                    else
                    {
                        printf("Sub-opcion no valida en administracion_espacio: %s\n", sub_opcion[0]);
                        resultado = RET_ERROR_GENERIC;
                        detalle_resultado = "Sub-opcion no valida en administracion_espacio.";
                    }
                }
                else
                {
                    printf("Sub-opcion incompleta en administracion_espacio.\n");
                    resultado = RET_ERROR_GENERIC;
                    detalle_resultado = "Sub-opcion incompleta en administracion_espacio.";
                }

                free_split(sub_opcion);
            }

            else if (opciones && strcmp(opciones[0], "procesos_generales") == 0)
            {
                // entrada salidad de dinero
                // SOLO CON EL DINERO - NO CON PRODUCTOS NI CON SERVICIOS SOLO CON EL DINERO
                // pero talves impuestos y todo lo que un administrador y contador utilizaria lo mas general en realidad no se si esto iria aqui o en otro dedicado a eso
                resultado = RET_OK;
                detalle_resultado = "Proceso general ejecutado.";
            }

            else if (opciones && strcmp(opciones[0], "procesos_sistema") == 0)
            {
                // aqui se habla directamente con el sistema solo el programador
                resultado = RET_OK;
                detalle_resultado = "Proceso de sistema ejecutado.";
            }
        }
    }
    else
    {
        resultado = RET_ERROR_GENERIC;
        detalle_resultado = "Permisos insuficientes o credenciales invalidas.";
    }

    free_split(opciones);
    if (estado_out != NULL)
    {
        *estado_out = resultado;
    }
    return duplicar_texto_local(detalle_resultado);
}

static int extraer_datos_transferencia(const char *linea_transferencia,
                                       char **programa_respuesta_out,
                                       char **comando_out,
                                       char **info_espejo_out)
{
    char **partes_transferencia = NULL;
    char **partes_comando = NULL;
    int total_partes_transferencia = 0;
    int total_partes_comando = 0;

    if (linea_transferencia == NULL ||
        programa_respuesta_out == NULL ||
        comando_out == NULL ||
        info_espejo_out == NULL)
    {
        return RET_INVALID_ARG;
    }

    *programa_respuesta_out = NULL;
    *comando_out = NULL;
    *info_espejo_out = NULL;

    /* Formato: ID_DESTINO■ID_ORIGEN┴COMANDO■ESPEJO
       [0]="■" separa columnas, [1]="┴" separa DESTINO de ORIGEN */
    total_partes_transferencia = split(linea_transferencia, GG_caracter_para_transferencia_entre_archivos[0], &partes_transferencia);
    if (total_partes_transferencia >= 3 && partes_transferencia != NULL &&
        partes_transferencia[0] != NULL && partes_transferencia[1] != NULL && partes_transferencia[2] != NULL)
    {
        /* Separar "ID_DESTINO┴ID_ORIGEN" → ["ID_DESTINO", "ID_ORIGEN"] */
        total_partes_comando = split(partes_transferencia[0], GG_caracter_para_transferencia_entre_archivos[1], &partes_comando);
        if (total_partes_comando >= 2 && partes_comando != NULL &&
            partes_comando[0] != NULL && strcmp(partes_comando[0], GG_id_programa) == 0 &&
            partes_comando[1] != NULL)
        {
            *programa_respuesta_out = duplicar_texto_local(partes_comando[1]); /* ID_ORIGEN */
            *comando_out = duplicar_texto_local(partes_transferencia[1]);      /* COMANDO */
            *info_espejo_out = duplicar_texto_local(partes_transferencia[2]);  /* ESPEJO */

            free_split(partes_comando);
            free_split(partes_transferencia);

            if (*programa_respuesta_out == NULL || *comando_out == NULL || *info_espejo_out == NULL)
            {
                free(*programa_respuesta_out);
                free(*comando_out);
                free(*info_espejo_out);
                *programa_respuesta_out = NULL;
                *comando_out = NULL;
                *info_espejo_out = NULL;
                return RET_ERROR_GENERIC;
            }

            return RET_OK;
        }
    }

    free_split(partes_comando);
    free_split(partes_transferencia);
    return RET_NOT_FOUND;
}

int main()
{
    inicializacion();

    /* ejemplos de comandos que el sistema entrega al modelo
    const char *ejemplos[] = {
        //"op_tienda~agregar_producto§1¶Leche§1L¶unidad¶10¶123456¶100¶50¶ProveedorA",
        //"administracion_espacio~crear_espacio§nom_espacio⊓ferreteria_dan¶usuario_de_negocio⊓administrador_negocio¶contraseña_de_negocio⊓54321~id_de_espacio⊓0§usuario_de_espacio⊓administrador_de_espacio§contraseña_de_espacio⊓0",
        "op_tienda~agregar_producto§producto⊓2¶contenido⊓3¶tipo_medida⊓4¶precio_venta⊓5⊓no_predeterminado¶cod_barras⊓6¶cantidad⊓7¶costo_compra⊓8¶proveedor⊓9~id_de_espacio⊓20260330113640_ferreteria_dan~usuario_de_espacio⊓administrador_de_espacio§contraseña_de_espacio⊓12345~usuario_de_negocio⊓administrador_negocio§contraseña_de_negocio⊓54321",
        "op_tienda~ventas§ABC123¶2§SucursalX",
        "op_tienda~compras§XYZ987¶5§Proveedor1",
        NULL};


    for (int i = 0; ejemplos[i]; i++)
    {
        printf("Ejecutando comando: %s\n", ejemplos[i]);
        int estado_ejemplo = RET_ERROR_GENERIC;
        char *respuesta_ejemplo = conmutador((char *)ejemplos[i], &estado_ejemplo);
        free(respuesta_ejemplo);
    }
    */

    char **retorno_comando = NULL;
    int retorno_numero_lineas = 0;
    int estado_monitoreo = datos_recibidos_a_procesar_y_borrar(&retorno_comando, &retorno_numero_lineas);

    imprimirMensaje_para_depurar("Lineas detectadas en archivo de entrada: %d\n", retorno_numero_lineas);

    if (estado_monitoreo == 1 && retorno_comando != NULL)
    {
        for (int i = 0; i < retorno_numero_lineas; i++)
        {
            char *programa_respuesta = NULL;
            char *comando_para_conmutar = NULL;
            char *info_espejo = NULL;
            char *respuesta_conmutador = NULL;
            int estado_conmutador = RET_ERROR_GENERIC;

            imprimirMensaje_para_depurar("\n\nComando monitoreado[%d]: %s\n", i, retorno_comando[i]);

            // 1) El main recibe comandos ya extraidos por monitoreo.
            // 2) Se separa cada comando para obtener destino/comando/espejo.
            if (RET_IS_OK(extraer_datos_transferencia(retorno_comando[i],
                                                      &programa_respuesta,
                                                      &comando_para_conmutar,
                                                      &info_espejo)))
            {
                // 2) Manda el comando a conmutador para ejecutar operaciones.
                respuesta_conmutador = conmutador(comando_para_conmutar, &estado_conmutador);

                imprimirMensaje_para_depurar("Respuesta del conmutador: %s\n", respuesta_conmutador);
                // 3) El resultado textual de conmutador se envia por respuesta.
                respuesta(respuesta_conmutador, programa_respuesta, info_espejo);
            }

            finalizar_comando_procesado(retorno_comando[i], estado_conmutador);
            free(respuesta_conmutador);
            free(programa_respuesta);
            free(comando_para_conmutar);
            free(info_espejo);
        }
        free_lineas(retorno_comando, retorno_numero_lineas);
    }

    modelo_delay_ms("1000");

    return 0;
}

#elif defined(__XC)
/* ============================================================
   COMPILACIÓN PARA PIC16/18 - COMUNICACIÓN USB

   NOTA: En PIC, la comunicación es por USB/UART en lugar
   de archivos. Los stubs USB se implementarán en futuro.
   ============================================================ */

/* ============================================================
   FUNCIONES USB STUB - A IMPLEMENTAR EN FUTURO
   ============================================================ */

/* Lee entrada desde USB/UART.
   A IMPLEMENTAR: usb_leer_entrada() */
static int usb_leer_entrada(char ***retorno_comando, int *retorno_numero_lineas)
{
    /* TODO: Implementar lectura desde UART/USB en PIC
       - Configurar UART a velocidad adecuada
       - Leer buffer de entrada
       - Parsear comandos recibidos
       - Llenar retorno_comando con comandos válidos
       - Retornar total de comandos leídos
    */
    if (retorno_comando)
        *retorno_comando = NULL;
    if (retorno_numero_lineas)
        *retorno_numero_lineas = 0;
    return 0; /* Sin datos aún (implementar en futuro) */
}

void inicializacion(void)
{
    /* TODO: En PIC inicializar uart/USB cuando esté implementado */
    /* Por ahora: stub vacío */
}

char *conmutador(char *texto_prueba, int *estado_out)
{
    /* PIC: Procesar comando desde USB */
    /* TODO: En futuro, aquí procesar comandos pero
             adaptados para limitaciones de memoria en PIC */
    (void)texto_prueba;
    if (estado_out != NULL)
    {
        *estado_out = RET_OK;
    }
    return duplicar_texto_local("Stub PIC: comando aceptado.");
}

int main(void)
{
    inicializacion();

    /* En PIC, entrada continua desde USB/UART */
    char **retorno_comando = NULL;
    int retorno_numero_lineas = 0;

    while (1)
    {
        /* Leer comandos desde USB */
        int estado = usb_leer_entrada(&retorno_comando, &retorno_numero_lineas);

        if (estado == 1 && retorno_comando != NULL)
        {
            /* Procesar cada comando recibido */
            for (int i = 0; i < retorno_numero_lineas; i++)
            {
                if (retorno_comando[i] != NULL)
                {
                    int estado_pic = RET_ERROR_GENERIC;
                    char *respuesta_pic = conmutador(retorno_comando[i], &estado_pic);
                    free(respuesta_pic);
                }
            }

            /* Liberar comando (si hay malloc disponible) */
            /* free_lineas(retorno_comando, retorno_numero_lineas); */
            retorno_comando = NULL;
            retorno_numero_lineas = 0;
        }

        /* En PIC, típicamente hay delays para no saturar */
        /* delay_ms(100); */
    }

    return 0;

#else
/* ============================================================
   COMPILACIÓN POR DEFECTO
   ============================================================ */

void inicializacion(void)
{
    /* Stubs por defecto */
}

char *conmutador(char *texto_prueba, int *estado_out)
{
    (void)texto_prueba;
    if (estado_out != NULL)
    {
        *estado_out = RET_OK;
    }
    return duplicar_texto_local("Stub por defecto: comando aceptado.");
}

int main(void)
{
    inicializacion();
    return 0;
}

#endif /* Fin compilación condicional */