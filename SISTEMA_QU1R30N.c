#include <stdio.h>
#include "cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_tex_bas.h"
#include "cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"

#include "cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"


// Inicialización
void inicializacion() {
    crearArchivo(G_archivos[ARCH_INVENTARIO][0], G_archivos[ARCH_INVENTARIO][1]);
    for(int i=0;i<2;i++)
        crearArchivo(G_archivos_registros[i][0], G_archivos_registros[i][1]);
}


int main() 
{
    //inicializacion();

    char* texto_prueba = "compras|2|3|4|5|6";
// Opción como string con varias acciones separadas por '|'
    char* opcion;

    while(1) { // while true para usar en un futuro
        // Hacemos split de la cadena de opciones
        int n_opciones = 0;
        char** opciones = modelo_split(texto_prueba, "|");
        
        
            if(strcmp(opciones[0], "ventas") == 0) {
                
                venta(opciones[1]);
                
            } 
            else if(strcmp(opciones[0], "compras") == 0) {
                
                compra(opciones[1]);
                
            } 
            else if(strcmp(opciones[0], "agregar_producto") == 0) {
                
                agregarProducto(opciones[1]);
                
            }
            // Puedes agregar más opciones si quieres
        

        free_split(opciones, n_opciones);
    }

    return 0;
}



