#include <stdio.h>
#include <string.h> /* strcmp, etc. */

#include "CLASE_QU1R30N.h"

/* los encabezados incluidos en CLASE ya aportan los prototipos necesarios */

/* apuntadores simples a las arreglos definidos en var_fun_GG.c
   se usan así porque GG_caracter_separacion es un "char *[]"
   no un arreglo fijo; el doble puntero permite indexar con G_caracter_separacion[i] */
char **G_caracter_separacion = GG_caracter_separacion;
char **G_caracter_separacion_funciones_espesificas = GG_caracter_separacion_funciones_espesificas;

/* los archivos son en realidad un puntero a un arreglo de dos punteros a char.
   NO deben declararse como "char **[2]" ni "char ***[2]" porque eso crearía
   un arreglo en esta unidad de traducción en lugar de un alias al arreglo
   original. usamos char *(*G_archivos)[2] para que el tipo coincida con el
   extern declarado en el header y podamos hacer G_archivos[i][j]. */
char *(*G_archivos)[2] = GG_archivos;
char *(*G_archivos_registros)[2] = GG_archivos_registros;

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
            n_opciones++;
    }

    if (opciones && n_opciones >= 2 && strcmp(opciones[0], "op_tienda") == 0)
    {
        char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas[1]);
        int n_sub = 0;
        if (sub_opcion)
            while (sub_opcion[n_sub])
                n_sub++;

        if (n_sub >= 2)
        {
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
        "op_tienda~agregar_producto§1¶2§3¶4¶5¶6¶7¶8¶9",
        "op_tienda~ventas§ABC123¶2§SucursalX",
        "op_tienda~compras§XYZ987¶5§Proveedor1",
        NULL};

    for (int i = 0; ejemplos[i]; i++)
    {
        printf("Ejecutando comando: %s\n", ejemplos[i]);
        conmutador((char *)ejemplos[i]);
    }

    modelo_delay_ms("1000");

    return 0;
}