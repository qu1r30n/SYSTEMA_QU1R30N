/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - stdio.h: Entrada y salida estandar (printf, fopen, etc.)
 * - stdlib.h: Memoria dinamica, conversiones y utilidades generales
 * - string.h: Manejo de cadenas y memoria (strlen, strcmp, memcpy)
 * - ../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h: Dependencia interna del proyecto
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

int GG_indice_donde_comensar = 1;

char *GG_cantidado_por_archivo = "100";

char *GG_caracter_separacion[] = {"|", "°", "¬", "╦", "╔"};
char *GG_caracter_separacion_2[] = {"⚭", "⚮", "⚯", "⚰", "⚱"};

char *GG_caracter_separacion_funciones_espesificas[] = {"~", "§", "¶", "╬", "╝", "╩", "║", "╗", "┐", "└", "┬", "├", "┼"};
char *GG_caracter_separacion_funciones_espesificas_2[] = {"⚲", "⚳", "⚴", "⚵", "⚶", "⚷", "⚸", "⚺", "⚻", "⚼", "⚿", "⛊", "⛋"};

char *GG_caracter_para_confirmacion_o_error[] = {"╣", "╠"};
char *GG_caracter_para_confirmacion_o_error_2[] = {"⛑", "⛒"};

char *GG_caracter_para_transferencia_entre_archivos[] = {"┴", "■", "¤"};
char *GG_caracter_para_transferencia_entre_archivos_2[] = {"⛕", "⛘", "⛍"};

char *GG_caracter_para_usar_como_enter_y_nuevo_mensaje[] = {"•", "∆"};
char *GG_caracter_para_usar_como_enter_y_nuevo_mensaje_2[] = {"⛙", "⛚"};

char *GG_caracter_separacion_nom_parametro_de_valor[] = {"⊓", "⊔"};
char *GG_caracter_separacion_nom_parametro_de_valor_2[] = {"⊑", "⊒"};

char *GG_caracter_guardado_para_confirmacion[] = {"⛞", "⛝"};

char *GG_id_programa = "SISTEMA_QU1R30N";

#ifdef _WIN32
char *GG_archivos[][3] = {
    {"espacios\\",
     "ID|Usuario|Contraseña|Directorio_Archivo_permisos_usuarios|Nivel",
     "archivo_espacios.txt"},
    {"conexion_arc\\",
     "ID_DESTINO┴ID_ORIGEN■COMANDO■INFORMACION_ESPEJO_NO_SE_MODIFICA", // la informacion espejo regresa esa misma informacion tal y como esta
     "archivo_entrada.txt"},
    {"conexion_arc\\",
     "ID_DESTINO┴ID_ORIGEN■COMANDO■INFORMACION_ESPEJO_NO_SE_MODIFICA", // la informacion espejo regresa esa misma informacion tal y como esta
     "archivo_salida.txt"},
    {"conexion_arc\\",
     NULL,
     "banderas.txt"},
    {NULL, NULL, NULL}};
#else
char *GG_archivos[][3] = {
    {"espacios/",
     "ID|Usuario|Contraseña|Directorio_Archivo_permisos_usuarios|Nivel",
     "archivo_espacios.txt"},
    {"conexion_arc/",
     "ID_DESTINO┴ID_ORIGEN■COMANDO■INFORMACION_ESPEJO_NO_SE_MODIFICA", // la informacion espejo regresa esa misma informacion tal y como esta
     "archivo_entrada.txt"},
    {"conexion_arc/",
     "ID_DESTINO┴ID_ORIGEN■COMANDO■INFORMACION_ESPEJO_NO_SE_MODIFICA", // la informacion espejo regresa esa misma informacion tal y como esta
     "archivo_salida.txt"},
    {NULL, NULL, NULL}};
#endif

char *GG_archivos_registros[][2] = {
    {"registros_ventas.txt", ""},
    {"registros_compras.txt", ""},
    {NULL, NULL}};

/* ===== VARIABLES STRING GLOBALES ===== */

char *GG_variables_string[MAX_VAR_STRING] = {
    "", /* [0] codbar */
    "", /* [1] prov_anterior */
    "", /* [2] provedores_txt */
    "", /* [3] impuesto anterior */
    "", /* [4] impuestos_txt */
    "", /* [5] tipo_medida_producto_anterior */
    ""  /* [6] tipo_medida_producto_txt */
};

/* ===== TABLAS DE CONFIGURACIÓN VENTANAS ===== */

/* Ventana: Datos de Configuración (2 campos) */
const char *GG_ventana_datos_conf[][5] = {
    {"2", "dato_de_configuracion", "", "", "TEXTO"},
    {"2", "descripcion_de_configuracion", "", "", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Productos (33 campos) */
const char *GG_ventana_emergente_productos[][5] = {

    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_PRODUCTO", "", "NOSE", "TEXTO"},
    {"1", "_02_CONTENIDO", "0°SOLO_NUMEROS", "-0", "ENTERO_DECIMAL"},
    {"4", "_03_TIPO_MEDIDA", "NOSE°TODAS_MAYUSCULAS", "NOSE", "TEXTO"},
    {"1", "_04_PRECIO_VENTA", "0°SOLO_NUMEROS", "-0", "ENTERO_DECIMAL"},
    {"2", "_05_COD_BARRAS", "", "NOSE", "TEXTO"},
    {"1", "_06_CANTIDAD", "1°SOLO_NUMEROS", "-0", "ENTERO_DECIMAL"},
    {"1", "_07_COSTO_COMP", "0°SOLO_NUMEROS", "-0", "ENTERO_DECIMAL"},
    {"4", "_08_PROVEDOR", "NOSE°TODAS_MAYUSCULAS", "NOSE¬0", "TEXTO"},
    {"4", "_09_GRUPO", "PRODUCTO_PIEZA", "PRODUCTO_PIEZA", "TEXTO"},
    {"1", "_10_CANT_X_PAQUET", "1°SOLO_NUMEROS", "-0", "ENTERO_DECIMAL"},
    {"4", "_11_ES_PAQUETE", "INDIVIDUAL", "INDIVIDUAL", "TEXTO"},
    {"1", "_12_CODBAR_PAQUETE_E_ID", "", "NOSE_2", "TEXTO"},
    {"1", "_13_COD_BAR_INDIVIDUAL_ES_PAQ_E_ID", "", "NOSE_3¬1", "TEXTO"},
    {"1", "_14_LIGAR_PROD_SAB", "", "NOSE", "TEXTO"},
    {"1", "_15_IMPUESTOS", "REYENO_TEXTBOX_VENTANA_IMPU", "NOSE", "TEXTO"},
    {"1", "_16_INGREDIENTES", "NO_VISIBLE¬PRODUCTO_ELABORADO", "NOSE", "TEXTO"},
    {"1", "_17_CADUCIDAD", "0°SOLO_NUMEROS", "-0", "TEXTO"},
    {"1", "_18_ULTIMO_MOV", "0°SOLO_NUMEROS", "-0", "TEXTO"},
    {"1", "_19_SUCUR_VENT", "", "NOSE¬0", "TEXTO"},
    {"1", "_20_CLAF_PROD", "", "-0", "ENTERO_DECIMAL"},
    {"1", "_21_DIR_IMG_INTER", "", "NOSE", "TEXTO"},
    {"1", "_22_DIR_IMG_COMP", "", "NOSE", "TEXTO"},
    {"1", "_23_INFO_EXTRA", "", "NOSE", "TEXTO"},
    {"1", "_24_PROCESO_CREAR", "NO_VISIBLE", "NOSE", "TEXTO"},
    {"1", "_25_DIR_VID_PROC_CREAR", "", "NOSE", "TEXTO"},
    {"1", "_26_TIEMPO_FABRICACION", "0", "-0", "ENTERO_DECIMAL"},
    {"2", "_27_INDICES_DIA_REGISTRO_PRODUC_VENDIDO", "", "0", "TEXTO"},
    {"2", "_28_INDICES_MES_REGISTRO_PRODUC_VENDIDO", "", "0", "TEXTO"},
    {"2", "_29_INDICES_AÑO_REGISTRO_PRODUC_VENDIDO", "", "0", "TEXTO"},
    {"2", "_30_ULTIMA_VENTA", "", "", "TEXTO"},
    {"2", "_31_INDICES_TOTAL_REGISTRO_PRODUC_VENDIDO", "", "0", "TEXTO"},
    {"2", "_32_NO_PONER_NADA", "", "", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};
/* Ventana: Cosas No Estaban en Inventario (3 campos) */
const char *GG_ventana_COSAS_NO_ESTABAN_INVENTARIO[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_COD_BAR", "", "NOSE", "TEXTO"},
    {"1", "_02_NOMBRE", "", "NOSE", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Proveedores (24 campos) */
const char *GG_ventana_provedor[][5] = {
    {"2", "_00_ID_EMPRESA", "", "-0", "TEXTO"},
    {"1", "_01_NOMBRE_EMPRESA", "", "NOSE", "TEXTO"},
    {"1", "_02_NOMBRE_ENCARGADO", "", "NOSE", "TEXTO"},
    {"1", "_03_DIRECCIÓN_EMPRESA", "", "NOSE", "TEXTO"},
    {"1", "_04_CIUDAD_EMPRESA", "", "NOSE", "TEXTO"},
    {"1", "_05_ESTADO_EMPRESA", "", "NOSE", "TEXTO"},
    {"1", "_06_CÓDIGO_POSTAL", "", "NOSE", "TEXTO"},
    {"1", "_07_PAÍS", "", "NOSE", "TEXTO"},
    {"1", "_08_CORREO_ELECTRÓNICO", "", "NOSE", "TEXTO"},
    {"1", "_09_TELÉFONO_ENCARGADO", "", "NOSE", "TEXTO"},
    {"1", "_10_TELEFONO_EMPRESA", "", "NOSE", "TEXTO"},
    {"1", "_11_TIPO_DE_PROVEEDOR", "", "NOSE", "TEXTO"},
    {"1", "_12_PRODUCTOS_SERVICIOS_SUMINISTRADOS", "", "NOSE", "TEXTO"},
    {"1", "_13_CUENTA_BANCO", "", "NOSE", "TEXTO"},
    {"1", "_14_UBICACIÓN_(GPS)", "", "-0", "TEXTO"},
    {"1", "_15_NOTAS", "", "NOSE", "TEXTO"},
    {"1", "_16_RECORDATORIO", "", "", "TEXTO"},
    {"1", "_17_ACTIVO_O_NO_ACTIVO", "", "ACTIVO", "TEXTO"},
    {"1", "_18_CALIFICACIÓN", "", "0", "TEXTO"},
    {"1", "_19_COMENTARIOS", "", "NOSE", "TEXTO"},
    {"1", "_20_SUCURSALES_QUE_LE_COMPRAN", "", "NOSE", "TEXTO"},
    {"1", "_21_DINERO_A_COMPRARLE", "0°SOLO_NUMEROS", "0", "TEXTO"},
    {"1", "_22_DIAS_DE_PREVENTA", "", "NOSE¬NOSE", "TEXTO"},
    {"1", "_23_DIAS_DE_ENTREGA", "", "NOSE¬NOSE", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Aprendices (32 campos) */
const char *GG_ventana_APRENDICES_E[][5] = {
    {"2", "_00_ID", "", "-0", "TEXTO"},
    {"1", "_01_NOMBRE", "", "NOSE", "TEXTO"},
    {"1", "_02_APELLIDO_PATERNO", "", "NOSE", "TEXTO"},
    {"1", "_03_APELLIDO_MATERNO", "", "NOSE", "TEXTO"},
    {"1", "_04_FECHA_DE_NACIMIENTO", "", "NOSE", "TEXTO"},
    {"1", "_05_GÉNERO", "", "NOSE", "TEXTO"},
    {"1", "_06_DIRECCIÓN", "", "NOSE", "TEXTO"},
    {"1", "_07_CIUDAD", "", "NOSE", "TEXTO"},
    {"1", "_08_ESTADO_PROVINCIA", "", "NOSE", "TEXTO"},
    {"1", "_09_CÓDIGO_POSTAL", "", "NOSE", "TEXTO"},
    {"1", "_10_PAÍS", "", "NOSE", "TEXTO"},
    {"1", "_11_CORREO_ELECTRÓNICO", "", "NOSE", "TEXTO"},
    {"1", "_12_TELÉFONO", "", "NOSE", "TEXTO"},
    {"1", "_13_FECHA_DE_INGRESO", "", "NOSE", "TEXTO"},
    {"1", "_14_SUELDO", "", "NOSE", "TEXTO"},
    {"1", "_15_CARGO", "", "NOSE", "TEXTO"},
    {"1", "_16_ESTADO_DE_CURS_APRENDIS_E", "", "NOSE", "TEXTO"},
    {"1", "_17_SUPERVISOR", "", "NOSE", "TEXTO"},
    {"1", "_18_NOTAS", "", "", "TEXTO"},
    {"1", "_19_AFILIADO", "", "NOSE", "TEXTO"},
    {"1", "_20_FECHA_DE_TERMINACIÓN", "0°SOLO_NUMEROS", "0", "TEXTO"},
    {"1", "_21_MOTIVO_DE_TERMINACIÓN", "", "NOSE", "TEXTO"},
    {"1", "_22_HORAS_TRABAJADAS", "", "NOSE", "TEXTO"},
    {"1", "_23_EVALUACIONES_DE_DESEMPEÑO", "", "NOSE", "TEXTO"},
    {"1", "_24_HABILIDADES_Y_CERTIFICACIONES", "", "NOSE", "TEXTO"},
    {"1", "_25_IDIOMAS", "", "NOSE", "TEXTO"},
    {"1", "_26_FECHA_DE_ÚLTIMA_PROMOCIÓN", "", "NOSE", "TEXTO"},
    {"1", "_27_ID_DEPARTAMENTO", "", "NOSE", "TEXTO"},
    {"1", "_28_HISTORIAL_DE_CAPACITACIÓN", "", "NOSE", "TEXTO"},
    {"1", "_29_ÚLTIMO_AUMENTO_DE_SALARIO", "", "NOSE", "TEXTO"},
    {"1", "_30_TIPO_EMPLEADO", "", "NOSE", "TEXTO"},
    {"1", "_31_RANGO_CALIF", "", "-0", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Afiliados Unificados (8 campos) */
const char *GG_ventana_afiliados_unificados[][5] = {
    {"1", "_00_ID_USUARIO", "", "0", "TEXTO"},
    {"1", "_01_IDP", "", "0╔0╦0¬0╔1╦1", "TEXTO"},
    {"1", "_02_PUNTOS_D_R", "", "0╦0¬0╦0", "TEXTO"},
    {"1", "_03_PUNTOS_D_R_TOTALES", "", "0", "TEXTO"},
    {"1", "_04_DATOS", "", "NOSE", "TEXTO"},
    {"1", "_05_NIVEL", "", "0", "TEXTO"},
    {"1", "_06_ID_HORIZONTAL", "", "0", "TEXTO"},
    {"1", "_07_TIPO_AFILIADO", "", "NOSE", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};
/* Ventana: Niveles Afiliados Unificado (4 campos) */
const char *GG_ventana_niv_afiliados_unificado[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_NIVEL", "", "0", "TEXTO"},
    {"1", "_02_ID_HORIZONTAL", "", "0", "TEXTO"},
    {"1", "_03_VACIOS", "", "", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Sucursales (20 campos) */
const char *GG_ventana_SUCUR[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_NOM_ID_SUCUR", "", "-0", "TEXTO"},
    {"1", "_02_NOMBRE_SUCUR", "", "NOSE", "TEXTO"},
    {"1", "_03_NOMBRE_ENCARGADO", "", "NOSE", "TEXTO"},
    {"1", "_04_DIRECCIÓN_SUCUR", "", "NOSE", "TEXTO"},
    {"1", "_05_CIUDAD_SUCUR", "", "NOSE", "TEXTO"},
    {"1", "_06_ESTADO_SUCUR", "", "NOSE", "TEXTO"},
    {"1", "_07_CÓDIGO_POSTAL", "", "NOSE", "TEXTO"},
    {"1", "_08_PAÍS", "", "NOSE", "TEXTO"},
    {"1", "_09_CORREO_ELECTRÓNICO", "", "NOSE", "TEXTO"},
    {"1", "_10_TELÉFONO_ENCARGADO", "", "NOSE", "TEXTO"},
    {"1", "_11_TELEFONO_SUCUR", "", "NOSE", "TEXTO"},
    {"1", "_12_TIPO_DE_SUCUR", "", "NOSE", "TEXTO"},
    {"1", "_13_PRODUCTOS_SERVICIOS", "", "NOSE", "TEXTO"},
    {"1", "_14_CUENTA_BANCO", "", "NOSE", "TEXTO"},
    {"1", "_15_UBICACIÓN_(GPS)", "", "-0", "TEXTO"},
    {"1", "_16_NOTAS", "", "", "TEXTO"},
    {"1", "_17_RECORDATORIO", "", "NOSE", "TEXTO"},
    {"1", "_18_ACTIVO_O_NO_ACTIVO", "", "NOSE", "TEXTO"},
    {"1", "_19_HORA_ABRIR_CERRAR", "", "NOSE", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Registro Día (11 campos) */
const char *GG_ventana_reg_dia[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_HORA", "", "0", "TEXTO"},
    {"1", "_02_OPERACION", "", "NOSE", "TEXTO"},
    {"1", "_03_TOTAL_IMPUESTO", "", "NOSE╦0", "TEXTO"},
    {"1", "_04_CÓDIGO_PRECIO", "", "NOSE", "TEXTO"},
    {"1", "_05_COMENTARIO", "", "", "TEXTO"},
    {"1", "_06_TOTAL_VENTA", "", "0", "TEXTO"},
    {"1", "_07_TOTAL_COSTO_COMP", "", "0", "TEXTO"},
    {"1", "_08_TOTAL_IMPUESTOS", "", "0", "TEXTO"},
    {"1", "_09_TOTAL_DEDUSIBLES", "", "0", "TEXTO"},
    {"1", "_10_PLATAFORMA", "", "NOSE", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Registro Mes (9 campos) */
const char *GG_ventana_reg_mes[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_DIA", "", "0", "TEXTO"},
    {"1", "_02_OPERACION", "", "NOSE", "TEXTO"},
    {"1", "_03_TOTAL_IMPUESTO", "", "NOSE╦0", "TEXTO"},
    {"1", "_04_COMENTARIO", "", "", "TEXTO"},
    {"1", "_05_TOTAL_VENTA", "", "0", "TEXTO"},
    {"1", "_06_TOTAL_COSTO_COMP", "", "0", "TEXTO"},
    {"1", "_07_TOTAL_IMPUESTOS", "", "0", "TEXTO"},
    {"1", "_08_TOTAL_GANANCIA", "", "0", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Registro Año (9 campos) */
const char *GG_ventana_reg_año[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_MES", "", "0", "TEXTO"},
    {"1", "_02_OPERACION", "", "NOSE", "TEXTO"},
    {"1", "_03_TOTAL_IMPUESTO", "", "NOSE╦0", "TEXTO"},
    {"1", "_04_COMENTARIO", "", "", "TEXTO"},
    {"1", "_05_TOTAL_VENTA", "", "0", "TEXTO"},
    {"1", "_06_TOTAL_COSTO_COMP", "", "0", "TEXTO"},
    {"1", "_07_TOTAL_IMPUESTOS", "", "0", "TEXTO"},
    {"1", "_08_TOTAL_GANANCIA", "", "0", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Registro Total (9 campos) */
const char *GG_ventana_reg_total[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_AÑO", "", "0", "TEXTO"},
    {"1", "_02_OPERACION", "", "NOSE", "TEXTO"},
    {"1", "_03_TOTAL_IMPUESTO", "", "NOSE╦0", "TEXTO"},
    {"1", "_04_COMENTARIO", "", "", "TEXTO"},
    {"1", "_05_TOTAL_VENTA", "", "0", "TEXTO"},
    {"1", "_06_TOTAL_COSTO_COMP", "", "0", "TEXTO"},
    {"1", "_07_TOTAL_IMPUESTOS", "", "0", "TEXTO"},
    {"1", "_08_TOTAL_GANANCIA", "", "0", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Registro Productos Día (12 campos) */
const char *GG_ventana_reg_prod_dia[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_NOMBRE_PRODUCTO", "", "NOSE", "TEXTO"},
    {"1", "_02_CANTIDAD", "", "0", "TEXTO"},
    {"1", "_03_COD_BAR", "", "NOSE", "TEXTO"},
    {"1", "_04_PROVEDORES", "", "NOSE", "TEXTO"},
    {"1", "_05_HISTORIAL", "", "0", "TEXTO"},
    {"1", "_06_RANKING", "", "0", "TEXTO"},
    {"1", "_07_PROMEDIO", "", "0", "TEXTO"},
    {"1", "_08_VECES_SUPERA_PROMEDIO", "", "7", "TEXTO"},
    {"1", "_09_USO_MULTIPLE", "", "", "TEXTO"},
    {"1", "_10_TIPO_PRODUCTO", "", "", "TEXTO"},
    {"1", "_11_NIVEL_NECESIDAD", "", "0", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Registro Productos Mes (12 campos) */
const char *GG_ventana_reg_prod_mes[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_NOMBRE_PRODUCTO", "", "NOSE", "TEXTO"},
    {"1", "_02_CANTIDAD", "", "0", "TEXTO"},
    {"1", "_03_COD_BAR", "", "NOSE", "TEXTO"},
    {"1", "_04_PROVEDORES", "", "NOSE", "TEXTO"},
    {"1", "_05_HISTORIAL", "", "0", "TEXTO"},
    {"1", "_06_RANKING", "", "0", "TEXTO"},
    {"1", "_07_PROMEDIO", "", "0", "TEXTO"},
    {"1", "_08_VECES_SUPERA_PROMEDIO", "", "7", "TEXTO"},
    {"1", "_09_USO_MULTIPLE", "", "", "TEXTO"},
    {"1", "_10_TIPO_PRODUCTO", "", "", "TEXTO"},
    {"1", "_11_NIVEL_NECESIDAD", "", "0", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Registro Productos Año (12 campos) */
const char *GG_ventana_reg_prod_año[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_NOMBRE_PRODUCTO", "", "NOSE", "TEXTO"},
    {"1", "_02_CANTIDAD", "", "0", "TEXTO"},
    {"1", "_03_COD_BAR", "", "NOSE", "TEXTO"},
    {"1", "_04_PROVEDORES", "", "NOSE", "TEXTO"},
    {"1", "_05_HISTORIAL", "", "0", "TEXTO"},
    {"1", "_06_RANKING", "", "0", "TEXTO"},
    {"1", "_07_PROMEDIO", "", "0", "TEXTO"},
    {"1", "_08_VECES_SUPERA_PROMEDIO", "", "7", "TEXTO"},
    {"1", "_09_USO_MULTIPLE", "", "", "TEXTO"},
    {"1", "_10_TIPO_PRODUCTO", "", "", "TEXTO"},
    {"1", "_11_NIVEL_NECESIDAD", "", "0", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Registro Productos Total (12 campos) */
const char *GG_ventana_reg_prod_total[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_NOMBRE_PRODUCTO", "", "NOSE", "TEXTO"},
    {"1", "_02_CANTIDAD", "", "0", "TEXTO"},
    {"1", "_03_COD_BAR", "", "NOSE", "TEXTO"},
    {"1", "_04_PROVEDORES", "", "NOSE", "TEXTO"},
    {"1", "_05_HISTORIAL", "", "0", "TEXTO"},
    {"1", "_06_RANKING", "", "0", "TEXTO"},
    {"1", "_07_PROMEDIO", "", "0", "TEXTO"},
    {"1", "_08_VECES_SUPERA_PROMEDIO", "", "7", "TEXTO"},
    {"1", "_09_USO_MULTIPLE", "", "", "TEXTO"},
    {"1", "_10_TIPO_PRODUCTO", "", "", "TEXTO"},
    {"1", "_11_NIVEL_NECESIDAD", "", "0", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Impuestos (6 campos) */
const char *GG_ventana_IMPUESTOS[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_IMPUESTO", "", "0", "TEXTO"},
    {"1", "_02_PORCENTAGE", "", "0", "TEXTO"},
    {"1", "_03_DESCRIPCION", "", "NOSE", "TEXTO"},
    {"1", "_04_INFO_EXTRA", "", "NOSE", "TEXTO"},
    {"1", "_05_TIPO_IMPUESTO", "", "3", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Deducibles (7 campos) */
const char *GG_ventana_DEDUSIBLES[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_FECHA", "", "0", "TEXTO"},
    {"1", "_02_MONTO", "", "0", "TEXTO"},
    {"1", "_03_DESCRIPCION", "", "NOSE", "TEXTO"},
    {"1", "_04_PROVEDOR", "", "NOSE", "TEXTO"},
    {"1", "_05_ARCHIVO_FACTURA", "", "NOSE", "TEXTO"},
    {"1", "_06_FOLIO", "", "NOSE", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Herramientas (2 campos) */
const char *GG_ventana_HERRAMIENTAS[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_COD_BAR", "", "", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

/* Ventana: Trabajos por Día (8 campos) */
const char *GG_trabajos_dia[][5] = {
    {"2", "_00_ID", "", "-1", "ENTERO_DECIMAL"},
    {"1", "_01_DIA", "", "", "TEXTO"},
    {"1", "_02_ID_TRABAJADOR", "", "", "TEXTO"},
    {"1", "_03_HECHO_O_NO", "", "", "TEXTO"},
    {"1", "_04_CANTIDAD", "", "", "TEXTO"},
    {"1", "_05_COSTO_COMP", "", "", "TEXTO"},
    {"1", "_06_ID_QUIENLOISO", "", "", "TEXTO"},
    {"1", "_07_ID_PROGRAMA", "", "", "TEXTO"},
    {NULL, NULL, NULL, NULL, NULL}};

void RecargarVentanaEmergenteDatosConfiguracion(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteProductos(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergente_Cosas_que_no_estaban(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteProvedor(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteAPRENDICES_E(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteAfiliados_simples(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteAfiliados_complejos(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergente_niv_afiliados_simples(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergente_niv_afiliados_comp(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteAfiliados_unificados(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergente_niv_afiliados_unificado(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteSUCUR(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteRegDia(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteRegMes(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteRegAño(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteRegTotal(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteReg_prod_Dia(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteReg_prod_Mes(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteReg_prod_Año(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteReg_prod_total(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteImpuestos(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergenteDedusibles(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergente_HERRAMIENTAS(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

void RecargarVentanaEmergente_TRABAJOS_DIA(const char *al_finalizar_que_borrar)
{
    if (al_finalizar_que_borrar != NULL && strcmp(al_finalizar_que_borrar, "TODO") == 0)
    {
        for (int i = 0; i < MAX_VAR_STRING; i++)
        {
            if (GG_variables_string[i] != NULL)
            {
                strcpy(GG_variables_string[i], "");
            }
        }
    }
}

/* Función auxiliar para concatenar valores de columnas
   id_columna se pasa para futuras extensiones; actualmente no se usa. */
char *columnas_concatenadas(const char *arreglo[][5], int filas, int id_columna, const char *caracter_separacion)
{
    static char resultado[4096];
    memset(resultado, 0, sizeof(resultado));

    if (!arreglo)
    {
        return resultado;
    }

    if (caracter_separacion == NULL)
    {
        caracter_separacion = GG_caracter_separacion[1];
    }

    if (id_columna < 0 || id_columna >= 5)
    {
        id_columna = 1;
    }

    int total_filas = 0;
    if (filas > 0)
    {
        total_filas = filas;
    }
    else
    {
        while (arreglo[total_filas][0] != NULL)
        {
            total_filas++;
        }
    }

    for (int i = 0; i < total_filas; i++)
    {
        const char *valor = arreglo[i][id_columna];

        if (!valor)
        {
            continue;
        }

        if (resultado[0] != '\0')
        {
            strcat(resultado, caracter_separacion);
        }

        strcat(resultado, valor);
    }

    return resultado;
}

char *GG_direccion_carpetas_base[] = {
    "",
    NULL};

GG_ArchivoBaseNegocio *GG_dir_nom_archivos = NULL;

GG_ArchivoInventarioPendiente *GG_direccion_hacer_inventarios = NULL;

static char *duplicar_texto(const char *txt)
{
    if (!txt)
        return NULL;

    char *salida = (char *)malloc(strlen(txt) + 1);
    if (!salida)
        return NULL;

    strcpy(salida, txt);
    return salida;
}

static char *crear_metadata_archivo_base(const char *columnas)
{
    const char *columnas_seguras = columnas ? columnas : "";
    const char *cantidad_por_archivo = GG_cantidado_por_archivo ? GG_cantidado_por_archivo : "0";
    size_t longitud_total = strlen("ID_TOT|0\nCOLUMNAS|\nCANT_POR_ARCH|") + strlen(columnas_seguras) + strlen(cantidad_por_archivo) + 1;
    char *metadata = (char *)malloc(longitud_total);

    if (!metadata)
    {
        return NULL;
    }

    snprintf(metadata, longitud_total, "ID_TOT|0\nCOLUMNAS|%s\nCANT_POR_ARCH|%s", columnas_seguras, cantidad_por_archivo);
    return metadata;
}

static int agregar_archivo_base_negocio(const char *ruta, const char *cabecera, const char *extra)
{
    int cantidad = 0;
    GG_ArchivoBaseNegocio *tmp = NULL;

    if (GG_dir_nom_archivos)
    {
        while (GG_dir_nom_archivos[cantidad].ruta || GG_dir_nom_archivos[cantidad].cabecera || GG_dir_nom_archivos[cantidad].extra)
        {
            cantidad++;
        }
    }

    tmp = (GG_ArchivoBaseNegocio *)realloc(GG_dir_nom_archivos, sizeof(GG_ArchivoBaseNegocio) * (cantidad + 2));
    if (!tmp)
    {
        return -1;
    }

    GG_dir_nom_archivos = tmp;
    GG_dir_nom_archivos[cantidad].ruta = NULL;
    GG_dir_nom_archivos[cantidad].cabecera = NULL;
    GG_dir_nom_archivos[cantidad].extra = NULL;
    GG_dir_nom_archivos[cantidad + 1].ruta = NULL;
    GG_dir_nom_archivos[cantidad + 1].cabecera = NULL;
    GG_dir_nom_archivos[cantidad + 1].extra = NULL;

    GG_dir_nom_archivos[cantidad].ruta = duplicar_texto(ruta ? ruta : "");
    GG_dir_nom_archivos[cantidad].cabecera = duplicar_texto(cabecera ? cabecera : "");
    GG_dir_nom_archivos[cantidad].extra = duplicar_texto(extra ? extra : "");

    if (!GG_dir_nom_archivos[cantidad].ruta || !GG_dir_nom_archivos[cantidad].cabecera || !GG_dir_nom_archivos[cantidad].extra)
    {
        free(GG_dir_nom_archivos[cantidad].ruta);
        free(GG_dir_nom_archivos[cantidad].cabecera);
        free(GG_dir_nom_archivos[cantidad].extra);
        GG_dir_nom_archivos[cantidad].ruta = NULL;
        GG_dir_nom_archivos[cantidad].cabecera = NULL;
        GG_dir_nom_archivos[cantidad].extra = NULL;
        return -1;
    }

    return 0;
}

static int agregar_archivo_base_negocio_con_columnas(const char *ruta, const char *columnas, const char *extra)
{
    char *metadata = crear_metadata_archivo_base(columnas);
    int resultado;

    if (!metadata)
    {
        return -1;
    }

    resultado = agregar_archivo_base_negocio(ruta, metadata, extra);
    free(metadata);
    return resultado;
}

static int agregar_archivo_inventario(const char *ruta, const char *cabecera)
{
    int cantidad = 0;
    GG_ArchivoInventarioPendiente *tmp = NULL;

    if (GG_direccion_hacer_inventarios)
    {
        while (GG_direccion_hacer_inventarios[cantidad].ruta || GG_direccion_hacer_inventarios[cantidad].cabecera)
        {
            cantidad++;
        }
    }

    tmp = (GG_ArchivoInventarioPendiente *)realloc(GG_direccion_hacer_inventarios, sizeof(GG_ArchivoInventarioPendiente) * (cantidad + 2));
    if (!tmp)
    {
        return -1;
    }

    GG_direccion_hacer_inventarios = tmp;
    GG_direccion_hacer_inventarios[cantidad].ruta = NULL;
    GG_direccion_hacer_inventarios[cantidad].cabecera = NULL;
    GG_direccion_hacer_inventarios[cantidad + 1].ruta = NULL;
    GG_direccion_hacer_inventarios[cantidad + 1].cabecera = NULL;

    GG_direccion_hacer_inventarios[cantidad].ruta = duplicar_texto(ruta ? ruta : "");
    GG_direccion_hacer_inventarios[cantidad].cabecera = duplicar_texto(cabecera ? cabecera : "");

    if (!GG_direccion_hacer_inventarios[cantidad].ruta || !GG_direccion_hacer_inventarios[cantidad].cabecera)
    {
        free(GG_direccion_hacer_inventarios[cantidad].ruta);
        free(GG_direccion_hacer_inventarios[cantidad].cabecera);
        GG_direccion_hacer_inventarios[cantidad].ruta = NULL;
        GG_direccion_hacer_inventarios[cantidad].cabecera = NULL;
        return -1;
    }

    return 0;
}

static void liberar_arreglo_dir_nom_archivos(void)
{
    if (!GG_dir_nom_archivos)
    {
        return;
    }

    for (int i = 0; GG_dir_nom_archivos[i].ruta || GG_dir_nom_archivos[i].cabecera || GG_dir_nom_archivos[i].extra; i++)
    {
        free(GG_dir_nom_archivos[i].ruta);
        free(GG_dir_nom_archivos[i].cabecera);
        free(GG_dir_nom_archivos[i].extra);
    }

    free(GG_dir_nom_archivos);
    GG_dir_nom_archivos = NULL;
}

static void liberar_arreglo_direccion_inventarios(void)
{
    if (!GG_direccion_hacer_inventarios)
    {
        return;
    }

    for (int i = 0; GG_direccion_hacer_inventarios[i].ruta || GG_direccion_hacer_inventarios[i].cabecera; i++)
    {
        free(GG_direccion_hacer_inventarios[i].ruta);
        free(GG_direccion_hacer_inventarios[i].cabecera);
    }

    free(GG_direccion_hacer_inventarios);
    GG_direccion_hacer_inventarios = NULL;
}

void RecargarArregloArchivos_dir_nom_archivos(void)
{
    liberar_arreglo_dir_nom_archivos();

    time_t ahora = time(NULL);
    struct tm *t = localtime(&ahora);
    char yyyy[5] = "0000";
    char yyyymm[7] = "000000";
    char yyyymmdd[9] = "00000000";

    if (t)
    {
        strftime(yyyy, sizeof(yyyy), "%Y", t);
        strftime(yyyymm, sizeof(yyyymm), "%Y%m", t);
        strftime(yyyymmdd, sizeof(yyyymmdd), "%Y%m%d", t);
    }

    char tmp[512];
    const char *base = GG_direccion_carpetas_base[0] ? GG_direccion_carpetas_base[0] : "";

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\INVENTARIO\\INVENTARIO.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_emergente_productos, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\DAT\\PROVEDORES.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_provedor, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\DAT\\APRENDICES_E.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_APRENDICES_E, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\AFILIADOS\\AFILIADOS_UNIFICADO.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_afiliados_unificados, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REG_A_CONFIRMAR_.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_afiliados_unificados, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\AFILIADOS\\NIVELES_E_ID_HORISONTAL_AFILIADOS_UNIFICADO.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_niv_afiliados_unificado, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\AFILIADOS\\NIVELES_E_ID_HORISONTAL_AFILIADOS_UNIFICADO.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_niv_afiliados_unificado, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\AFILIADOS\\AFILIADOS_UNIFICADO.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_afiliados_unificados, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\AFILIADOS\\NIVELES_E_ID_HORISONTAL_AFILIADOS_UNIFICADO.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_niv_afiliados_unificado, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\DAT\\SUCUR.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_SUCUR, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REGISTROS\\FECHAS\\%s\\%s\\%s_REGISTRO.TXT", base, yyyy, yyyymm, yyyymmdd);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_reg_dia, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REGISTROS\\FECHAS\\%s\\%s_REGISTRO.TXT", base, yyyy, yyyymm);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_reg_mes, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REGISTROS\\FECHAS\\%s_REGISTRO.TXT", base, yyyy);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_reg_año, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REGISTROS\\ACUMULADO_REGISTRO.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_reg_total, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REGISTROS\\FECHAS\\%s\\%s\\%s_PRODUC_REGISTRO.TXT", base, yyyy, yyyymm, yyyymmdd);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_reg_prod_dia, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REGISTROS\\FECHAS\\%s\\%s_PRODUC_REGISTRO.TXT", base, yyyy, yyyymm);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_reg_prod_mes, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REGISTROS\\FECHAS\\%s_PRODUC_REGISTRO.TXT", base, yyyy);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_reg_prod_año, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\REGISTROS\\ACUMULADO_PRODUC_REGISTRO.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_reg_prod_total, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\IMPUESTOS\\IMPUESTOS.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_IMPUESTOS, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\IMPUESTOS\\DEDUSIBLES.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_DEDUSIBLES, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\INVENTARIO\\COSAS_NO_ESTABAN.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_COSAS_NO_ESTABAN_INVENTARIO, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\INVENTARIO\\TIPOS_DE_MEDIDA.TXT", base);
    if (agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_ventana_HERRAMIENTAS, 0, 1, GG_caracter_separacion[1]), "") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "%sCONFIG\\INF\\DAT\\TRABAJOS_POR_DIA.TXT", base);
    agregar_archivo_base_negocio_con_columnas(tmp, columnas_concatenadas(GG_trabajos_dia, 0, 1, GG_caracter_separacion[1]), "");
}

void RecargarArregloDireccionInventarios(void)
{
    liberar_arreglo_direccion_inventarios();

    time_t ahora = time(NULL);
    struct tm *t = localtime(&ahora);
    char yyyymmdd[9] = "00000000";

    if (t)
        strftime(yyyymmdd, sizeof(yyyymmdd), "%Y%m%d", t);

    char tmp[512];

    snprintf(tmp, sizeof(tmp), "CONFIG\\INF\\INVENTARIO\\HACER_INVENTARIO\\%s_VENTAS_DURANTE_INV.TXT", yyyymmdd);
    if (agregar_archivo_inventario(tmp, "CODBAR°nombre_producto°CANTIDA°ULTIMO_MOVIMIENTO") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "CONFIG\\INF\\INVENTARIO\\HACER_INVENTARIO\\%s_SOBRANTES.TXT", yyyymmdd);
    if (agregar_archivo_inventario(tmp, "CODBAR°nombre_producto°CANTIDA°ULTIMO_MOVIMIENTO") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "CONFIG\\INF\\INVENTARIO\\HACER_INVENTARIO\\%s_FALTANTES.TXT", yyyymmdd);
    if (agregar_archivo_inventario(tmp, "CODBAR°nombre_producto°CANTIDA°ULTIMO_MOVIMIENTO") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "CONFIG\\INF\\INVENTARIO\\HACER_INVENTARIO\\%s_NO_ESTAN_EN_EL_FISICO.TXT", yyyymmdd);
    if (agregar_archivo_inventario(tmp, "CODBAR°nombre_producto°CANTIDA°ULTIMO_MOVIMIENTO") < 0)
        return;

    snprintf(tmp, sizeof(tmp), "CONFIG\\INF\\INVENTARIO\\HACER_INVENTARIO\\%s_NO_ESTAN_EN_EL_FISICO_PERO_PUEDE_QUE_FALTEN.TXT", yyyymmdd);
    agregar_archivo_inventario(tmp, "CODBAR°nombre_producto°CANTIDA°ULTIMO_MOVIMIENTO");
}
