#include <stdio.h>

#include "cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_compu.h"
#include "cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_tex_bas.h"
#include "cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"

#include "cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

const char** G_caracter_separacion = GG_caracter_separacion;
// Inicialización
void inicializacion() 
{
    crearArchivo(G_archivos[ARCH_INVENTARIO][0], G_archivos[ARCH_INVENTARIO][1]);
    for(int i=0;i<2;i++)
        crearArchivo(G_archivos_registros[i][0], G_archivos_registros[i][1]);
}


void procesar_opcion(char* texto_prueba)
{
    int n_opciones = 0;
    char** opciones = modelo_split(texto_prueba, G_caracter_separacion[0]);

    if (strcmp(opciones[0], "op_tienda"))
    {
        char** sub_opcion = modelo_split(texto_prueba, G_caracter_separacion[1]);
        if (sub_opcion == NULL || sub_opcion[0] == NULL)
            return;

        if (strcmp(sub_opcion[0], "ventas") == 0) 
        {
            venta(sub_opcion[1]);
        } 
        else if (strcmp(sub_opcion[0], "compras") == 0) 
        {
            compra(sub_opcion[1]);
        } 
        else if (strcmp(sub_opcion[0], "agregar_producto") == 0) 
        {
            agregarProducto(sub_opcion[1]);
        }
        else 
        {
            printf("Opción no válida: %s\n", sub_opcion[0]);
        }
    }
    else if (strcmp(opciones[0], "procesos_generales"))
    {
        // entrada salidad de dinero
        //SOLO CON EL DINERO - NO CON PRODUCTOS NI CON SERVICIOS SOLO CON EL DINERO 
        //pero talves impuestos y todo lo que un administrador y contador utilizaria lo mas general en realidad no se si esto iria aqui o en otro dedicado a eso
        
    }
    else if (strcmp(opciones[0], "procesos_sistema"))
    {
        //aqui se habla directamente con el sistema solo el programador
    }
    

    free_split(opciones, n_opciones);

}




int main() 
{
    //inicializacion();

    char* texto_prueba = "compras|2|3|4|5|6";

    
    

    // Llamamos al conmutador
    procesar_opcion(texto_prueba);

    
    modelo_delay_ms("1000");       
	


    return 0;
}