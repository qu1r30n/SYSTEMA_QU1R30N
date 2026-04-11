/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - CLASE_QU1R30N.h: Dependencia interna del proyecto
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp, etc. */

#include "CLASE_QU1R30N.h"
#include "cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/ControladorMonitoreoArchivo.h"

// Inicialización
void inicializacion()
{
}

void conmutador(char *texto_prueba)
{
    char **opciones = modelo_split(texto_prueba, G_caracter_separacion_funciones_espesificas[0]);
    if (!opciones || !opciones[0])
    {
        free_split(opciones);
        return;
    }

    imprimirMensaje_para_depurar("\n\n%s\n%s\n%s\n%s", opciones[0], opciones[1], opciones[2], opciones[3]);

    char *texto_permiso = NULL;

    concatenar_formato_separado_por_variable(&texto_permiso, NULL, "nivel_minimo%s1%sruta_archivo%s%s\\%s%s%s%s%s", GG_caracter_separacion_nom_parametro_de_valor[0], G_caracter_separacion_funciones_espesificas[1], GG_caracter_separacion_nom_parametro_de_valor[0], GG_archivos[0][0], GG_archivos[0][2], G_caracter_separacion_funciones_espesificas[1], opciones[2], G_caracter_separacion_funciones_espesificas[1], opciones[2]);

    imprimirMensaje_para_depurar("\n\n%s\n", texto_permiso);

    // La verificación completa de permisos la maneja modelo_checar_permiso.
    // conmutador recibe la respuesta y la direccion del espacio para usarla en su flujo.
    char *retorna_direccion_espacio_negocio = NULL;
    int nivel_del_usuario_espacio = -1;
    int tiene_permiso_espacio = modelo_checar_permiso(texto_permiso, &retorna_direccion_espacio_negocio, &nivel_del_usuario_espacio);

    imprimirMensaje_para_depurar("tiene_permiso_espacio=%d\n", tiene_permiso_espacio);
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
                return;
            }

            char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);

            if (sub_opcion && sub_opcion[0] && sub_opcion[1])
            {
                imprimirMensaje_para_depurar("%s\n", sub_opcion[0]);
                imprimirMensaje_para_depurar("%s\n", sub_opcion[1]);

                if (strcmp(sub_opcion[0], "ventas") == 0)
                {
                    modelo_venta(sub_opcion[1]);
                }
                else if (strcmp(sub_opcion[0], "compras") == 0)
                {
                    modelo_compra(sub_opcion[1]);
                }
                else if (strcmp(sub_opcion[0], "agregar_producto") == 0)
                {
                    modelo_agregarProducto(sub_opcion[1]);
                }
                else
                {
                    printf("Opción no válida: %s\n", sub_opcion[0]);
                }
            }
            else
            {
                printf("Sub-opcion incompleta en op_tienda.\n");
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
                    return;
                }

                char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);

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
                            return;
                        }

                        imprimirMensaje_para_depurar("%s\n", direccion_archivo_espacios);
                        crearArchivo(direccion_archivo_espacios, GG_archivos[0][1]);
                        imprimirMensaje_para_depurar("%s\n", sub_opcion[1]);
                        modelo_administracion_espacios_crear_espacio(sub_opcion[1]);
                        free(direccion_archivo_espacios);
                    }
                    else
                    {
                        printf("Sub-opcion no valida en administracion_espacio: %s\n", sub_opcion[0]);
                    }
                }
                else
                {
                    printf("Sub-opcion incompleta en administracion_espacio.\n");
                }

                free_split(sub_opcion);
            }

            else if (opciones && strcmp(opciones[0], "procesos_generales") == 0)
            {
                // entrada salidad de dinero
                // SOLO CON EL DINERO - NO CON PRODUCTOS NI CON SERVICIOS SOLO CON EL DINERO
                // pero talves impuestos y todo lo que un administrador y contador utilizaria lo mas general en realidad no se si esto iria aqui o en otro dedicado a eso
            }
            else if (opciones && strcmp(opciones[0], "procesos_sistema") == 0)
            {
                // aqui se habla directamente con el sistema solo el programador
            }
        }
    }

    free_split(opciones);
}

int main()
{
    inicializacion();

    char *ruta_archivo_espacios = NULL;

    char *direccion_archivo_espacios = NULL;

    imprimirMensaje_para_depurar("\n\nGG_archivos[0][]: %s\\%s\n", GG_archivos[0][0], GG_archivos[0][2]);
    concatenar_formato_separado_por_variable(&direccion_archivo_espacios, NULL, "%s\\%s", GG_archivos[0][0], GG_archivos[0][2]);
    imprimirMensaje_para_depurar("direccion_archivo_espacios: %s\n\n", direccion_archivo_espacios);
    char *contenido_inicial_archivo_espacio = NULL;
    concatenar_formato_separado_por_variable(&contenido_inicial_archivo_espacio, NULL, "%s\n0%sadministrador_de_espacio%s0%s%s0", GG_archivos[0][1], GG_caracter_separacion[0], GG_caracter_separacion[0], GG_caracter_separacion[0], GG_caracter_separacion[0]);

    crearArchivo(direccion_archivo_espacios, contenido_inicial_archivo_espacio);

    free(ruta_archivo_espacios);
    free(direccion_archivo_espacios);
    free(contenido_inicial_archivo_espacio);

    /* ejemplos de comandos que el sistema entrega al modelo */
    const char *ejemplos[] = {
        //"op_tienda~agregar_producto§1¶Leche§1L¶unidad¶10¶123456¶100¶50¶ProveedorA",
        //"administracion_espacio~crear_espacio§nom_espacio⊓ferreteria_dan¶usuario_de_negocio⊓administrador_negocio¶contraseña_de_negocio⊓54321~id_de_espacio⊓0§usuario_de_espacio⊓administrador_de_espacio§contraseña_de_espacio⊓0",
        "op_tienda~agregar_producto§producto⊓2¶contenido⊓3¶tipo_medida⊓4¶precio_venta⊓5⊓no_predeterminado¶cod_barras⊓6¶cantidad⊓7¶costo_compra⊓8¶proveedor⊓9~id_de_espacio⊓20260330113640_ferreteria_dan~usuario_de_espacio⊓administrador_de_espacio§contraseña_de_espacio⊓12345~usuario_de_negocio⊓administrador_negocio§contraseña_de_negocio⊓54321",
        "op_tienda~ventas§ABC123¶2§SucursalX",
        "op_tienda~compras§XYZ987¶5§Proveedor1",
        NULL};

    char *retorno_comando = NULL;
    int estado_monitoreo = monitoreo_archivo_entrada(&retorno_comando);

    if (estado_monitoreo == 1 && retorno_comando != NULL)
    {
        imprimirMensaje_para_depurar("Comando monitoreado: %s\n", retorno_comando);
        free(retorno_comando);
    }

    for (int i = 0; ejemplos[i]; i++)
    {
        printf("Ejecutando comando: %s\n", ejemplos[i]);
        conmutador((char *)ejemplos[i]);
    }

    modelo_delay_ms("1000");

    return 0;
}