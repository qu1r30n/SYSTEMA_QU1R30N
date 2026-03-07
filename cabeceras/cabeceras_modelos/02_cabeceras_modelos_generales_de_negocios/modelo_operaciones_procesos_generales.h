#ifndef MODELO_OPERACIONES_PROCESOS_GENERALES_H
#define MODELO_OPERACIONES_PROCESOS_GENERALES_H

int modelo_pg_registrar_movimiento(char *texto);
int modelo_pg_contador_resumen_general(char *texto);
int modelo_pg_contador_resumen_negocio(char *texto);
int modelo_pg_admin_configurar_presupuesto(char *texto);
int modelo_pg_admin_verificar_presupuesto(char *texto);

#endif
