#ifndef OPERACIONES_BANCO_H
#define OPERACIONES_BANCO_H

int banco_registrar_cuenta(const char *cuenta, const char *titular, float saldo_inicial);
int banco_depositar(const char *cuenta, float monto);
int banco_retirar(const char *cuenta, float monto, const char *motivo);
int banco_consultar_saldo(const char *cuenta, float *saldo);

#endif
