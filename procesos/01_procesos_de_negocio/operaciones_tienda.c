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
    concatenar_formato_separado_por_variable(&fila, "|", "%s%.2f%s%.2f%s%.2f%.2f%s%s%.2f%s%s%s%s%s%s%s%s%s%.2f%s%s%s%s%s%.2f%s%s%s%s%s", // une todos los campos del producto separados por "|"; ejemplo resultado: "Leche|1.00|L|25.50|123456|50.00|..."
                                             producto, contenido, tipo_medida, precio_venta, cod_barras, cantidad, costo_compra, proveedor, grupo, cant_x_paquet, es_paquete, codbar_paquete_e_id, cod_bar_individual_es_paq_e_id, ligar_prod_sab, impuestos, ingredientes, caducidad, ultimo_mov, sucur_vent, claf_prod, dir_img_inter, dir_img_comp, info_extra, proceso_crear, dir_vid_proc_crear, tiempo_fabricacion, indices_dia_registro_produc_vendido, indices_mes_registro_produc_vendido, indices_anio_registro_produc_vendido, ultima_venta, indices_total_registro_produc_vendido);

    // si la concatenacion fallo, no hay nada que guardar
    if (!fila) {return;}

    char *ruta = NULL; // ruta destino del inventario
    // obtiene la ruta exacta del inventario
    if (obtener_ruta_inventario(dir_espacio, &ruta) < 0){free(fila);return;}

    // genera la cabecera del inventario
    char *cabecera_inventario = columnas_concatenadas(GG_ventana_emergente_productos, 0, 1, GG_caracter_separacion[0]);
    if (!cabecera_inventario){free(ruta);free(fila);return;}

    imprimirMensaje_para_depurar("\nruta: %s\n", ruta);
    imprimirMensaje_para_depurar("\n\ncabecera: %s\n", cabecera_inventario);
    imprimirMensaje_para_depurar("\n\nfila: %s\n", fila);
    
    // arma el argumento para agregar_info_dividida: ruta╬fila╬columnas
    char *datos_divididos = NULL;
    if (concatenar_formato_separado_por_variable(&datos_divididos, NULL, "%s%s%s%s%s",
                                                 ruta,
                                                 GG_caracter_separacion_funciones_espesificas[3],
                                                 fila,
                                                 GG_caracter_separacion_funciones_espesificas[3],
                                                 cabecera_inventario) < 0)
    {free(cabecera_inventario);free(ruta);free(fila);return;}

    imprimirMensaje_para_depurar("\n\ndatos: %s\n", datos_divididos);    

    // agrega el producto al inventario (crea el archivo si no existe)
    char *respuesta = agregar_info_dividida(datos_divididos);
    
    free(respuesta);free(datos_divididos);free(cabecera_inventario);free(ruta);free(fila);

}

// Venta
/*
 * Uso: Ejecuta venta de forma segura.
 * Entrada ejemplo: venta(codigo, cantidad, sucursal, dir_espacio)
 */
int venta(char *codigo, int cantidad, char *sucursal, char *dir_espacio)
{
    (void)sucursal;

    // valida parametros esenciales
    if (!codigo || cantidad <= 0 || !dir_espacio)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // resuelve el archivo de inventario del espacio y trabaja sobre su fila real
    char *ruta_inventario = NULL; // inventario destino
    // obtiene la ruta exacta del inventario
    if (obtener_ruta_inventario(dir_espacio, &ruta_inventario) < 0)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    char *fila_encontrada = NULL; // copia de la fila encontrada
    // busca el producto por codigo
    int indice_fila = buscar_fila(ruta_inventario, 4, codigo, &fila_encontrada);
    if (indice_fila < 0 || !fila_encontrada)
    {
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    char **partes = NULL; // columnas de la fila
    // separa la fila en columnas
    int total_partes = split(fila_encontrada, GG_caracter_separacion[0], &partes);
    // si no hay suficientes columnas, aborta
    if (total_partes <= 5 || !partes)
    {
        if (partes)
        {
            free_split(partes);
        }
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    float cantidad_actual = 0.0f; // stock actual
    // convierte la cantidad actual a numero
    if (texto_a_float_seguro(partes[5], &cantidad_actual) < 0)
    {
        free_split(partes);
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    float nueva_cantidad = cantidad_actual - (float)cantidad;
    if (nueva_cantidad < 0.0f)
    {
        free_split(partes);
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // actualiza la cantidad y deja trazabilidad básica del movimiento
    char *nuevo_texto = NULL; // cantidad nueva en texto
    // formatea la cantidad restante
    if (concatenar_formato_separado_por_variable(&nuevo_texto, NULL, "%.2f", nueva_cantidad) < 0)
    {
        free_split(partes);
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // escribe la cantidad nueva en la columna de stock
    editar_celda(ruta_inventario, 4, codigo, 5, nuevo_texto);

    char *fecha_actual = (char *)malloc(20); // buffer de fecha
    if (fecha_actual)
    {
        // reutiliza la funcion de operacion de compu
        fechaActual(fecha_actual, "%Y-%m-%d");
        // fecha del ultimo movimiento
        editar_celda(ruta_inventario, 4, codigo, 17, fecha_actual);
        // sucursal de la venta
        editar_celda(ruta_inventario, 4, codigo, 18, sucursal ? sucursal : "");
        // ultima venta registrada
        editar_celda(ruta_inventario, 4, codigo, 29, fecha_actual);

        float total_vendido = 0.0f; // acumulado total vendido
        // intenta leer el acumulado anterior
        if (partes[30] && texto_a_float_seguro(partes[30], &total_vendido) == 0)
        {
            char *total_vendido_texto = NULL; // nuevo acumulado
            // incrementa el total vendido
            if (concatenar_formato_separado_por_variable(&total_vendido_texto, NULL, "%.2f", total_vendido + (float)cantidad) == 0)
            {
                // escribe el total vendido actualizado
                editar_celda(ruta_inventario, 4, codigo, 30, total_vendido_texto);
                free(total_vendido_texto);
            }
        }

        free(fecha_actual);
    }

    free(nuevo_texto);
    free_split(partes);
    free(fila_encontrada);
    free(ruta_inventario);
    RETORNAR_PROCESO_ESTANDAR(0);
}

// Compra
/*
 * Uso: Ejecuta compra de forma segura.
 * Entrada ejemplo: compra(codigo, cantidad, proveedor, dir_espacio)
 */
int compra(char *codigo, int cantidad, char *proveedor, char *dir_espacio)
{
    (void)proveedor;

    // valida parametros esenciales
    if (!codigo || cantidad <= 0 || !dir_espacio)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // resuelve el archivo de inventario del espacio y deja lista la fila a modificar
    char *ruta_inventario = NULL; // inventario destino
    // obtiene la ruta exacta del inventario
    if (obtener_ruta_inventario(dir_espacio, &ruta_inventario) < 0)
    {
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    char *fila_encontrada = NULL; // copia de la fila encontrada
    // busca el producto por codigo
    int indice_fila = buscar_fila(ruta_inventario, 4, codigo, &fila_encontrada);
    if (indice_fila < 0 || !fila_encontrada)
    {
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    char **partes = NULL; // columnas de la fila
    // separa la fila en columnas
    int total_partes = split(fila_encontrada, GG_caracter_separacion[0], &partes);
    // si no hay suficientes columnas, aborta
    if (total_partes <= 5 || !partes)
    {
        if (partes)
        {
            free_split(partes);
        }
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    float cantidad_actual = 0.0f; // stock actual
    // convierte la cantidad actual a numero
    if (texto_a_float_seguro(partes[5], &cantidad_actual) < 0)
    {
        free_split(partes);
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    float nueva_cantidad = cantidad_actual + (float)cantidad;
    // incrementa existencias y registra el ultimo movimiento
    char *nuevo_texto = NULL; // cantidad nueva en texto
    // formatea la cantidad nueva
    if (concatenar_formato_separado_por_variable(&nuevo_texto, NULL, "%.2f", nueva_cantidad) < 0)
    {
        free_split(partes);
        free(fila_encontrada);
        free(ruta_inventario);
        RETORNAR_PROCESO_ESTANDAR(-1);
    }

    // escribe la cantidad nueva en la columna de stock
    editar_celda(ruta_inventario, 4, codigo, 5, nuevo_texto);

    char *fecha_actual = (char *)malloc(20); // buffer de fecha
    if (fecha_actual)
    {
        // reutiliza la funcion de operacion de compu
        fechaActual(fecha_actual, "%Y-%m-%d");
        // fecha del ultimo movimiento
        editar_celda(ruta_inventario, 4, codigo, 17, fecha_actual);
        // actualiza proveedor si vino uno nuevo
        if (proveedor && proveedor[0])
        {
            editar_celda(ruta_inventario, 4, codigo, 8, proveedor);
        }
        free(fecha_actual);
    }

    free(nuevo_texto);
    free_split(partes);
    free(fila_encontrada);
    free(ruta_inventario);
    RETORNAR_PROCESO_ESTANDAR(0);
}

// Editar precio
/*
 * Uso: Ejecuta editarPrecio de forma segura.
 * Entrada ejemplo: editarPrecio(codigo, precio, proveedor, dir_espacio)
 */
int editarPrecio(char *codigo, char *precio, char *proveedor, char *dir_espacio)
{
    // valida parametros esenciales
    if (!codigo || !precio || !dir_espacio)
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
    if (concatenar_formato_separado_por_variable(&precio_nuevo, NULL, "%.2f", precio_decimal) < 0)
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

    // actualiza precio y, si se recibe, tambien el proveedor asociado
    // escribe el nuevo precio
    editar_celda(ruta_inventario, 4, codigo, 4, precio_nuevo);
    // escribe el proveedor cuando viene lleno
    if (proveedor && proveedor[0])
    {
        editar_celda(ruta_inventario, 4, codigo, 8, proveedor);
    }

    free(precio_nuevo);
    free(ruta_inventario);
    RETORNAR_PROCESO_ESTANDAR(0);
}