#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

const char* GG_caracter_separacion[] = { "|", "°", "¬", "╦", "╔" };

const char* GG_archivos[][2] = {
    { "inventario.txt",
      "ID|Producto|Contenido|TipoMedida|PrecioVenta|CodBarras|Cantidad|CostoCompra|Proveedor|Col10|Col11|Col12|Col13|Col14|Col15|Col16|Col17|Fecha" }
};


const char* GG_archivos_registros[][2] = {
    { "registros_ventas.txt", "" },
    { "registros_compras.txt", "" }
};
