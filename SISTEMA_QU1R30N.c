#include <stdio.h>
#include "cabeceras/tex_bas.h"
#include "cabeceras/operaciones_tienda.h"

int main() {
    inicializacion();

    int opcion;
    do {
        printf("\n--- POS TIENDA ---\n");
        printf("1. Venta\n2. Compra\n3. Agregar producto\n0. Salir\nOpcion: ");
        scanf("%d",&opcion);
        getchar();

        if(opcion==1){
            char codigo[50], sucursal[50];
            int cantidad;
            printf("Codigo de barras: "); scanf("%s",codigo);
            printf("Cantidad: "); scanf("%d",&cantidad);
            printf("Sucursal: "); scanf("%s",sucursal);
            if(venta(codigo,cantidad,sucursal)) printf("Venta realizada\n");
            else printf("Stock insuficiente o codigo invalido\n");
        }
        else if(opcion==2){
            char codigo[50], proveedor[50];
            int cantidad;
            printf("Codigo de barras: "); scanf("%s",codigo);
            printf("Cantidad: "); scanf("%d",&cantidad);
            printf("Proveedor: "); scanf("%s",proveedor);
            if(compra(codigo,cantidad,proveedor)) printf("Compra realizada\n");
            else printf("Codigo invalido\n");
        }
        else if(opcion==3){
            char id[50], producto[100], contenido[50], tipo_medida[50];
            char precio_venta[50], cod_barras[50], cantidad[50], costo_comp[50], proveedor[50];
            printf("ID: "); scanf("%s",id);
            printf("Producto: "); scanf("%s",producto);
            printf("Contenido: "); scanf("%s",contenido);
            printf("Tipo medida: "); scanf("%s",tipo_medida);
            printf("Precio venta: "); scanf("%s",precio_venta);
            printf("Codigo barras: "); scanf("%s",cod_barras);
            printf("Cantidad: "); scanf("%s",cantidad);
            printf("Costo compra: "); scanf("%s",costo_comp);
            printf("Proveedor: "); scanf("%s",proveedor);
            agregarProducto(id,producto,contenido,tipo_medida,precio_venta,cod_barras,cantidad,costo_comp,proveedor);
            printf("Producto agregado\n");
        }

    } while(opcion!=0);

    return 0;
}
