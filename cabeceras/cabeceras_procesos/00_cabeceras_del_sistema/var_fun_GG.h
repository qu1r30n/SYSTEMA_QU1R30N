#ifndef VAR_FUN_GG_H
#define VAR_FUN_GG_H

#define COLUMNAS 33
#define MAX_PRODUCTOS 1000

extern char *GG_archivos[1][2];
extern char *GG_archivos_registros[2][2];

/* nuevas variables globales añadidas */
extern int GG_indice_donde_comensar;
extern char *GG_cantidado_por_archivo;

extern char *GG_caracter_separacion[];
extern char *GG_caracter_separacion_2[];

/* separadores para funciones específicas (13 elementos) */
extern char *GG_caracter_separacion_funciones_espesificas[];
extern char *GG_caracter_separacion_funciones_espesificas_2[];

extern char *GG_caracter_para_confirmacion_o_error[];
extern char *GG_caracter_para_confirmacion_o_error_2[];

extern char *GG_caracter_para_transferencia_entre_archivos[];
extern char *GG_caracter_para_transferencia_entre_archivos_2[];

extern char *GG_caracter_para_usar_como_enter_y_nuevo_mensaje[];
extern char *GG_caracter_para_usar_como_enter_y_nuevo_mensaje_2[];

extern char *GG_caracter_guardado_para_confirmacion[];

extern char *GG_id_programa;

#define ARCH_INVENTARIO 0

/* Estructura para filas de configuración de ventanas emergentes */
#define MAX_CAMPOS_CONFIG 5
#define MAX_LONGITUD_CAMPO 256

typedef struct
{
    char tipo[16]; /* "1", "2", "4" etc */
    char nombre[MAX_LONGITUD_CAMPO];
    char validacion[MAX_LONGITUD_CAMPO];
    char valor_default[MAX_LONGITUD_CAMPO];
    char tipo_dato[32]; /* "TEXTO", "ENTERO_DECIMAL", etc */
} ConfigField;

/* Estructura para variables string temporales */
#define MAX_VAR_STRING 7
extern char *GG_variables_string[MAX_VAR_STRING];

/* Declaraciones de arreglos de configuración */
extern ConfigField GG_ventana_datos_conf[2];
extern ConfigField GG_ventana_emergente_productos[33];
extern ConfigField GG_ventana_COSAS_NO_ESTABAN_INVENTARIO[3];
extern ConfigField GG_ventana_provedor[24];
extern ConfigField GG_ventana_APRENDICES_E[32];
extern ConfigField GG_ventana_afiliados_unificados[8];
extern ConfigField GG_ventana_niv_afiliados_unificado[4];
extern ConfigField GG_ventana_SUCUR[20];
extern ConfigField GG_ventana_reg_dia[11];
extern ConfigField GG_ventana_reg_mes[9];
extern ConfigField GG_ventana_reg_año[9];
extern ConfigField GG_ventana_reg_total[9];
extern ConfigField GG_ventana_reg_prod_dia[12];
extern ConfigField GG_ventana_reg_prod_mes[12];
extern ConfigField GG_ventana_reg_prod_año[12];
extern ConfigField GG_ventana_reg_prod_total[12];
extern ConfigField GG_ventana_IMPUESTOS[6];
extern ConfigField GG_ventana_DEDUSIBLES[7];
extern ConfigField GG_ventana_HERRAMIENTAS[2];
extern ConfigField GG_trabajos_dia[8];

/* Funciones para reinicializar estructuras */
void RecargarVentanaEmergenteDatosConfiguracion(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteProductos(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergente_Cosas_que_no_estaban(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteProvedor(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteAPRENDICES_E(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteAfiliados_unificados(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergente_niv_afiliados_unificado(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteSUCUR(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteRegDia(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteRegMes(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteRegAño(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteRegTotal(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteReg_prod_Dia(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteReg_prod_Mes(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteReg_prod_Año(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteReg_prod_total(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteImpuestos(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergenteDedusibles(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergente_HERRAMIENTAS(const char *al_finalizar_que_borrar);
void RecargarVentanaEmergente_TRABAJOS_DIA(const char *al_finalizar_que_borrar);

/* Función auxiliar para concatenar columnas */
char *columnas_concatenadas(ConfigField *arreglo, int filas, int id_columna, const char *caracter_separacion);

#endif