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

#if defined(_WIN32) || defined(__linux__)
/* ============================================================
   COMPILACIÓN PARA WINDOWS Y LINUX
   (Sistema de archivos disponible)
   ============================================================ */

// Wrapper para atexit() - se ejecuta automáticamente al cerrar el programa
/*
 * Uso: Ejecuta limpieza_al_salir de forma segura.
 * Entrada ejemplo: limpieza_al_salir()
 */
static void limpieza_al_salir(void)
{
    quitar_id_prog_del_archivo(); // elimina el ID de este programa del archivo de banderas al cerrar; asi otros programas saben que este ya no esta corriendo
}

static int acumular_texto_con_separador(char **acumulador, const char *nuevo_texto, const char *separador)
{
    if (acumulador == NULL || nuevo_texto == NULL || nuevo_texto[0] == '\0') // evita operar con punteros invalidos o texto vacio
    {
        return RET_INVALID_ARG; // informa que la entrada recibida no era valida
    }

    if (*acumulador == NULL) // si aun no hay lista de modelos, este texto sera el primero
    {
        *acumulador = variable_string("%s", nuevo_texto);          // duplica el primer retorno de modelo en memoria nueva
        return (*acumulador != NULL) ? RET_OK : RET_ERROR_GENERIC; // reporta exito o error de memoria
    }

    size_t largo_actual = strlen(*acumulador);                                            // mide la cadena acumulada hasta este momento
    size_t largo_nuevo = strlen(nuevo_texto);                                             // mide el nuevo retorno de modelo a anexar
    size_t largo_sep = (separador != NULL) ? strlen(separador) : 0;                       // mide el separador entre modelos o usa cero
    char *tmp = (char *)realloc(*acumulador, largo_actual + largo_sep + largo_nuevo + 1); // redimensiona el buffer para el contenido total

    if (tmp == NULL)
    {
        return RET_ERROR_GENERIC; // reporta fallo de memoria sin destruir el acumulador anterior
    }

    *acumulador = tmp; // actualiza el acumulador con el nuevo bloque de memoria valido

    if (largo_sep > 0) // si existe separador, lo inserta antes del nuevo retorno
    {
        memcpy(*acumulador + largo_actual, separador, largo_sep); // copia el separador despues del contenido actual
        largo_actual += largo_sep;                                // mueve la posicion al final del separador copiado
    }

    memcpy(*acumulador + largo_actual, nuevo_texto, largo_nuevo + 1); // copia el nuevo retorno incluyendo el terminador nulo
    return RET_OK;                                                    // confirma que la acumulacion se hizo correctamente
}

// Inicialización
/*
 * Uso: Ejecuta inicializacion de forma segura.
 * Entrada ejemplo: inicializacion()
 */
void inicializacion()
{
    for (int i = 0; GG_archivos[i][0] != NULL && GG_archivos[i][1] != NULL && GG_archivos[i][2] != NULL; i++) // recorre el arreglo GG_archivos hasta encontrar una entrada con NULL; ejemplo de entrada: {"conexion_arc\\", "ID_DESTINO■...", "archivo_entrada.txt"}
    {
        char *ruta_archivo = NULL; // guardara la ruta completa del archivo; ejemplo: "conexion_arc\\archivo_entrada.txt"

        if (concatenar_formato_separado_por_variable(&ruta_archivo, NULL, "%s%s", GG_archivos[i][0], GG_archivos[i][2]) < 0) // une directorio + nombre de archivo; ejemplo: "conexion_arc\\" + "archivo_entrada.txt" = "conexion_arc\\archivo_entrada.txt"
        {
            free(ruta_archivo); // libera si algo se asigno antes del fallo
            continue;           // salta al siguiente archivo en el arreglo
        }

        crearArchivo(ruta_archivo, GG_archivos[i][1]); // crea el archivo si no existe con su cabecera; ejemplo cabecera: "ID_DESTINO■ID_ORIGEN┴COMANDO■ESPEJO"
        free(ruta_archivo);                            // libera la memoria de la ruta construida
    }

    // aqui_agrega_el_id_al_archivo
    char *ruta_banderas = NULL;                                                                                            // ruta del archivo que coordina que programa esta activo; ejemplo: "conexion_arc\\banderas.txt"
    if (concatenar_formato_separado_por_variable(&ruta_banderas, NULL, "%s%s", GG_archivos[3][0], GG_archivos[3][2]) >= 0) // construye la ruta del archivo de banderas (indice 3 de GG_archivos)
    {
        int n_lineas_banderas = 0;                                                // contara cuantas lineas tiene el archivo de banderas al leerlo
        char **lineas_banderas = leer_archivo(ruta_banderas, &n_lineas_banderas); // lee el contenido del archivo de banderas; retorna NULL si no existe aun

        if (n_lineas_banderas == 0) // si el archivo esta vacio (primer arranque del sistema)
        {
            // archivo vacio: agregar 2 veces porque la linea 0 es la que se checa a quien le toca
            agregar_fila(ruta_banderas, GG_id_programa); // linea 0: programa activo actualmente; ejemplo: "SISTEMA_QU1R30N"
            agregar_fila(ruta_banderas, GG_id_programa); // linea 1: registro de que este programa existe; ejemplo: "SISTEMA_QU1R30N"
        }
        else // el archivo ya tiene contenido (el sistema ya arranco antes)
        {
            agregar_sino_existe(ruta_banderas, 0, GG_id_programa, GG_id_programa); // agrega el ID solo si no esta ya registrado, para no duplicarlo
        }

        if (lineas_banderas) // si se leyeron lineas del archivo, liberarlas
        {
            free_lineas(lineas_banderas, n_lineas_banderas); // libera el arreglo de strings de lineas
        }
        free(ruta_banderas); // libera la memoria de la ruta del archivo de banderas
    }

    // Registrar limpieza automática al cerrar el programa
    atexit(limpieza_al_salir); // registra la funcion limpieza_al_salir para que se llame automaticamente cuando el programa termine
}

/*
 * Uso: Ejecuta conmutador de forma segura.
 * Entrada ejemplo: conmutador(info_a_conmutar, estado_out)
 */
char *conmutador(char *info_a_conmutar, int *estado_out)
{
    // return variable_string("prueba de retortno");                                                    // TEMPORAL: mientras se desarrolla, siempre retorna este texto; ejemplo resultado: "prueba de retortno"
    imprimirMensaje_para_depurar("%s", info_a_conmutar);                                             // muestra en consola el comando completo recibido; ejemplo: "op_tienda~agregar_producto§producto⊓2¶..."
    int resultado = RET_ERROR_GENERIC;                                                               // guarda el codigo de resultado de la operacion; valor inicial: -1 (error)
    const char *detalle_resultado = "No se pudo ejecutar el comando.";                               // texto que se devolvera; cambia segun la operacion; ejemplo final: "Producto agregado."
    char *detalle_capa_modelo = NULL;                                                                // guarda el retorno estandarizado de la capa modelo; ejemplo: "0╠todo salio bien en este modelo llamado ventas╠ok"
    char *detalle_capa_proceso = NULL;                                                               // guarda el retorno estandarizado de la capa proceso; ejemplo: "0⛐todo salio bien en este proseso llamado procesos_generales⛐ok"
    char *acumulador_modelos = NULL;                                                                 // junta todos los retornos de modelos separados por ⛐ para incrustarlos en el retorno del conmutador
    char *retorno_conmutador = NULL;                                                                 // string final de retorno del conmutador; ejemplo: "0╣todo salio bien en el conmutador╣..."
    char **opciones = modelo_split(info_a_conmutar, G_caracter_separacion_funciones_espesificas[0]); // divide el comando por "~"; ejemplo: opciones[0]="op_tienda", opciones[1]="agregar_producto§...", opciones[2]="id_de_espacio⊓20260330_ferreteria_dan", opciones[3]="usuario_de_espacio⊓administrador§contraseña⊓12345"
    char **sub_opcion = NULL;                                                                        // se usara despues para dividir opciones[1] por "§"; ejemplo: sub_opcion[0]="agregar_producto", sub_opcion[1]="producto⊓2¶contenido⊓3¶..."

    if (estado_out != NULL) // verifica que el puntero de salida no sea nulo antes de escribir en el
    {
        *estado_out = RET_ERROR_GENERIC; // asigna error por defecto; si todo sale bien se sobreescribira al final
    }

    if (!opciones || !opciones[0]) // verifica si el split fallo o el primer campo esta vacio
    {
        free_split(opciones);   // libera la memoria del arreglo aunque este vacio
        if (estado_out != NULL) // evita escribir en puntero nulo
        {
            *estado_out = RET_ERROR_GENERIC; // marca error en el estado de salida
        }
        return construir_retorno_estandar(RET_ERROR_GENERIC, GG_caracter_para_confirmacion_o_error[0], "error en el conmutador", "Comando invalido: no se pudo separar la solicitud.");
    }

    imprimirMensaje_para_depurar("\n\n%s\n%s\n%s\n%s\n%s", opciones[0], opciones[1], opciones[2], opciones[3], opciones[4]); // muestra las 5 partes del comando; ejemplo: "op_tienda" / "agregar_producto§..." / "id_de_espacio⊓..." / "usuario_de_espacio⊓..." / "contraseña_de_espacio⊓..."

    char *texto_permiso = NULL; // string con datos de permiso a verificar; se construye a continuacion

    if (concatenar_formato_separado_por_variable(&texto_permiso, NULL, "nivel_minimo%s1%sruta_archivo%s%s\\%s%s%s%s%s", GG_caracter_separacion_nom_parametro_de_valor[0], G_caracter_separacion_funciones_espesificas[1], GG_caracter_separacion_nom_parametro_de_valor[0], GG_archivos[0][0], GG_archivos[0][2], G_caracter_separacion_funciones_espesificas[1], opciones[2], G_caracter_separacion_funciones_espesificas[1], opciones[3]) < 0) // construye el texto de permiso; ejemplo resultado: "nivel_minimo⊓1§ruta_archivo⊓espacios\\archivo_espacios.txt§id_de_espacio⊓20260330_ferreteria_dan§usuario_de_espacio⊓administrador_de_espacio§contraseña_de_espacio⊓12345"
    {
        free(texto_permiso);  // libera memoria parcialmente asignada
        free_split(opciones); // libera el arreglo de opciones
        if (estado_out != NULL)
        {
            *estado_out = RET_ERROR_GENERIC; // marca error en la salida
        }
        return construir_retorno_estandar(RET_ERROR_GENERIC, GG_caracter_para_confirmacion_o_error[0], "error en el conmutador", "Error al construir texto de permiso.");
    }

    imprimirMensaje_para_depurar("\n\n%s\n", texto_permiso); // muestra el string de permiso construido para depuracion

    // La verificación completa de permisos la maneja modelo_checar_permiso.
    // conmutador recibe la respuesta y la direccion del espacio para usarla en su flujo.
    char *retorna_direccion_espacio_negocio = NULL;                                                                                   // recibira la ruta del espacio si el usuario tiene permiso; ejemplo: "espacios\\20260330113640_ferreteria_dan\\"
    int nivel_del_usuario_espacio = -1;                                                                                               // nivel de acceso: -1=sin permiso, 0=programador (maximo), 1=administrador
    int tiene_permiso_espacio = modelo_checar_permiso(texto_permiso, &retorna_direccion_espacio_negocio, &nivel_del_usuario_espacio); // verifica credenciales y nivel; retorna 0 si tiene permiso; ejemplo: tiene_permiso_espacio=0

    imprimirMensaje_para_depurar("tiene_permiso_espacio=%d\n", tiene_permiso_espacio);         // si es 0 significa que si lo tiene; ejemplo: tiene_permiso_espacio=0
    imprimirMensaje_para_depurar("nivel_del_usuario_espacio=%d\n", nivel_del_usuario_espacio); // muestra el nivel obtenido; ejemplo: nivel_del_usuario_espacio=1
    free(texto_permiso);                                                                       // libera el string de permiso que ya fue utilizado

    // --- resumen de lo que llego antes de decidir que hacer ---
    imprimirMensaje_para_depurar("\n=== ANTES DEL CONMUTADOR ===\n");
    imprimirMensaje_para_depurar("operacion                    opciones[0] = %s\n", opciones[0] ? opciones[0] : "(nulo)");                                              // posicion 0: op_tienda, op_sistema, etc.
    imprimirMensaje_para_depurar("comando/params               opciones[1] = %s\n", opciones[1] ? opciones[1] : "(nulo)");                                              // posicion 1: sub-operacion y sus parametros
    imprimirMensaje_para_depurar("id_espacio_negocio           opciones[2] = %s\n", opciones[2] ? opciones[2] : "(nulo)");                                              // posicion 2: identificador del espacio de negocio
    imprimirMensaje_para_depurar("usuario/contraseña_espacio   opciones[3] = %s\n", opciones[3] ? opciones[3] : "(nulo)");                                              // posicion 3: usuario y contraseña del administrador del espacio
    imprimirMensaje_para_depurar("usuario/contraseña_negocio   opciones[4] = %s\n", opciones[4] ? opciones[4] : "(nulo)");                                              // posicion 4: usuario y contraseña del administrador del negocio
    imprimirMensaje_para_depurar("dir_espacio_negocio                       = %s\n", retorna_direccion_espacio_negocio ? retorna_direccion_espacio_negocio : "(nulo)"); // ruta del espacio si el permiso fue valido; ejemplo: "espacios\\20260330113640_ferreteria_dan\\"
    imprimirMensaje_para_depurar("nivel_usuario de espacio                  = %d\n", nivel_del_usuario_espacio);                                                        // -1=sin permiso, 0=programador, 1=administrador
    imprimirMensaje_para_depurar("============================\n\n");

    if (retorna_direccion_espacio_negocio) // libera la direccion del espacio despues de haberla impreso
    {
        free(retorna_direccion_espacio_negocio); // libera la memoria de la direccion ya que no se usa en el conmutador
    }

    if (nivel_del_usuario_espacio <= 1 && nivel_del_usuario_espacio > -1) // entra solo si el nivel es 0 o 1 (valido); nivel -1 significa acceso denegado
    {

        if (strcmp(opciones[0], "op_tienda") == 0) // revisa si el primer campo del comando es "op_tienda"
        {
            if (!opciones[1]) // verifica que exista la sub-operacion despues del primer "~"
            {
                printf("Falta sub-opcion en op_tienda.\n"); // avisa en consola
                free_split(opciones);                       // libera memoria antes de retornar
                if (estado_out != NULL)
                {
                    *estado_out = RET_ERROR_GENERIC;
                }
                return construir_retorno_estandar(RET_ERROR_GENERIC, GG_caracter_para_confirmacion_o_error[0], "error en el conmutador", "Falta sub-opcion en op_tienda.");
            }

            sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]); // divide opciones[1] por "§"; ejemplo: "agregar_producto§producto⊓2¶..." → sub_opcion[0]="agregar_producto", sub_opcion[1]="producto⊓2¶contenido⊓3¶..."

            if (sub_opcion && sub_opcion[0] && sub_opcion[1]) // verifica que el split dio al menos dos partes validas
            {
                imprimirMensaje_para_depurar("%s\n", sub_opcion[0]); // muestra nombre de la sub-operacion; ejemplo: "agregar_producto"
                imprimirMensaje_para_depurar("%s\n", sub_opcion[1]); // muestra los parametros; ejemplo: "producto⊓2¶contenido⊓3¶tipo_medida⊓4¶..."

                if (strcmp(sub_opcion[0], "ventas") == 0) // si la sub-operacion es "ventas"
                {
                    resultado = modelo_venta(sub_opcion[1]);                                                      // ejecuta el modelo de venta con los parametros; ejemplo sub_opcion[1]: "ABC123¶2§SucursalX"
                    detalle_resultado = RET_IS_OK(resultado) ? "Venta procesada." : "Fallo en proceso de venta."; // asigna mensaje segun si el resultado es OK
                    const char *retorno_modelo_actual = obtener_ultimo_retorno_formateado();
                    if (retorno_modelo_actual != NULL)
                    {
                        if (acumular_texto_con_separador(&acumulador_modelos, retorno_modelo_actual, GG_caracter_para_confirmacion_o_error[2]) != RET_OK)
                        {
                            resultado = RET_ERROR_GENERIC;
                            detalle_resultado = "Error al acumular retorno de modelo ventas.";
                        }
                    }
                }
                else if (strcmp(sub_opcion[0], "compras") == 0) // si la sub-operacion es "compras"
                {
                    resultado = modelo_compra(sub_opcion[1]); // ejecuta el modelo de compra; ejemplo sub_opcion[1]: "XYZ987¶5§Proveedor1"
                    detalle_resultado = RET_IS_OK(resultado) ? "Compra procesada." : "Fallo en proceso de compra.";
                    const char *retorno_modelo_actual = obtener_ultimo_retorno_formateado();
                    if (retorno_modelo_actual != NULL)
                    {
                        if (acumular_texto_con_separador(&acumulador_modelos, retorno_modelo_actual, GG_caracter_para_confirmacion_o_error[2]) != RET_OK)
                        {
                            resultado = RET_ERROR_GENERIC;
                            detalle_resultado = "Error al acumular retorno de modelo compras.";
                        }
                    }
                }
                else if (strcmp(sub_opcion[0], "agregar_producto") == 0) // si la sub-operacion es "agregar_producto"
                {
                    resultado = modelo_agregarProducto(sub_opcion[1]); // ejecuta el modelo de agregar producto; ejemplo sub_opcion[1]: "producto⊓2¶contenido⊓3¶tipo_medida⊓4¶precio_venta⊓5⊓no_predeterminado¶..."
                    detalle_resultado = RET_IS_OK(resultado) ? "Producto agregado." : "No se pudo agregar producto.";
                    const char *retorno_modelo_actual = obtener_ultimo_retorno_formateado();
                    if (retorno_modelo_actual != NULL)
                    {
                        if (acumular_texto_con_separador(&acumulador_modelos, retorno_modelo_actual, GG_caracter_para_confirmacion_o_error[2]) != RET_OK)
                        {
                            resultado = RET_ERROR_GENERIC;
                            detalle_resultado = "Error al acumular retorno de modelo agregar_producto.";
                        }
                    }
                }
                else // sub-operacion desconocida dentro de op_tienda
                {
                    printf("Opción no válida: %s\n", sub_opcion[0]); // muestra la sub-opcion invalida; ejemplo: "Opción no válida: eliminar_tienda"
                    resultado = RET_ERROR_GENERIC;                   // marca error
                    detalle_resultado = "Sub-opcion de op_tienda no valida.";
                    free(detalle_capa_modelo);
                    detalle_capa_modelo = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[1], "error en este modelo llamado op_tienda", detalle_resultado);
                }
            }
            else // el split no dio suficientes partes (falta el "§" o los datos)
            {
                printf("Sub-opcion incompleta en op_tienda.\n");
                resultado = RET_ERROR_GENERIC;
                detalle_resultado = "Sub-opcion incompleta en op_tienda.";
                free(detalle_capa_modelo);
                detalle_capa_modelo = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[1], "error en este modelo llamado op_tienda", detalle_resultado);
            }

            free_split(sub_opcion); // libera el arreglo de sub-opciones
        }

        // nivel programador aqui se podra usar en un futuro directamente talves el tex_bas o algo asi para hablar directamente con el sistema y hacer cosas que solo el programador puede hacer como revisar errores del sistema o cosas asi
        if (nivel_del_usuario_espacio == 0) // solo entra si el nivel es 0 (programador/administrador maximo del sistema)
        {

            if (strcmp(opciones[0], "administracion_espacio") == 0) // si el comando es "administracion_espacio"
            {
                if (!opciones[1]) // verifica que exista la sub-operacion
                {
                    printf("Falta sub-opcion en administracion_espacio.\n");
                    free_split(opciones);
                    if (estado_out != NULL)
                    {
                        *estado_out = RET_ERROR_GENERIC;
                    }
                    return construir_retorno_estandar(RET_ERROR_GENERIC, GG_caracter_para_confirmacion_o_error[0], "error en el conmutador", "Falta sub-opcion en administracion_espacio.");
                }

                sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]); // divide por "§"; ejemplo: "crear_espacio§nom_espacio⊓ferreteria_dan¶..." → sub_opcion[0]="crear_espacio", sub_opcion[1]="nom_espacio⊓ferreteria_dan¶..."

                if (sub_opcion && sub_opcion[0] && sub_opcion[1]) // verifica que hay al menos dos partes
                {
                    imprimirMensaje_para_depurar("%s\n", sub_opcion[0]); // ejemplo: "crear_espacio"
                    imprimirMensaje_para_depurar("%s\n", sub_opcion[1]); // ejemplo: "nom_espacio⊓ferreteria_dan¶usuario_de_negocio⊓administrador_negocio¶..."

                    if (strcmp(sub_opcion[0], "crear_espacio") == 0) // si la sub-operacion es "crear_espacio"
                    {
                        char *direccion_archivo_espacios = NULL;                                                                                             // guardara la ruta del archivo de espacios
                        if (concatenar_formato_separado_por_variable(&direccion_archivo_espacios, NULL, "%s\\%s", GG_archivos[0][0], GG_archivos[0][2]) < 0) // construye la ruta; ejemplo resultado: "espacios\\archivo_espacios.txt"
                        {
                            free_split(sub_opcion);
                            free_split(opciones);
                            if (estado_out != NULL)
                            {
                                *estado_out = RET_ERROR_GENERIC;
                            }
                            return construir_retorno_estandar(RET_ERROR_GENERIC, GG_caracter_para_confirmacion_o_error[0], "error en el conmutador", "Error al preparar archivo de espacios.");
                        }

                        imprimirMensaje_para_depurar("%s\n", direccion_archivo_espacios);                                            // ejemplo: "espacios\\archivo_espacios.txt"
                        crearArchivo(direccion_archivo_espacios, GG_archivos[0][1]);                                                 // crea el archivo de espacios si no existe, con su cabecera definida en GG_archivos[0][1]
                        imprimirMensaje_para_depurar("%s\n", sub_opcion[1]);                                                         // muestra los parametros del espacio a crear
                        resultado = modelo_administracion_espacios_crear_espacio(sub_opcion[1]);                                     // ejecuta la creacion del espacio con los parametros; ejemplo sub_opcion[1]: "nom_espacio⊓ferreteria_dan¶usuario_de_negocio⊓administrador_negocio¶contraseña_de_negocio⊓54321"
                        detalle_resultado = RET_IS_OK(resultado) ? "Espacio creado correctamente." : "No se pudo crear el espacio."; // mensaje segun resultado
                        const char *retorno_modelo_actual = obtener_ultimo_retorno_formateado();
                        if (retorno_modelo_actual != NULL)
                        {
                            if (acumular_texto_con_separador(&acumulador_modelos, retorno_modelo_actual, GG_caracter_para_confirmacion_o_error[2]) != RET_OK)
                            {
                                resultado = RET_ERROR_GENERIC;
                                detalle_resultado = "Error al acumular retorno de modelo crear_espacio.";
                            }
                        }
                        free(direccion_archivo_espacios); // libera la ruta construida
                    }
                    else // sub-operacion de administracion_espacio desconocida
                    {
                        printf("Sub-opcion no valida en administracion_espacio: %s\n", sub_opcion[0]); // ejemplo: "Sub-opcion no valida en administracion_espacio: borrar_espacio"
                        resultado = RET_ERROR_GENERIC;
                        detalle_resultado = "Sub-opcion no valida en administracion_espacio.";
                        free(detalle_capa_modelo);
                        detalle_capa_modelo = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[1], "error en este modelo llamado administracion_espacio", detalle_resultado);
                    }
                }
                else // el split no dio suficientes partes
                {
                    printf("Sub-opcion incompleta en administracion_espacio.\n");
                    resultado = RET_ERROR_GENERIC;
                    detalle_resultado = "Sub-opcion incompleta en administracion_espacio.";
                    free(detalle_capa_modelo);
                    detalle_capa_modelo = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[1], "error en este modelo llamado administracion_espacio", detalle_resultado);
                }

                free_split(sub_opcion); // libera sub-opciones
            }

            else if (opciones && strcmp(opciones[0], "procesos_generales") == 0) // si el comando es "procesos_generales" (operaciones contables generales)
            {
                // entrada salidad de dinero
                // SOLO CON EL DINERO - NO CON PRODUCTOS NI CON SERVICIOS SOLO CON EL DINERO
                // pero talves impuestos y todo lo que un administrador y contador utilizaria lo mas general en realidad no se si esto iria aqui o en otro dedicado a eso
                resultado = RET_OK; // por ahora marca exito; logica pendiente de implementar
                detalle_resultado = "Proceso general ejecutado.";
                free(detalle_capa_proceso);
                detalle_capa_proceso = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[4], "todo salio bien en este proseso llamado procesos_generales", detalle_resultado);
            }

            else if (opciones && strcmp(opciones[0], "procesos_sistema") == 0) // si el comando es "procesos_sistema" (comunicacion directa con el sistema, solo programador)
            {
                // aqui se habla directamente con el sistema solo el programador
                resultado = RET_OK; // por ahora marca exito; logica pendiente de implementar
                detalle_resultado = "Proceso de sistema ejecutado.";
                free(detalle_capa_proceso);
                detalle_capa_proceso = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[4], "todo salio bien en este proseso llamado procesos_sistema", detalle_resultado);
            }
        }
    }
    else // usuario sin nivel valido (nivel -1): credenciales incorrectas o no tiene acceso al espacio
    {
        resultado = RET_ERROR_GENERIC; // marca error
        detalle_resultado = "Permisos insuficientes o credenciales invalidas.";
    }

    free_split(opciones);   // libera el arreglo de opciones al final de la funcion
    if (estado_out != NULL) // si se paso un puntero para recibir el estado
    {
        *estado_out = resultado; // guarda el resultado final (RET_OK o RET_ERROR_GENERIC) en el puntero del llamador
    }

    if (acumulador_modelos != NULL) // si hubo uno o varios modelos ejecutados, el conmutador devuelve esa cadena como detalle principal
    {
        retorno_conmutador = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[0], RET_IS_OK(resultado) ? "todo salio bien en el conmutador" : "error en el conmutador", acumulador_modelos); // arma el retorno final del conmutador incrustando todos los modelos separados por ⛐
    }
    else if (detalle_capa_modelo != NULL) // si no hubo acumulador pero si un detalle individual de modelo, usa ese detalle
    {
        retorno_conmutador = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[0], RET_IS_OK(resultado) ? "todo salio bien en el conmutador" : "error en el conmutador", detalle_capa_modelo); // arma el retorno final usando un solo modelo como detalle
    }
    else if (detalle_capa_proceso != NULL) // si la ruta fue directa a proceso, reutiliza ese detalle como extra del conmutador
    {
        retorno_conmutador = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[0], RET_IS_OK(resultado) ? "todo salio bien en el conmutador" : "error en el conmutador", detalle_capa_proceso); // arma el retorno final reutilizando el detalle de proceso
    }
    else // si no existe detalle de capas internas, devuelve el mensaje general acumulado en detalle_resultado
    {
        retorno_conmutador = construir_retorno_estandar(resultado, GG_caracter_para_confirmacion_o_error[0], RET_IS_OK(resultado) ? "todo salio bien en el conmutador" : "error en el conmutador", detalle_resultado); // usa el texto general como ultimo respaldo del retorno final
    }

    free(detalle_capa_modelo);
    free(detalle_capa_proceso);
    free(acumulador_modelos);
    return retorno_conmutador; // retorna formato estandarizado del conmutador
}

/*
 * Uso: Ejecuta extraer_datos_transferencia de forma segura.
 * Entrada ejemplo: extraer_datos_transferencia("SISTEMA_QU1R30N┴NEXOPORTALARCANO■op_tienda~...■PREGUNTAS_WS¤", &prog, &cmd, &espejo)
 */
static int extraer_datos_transferencia(const char *linea_transferencia,
                                       char **programa_respuesta_out,
                                       char **comando_out,
                                       char **info_espejo_out)
{
    char **partes_transferencia = NULL; // arreglo con las 3 columnas divididas por "■"; ejemplo: ["SISTEMA_QU1R30N┴NEXOPORTALARCANO", "op_tienda~...", "PREGUNTAS_WS¤"]
    char **partes_comando = NULL;       // arreglo con DESTINO y ORIGEN divididos por "┴"; ejemplo: ["SISTEMA_QU1R30N", "NEXOPORTALARCANO"]
    int total_partes_transferencia = 0; // cantidad de columnas encontradas al dividir por "■"; debe ser minimo 3
    int total_partes_comando = 0;       // cantidad de partes al dividir la columna 0 por "┴"; debe ser minimo 2

    if (linea_transferencia == NULL ||    // verifica que la linea de entrada no sea nula
        programa_respuesta_out == NULL || // verifica que el puntero de salida del emisor no sea nulo
        comando_out == NULL ||            // verifica que el puntero de salida del comando no sea nulo
        info_espejo_out == NULL)          // verifica que el puntero de salida del espejo no sea nulo
    {
        return RET_INVALID_ARG; // retorna codigo de argumento invalido
    }

    *programa_respuesta_out = NULL; // inicializa a nulo por seguridad
    *comando_out = NULL;            // inicializa a nulo por seguridad
    *info_espejo_out = NULL;        // inicializa a nulo por seguridad

    /* Formato: ID_DESTINO■ID_ORIGEN┴COMANDO■ESPEJO
       [0]="■" separa columnas, [1]="┴" separa DESTINO de ORIGEN */
    total_partes_transferencia = split(linea_transferencia, GG_caracter_para_transferencia_entre_archivos[0], &partes_transferencia); // divide por "■"; ejemplo entrada: "SISTEMA_QU1R30N┴NEXOPORTALARCANO■op_tienda~...■PREGUNTAS_WS¤"
    if (total_partes_transferencia >= 3 && partes_transferencia != NULL &&                                                            // necesita al menos 3 columnas
        partes_transferencia[0] != NULL && partes_transferencia[1] != NULL && partes_transferencia[2] != NULL)                        // ninguna columna puede ser nula
    {
        /* Separar "ID_DESTINO┴ID_ORIGEN" → ["ID_DESTINO", "ID_ORIGEN"] */
        total_partes_comando = split(partes_transferencia[0], GG_caracter_para_transferencia_entre_archivos[1], &partes_comando); // divide por "┴"; ejemplo: "SISTEMA_QU1R30N┴NEXOPORTALARCANO" → ["SISTEMA_QU1R30N", "NEXOPORTALARCANO"]
        if (total_partes_comando >= 2 && partes_comando != NULL &&                                                                // necesita al menos 2 partes
            partes_comando[0] != NULL && strcmp(partes_comando[0], GG_id_programa) == 0 &&                                        // el destino debe ser este programa: "SISTEMA_QU1R30N"
            partes_comando[1] != NULL)                                                                                            // el origen debe existir
        {
            *programa_respuesta_out = variable_string("%s", partes_comando[1]); /* ID_ORIGEN: quien envio el comando; ejemplo: "NEXOPORTALARCANO" */
            *comando_out = variable_string("%s", partes_transferencia[1]);      /* COMANDO: cuerpo del comando; ejemplo: "op_tienda~agregar_producto§..." */
            *info_espejo_out = variable_string("%s", partes_transferencia[2]);  /* ESPEJO: se retornara intacto al emisor; ejemplo: "PREGUNTAS_WS¤" */

            free_split(partes_comando);       // libera el arreglo de destino/origen
            free_split(partes_transferencia); // libera el arreglo de columnas

            if (*programa_respuesta_out == NULL || *comando_out == NULL || *info_espejo_out == NULL) // verifica que todos los malloc funcionaron
            {
                free(*programa_respuesta_out); // libera lo que se haya asignado
                free(*comando_out);
                free(*info_espejo_out);
                *programa_respuesta_out = NULL; // deja los punteros en nulo
                *comando_out = NULL;
                *info_espejo_out = NULL;
                return RET_ERROR_GENERIC; // retorna error de memoria
            }

            return RET_OK; // todo salio bien; los 3 punteros de salida tienen sus valores
        }
    }

    free_split(partes_comando);       // libera si se asigno antes del fallo
    free_split(partes_transferencia); // libera si se asigno antes del fallo
    return RET_NOT_FOUND;             // la linea no era para este programa o el formato era incorrecto
}

/*
 * Uso: Punto de entrada principal del programa en Windows/Linux.
 * Entrada ejemplo: se ejecuta directamente; no recibe argumentos de linea de comandos
 */
int main()
{
    inicializacion(); // crea los archivos del sistema si no existen y registra este programa en banderas.txt

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

    char **retorno_comando = NULL;                                                                        // arreglo donde se guardaran las lineas del archivo de entrada dirigidas a este programa
    int retorno_numero_lineas = 0;                                                                        // cantidad de lineas/comandos encontrados
    int estado_monitoreo = datos_recibidos_a_procesar_y_borrar(&retorno_comando, &retorno_numero_lineas); // lee archivo_entrada.txt y extrae comandos para este programa; retorna 1=hay comandos, 0=sin comandos, -1=error

    imprimirMensaje_para_depurar("Lineas detectadas en archivo de entrada: %d\n", retorno_numero_lineas); // ejemplo: "Lineas detectadas en archivo de entrada: 2"

    if (estado_monitoreo == 1 && retorno_comando != NULL) // solo entra si hay al menos un comando valido
    {
        for (int i = 0; i < retorno_numero_lineas; i++) // recorre cada comando encontrado
        {
            char *programa_respuesta = NULL;           // ID del programa que envio el comando; ejemplo: "NEXOPORTALARCANO"
            char *comando_para_conmutar = NULL;        // cuerpo del comando a ejecutar; ejemplo: "op_tienda~agregar_producto§producto⊓2¶..."
            char *info_espejo = NULL;                  // informacion espejo que se devuelve intacta al emisor; ejemplo: "PREGUNTAS_WS¤"
            char *respuesta_conmutador = NULL;         // texto resultado de ejecutar el comando; ejemplo: "Producto agregado."
            int estado_conmutador = RET_ERROR_GENERIC; // estado del resultado; valor inicial: -1 (error)

            imprimirMensaje_para_depurar("\n\nComando monitoreado[%d]: %s\n", i, retorno_comando[i]); // ejemplo: "Comando monitoreado[0]: SISTEMA_QU1R30N┴NEXOPORTALARCANO■op_tienda~...■PREGUNTAS_WS¤"

            // 1) El main recibe comandos ya extraidos por monitoreo.
            // 2) Se separa cada comando para obtener destino/comando/espejo.
            if (RET_IS_OK(extraer_datos_transferencia(retorno_comando[i],     // linea completa del archivo de entrada
                                                      &programa_respuesta,    // recibira: "NEXOPORTALARCANO"
                                                      &comando_para_conmutar, // recibira: "op_tienda~agregar_producto§..."
                                                      &info_espejo)))         // recibira: "PREGUNTAS_WS¤"
            {
                // 2) Manda el comando a conmutador para ejecutar operaciones.
                respuesta_conmutador = conmutador(comando_para_conmutar, &estado_conmutador); // ejecuta el comando y obtiene el texto de resultado; ejemplo: "Producto agregado."

                imprimirMensaje_para_depurar("Respuesta del conmutador: %s\n", respuesta_conmutador); // ejemplo: "Respuesta del conmutador: Producto agregado."
                // 3) El resultado textual de conmutador se envia por respuesta.
                respuesta(respuesta_conmutador, programa_respuesta, info_espejo); // escribe en archivo_salida.txt; formato: "NEXOPORTALARCANO┴SISTEMA_QU1R30N■Producto agregado.■PREGUNTAS_WS¤"
            }

            finalizar_comando_procesado(retorno_comando[i], estado_conmutador); // borra la linea del archivo de entrada; si hay error la guarda en errores_de_com.txt
            free(respuesta_conmutador);                                         // libera el texto de respuesta
            free(programa_respuesta);                                           // libera el ID del emisor
            free(comando_para_conmutar);                                        // libera el comando
            free(info_espejo);                                                  // libera el espejo
        }
        free_lineas(retorno_comando, retorno_numero_lineas); // libera todos los strings del arreglo de comandos
    }

    modelo_delay_ms("1000"); // espera 1000 milisegundos antes de terminar; da tiempo al sistema de archivos para procesar los cambios

    return 0; // programa termino correctamente
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

/*
 * Uso: Ejecuta inicializacion de forma segura.
 * Entrada ejemplo: inicializacion()
 */
void inicializacion(void)
{
    /* TODO: En PIC inicializar uart/USB cuando esté implementado */
    /* Por ahora: stub vacío */
}

/*
 * Uso: Ejecuta conmutador de forma segura.
 * Entrada ejemplo: conmutador(texto_prueba, estado_out)
 */
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
    return variable_string("%s", "Stub PIC: comando aceptado.");
}

/*
 * Uso: Ejecuta main de forma segura.
 * Entrada ejemplo: main()
 */
int main(void)
{
    /* Paso a paso: validar entradas, procesar y manejar errores. */
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
    return variable_string("%s", "Stub por defecto: comando aceptado.");
}

int main(void)
{
    inicializacion();
    return 0;
}

#endif /* Fin compilación condicional */