#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h"

int GG_indice_donde_comensar = 1;

char *GG_cantidado_por_archivo = "100";

char *GG_caracter_separacion[] = {"|", "°", "¬", "╦", "╔"};
char *GG_caracter_separacion_2[] = {"⚭", "⚮", "⚯", "⚰", "⚱"};

char *GG_caracter_separacion_funciones_espesificas[] = {"~", "§", "¶", "╬", "╝", "╩", "║", "╗", "┐", "└", "┬", "├", "┼"};
char *GG_caracter_separacion_funciones_espesificas_2[] = {"⚲", "⚳", "⚴", "⚵", "⚶", "⚷", "⚸", "⚺", "⚻", "⚼", "⚿", "⛊", "⛋"};

char *GG_caracter_para_confirmacion_o_error[] = {"╣", "╠"};
char *GG_caracter_para_confirmacion_o_error_2[] = {"⛑", "⛒"};

char *GG_caracter_para_transferencia_entre_archivos[] = {"┴", "■"};
char *GG_caracter_para_transferencia_entre_archivos_2[] = {"⛕", "⛘"};

char *GG_caracter_para_usar_como_enter_y_nuevo_mensaje[] = {"•", "∆"};
char *GG_caracter_para_usar_como_enter_y_nuevo_mensaje_2[] = {"⛙", "⛚"};

char *GG_caracter_guardado_para_confirmacion[] = {"⛞", "⛝"};

char *GG_id_programa = "CLASE_QU1R30N_2";

char *GG_archivos[][2] = {
    {"inventario.txt",
     "ID|Producto|Contenido|TipoMedida|PrecioVenta|CodBarras|Cantidad|CostoCompra|Proveedor|Col10|Col11|Col12|Col13|Col14|Col15|Col16|Col17|Fecha"}};

char *GG_archivos_registros[][2] = {
    {"registros_ventas.txt", ""},
    {"registros_compras.txt", ""}};
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
ConfigField GG_ventana_datos_conf[2] = {
    {.tipo = "2", .nombre = "dato_de_configuracion", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "2", .nombre = "descripcion_de_configuracion", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"}};

/* Ventana: Productos (33 campos) */
ConfigField GG_ventana_emergente_productos[33] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_PRODUCTO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_CONTENIDO", .validacion = "0°SOLO_NUMEROS", .valor_default = "-0", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "4", .nombre = "_03_TIPO_MEDIDA", .validacion = "NOSE°TODAS_MAYUSCULAS", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_PRECIO_VENTA", .validacion = "0°SOLO_NUMEROS", .valor_default = "-0", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "2", .nombre = "_05_COD_BARRAS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_CANTIDAD", .validacion = "1°SOLO_NUMEROS", .valor_default = "-0", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_07_COSTO_COMP", .validacion = "0°SOLO_NUMEROS", .valor_default = "-0", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "4", .nombre = "_08_PROVEDOR", .validacion = "NOSE°TODAS_MAYUSCULAS", .valor_default = "NOSE¬0", .tipo_dato = "TEXTO"},
    {.tipo = "4", .nombre = "_09_GRUPO", .validacion = "PRODUCTO_PIEZA", .valor_default = "PRODUCTO_PIEZA", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_CANT_X_PAQUET", .validacion = "1°SOLO_NUMEROS", .valor_default = "-0", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "4", .nombre = "_11_ES_PAQUETE", .validacion = "INDIVIDUAL", .valor_default = "INDIVIDUAL", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_12_CODBAR_PAQUETE_E_ID", .validacion = "", .valor_default = "NOSE_2", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_13_COD_BAR_INDIVIDUAL_ES_PAQ_E_ID", .validacion = "", .valor_default = "NOSE_3¬1", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_14_LIGAR_PROD_SAB", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_15_IMPUESTOS", .validacion = "REYENO_TEXTBOX_VENTANA_IMPU", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_16_INGREDIENTES", .validacion = "NO_VISIBLE¬PRODUCTO_ELABORADO", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_17_CADUCIDAD", .validacion = "0°SOLO_NUMEROS", .valor_default = "-0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_18_ULTIMO_MOV", .validacion = "0°SOLO_NUMEROS", .valor_default = "-0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_19_SUCUR_VENT", .validacion = "", .valor_default = "NOSE¬0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_20_CLAF_PROD", .validacion = "", .valor_default = "-0", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_21_DIR_IMG_INTER", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_22_DIR_IMG_COMP", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_23_INFO_EXTRA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_24_PROCESO_CREAR", .validacion = "NO_VISIBLE", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_25_DIR_VID_PROC_CREAR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_26_TIEMPO_FABRICACION", .validacion = "0", .valor_default = "-0", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "2", .nombre = "_27_INDICES_DIA_REGISTRO_PRODUC_VENDIDO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "2", .nombre = "_28_INDICES_MES_REGISTRO_PRODUC_VENDIDO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "2", .nombre = "_29_INDICES_AÑO_REGISTRO_PRODUC_VENDIDO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "2", .nombre = "_30_ULTIMA_VENTA", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "2", .nombre = "_31_INDICES_TOTAL_REGISTRO_PRODUC_VENDIDO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "2", .nombre = "_32_NO_PONER_NADA", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"}};

/* Ventana: Cosas No Estaban en Inventario (3 campos) */
ConfigField GG_ventana_COSAS_NO_ESTABAN_INVENTARIO[3] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_COD_BAR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_NOMBRE", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"}};

/* Ventana: Proveedores (24 campos) */
ConfigField GG_ventana_provedor[24] = {
    {.tipo = "2", .nombre = "_00_ID_EMPRESA", .validacion = "", .valor_default = "-0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_01_NOMBRE_EMPRESA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_NOMBRE_ENCARGADO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_DIRECCIÓN_EMPRESA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_CIUDAD_EMPRESA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_ESTADO_EMPRESA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_CÓDIGO_POSTAL", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_PAÍS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_CORREO_ELECTRÓNICO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_09_TELÉFONO_ENCARGADO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_TELEFONO_EMPRESA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_11_TIPO_DE_PROVEEDOR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_12_PRODUCTOS_SERVICIOS_SUMINISTRADOS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_13_CUENTA_BANCO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_14_UBICACIÓN_(GPS)", .validacion = "", .valor_default = "-0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_15_NOTAS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_16_RECORDATORIO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_17_ACTIVO_O_NO_ACTIVO", .validacion = "", .valor_default = "ACTIVO", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_18_CALIFICACIÓN", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_19_COMENTARIOS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_20_SUCURSALES_QUE_LE_COMPRAN", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_21_DINERO_A_COMPRARLE", .validacion = "0°SOLO_NUMEROS", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_22_DIAS_DE_PREVENTA", .validacion = "", .valor_default = "NOSE¬NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_23_DIAS_DE_ENTREGA", .validacion = "", .valor_default = "NOSE¬NOSE", .tipo_dato = "TEXTO"}};

/* Ventana: Aprendices (32 campos) */
ConfigField GG_ventana_APRENDICES_E[32] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_01_NOMBRE", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_APELLIDO_PATERNO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_APELLIDO_MATERNO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_FECHA_DE_NACIMIENTO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_GÉNERO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_DIRECCIÓN", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_CIUDAD", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_ESTADO_PROVINCIA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_09_CÓDIGO_POSTAL", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_PAÍS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_11_CORREO_ELECTRÓNICO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_12_TELÉFONO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_13_FECHA_DE_INGRESO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_14_SUELDO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_15_CARGO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_16_ESTADO_DE_CURS_APRENDIS_E", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_17_SUPERVISOR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_18_NOTAS", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_19_AFILIADO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_20_FECHA_DE_TERMINACIÓN", .validacion = "0°SOLO_NUMEROS", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_21_MOTIVO_DE_TERMINACIÓN", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_22_HORAS_TRABAJADAS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_23_EVALUACIONES_DE_DESEMPEÑO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_24_HABILIDADES_Y_CERTIFICACIONES", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_25_IDIOMAS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_26_FECHA_DE_ÚLTIMA_PROMOCIÓN", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_27_ID_DEPARTAMENTO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_28_HISTORIAL_DE_CAPACITACIÓN", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_29_ÚLTIMO_AUMENTO_DE_SALARIO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_30_TIPO_EMPLEADO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_31_RANGO_CALIF", .validacion = "", .valor_default = "-0", .tipo_dato = "TEXTO"}};

/* Ventana: Afiliados Unificados (8 campos) */
ConfigField GG_ventana_afiliados_unificados[8] = {
    {.tipo = "1", .nombre = "_00_ID_USUARIO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_01_IDP", .validacion = "", .valor_default = "0╔0╦0¬0╔1╦1", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_PUNTOS_D_R", .validacion = "", .valor_default = "0╦0¬0╦0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_PUNTOS_D_R_TOTALES", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_DATOS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_NIVEL", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_ID_HORIZONTAL", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_TIPO_AFILIADO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"}};

/* Ventana: Niveles Afiliados Unificado (4 campos) */
ConfigField GG_ventana_niv_afiliados_unificado[4] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_NIVEL", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_ID_HORIZONTAL", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_VACIOS", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"}};

/* Ventana: Sucursales (20 campos) */
ConfigField GG_ventana_SUCUR[20] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_NOM_ID_SUCUR", .validacion = "", .valor_default = "-0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_NOMBRE_SUCUR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_NOMBRE_ENCARGADO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_DIRECCIÓN_SUCUR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_CIUDAD_SUCUR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_ESTADO_SUCUR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_CÓDIGO_POSTAL", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_PAÍS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_09_CORREO_ELECTRÓNICO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_TELÉFONO_ENCARGADO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_11_TELEFONO_SUCUR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_12_TIPO_DE_SUCUR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_13_PRODUCTOS_SERVICIOS", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_14_CUENTA_BANCO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_15_UBICACIÓN_(GPS)", .validacion = "", .valor_default = "-0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_16_NOTAS", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_17_RECORDATORIO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_18_ACTIVO_O_NO_ACTIVO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_19_HORA_ABRIR_CERRAR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"}};

/* Ventana: Registro Día (11 campos) */
ConfigField GG_ventana_reg_dia[11] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_HORA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_OPERACION", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_TOTAL_IMPUESTO", .validacion = "", .valor_default = "NOSE╦0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_CÓDIGO_PRECIO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_COMENTARIO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_TOTAL_VENTA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_TOTAL_COSTO_COMP", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_TOTAL_IMPUESTOS", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_09_TOTAL_DEDUSIBLES", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_PLATAFORMA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"}};

/* Ventana: Registro Mes (9 campos) */
ConfigField GG_ventana_reg_mes[9] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_DIA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_OPERACION", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_TOTAL_IMPUESTO", .validacion = "", .valor_default = "NOSE╦0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_COMENTARIO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_TOTAL_VENTA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_TOTAL_COSTO_COMP", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_TOTAL_IMPUESTOS", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_TOTAL_GANANCIA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"}};

/* Ventana: Registro Año (9 campos) */
ConfigField GG_ventana_reg_año[9] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_MES", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_OPERACION", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_TOTAL_IMPUESTO", .validacion = "", .valor_default = "NOSE╦0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_COMENTARIO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_TOTAL_VENTA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_TOTAL_COSTO_COMP", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_TOTAL_IMPUESTOS", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_TOTAL_GANANCIA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"}};

/* Ventana: Registro Total (9 campos) */
ConfigField GG_ventana_reg_total[9] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_AÑO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_OPERACION", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_TOTAL_IMPUESTO", .validacion = "", .valor_default = "NOSE╦0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_COMENTARIO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_TOTAL_VENTA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_TOTAL_COSTO_COMP", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_TOTAL_IMPUESTOS", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_TOTAL_GANANCIA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"}};

/* Ventana: Registro Productos Día (12 campos) */
ConfigField GG_ventana_reg_prod_dia[12] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_NOMBRE_PRODUCTO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_CANTIDAD", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_COD_BAR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_PROVEDORES", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_HISTORIAL", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_RANKING", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_PROMEDIO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_VECES_SUPERA_PROMEDIO", .validacion = "", .valor_default = "7", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_09_USO_MULTIPLE", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_TIPO_PRODUCTO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_11_NIVEL_NECESIDAD", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"}};

/* Ventana: Registro Productos Mes (12 campos) */
ConfigField GG_ventana_reg_prod_mes[12] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_NOMBRE_PRODUCTO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_CANTIDAD", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_COD_BAR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_PROVEDORES", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_HISTORIAL", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_RANKING", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_PROMEDIO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_VECES_SUPERA_PROMEDIO", .validacion = "", .valor_default = "7", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_09_USO_MULTIPLE", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_TIPO_PRODUCTO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_11_NIVEL_NECESIDAD", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"}};

/* Ventana: Registro Productos Año (12 campos) */
ConfigField GG_ventana_reg_prod_año[12] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_NOMBRE_PRODUCTO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_CANTIDAD", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_COD_BAR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_PROVEDORES", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_HISTORIAL", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_RANKING", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_PROMEDIO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_VECES_SUPERA_PROMEDIO", .validacion = "", .valor_default = "7", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_09_USO_MULTIPLE", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_TIPO_PRODUCTO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_11_NIVEL_NECESIDAD", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"}};

/* Ventana: Registro Productos Total (12 campos) */
ConfigField GG_ventana_reg_prod_total[12] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_NOMBRE_PRODUCTO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_CANTIDAD", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_COD_BAR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_PROVEDORES", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_HISTORIAL", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_RANKING", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_PROMEDIO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_08_VECES_SUPERA_PROMEDIO", .validacion = "", .valor_default = "7", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_09_USO_MULTIPLE", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_10_TIPO_PRODUCTO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_11_NIVEL_NECESIDAD", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"}};

/* Ventana: Impuestos (6 campos) */
ConfigField GG_ventana_IMPUESTOS[6] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_IMPUESTO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_PORCENTAGE", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_DESCRIPCION", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_INFO_EXTRA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_TIPO_IMPUESTO", .validacion = "", .valor_default = "3", .tipo_dato = "TEXTO"}};

/* Ventana: Deducibles (7 campos) */
ConfigField GG_ventana_DEDUSIBLES[7] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_FECHA", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_MONTO", .validacion = "", .valor_default = "0", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_DESCRIPCION", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_PROVEDOR", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_ARCHIVO_FACTURA", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_FOLIO", .validacion = "", .valor_default = "NOSE", .tipo_dato = "TEXTO"}};

/* Ventana: Herramientas (2 campos) */
ConfigField GG_ventana_HERRAMIENTAS[2] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_COD_BAR", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"}};

/* Ventana: Trabajos por Día (8 campos) */
ConfigField GG_trabajos_dia[8] = {
    {.tipo = "2", .nombre = "_00_ID", .validacion = "", .valor_default = "-1", .tipo_dato = "ENTERO_DECIMAL"},
    {.tipo = "1", .nombre = "_01_DIA", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_02_ID_TRABAJADOR", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_03_HECHO_O_NO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_04_CANTIDAD", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_05_COSTO_COMP", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_06_ID_QUIENLOISO", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"},
    {.tipo = "1", .nombre = "_07_ID_PROGRAMA", .validacion = "", .valor_default = "", .tipo_dato = "TEXTO"}};

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

/* Función auxiliar para concatenar valores de columnas */
char *columnas_concatenadas(ConfigField *arreglo, int filas, int id_columna, const char *caracter_separacion)
{
    static char resultado[4096];
    memset(resultado, 0, sizeof(resultado));

    if (caracter_separacion == NULL)
    {
        caracter_separacion = GG_caracter_separacion[1];
    }

    for (int i = 0; i < filas; i++)
    {
        strcat(resultado, arreglo[i].nombre);
        if (i < filas - 1)
        {
            strcat(resultado, caracter_separacion);
        }
    }

    return resultado;
}
