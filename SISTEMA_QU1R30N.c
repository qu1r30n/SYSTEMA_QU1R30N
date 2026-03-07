#include <stdio.h>
#include <string.h> /* strcmp, etc. */

#include "CLASE_QU1R30N.h"

// Inicialización
void inicializacion()
{
    crearArchivo(G_archivos[ARCH_INVENTARIO][0], G_archivos[ARCH_INVENTARIO][1]);
    for (int i = 0; i < 2; i++)
        crearArchivo(G_archivos_registros[i][0], G_archivos_registros[i][1]);
}

void conmutador(char *texto_prueba)
{
    char **opciones = modelo_split(texto_prueba, G_caracter_separacion_funciones_espesificas[0]);
    int n_opciones = 0;
    if (opciones)
    {
        while (opciones[n_opciones])
        {
            imprimirMensaje_para_depurar("%s\n", opciones[n_opciones]); // Imprime el nombre y valor que se van a asignar (para depuración)
            n_opciones++;
        }
    }

    if (opciones && n_opciones >= 2 && strcmp(opciones[0], "op_tienda") == 0)
    {
        char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        char *carga_util = strstr(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        if (carga_util)
        {
            carga_util += strlen(G_caracter_separacion_funciones_espesificas[1]);
        }
        int n_sub = 0;
        if (sub_opcion)
        {
            while (sub_opcion[n_sub])
            {
                imprimirMensaje_para_depurar("%s\n", sub_opcion[n_sub]); // Imprime el nombre y valor que se van a asignar (para depuración)
                n_sub++;
            }
        }
        if (n_sub >= 2)
        {
            if (strcmp(sub_opcion[0], "ventas") == 0)
            {
                modelo_venta(carga_util ? carga_util : sub_opcion[1]);
            }
            else if (strcmp(sub_opcion[0], "compras") == 0)
            {
                modelo_compra(carga_util ? carga_util : sub_opcion[1]);
            }
            else if (strcmp(sub_opcion[0], "agregar_producto") == 0)
            {
                modelo_agregarProducto(carga_util ? carga_util : sub_opcion[1]);
            }
            else
            {
                printf("Opción no válida: %s\n", sub_opcion[0]);
            }
        }

        free_split(sub_opcion);
    }

    else if (opciones && n_opciones >= 2 && strcmp(opciones[0], "op_restaurante") == 0)
    {
        char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        char *carga_util = strstr(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        if (carga_util)
        {
            carga_util += strlen(G_caracter_separacion_funciones_espesificas[1]);
        }
        int n_sub = 0;
        if (sub_opcion)
        {
            while (sub_opcion[n_sub])
            {
                imprimirMensaje_para_depurar("%s\n", sub_opcion[n_sub]);
                n_sub++;
            }
        }

        if (n_sub >= 2)
        {
            if (strcmp(sub_opcion[0], "registrar_platillo") == 0)
            {
                modelo_restaurante_registrar_platillo(carga_util ? carga_util : sub_opcion[1]);
            }
            else if (strcmp(sub_opcion[0], "registrar_pedido") == 0)
            {
                modelo_restaurante_registrar_pedido(carga_util ? carga_util : sub_opcion[1]);
            }
            else
            {
                printf("Opción no válida: %s\n", sub_opcion[0]);
            }
        }

        free_split(sub_opcion);
    }

    else if (opciones && n_opciones >= 2 && strcmp(opciones[0], "op_banco") == 0)
    {
        char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        char *carga_util = strstr(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        if (carga_util)
        {
            carga_util += strlen(G_caracter_separacion_funciones_espesificas[1]);
        }

        int n_sub = 0;
        if (sub_opcion)
        {
            while (sub_opcion[n_sub])
            {
                n_sub++;
            }
        }

        if (n_sub >= 2)
        {
            if (strcmp(sub_opcion[0], "registrar_cuenta") == 0)
            {
                modelo_banco_registrar_cuenta(carga_util ? carga_util : sub_opcion[1]);
            }
            else if (strcmp(sub_opcion[0], "depositar") == 0)
            {
                modelo_banco_depositar(carga_util ? carga_util : sub_opcion[1]);
            }
            else if (strcmp(sub_opcion[0], "retirar") == 0)
            {
                modelo_banco_retirar(carga_util ? carga_util : sub_opcion[1]);
            }
            else
            {
                printf("Opción no válida: %s\n", sub_opcion[0]);
            }
        }

        free_split(sub_opcion);
    }

    else if (opciones && n_opciones >= 2 && strcmp(opciones[0], "op_feria") == 0)
    {
        char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        char *carga_util = strstr(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        if (carga_util)
        {
            carga_util += strlen(G_caracter_separacion_funciones_espesificas[1]);
        }

        int n_sub = 0;
        if (sub_opcion)
        {
            while (sub_opcion[n_sub])
            {
                n_sub++;
            }
        }

        if (n_sub >= 2)
        {
            if (strcmp(sub_opcion[0], "registrar_premio") == 0)
            {
                modelo_feria_registrar_premio(carga_util ? carga_util : sub_opcion[1]);
            }
            else if (strcmp(sub_opcion[0], "canjear_premio") == 0)
            {
                modelo_feria_canjear_premio(carga_util ? carga_util : sub_opcion[1]);
            }
            else
            {
                printf("Opción no válida: %s\n", sub_opcion[0]);
            }
        }

        free_split(sub_opcion);
    }

    else if (opciones && n_opciones >= 2 && strcmp(opciones[0], "op_renta_equipos") == 0)
    {
        char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        char *carga_util = strstr(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        if (carga_util)
        {
            carga_util += strlen(G_caracter_separacion_funciones_espesificas[1]);
        }

        int n_sub = 0;
        if (sub_opcion)
        {
            while (sub_opcion[n_sub])
            {
                n_sub++;
            }
        }

        if (n_sub >= 2)
        {
            if (strcmp(sub_opcion[0], "registrar_equipo") == 0)
            {
                modelo_renta_registrar_equipo(carga_util ? carga_util : sub_opcion[1]);
            }
            else if (strcmp(sub_opcion[0], "registrar_alquiler") == 0)
            {
                modelo_renta_registrar_alquiler(carga_util ? carga_util : sub_opcion[1]);
            }
            else
            {
                printf("Opción no válida: %s\n", sub_opcion[0]);
            }
        }

        free_split(sub_opcion);
    }

    else if (opciones && n_opciones >= 2 && strcmp(opciones[0], "op_tex_bas") == 0)
    {
        char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        char *carga_util = strstr(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        if (carga_util)
        {
            carga_util += strlen(G_caracter_separacion_funciones_espesificas[1]);
        }

        int n_sub = 0;
        if (sub_opcion)
        {
            while (sub_opcion[n_sub])
            {
                n_sub++;
            }
        }

        if (n_sub >= 2)
        {
            char *payload = carga_util ? carga_util : sub_opcion[1];

            if (strcmp(sub_opcion[0], "agregar_fila") == 0)
            {
                modelo_agregar_fila(payload);
            }
            else if (strcmp(sub_opcion[0], "editar_fila") == 0)
            {
                modelo_editar_fila(payload);
            }
            else if (strcmp(sub_opcion[0], "eliminar_fila") == 0)
            {
                modelo_eliminar_fila(payload);
            }
            else if (strcmp(sub_opcion[0], "editar_celda") == 0)
            {
                modelo_editar_celda(payload);
            }
            else if (strcmp(sub_opcion[0], "incrementar_celda") == 0)
            {
                modelo_incrementar_celda(payload);
            }
            else if (strcmp(sub_opcion[0], "editar_columna") == 0)
            {
                modelo_editar_columna_completa(payload);
            }
            else if (strcmp(sub_opcion[0], "eliminar_columna") == 0)
            {
                modelo_eliminar_columna(payload);
            }
            else if (strcmp(sub_opcion[0], "agregar_columna") == 0)
            {
                modelo_agregar_columna(payload);
            }
            else
            {
                printf("Opción no válida: %s\n", sub_opcion[0]);
            }
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

    free_split(opciones);
}

int main()
{
    inicializacion();

    /* ejemplos de comandos que el sistema entrega al modelo */
    const char *ejemplos[] = {
        //"op_tienda~agregar_producto§1¶Leche§1L¶unidad¶10¶123456¶100¶50¶ProveedorA",
        "op_tienda~agregar_producto§id⊓1¶producto⊓2¶contenido⊓3¶tipo_medida⊓4¶precio_venta⊓5¶cod_barras⊓6¶cantidad⊓7¶costo_compra⊓8¶proveedor⊓9",
        "op_tienda~ventas§ABC123¶2§SucursalX",
        "op_tienda~compras§XYZ987¶5§Proveedor1",
        "op_restaurante~registrar_platillo§codigo⊓P001¶nombre⊓Hamburguesa¶precio⊓95.5¶stock⊓30",
        "op_restaurante~registrar_pedido§mesa⊓MESA3¶codigo⊓P001¶cantidad⊓2",
        "op_banco~registrar_cuenta§cuenta⊓C0001¶titular⊓JUAN¶saldo_inicial⊓5000",
        "op_banco~depositar§cuenta⊓C0001¶monto⊓250.50",
        "op_banco~retirar§cuenta⊓C0001¶monto⊓100¶motivo⊓CAJA_CHICA",
        "op_feria~registrar_premio§codigo⊓PR01¶nombre⊓PELUCHE¶puntos⊓120¶stock⊓10",
        "op_feria~canjear_premio§usuario⊓USR100¶codigo⊓PR01¶cantidad⊓2",
        "op_renta_equipos~registrar_equipo§codigo⊓EQ01¶nombre⊓BOCINA¶costo_dia⊓350¶stock⊓4",
        "op_renta_equipos~registrar_alquiler§cliente⊓ANA¶codigo⊓EQ01¶dias⊓3¶cantidad⊓1",
        "op_tex_bas~agregar_fila§ruta⊓demo_tex_bas.txt¶fila⊓1|usuario_demo|tipo¬1°tipo¬2╦sub_info|contrasena",
        "op_tex_bas~editar_celda§ruta⊓demo_tex_bas.txt¶col_buscar⊓0¶valor_buscar⊓1¶col_editar⊓1¶nuevo⊓usuario_editado",
        "op_tex_bas~incrementar_celda§ruta⊓demo_tex_bas.txt¶col_buscar⊓0¶valor_buscar⊓1¶col_editar⊓0¶incremento⊓1",
        NULL};

    for (int i = 0; ejemplos[i]; i++)
    {
        printf("Ejecutando comando: %s\n", ejemplos[i]);
        conmutador((char *)ejemplos[i]);
    }

    modelo_delay_ms("1000");

    return 0;
}