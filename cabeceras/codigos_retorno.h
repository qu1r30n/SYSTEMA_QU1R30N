#ifndef CODIGOS_RETORNO_H
#define CODIGOS_RETORNO_H

/* Convención de proyecto:
   - <0 : errores
   -  0 : OK (sin problemas)
   - >0 : creación / resultado positivo (p. ej. id generado, cantidad creada)
*/

#define RET_OK 0
#define RET_ERROR_GENERIC (-1)
#define RET_NOT_FOUND (-2)
#define RET_INVALID_ARG (-3)

/* Convierte un valor booleano-legacy (1=ok,0=falla) a la convención: 0=ok, <0=error
   Uso sugerido: return RET_FROM_BOOL(posible_bool); */
static inline int RET_FROM_BOOL(int legacy_bool) { return legacy_bool ? RET_OK : RET_ERROR_GENERIC; }

static inline int RET_IS_ERROR(int r) { return (r) < 0; }
static inline int RET_IS_OK(int r) { return (r) == 0; }
static inline int RET_IS_CREATED(int r) { return (r) > 0; }

#endif /* CODIGOS_RETORNO_H */
