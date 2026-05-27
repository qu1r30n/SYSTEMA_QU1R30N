/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - stdlib.h: Memoria dinamica, conversiones y utilidades generales
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - ../../CLASE_QU1R30N.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h: Dependencia interna del proyecto
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h: Dependencia interna del proyecto
 */
#include "../../cabeceras/cabeceras_procesos/01_cabeceras_procesos_de_negocios/operaciones_tienda.h"
#include "../../CLASE_QU1R30N.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_compu.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h"
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int obtener_ruta_inventario(char *dir_espacio, char **ruta_inventario)
{
    // valida parametros de entrada
    if (!dir_espacio || !ruta_inventario)
    {
        return -1;
    }

    *ruta_inventario = NULL; // deja la salida limpia

    char *base_limpia = NULL;       // base del espacio
    char *nombre_archivo = NULL;    // nombre temporal
    char *extencion_archivo = NULL; // extension temporal
    // separa la ruta para quedarse con la base
    int separacion_ok = desfragmentar_direccion(dir_espacio, &base_limpia, &nombre_archivo, &extencion_archivo);

    // si no quedo una base util, usa el valor original
    if (separacion_ok != 0 || base_limpia == NULL || base_limpia[0] == '\0' || extencion_archivo == NULL || extencion_archivo[0] == '\0')
    {
        free(base_limpia);
        base_limpia = NULL;
    }

    // libera auxiliares temporales
    free(nombre_archivo);
    free(extencion_archivo);

    // usa la ruta tal cual si no hubo base limpia
    if (base_limpia == NULL)
    {
        // duplica la ruta recibida
        if (concatenar_formato_separado_por_variable(&base_limpia, NULL, "%s", dir_espacio) < 0)
        {
            return -1;
        }
    }

    // asegura separador final en la base
    if (base_limpia[0] != '\0')
    {
        size_t largo_base = strlen(base_limpia);
        // agrega barra final si falta
        if (base_limpia[largo_base - 1] != '\\' && base_limpia[largo_base - 1] != '/')
        {
            char *base_con_sep = NULL;
            // construye la base con separador final
            if (concatenar_formato_separado_por_variable(&base_con_sep, NULL, "%s%s", base_limpia, "\\") < 0)
            {
                free(base_limpia);
                return -1;
            }

            free(base_limpia);
            base_limpia = base_con_sep;
        }
    }

    // arma la ruta final del inventario
    if (concatenar_formato_separado_por_variable(ruta_inventario, NULL, "%sCONFIG\\INF\\INVENTARIO\\INVENTARIO.TXT", base_limpia) < 0)
    {
        free(base_limpia);
        return -1;
    }

    free(base_limpia);
    return 0;
}

// Leer inventario
/*
 * Uso: Ejecuta leerInventario de forma segura.
 * Entrada ejemplo: leerInventario(inventario, maxProductos, dir_espacio)
 */
int leerInventario(char inventario[][COLUMNAS][256], int maxProductos, char *dir_espacio)
{
    // valida parametros principales
    if (!inventario || maxProductos <= 0 || !dir_espacio)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    char *ruta_inventario = NULL; // ruta final del inventario
    // calcula la ruta exacta del archivo
    if (obtener_ruta_inventario(dir_espacio, &ruta_inventario) < 0)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    int total_lineas = 0; // total de lineas leidas
    // carga el archivo completo en memoria
    char **lineas = leer_archivo(ruta_inventario, &total_lineas);
    // si no hay archivo o esta vacio, devuelve cero
    if (!lineas || total_lineas <= 0)
    {
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(0);
    }

    int cantidad_productos = 0; // productos cargados
    // salta la cabecera y recorre las filas reales
    for (int i = 1; i < total_lineas && cantidad_productos < maxProductos; i++)
    {
        // ignora lineas vacias
        if (!lineas[i] || lineas[i][0] == '\0')
        {
            continue;
        }

        char **partes = NULL; // columnas de una fila
        // separa la fila por columnas
        int total_partes = split(lineas[i], GG_caracter_separacion[0], &partes);
        // si no pudo separar, salta la fila
        if (total_partes <= 0 || !partes)
        {
            if (partes)
            {
                free_split(partes);
            }
            continue;
        }

        for (int j = 0; j < COLUMNAS; j++)
        {
            inventario[cantidad_productos][j][0] = '\0'; // limpia cada celda
        }

        // copia cada campo al arreglo destino
        for (int j = 0; j < COLUMNAS && j < total_partes; j++)
        {
            snprintf(inventario[cantidad_productos][j], 256, "%s", partes[j] ? partes[j] : "");
        }

        // libera columnas temporales
        free_split(partes);
        cantidad_productos++;
    }

    // libera todo lo leido
    free_lineas(lineas, total_lineas);
    free(ruta_inventario);
    RETORNAR_PROCESO_ESTANDAR(cantidad_productos);
}

// Guardar inventario
/*
 * Uso: Ejecuta guardarInventario de forma segura.
 * Entrada ejemplo: guardarInventario(inventario, n, dir_espacio)
 */
void guardarInventario(char inventario[][COLUMNAS][256], int n, char *dir_espacio)
{
    // valida parametros de entrada
    if (!inventario || n < 0 || !dir_espacio)
    {
        return;
    }

    char *ruta_inventario = NULL; // ruta de salida
    // calcula la ruta destino
    if (obtener_ruta_inventario(dir_espacio, &ruta_inventario) < 0)
    {
        return;
    }

    // genera la cabecera del archivo
    char *cabecera = columnas_concatenadas(GG_ventana_emergente_productos, 0, 1, GG_caracter_separacion[0]);
    if (!cabecera)
    {
        free(ruta_inventario);
        return;
    }

    // crea el archivo si no existe
    crearArchivo(ruta_inventario, cabecera);

    int total_lineas = n + 1; // cabecera + productos
    // reserva el arreglo de lineas a guardar
    char **lineas = (char **)malloc(sizeof(char *) * total_lineas);
    if (!lineas)
    {
        free(cabecera);
        free(ruta_inventario);
        return;
    }

    lineas[0] = cabecera;
    // arma cada fila del inventario
    for (int i = 0; i < n; i++)
    {
        char *fila = NULL; // fila dinamica
        for (int j = 0; j < COLUMNAS; j++)
        {
            // agrega separador entre columnas
            if (j > 0)
            {
                if (concatenar_formato_separado_por_variable(&fila, NULL, "%s", GG_caracter_separacion[0]) < 0)
                {
                    free(fila);
                    for (int k = 0; k < i; k++)
                    {
                        free(lineas[k + 1]);
                    }
                    free(lineas);
                    free(ruta_inventario);
                    return;
                }
            }

            // agrega el valor de la celda actual
            if (concatenar_formato_separado_por_variable(&fila, NULL, "%s", inventario[i][j]) < 0)
            {
                free(fila);
                for (int k = 0; k < i; k++)
                {
                    free(lineas[k + 1]);
                }
                free(lineas);
                free(ruta_inventario);
                return;
            }
        }

        lineas[i + 1] = fila;
    }

    // guarda el archivo completo ya reconstruido
    guardar_archivo(ruta_inventario, lineas, total_lineas);

    for (int i = 1; i < total_lineas; i++)
    {
        free(lineas[i]);
    }
    free(lineas);
    free(ruta_inventario);
}

// Buscar producto
/*
 * Uso: Ejecuta buscarProducto de forma segura.
 * Entrada ejemplo: buscarProducto(inventario, n, codigo, dir_espacio)
 */
int buscarProducto(char inventario[][COLUMNAS][256], int n, char *codigo, char *dir_espacio)
{
    (void)dir_espacio;

    // valida parametros clave
    if (!inventario || !codigo || n <= 0){RETORNAR_PROCESO_ESTANDAR(-1);}

    // busca por la columna del codigo de barras
    for (int i = 0; i < n; i++)
    {
        if (strcmp(inventario[i][4], codigo) == 0)
        {
            RETORNAR_PROCESO_ESTANDAR(i);
        }
    }

    RETORNAR_PROCESO_ESTANDAR(-1);
}

// Agregar producto
/*
 * Uso: Ejecuta agregarProducto de forma segura.
 * Entrada ejemplo: agregarProducto(producto, ..., dir_espacio)
 */
void agregarProducto(char *producto, float contenido, char *tipo_medida, float precio_venta, char *cod_barras, float cantidad, float costo_compra, char *proveedor, char *grupo, float cant_x_paquet, char *es_paquete, char *codbar_paquete_e_id, char *cod_bar_individual_es_paq_e_id, char *ligar_prod_sab, char *impuestos, char *ingredientes, char *caducidad, char *ultimo_mov, char *sucur_vent, float claf_prod, char *dir_img_inter, char *dir_img_comp, char *info_extra, char *proceso_crear, char *dir_vid_proc_crear, float tiempo_fabricacion, char *indices_dia_registro_produc_vendido, char *indices_mes_registro_produc_vendido, char *indices_anio_registro_produc_vendido, char *ultima_venta, char *indices_total_registro_produc_vendido,
                     char *dir_espacio) // ruta del espacio de negocio donde se guardara el producto; ejemplo: "espacios\\20260330113640_ferreteria_dan\\"
{
    // valida que se haya recibido la ruta del espacio
    if (!dir_espacio){return;}

    char *fila = NULL; // fila completa a guardar

    // arma la fila completa del producto
    concatenar_formato_separado_por_variable(&fila, "|", "%s%.3f%s%.3f%s%.3f%.3f%s%s%.3f%s%s%s%s%s%s%s%s%s%.3f%s%s%s%s%s%.3f%s%s%s%s%s", // une todos los campos del producto separados por "|"; ejemplo resultado: "Leche|1.00|L|25.50|123456|50.00|..."
                                             producto, contenido, tipo_medida, precio_venta, cod_barras, cantidad, costo_compra, proveedor, grupo, cant_x_paquet, es_paquete, codbar_paquete_e_id, cod_bar_individual_es_paq_e_id, ligar_prod_sab, impuestos, ingredientes, caducidad, ultimo_mov, sucur_vent, claf_prod, dir_img_inter, dir_img_comp, info_extra, proceso_crear, dir_vid_proc_crear, tiempo_fabricacion, indices_dia_registro_produc_vendido, indices_mes_registro_produc_vendido, indices_anio_registro_produc_vendido, ultima_venta, indices_total_registro_produc_vendido);

    // si la concatenacion fallo, no hay nada que guardar
    if (!fila) {return;}

    char *ruta = NULL; // ruta destino del inventario
    // obtiene la ruta exacta del inventario
    if (obtener_ruta_inventario(dir_espacio, &ruta) < 0){free(fila);return;}

    // genera la cabecera del inventario
    char *cabecera_inventario = columnas_concatenadas(GG_ventana_emergente_productos, 0, 1, GG_caracter_separacion[1]);
    if (!cabecera_inventario){free(ruta);free(fila);return;}

    imprimirMensaje_para_depurar("\nruta: %s\n", ruta);
    imprimirMensaje_para_depurar("\n\ncabecera: %s\n", cabecera_inventario);
    imprimirMensaje_para_depurar("\n\nfila: %s\n", fila);

    // agrega el producto al inventario (crea el archivo si no existe)
    char *respuesta = agregar_info_dividida(ruta, fila, cabecera_inventario);
    
    free(respuesta);free(cabecera_inventario);free(ruta);free(fila);

}

// Venta
/*
 * Uso: Ejecuta venta de forma segura.
 * Entrada ejemplo: venta(codigo, cantidad, sucursal, id, dir_espacio)
 * id: si no es NULL ni vacio, se verifica que el registro con ese id tenga el mismo codigo;
 *     si coincide se usa directo; si no, se cae a busqueda por codigo de barras.
 */
int venta(char *codigo, float cantidad, char *sucursal, char *id, char *dir_espacio)
{

    imprimirMensaje_para_depurar("\nventa: \ncodigo=%s, \ncantidad=%.3f, \nsucursal=%s, \nid=%s, \ndir_espacio=%s\n", codigo, cantidad, sucursal, id ? id : "", dir_espacio);

    // valida parametros esenciales
    if (!codigo || cantidad <= 0 || !dir_espacio){RETORNAR_PROCESO_ESTANDAR(-1);}

    // resuelve el archivo de inventario del espacio y trabaja sobre su fila real
    char *ruta_inventario = NULL;
    if (obtener_ruta_inventario(dir_espacio, &ruta_inventario) < 0){RETORNAR_PROCESO_ESTANDAR(-1);}

    char *id_resuelto   = NULL; // id confirmado del registro a operar
    char *fila_de_stock = NULL; // fila completa para validar el stock

    // si viene id, verifica que el registro tenga el mismo codigo de barras (col 4)
    if (id && id[0])
    {
        char *res_sel = seleccionar_id_info_dividida(ruta_inventario, id);
        if (res_sel)
        {
            char **p_sel = NULL;
            int    n_sel = split(res_sel, GG_caracter_para_confirmacion_o_error[0], &p_sel);
            free(res_sel);
            if (n_sel >= 2 && p_sel && p_sel[0][0] == '1')
            {
                char **cols_id = NULL;
                int    n_c     = split(p_sel[1], GG_caracter_separacion[0], &cols_id);
                if (n_c > 4 && cols_id && strcmp(cols_id[4], codigo) == 0)
                {
                    // el id corresponde al mismo codigo: usar directo
                    concatenar_formato_separado_por_variable(&id_resuelto,   NULL, "%s", id);
                    concatenar_formato_separado_por_variable(&fila_de_stock, NULL, "%s", p_sel[1]);
                }
                if (cols_id){free_split(cols_id);}
            }
            if (p_sel){free_split(p_sel);}
        }
    }

    // si no se resolvio por id (no vino, era invalido o no coincidio), busca por codigo de barras
    if (!id_resuelto)
    {
        char *resultado_busqueda = buscar_info_dividida(ruta_inventario, codigo, 5, -1);
        imprimirMensaje_para_depurar("\nresultado_busqueda: %s\n", resultado_busqueda ? resultado_busqueda : "NULL");
        if (!resultado_busqueda){free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);}

        char **partes_bus = NULL;
        int n_bus = split(resultado_busqueda, GG_caracter_para_confirmacion_o_error[0], &partes_bus);
        
        free(resultado_busqueda);

        if (n_bus < 3 || !partes_bus || partes_bus[0][0] != '1')
        {
            if (partes_bus){free_split(partes_bus);}free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);
        }

        concatenar_formato_separado_por_variable(&id_resuelto,   NULL, "%s", partes_bus[2]);
        concatenar_formato_separado_por_variable(&fila_de_stock, NULL, "%s", partes_bus[1]);
        free_split(partes_bus);
    }

    // verifica el stock antes de decrementar
    char **cols_fila = NULL;
    int n_cols = split(fila_de_stock, GG_caracter_separacion[0], &cols_fila);
    free(fila_de_stock);
    if (n_cols <= 5 || !cols_fila)
    {
        if (cols_fila){free_split(cols_fila);}free(id_resuelto);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);
    }

    float stock_actual = 0.0f;
    if (texto_a_float_seguro(cols_fila[5], &stock_actual) < 0 || stock_actual < cantidad)
    {
        free_split(cols_fila);free(id_resuelto);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);
    }
    free_split(cols_fila);

    // arma los argumentos: decrementa col 5 (stock) e incrementa col 30 (total_vendido)
    char *cant_neg  = NULL;
    char *cant_pos  = NULL;
    char *cols_inc  = NULL;
    char *cants_inc = NULL;

    if (concatenar_formato_separado_por_variable(&cant_neg, NULL, "%.3f", -(double)cantidad) < 0 ||
        concatenar_formato_separado_por_variable(&cant_pos, NULL, "%.3f",  (double)cantidad) < 0 ||
        concatenar_formato_separado_por_variable(&cols_inc, NULL, "6%s30",
            GG_caracter_separacion_funciones_espesificas[4]) < 0 ||
        concatenar_formato_separado_por_variable(&cants_inc, NULL, "%s%s%s",
            cant_neg, GG_caracter_separacion_funciones_espesificas[4], cant_pos) < 0)
    {
        free(cant_neg);free(cant_pos);free(cols_inc);free(cants_inc);free(id_resuelto);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);
    }

    imprimirMensaje_para_depurar("\nruta: %s\nid_res: %s\ncol_inc: %s\ncants_inc: %s\n", ruta_inventario, id_resuelto, cols_inc, cants_inc);
    char *res_inc = incrementa_celda_id_info_dividida(ruta_inventario, id_resuelto, cols_inc, cants_inc);
    free(res_inc);free(cols_inc);free(cants_inc);free(cant_neg);free(cant_pos);

    // actualiza fecha (col 17), sucursal (col 18) y ultima venta (col 29)
    char *fecha_actual = (char *)malloc(20);
    if (fecha_actual)
    {
        fechaActual(fecha_actual, "%Y%m%d");

        char *cols_edit = NULL;
        char *vals_edit = NULL;

        if (concatenar_formato_separado_por_variable(&cols_edit, NULL, "17%s18%s29",
                GG_caracter_separacion_funciones_espesificas[4],
                GG_caracter_separacion_funciones_espesificas[4]) == 0 &&
            concatenar_formato_separado_por_variable(&vals_edit, NULL, "%s%s%s%s%s",
                fecha_actual,
                GG_caracter_separacion_funciones_espesificas[4],
                sucursal ? sucursal : "",
                GG_caracter_separacion_funciones_espesificas[4],
                fecha_actual) == 0)
        {
            char *res_edit = editar_celda_id_info_dividida(ruta_inventario, id_resuelto, cols_edit, vals_edit);
            free(res_edit);
        }

        free(cols_edit);free(vals_edit);free(fecha_actual);
    }

    free(id_resuelto);
    free(ruta_inventario);
    RETORNAR_PROCESO_ESTANDAR(0);
}

// Compra
/*
 * Uso: Ejecuta compra de forma segura.
 * Entrada ejemplo: compra(codigo, cantidad, proveedor, id, dir_espacio)
 */
int compra(char *codigo, float cantidad, char *sucursal, char *id, char *dir_espacio)
{

    imprimirMensaje_para_depurar("\nventa: \ncodigo=%s, \ncantidad=%.3f, \nsucursal=%s, \nid=%s, \ndir_espacio=%s\n", codigo, cantidad, sucursal, id ? id : "", dir_espacio);

    // valida parametros esenciales
    if (!codigo || cantidad <= 0 || !dir_espacio){RETORNAR_PROCESO_ESTANDAR(-1);}

    // resuelve el archivo de inventario del espacio y trabaja sobre su fila real
    char *ruta_inventario = NULL;
    if (obtener_ruta_inventario(dir_espacio, &ruta_inventario) < 0){RETORNAR_PROCESO_ESTANDAR(-1);}

    char *id_resuelto   = NULL; // id confirmado del registro a operar
    char *fila_de_stock = NULL; // fila completa para validar el stock

    // si viene id, verifica que el registro tenga el mismo codigo de barras (col 4)
    if (id && id[0])
    {
        char *res_sel = seleccionar_id_info_dividida(ruta_inventario, id);
        if (res_sel)
        {
            char **p_sel = NULL;
            int    n_sel = split(res_sel, GG_caracter_para_confirmacion_o_error[0], &p_sel);
            free(res_sel);
            if (n_sel >= 2 && p_sel && p_sel[0][0] == '1')
            {
                char **cols_id = NULL;
                int    n_c     = split(p_sel[1], GG_caracter_separacion[0], &cols_id);
                if (n_c > 4 && cols_id && strcmp(cols_id[4], codigo) == 0)
                {
                    // el id corresponde al mismo codigo: usar directo
                    concatenar_formato_separado_por_variable(&id_resuelto,   NULL, "%s", id);
                    concatenar_formato_separado_por_variable(&fila_de_stock, NULL, "%s", p_sel[1]);
                }
                if (cols_id){free_split(cols_id);}
            }
            if (p_sel){free_split(p_sel);}
        }
    }

    // si no se resolvio por id (no vino, era invalido o no coincidio), busca por codigo de barras
    if (!id_resuelto)
    {
        char *resultado_busqueda = buscar_info_dividida(ruta_inventario, codigo, 5, -1);
        imprimirMensaje_para_depurar("\nresultado_busqueda: %s\n", resultado_busqueda ? resultado_busqueda : "NULL");
        if (!resultado_busqueda){free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);}

        char **partes_bus = NULL;
        int n_bus = split(resultado_busqueda, GG_caracter_para_confirmacion_o_error[0], &partes_bus);
        
        free(resultado_busqueda);

        if (n_bus < 3 || !partes_bus || partes_bus[0][0] != '1')
        {
            if (partes_bus){free_split(partes_bus);}free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);
        }

        concatenar_formato_separado_por_variable(&id_resuelto,   NULL, "%s", partes_bus[2]);
        concatenar_formato_separado_por_variable(&fila_de_stock, NULL, "%s", partes_bus[1]);
        free_split(partes_bus);
    }

    // verifica el stock antes de decrementar
    char **cols_fila = NULL;
    int n_cols = split(fila_de_stock, GG_caracter_separacion[0], &cols_fila);
    free(fila_de_stock);
    if (n_cols <= 5 || !cols_fila)
    {
        if (cols_fila){free_split(cols_fila);}free(id_resuelto);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);
    }

    float stock_actual = 0.0f;
    if (texto_a_float_seguro(cols_fila[5], &stock_actual) < 0 || stock_actual < cantidad)
    {
        free_split(cols_fila);free(id_resuelto);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);
    }
    free_split(cols_fila);

    // arma los argumentos: decrementa col 5 (stock) e incrementa col 30 (total_vendido)
    char *cant_neg  = NULL;
    char *cant_pos  = NULL;
    char *cols_inc  = NULL;
    char *cants_inc = NULL;

    if (concatenar_formato_separado_por_variable(&cant_neg, NULL, "%.3f", -(double)cantidad) < 0 ||
        concatenar_formato_separado_por_variable(&cant_pos, NULL, "%.3f",  (double)cantidad) < 0 ||
        concatenar_formato_separado_por_variable(&cols_inc, NULL, "6%s30",
            GG_caracter_separacion_funciones_espesificas[4]) < 0 ||
        concatenar_formato_separado_por_variable(&cants_inc, NULL, "%s%s%s",
            cant_pos, GG_caracter_separacion_funciones_espesificas[4], cant_neg) < 0)
    {
        free(cant_neg);free(cant_pos);free(cols_inc);free(cants_inc);free(id_resuelto);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);
    }

    imprimirMensaje_para_depurar("\nruta: %s\nid_res: %s\ncol_inc: %s\ncants_inc: %s\n", ruta_inventario, id_resuelto, cols_inc, cants_inc);
    char *res_inc = incrementa_celda_id_info_dividida(ruta_inventario, id_resuelto, cols_inc, cants_inc);
    free(res_inc);free(cols_inc);free(cants_inc);free(cant_neg);free(cant_pos);

    // actualiza fecha (col 17), sucursal (col 18) y ultima venta (col 29)
    char *fecha_actual = (char *)malloc(20);
    if (fecha_actual)
    {
        fechaActual(fecha_actual, "%Y%m%d");

        char *cols_edit = NULL;
        char *vals_edit = NULL;

        if (concatenar_formato_separado_por_variable(&cols_edit, NULL, "17%s18%s29",
                GG_caracter_separacion_funciones_espesificas[4],
                GG_caracter_separacion_funciones_espesificas[4]) == 0 &&
            concatenar_formato_separado_por_variable(&vals_edit, NULL, "%s%s%s%s%s",
                fecha_actual,
                GG_caracter_separacion_funciones_espesificas[4],
                sucursal ? sucursal : "",
                GG_caracter_separacion_funciones_espesificas[4],
                fecha_actual) == 0)
        {
            char *res_edit = editar_celda_id_info_dividida(ruta_inventario, id_resuelto, cols_edit, vals_edit);
            free(res_edit);
        }

        free(cols_edit);free(vals_edit);free(fecha_actual);
    }

    free(id_resuelto);
    free(ruta_inventario);
    RETORNAR_PROCESO_ESTANDAR(0);
}

// Editar precio
/*
 * Uso: Ejecuta editarPrecio de forma segura.
 * Entrada ejemplo: editarPrecio(codigo, precio, proveedor, id, dir_espacio)
 * id: si no es NULL ni vacio, se verifica que el registro con ese id tenga el mismo codigo;
 *     si coincide se usa directo; si no, se cae a busqueda por codigo de barras.
 */
int editarPrecio(char *codigo, char *precio, char *proveedor, char *id, char *dir_espacio)
{
    // valida parametros esenciales
    if (!precio || !dir_espacio || ((!codigo || !codigo[0]) && (!id || !id[0])))
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    float precio_decimal = 0.0f; // precio numerico
    // convierte precio de texto a numero
    if (texto_a_float_seguro(precio, &precio_decimal) < 0)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    char *precio_nuevo = NULL; // precio formateado
    // genera el texto final del precio
    if (concatenar_formato_separado_por_variable(&precio_nuevo, NULL, "%.3f", precio_decimal) < 0)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    char *ruta_inventario = NULL; // inventario destino
    // obtiene la ruta exacta del inventario
    if (obtener_ruta_inventario(dir_espacio, &ruta_inventario) < 0)
    {
        free(precio_nuevo);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    char *id_resuelto = NULL; // id final del registro a editar

    // si viene id, verifica que apunte al mismo codigo (si se recibio codigo)
    if (id && id[0])
    {
        char *res_sel = seleccionar_id_info_dividida(ruta_inventario, id);
        if (res_sel)
        {
            char **p_sel = NULL;
            int n_sel = split(res_sel, GG_caracter_para_confirmacion_o_error[0], &p_sel);
            free(res_sel);

            if (n_sel >= 2 && p_sel && p_sel[0][0] == '1')
            {
                int id_valido = 0;

                // si no viene codigo, acepta el id tal cual
                if (!codigo || !codigo[0])
                {
                    id_valido = 1;
                }
                else
                {
                    char **cols_id = NULL;
                    int n_c = split(p_sel[1], GG_caracter_separacion[0], &cols_id);
                    if (n_c > 4 && cols_id && strcmp(cols_id[4], codigo) == 0)
                    {
                        id_valido = 1;
                    }
                    if (cols_id)
                    {
                        free_split(cols_id);
                    }
                }

                if (id_valido)
                {
                    concatenar_formato_separado_por_variable(&id_resuelto, NULL, "%s", id);
                }
            }

            if (p_sel)
            {
                free_split(p_sel);
            }
        }
    }

    // si no se resolvio por id, intenta buscar por codigo de barras
    if (!id_resuelto)
    {
        if (!codigo || !codigo[0])
        {
            free(precio_nuevo);
            free(ruta_inventario);
            RETORNAR_PROCESO_ESTANDAR(-1);
        }

        char *resultado_busqueda = buscar_info_dividida(ruta_inventario, codigo, 5, -1);
        if (!resultado_busqueda)
        {
            free(precio_nuevo);
            free(ruta_inventario);
            RETORNAR_PROCESO_ESTANDAR(-1);
        }

        char **partes_bus = NULL;
        int n_bus = split(resultado_busqueda, GG_caracter_para_confirmacion_o_error[0], &partes_bus);
        free(resultado_busqueda);

        if (n_bus < 3 || !partes_bus || partes_bus[0][0] != '1')
        {
            if (partes_bus)
            {
                free_split(partes_bus);
            }
            free(precio_nuevo);
            free(ruta_inventario);
            RETORNAR_PROCESO_ESTANDAR(-1);
        }

        concatenar_formato_separado_por_variable(&id_resuelto, NULL, "%s", partes_bus[2]);
        free_split(partes_bus);
    }

    // actualiza precio y, si se recibe, tambien el proveedor asociado
    char *cols_edit = NULL;
    char *vals_edit = NULL;

    if (proveedor && proveedor[0])
    {
        if (concatenar_formato_separado_por_variable(&cols_edit, NULL, "4%s4", GG_caracter_separacion_funciones_espesificas[4]) < 0 ||
            concatenar_formato_separado_por_variable(&vals_edit, NULL, "%s%s%s", precio_nuevo, GG_caracter_separacion_funciones_espesificas[4], precio_nuevo) < 0)
        {free(cols_edit);free(vals_edit);free(id_resuelto);free(precio_nuevo);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);}
    }
    else
    {
        if (concatenar_formato_separado_por_variable(&cols_edit, NULL, "4%s4", GG_caracter_separacion_funciones_espesificas[4]) < 0 ||
            concatenar_formato_separado_por_variable(&vals_edit, NULL, "%s%s%s", precio_nuevo, GG_caracter_separacion_funciones_espesificas[4], precio_nuevo) < 0)
        {free(cols_edit);free(vals_edit);free(id_resuelto);free(precio_nuevo);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(-1);}
    }

    char *res_edit = editar_celda_id_info_dividida(ruta_inventario, id_resuelto, cols_edit, vals_edit);
    
    free(res_edit);free(cols_edit);free(vals_edit);free(id_resuelto);free(precio_nuevo);free(ruta_inventario);RETORNAR_PROCESO_ESTANDAR(0);

}