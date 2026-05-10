# 0 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\SISTEMA_QU1R30N.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\SISTEMA_QU1R30N.c"
# 1 "C:/msys64/ucrt64/include/stdio.h" 1 3
# 9 "C:/msys64/ucrt64/include/stdio.h" 3
# 1 "C:/msys64/ucrt64/include/corecrt_stdio_config.h" 1 3
# 10 "C:/msys64/ucrt64/include/corecrt_stdio_config.h" 3
# 1 "C:/msys64/ucrt64/include/corecrt.h" 1 3
# 10 "C:/msys64/ucrt64/include/corecrt.h" 3
# 1 "C:/msys64/ucrt64/include/_mingw.h" 1 3
# 10 "C:/msys64/ucrt64/include/_mingw.h" 3
# 1 "C:/msys64/ucrt64/include/_mingw_mac.h" 1 3
# 108 "C:/msys64/ucrt64/include/_mingw_mac.h" 3

# 117 "C:/msys64/ucrt64/include/_mingw_mac.h" 3

# 326 "C:/msys64/ucrt64/include/_mingw_mac.h" 3

# 405 "C:/msys64/ucrt64/include/_mingw_mac.h" 3

# 11 "C:/msys64/ucrt64/include/_mingw.h" 2 3
# 1 "C:/msys64/ucrt64/include/_mingw_secapi.h" 1 3
# 12 "C:/msys64/ucrt64/include/_mingw.h" 2 3
# 306 "C:/msys64/ucrt64/include/_mingw.h" 3
# 1 "C:/msys64/ucrt64/include/vadefs.h" 1 3
# 9 "C:/msys64/ucrt64/include/vadefs.h" 3
# 1 "C:/msys64/ucrt64/include/_mingw.h" 1 3
# 685 "C:/msys64/ucrt64/include/_mingw.h" 3
# 1 "C:/msys64/ucrt64/include/sdks/_mingw_ddk.h" 1 3
# 686 "C:/msys64/ucrt64/include/_mingw.h" 2 3
# 10 "C:/msys64/ucrt64/include/vadefs.h" 2 3

#pragma pack(push, _CRT_PACKING)
# 24 "C:/msys64/ucrt64/include/vadefs.h" 3

# 24 "C:/msys64/ucrt64/include/vadefs.h" 3
typedef __builtin_va_list __gnuc_va_list;

typedef __gnuc_va_list va_list;
# 103 "C:/msys64/ucrt64/include/vadefs.h" 3
#pragma pack(pop)
# 307 "C:/msys64/ucrt64/include/_mingw.h" 2 3
# 604 "C:/msys64/ucrt64/include/_mingw.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__debugbreak)
 */
void __attribute__((__cdecl__)) __debugbreak(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__always_inline__, __debugbreak)
 */
extern __inline__ __attribute__((__always_inline__, __gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */

  __asm__ __volatile__("int {$}3" :);
}
# 625 "C:/msys64/ucrt64/include/_mingw.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(code)
 */
void __attribute__((__cdecl__)) __attribute__((__noreturn__)) __fastfail(unsigned int code);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__always_inline__, code)
 */
extern __inline__ __attribute__((__always_inline__, __gnu_inline__)) void __attribute__((__cdecl__)) __attribute__((__noreturn__)) __fastfail(unsigned int code)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */

  __asm__ __volatile__("int {$}0x29" ::"c"(code));

  __builtin_unreachable();
}
# 665 "C:/msys64/ucrt64/include/_mingw.h" 3
/*
 * Uso: Ejecuta __mingw_get_crt_info de forma segura.
 * Entrada ejemplo: __mingw_get_crt_info()
 */
const char *__mingw_get_crt_info(void);
# 11 "C:/msys64/ucrt64/include/corecrt.h" 2 3

#pragma pack(push, _CRT_PACKING)
# 35 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef unsigned long long size_t;
# 45 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef long long ssize_t;

typedef size_t rsize_t;
# 62 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef long long intptr_t;
# 75 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef unsigned long long uintptr_t;
# 88 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef long long ptrdiff_t;
# 98 "C:/msys64/ucrt64/include/corecrt.h" 3
typedef unsigned short wchar_t;

typedef unsigned short wint_t;
typedef unsigned short wctype_t;

typedef int errno_t;

typedef long __time32_t;

__extension__ typedef long long __time64_t;
# 138 "C:/msys64/ucrt64/include/corecrt.h" 3
typedef __time64_t time_t;
# 157 "C:/msys64/ucrt64/include/corecrt.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_invalid_parameter_noinfo)
 */
__attribute__((__dllimport__)) void __attribute__((__cdecl__)) _invalid_parameter_noinfo(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_invalid_parameter_noinfo_noreturn)
 */
__attribute__((__dllimport__)) __attribute__((__noreturn__)) void __attribute__((__cdecl__)) _invalid_parameter_noinfo_noreturn(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(expression, function_name, file_name, line_number, reserved)
 */
__attribute__((__dllimport__)) __attribute__((__noreturn__)) void __attribute__((__cdecl__)) _invoke_watson(const wchar_t *expression, const wchar_t *function_name, const wchar_t *file_name, unsigned int line_number, uintptr_t reserved);
# 437 "C:/msys64/ucrt64/include/corecrt.h" 3
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct
{
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct, *_locale_t;

typedef struct tagLC_ID
{
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID, *LPLC_ID;

typedef struct threadlocaleinfostruct
{

  const unsigned short *_locale_pctype;
  int _locale_mb_cur_max;
  unsigned int _locale_lc_codepage;
# 489 "C:/msys64/ucrt64/include/corecrt.h" 3
} threadlocinfo;
# 508 "C:/msys64/ucrt64/include/corecrt.h" 3
#pragma pack(pop)
# 11 "C:/msys64/ucrt64/include/corecrt_stdio_config.h" 2 3

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__local_stdio_printf_options)
 */
unsigned long long *__attribute__((__cdecl__)) __local_stdio_printf_options(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__local_stdio_scanf_options)
 */
unsigned long long *__attribute__((__cdecl__)) __local_stdio_scanf_options(void);
# 10 "C:/msys64/ucrt64/include/stdio.h" 2 3

#pragma pack(push, _CRT_PACKING)

# 33 "C:/msys64/ucrt64/include/stdio.h" 3
struct _iobuf
{

  void *_Placeholder;
# 46 "C:/msys64/ucrt64/include/stdio.h" 3
};
typedef struct _iobuf FILE;
# 99 "C:/msys64/ucrt64/include/stdio.h" 3
# 1 "C:/msys64/ucrt64/include/_mingw_off_t.h" 1 3

typedef long _off_t;

typedef long off32_t;

__extension__ typedef long long _off64_t;

__extension__ typedef long long off64_t;
# 26 "C:/msys64/ucrt64/include/_mingw_off_t.h" 3
typedef off32_t off_t;
# 100 "C:/msys64/ucrt64/include/stdio.h" 2 3

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(index)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) __acrt_iob_func(unsigned index);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__iob_func)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) __iob_func(void);
# 112 "C:/msys64/ucrt64/include/stdio.h" 3
__extension__ typedef long long fpos_t;
# 156 "C:/msys64/ucrt64/include/stdio.h" 3
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _Src, _Format, arg5)
     */
    __attribute__((__format__(__gnu_scanf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __mingw_sscanf(const char *__restrict__ _Src, const char *__restrict__ _Format, ...);
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _Str, Format, argp)
     */
    __attribute__((__format__(__gnu_scanf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __mingw_vsscanf(const char *__restrict__ _Str, const char *__restrict__ Format, va_list argp);
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _Format, arg4)
     */
    __attribute__((__format__(__gnu_scanf__, 1, 2))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
    __mingw_scanf(const char *__restrict__ _Format, ...);
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, Format, argp)
     */
    __attribute__((__format__(__gnu_scanf__, 1, 0))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
    __mingw_vscanf(const char *__restrict__ Format, va_list argp);
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _File, _Format, arg5)
     */
    __attribute__((__format__(__gnu_scanf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __mingw_fscanf(FILE *__restrict__ _File, const char *__restrict__ _Format, ...);
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, fp, Format, argp)
     */
    __attribute__((__format__(__gnu_scanf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __mingw_vfscanf(FILE *__restrict__ fp, const char *__restrict__ Format, va_list argp);

extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _DstBuf, _MaxCount, _Format, _ArgList)
     */
    __attribute__((__format__(__gnu_printf__, 3, 0))) __attribute__((__nonnull__(3))) int __attribute__((__cdecl__))
    __mingw_vsnprintf(char *__restrict__ _DstBuf, size_t _MaxCount, const char *__restrict__ _Format,
                      va_list _ArgList);
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, s, n, format, arg6)
     */
    __attribute__((__format__(__gnu_printf__, 3, 4))) __attribute__((__nonnull__(3))) int __attribute__((__cdecl__))
    __mingw_snprintf(char *__restrict__ s, size_t n, const char *__restrict__ format, ...);
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__gnu_printf__, 1, 2))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
    __mingw_printf(const char *__restrict__, ...) __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__gnu_printf__, 1, 0))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
    __mingw_vprintf(const char *__restrict__, va_list) __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__gnu_printf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __mingw_fprintf(FILE *__restrict__, const char *__restrict__, ...) __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__gnu_printf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __mingw_vfprintf(FILE *__restrict__, const char *__restrict__, va_list) __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__gnu_printf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __mingw_sprintf(char *__restrict__, const char *__restrict__, ...) __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__gnu_printf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __mingw_vsprintf(char *__restrict__, const char *__restrict__, va_list) __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __attribute__, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__gnu_printf__, 2, 3))) __attribute__((nonnull(1, 2))) int __attribute__((__cdecl__))
    __mingw_asprintf(char **__restrict__, const char *__restrict__, ...) __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __attribute__, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__gnu_printf__, 2, 0))) __attribute__((nonnull(1, 2))) int __attribute__((__cdecl__))
    __mingw_vasprintf(char **__restrict__, const char *__restrict__, va_list) __attribute__((__nothrow__));

extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _Src, _Format, __asm__)
     */
    __attribute__((__format__(__ms_scanf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __ms_sscanf(const char *__restrict__ _Src, const char *__restrict__ _Format, ...) __asm__("sscanf");
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _Str, _Format, __asm__)
     */
    __attribute__((__format__(__ms_scanf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __ms_vsscanf(const char *__restrict__ _Str, const char *__restrict__ _Format, va_list argp) __asm__("vsscanf");
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _Format, __asm__)
     */
    __attribute__((__format__(__ms_scanf__, 1, 2))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
    __ms_scanf(const char *__restrict__ _Format, ...) __asm__("scanf");
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _Format, __asm__)
     */
    __attribute__((__format__(__ms_scanf__, 1, 0))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
    __ms_vscanf(const char *__restrict__ _Format, va_list argp) __asm__("vscanf");
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _File, _Format, __asm__)
     */
    __attribute__((__format__(__ms_scanf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __ms_fscanf(FILE *__restrict__ _File, const char *__restrict__ _Format, ...) __asm__("fscanf");
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, _File, _Format, __asm__)
     */
    __attribute__((__format__(__ms_scanf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __ms_vfscanf(FILE *__restrict__ _File, const char *__restrict__ _Format, va_list argp) __asm__("vfscanf");

extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__ms_printf__, 1, 2))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
    __ms_printf(const char *__restrict__, ...) __asm__("printf") __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__ms_printf__, 1, 0))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
    __ms_vprintf(const char *__restrict__, va_list) __asm__("vprintf") __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__ms_printf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __ms_fprintf(FILE *__restrict__, const char *__restrict__, ...) __asm__("fprintf") __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__ms_printf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __ms_vfprintf(FILE *__restrict__, const char *__restrict__, va_list) __asm__("vfprintf") __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__ms_printf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __ms_sprintf(char *__restrict__, const char *__restrict__, ...) __asm__("sprintf") __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__ms_printf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__))
    __ms_vsprintf(char *__restrict__, const char *__restrict__, va_list) __asm__("vsprintf") __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, arg4, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__ms_printf__, 3, 4))) __attribute__((__nonnull__(3))) int __attribute__((__cdecl__))
    __ms_snprintf(char *__restrict__, size_t, const char *__restrict__, ...) __asm__("snprintf") __attribute__((__nothrow__));
extern
    /*
     * Uso: Ejecuta __attribute__ de forma segura.
     * Entrada ejemplo: __attribute__(__format__, arg2, __restrict__, arg4, __restrict__, __nothrow__)
     */
    __attribute__((__format__(__ms_printf__, 3, 0))) __attribute__((__nonnull__(3))) int __attribute__((__cdecl__))
    __ms_vsnprintf(char *__restrict__, size_t, const char *__restrict__, va_list) __asm__("vsnprintf") __attribute__((__nothrow__));

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(options, str, len, format, locale, valist)
 */
int __attribute__((__cdecl__)) __stdio_common_vsprintf(unsigned long long options, char *str, size_t len, const char *format, _locale_t locale, va_list valist);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(options, file, format, locale, valist)
 */
int __attribute__((__cdecl__)) __stdio_common_vfprintf(unsigned long long options, FILE *file, const char *format, _locale_t locale, va_list valist);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(options, input, length, format, locale, valist)
 */
int __attribute__((__cdecl__)) __stdio_common_vsscanf(unsigned long long options, const char *input, size_t length, const char *format, _locale_t locale, va_list valist);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(options, file, format, locale, valist)
 */
int __attribute__((__cdecl__)) __stdio_common_vfscanf(unsigned long long options, FILE *file, const char *format, _locale_t locale, va_list valist);
# 444 "C:/msys64/ucrt64/include/stdio.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _File, _Format, arg5)
 */
__attribute__((__format__(__gnu_printf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) fprintf(FILE *__restrict__ _File, const char *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _Format, arg4)
 */
__attribute__((__format__(__gnu_printf__, 1, 2))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) printf(const char *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _Dest, _Format, arg5)
 */
__attribute__((__format__(__gnu_printf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) sprintf(char *__restrict__ _Dest, const char *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _File, _Format, _ArgList)
 */
__attribute__((__format__(__gnu_printf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) vfprintf(FILE *__restrict__ _File, const char *__restrict__ _Format, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _Format, _ArgList)
 */
__attribute__((__format__(__gnu_printf__, 1, 0))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) vprintf(const char *__restrict__ _Format, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _Dest, _Format, _Args)
 */
__attribute__((__format__(__gnu_printf__, 2, 0))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) vsprintf(char *__restrict__ _Dest, const char *__restrict__ _Format, va_list _Args);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_scanf__, arg2, _File, _Format, arg5)
 */
__attribute__((__format__(__gnu_scanf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) fscanf(FILE *__restrict__ _File, const char *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_scanf__, arg2, _Format, arg4)
 */
__attribute__((__format__(__gnu_scanf__, 1, 2))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) scanf(const char *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_scanf__, arg2, _Src, _Format, arg5)
 */
__attribute__((__format__(__gnu_scanf__, 2, 3))) __attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) sscanf(const char *__restrict__ _Src, const char *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_scanf__, arg2, __stream, __format, __local_argv)
 */
__attribute__((__format__(__gnu_scanf__, 2, 0))) __attribute__((__nonnull__(2))) int vfscanf(FILE *__stream, const char *__format, __builtin_va_list __local_argv);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_scanf__, arg2, __source, __format, __local_argv)
 */
__attribute__((__format__(__gnu_scanf__, 2, 0))) __attribute__((__nonnull__(2))) int vsscanf(const char *__restrict__ __source, const char *__restrict__ __format, __builtin_va_list __local_argv);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_scanf__, arg2, __format, __local_argv)
 */
__attribute__((__format__(__gnu_scanf__, 1, 0))) __attribute__((__nonnull__(1))) int vscanf(const char *__format, __builtin_va_list __local_argv);

#pragma GCC diagnostic pop
# 535 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _filbuf(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _flsbuf(int _Ch, FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename, _Mode, _ShFlag)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) _fsopen(const char *_Filename, const char *_Mode, int _ShFlag);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
void __attribute__((__cdecl__)) clearerr(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) fclose(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_fcloseall)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fcloseall(void);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_FileHandle, _Mode)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) _fdopen(int _FileHandle, const char *_Mode);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) feof(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) ferror(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) fflush(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) fgetc(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_fgetchar)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fgetchar(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Pos)
 */
int __attribute__((__cdecl__)) fgetpos(FILE *__restrict__ _File, fpos_t *__restrict__ _Pos);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Pos)
 */
int __attribute__((__cdecl__)) fgetpos64(FILE *__restrict__ _File, fpos_t *__restrict__ _Pos);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf, _MaxCount, _File)
 */
char *__attribute__((__cdecl__)) fgets(char *__restrict__ _Buf, int _MaxCount, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fileno(FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DirName, _FilePrefix)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _tempnam(const char *_DirName, const char *_FilePrefix);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_flushall)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _flushall(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename, _Mode)
 */
FILE *__attribute__((__cdecl__)) fopen(const char *__restrict__ _Filename, const char *__restrict__ _Mode);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(filename, mode)
 */
FILE *__attribute__((__cdecl__)) fopen64(const char *__restrict__ filename, const char *__restrict__ mode);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
int __attribute__((__cdecl__)) fputc(int _Ch, FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fputchar(int _Ch);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _File)
 */
int __attribute__((__cdecl__)) fputs(const char *__restrict__ _Str, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _ElementSize, _Count, _File)
 */
size_t __attribute__((__cdecl__)) fread(void *__restrict__ _DstBuf, size_t _ElementSize, size_t _Count, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename, _Mode, _File)
 */
FILE *__attribute__((__cdecl__)) freopen(const char *__restrict__ _Filename, const char *__restrict__ _Mode, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename, _Mode, _File)
 */
FILE *__attribute__((__cdecl__)) freopen64(const char *__restrict__ _Filename, const char *__restrict__ _Mode, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Pos)
 */
int __attribute__((__cdecl__)) fsetpos(FILE *_File, const fpos_t *_Pos);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Pos)
 */
int __attribute__((__cdecl__)) fsetpos64(FILE *_File, const fpos_t *_Pos);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Offset, _Origin)
 */
int __attribute__((__cdecl__)) fseek(FILE *_File, long _Offset, int _Origin);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
long __attribute__((__cdecl__)) ftell(FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Offset, _Origin)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fseeki64(FILE *_File, long long _Offset, int _Origin);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) long long __attribute__((__cdecl__)) _ftelli64(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Offset, _Origin)
 */
int __attribute__((__cdecl__)) fseeko(FILE *_File, off_t _Offset, int _Origin)

    ;
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Offset, _Origin)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) fseeko64(FILE *_File, _off64_t _Offset, int _Origin);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
off_t __attribute__((__cdecl__)) ftello(FILE *_File)

    ;
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) _off64_t __attribute__((__cdecl__)) ftello64(FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Size, _Count, _File)
 */
size_t __attribute__((__cdecl__)) fwrite(const void *__restrict__ _Str, size_t _Size, size_t _Count, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) getc(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(getchar)
 */
int __attribute__((__cdecl__)) getchar(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_getmaxstdio)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _getmaxstdio(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(instead)
 */
char *__attribute__((__cdecl__)) gets(char *_Buffer)

    __attribute__((__warning__("Using gets() is always unsafe - use fgets() instead")))

    ;
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) _getw(FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_ErrMsg)
 */
void __attribute__((__cdecl__)) perror(const char *_ErrMsg);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _pclose(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Command, _Mode)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) _popen(const char *_Command, const char *_Mode);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
int __attribute__((__cdecl__)) putc(int _Ch, FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch)
 */
int __attribute__((__cdecl__)) putchar(int _Ch);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
int __attribute__((__cdecl__)) puts(const char *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Word, _File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _putw(int _Word, FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename)
 */
int __attribute__((__cdecl__)) remove(const char *_Filename);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_OldFilename, _NewFilename)
 */
int __attribute__((__cdecl__)) rename(const char *_OldFilename, const char *_NewFilename);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _unlink(const char *_Filename);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename)
 */
int __attribute__((__cdecl__)) unlink(const char *_Filename);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
void __attribute__((__cdecl__)) rewind(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_rmtmp)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _rmtmp(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Buffer)
 */
void __attribute__((__cdecl__)) setbuf(FILE *__restrict__ _File, char *__restrict__ _Buffer);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Max)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _setmaxstdio(int _Max);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format)
 */
__attribute__((__dllimport__)) unsigned int __attribute__((__cdecl__)) _set_output_format(unsigned int _Format);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_get_output_format)
 */
__attribute__((__dllimport__)) unsigned int __attribute__((__cdecl__)) _get_output_format(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Buf, _Mode, _Size)
 */
int __attribute__((__cdecl__)) setvbuf(FILE *__restrict__ _File, char *__restrict__ _Buf, int _Mode, size_t _Size);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _Format, arg4)
 */
__attribute__((__pure__))
__attribute__((__format__(__gnu_printf__, 1, 2))) __attribute__((__nonnull__(1))) int __attribute__((__cdecl__))
_scprintf(const char *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_scanf__, arg2, _Src, _MaxCount, _Format, arg6)
 */
__attribute__((__format__(__gnu_scanf__, 3, 4))) __attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) _snscanf(const char *__restrict__ _Src, size_t _MaxCount, const char *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__attribute__, arg2, _Format, _ArgList)
 */
__attribute__((__pure__))
__attribute__((__format__(__ms_printf__, 1, 0))) __attribute__((__nonnull__(1)))
__attribute__((__dllimport__)) int __attribute__((__cdecl__))
_vscprintf(const char *__restrict__ _Format, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(tmpfile)
 */
FILE *__attribute__((__cdecl__)) tmpfile(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(tmpfile64)
 */
FILE *__attribute__((__cdecl__)) tmpfile64(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buffer)
 */
char *__attribute__((__cdecl__)) tmpnam(char *_Buffer);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
int __attribute__((__cdecl__)) ungetc(int _Ch, FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _Dest, _Count, _Format, _Args)
 */
__attribute__((__format__(__gnu_printf__, 3, 0))) __attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) _vsnprintf(char *__restrict__ _Dest, size_t _Count, const char *__restrict__ _Format, va_list _Args);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, _Dest, _Count, _Format, arg6)
 */
__attribute__((__format__(__gnu_printf__, 3, 4))) __attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) _snprintf(char *__restrict__ _Dest, size_t _Count, const char *__restrict__ _Format, ...);
# 718 "C:/msys64/ucrt64/include/stdio.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, __stream, __n, __format, __local_argv)
 */
__attribute__((__format__(__gnu_printf__, 3, 0))) __attribute__((__nonnull__(3))) int vsnprintf(char *__restrict__ __stream, size_t __n, const char *__restrict__ __format, va_list __local_argv);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__gnu_printf__, arg2, __stream, __n, __format, arg6)
 */
__attribute__((__format__(__gnu_printf__, 3, 4))) __attribute__((__nonnull__(3))) int snprintf(char *__restrict__ __stream, size_t __n, const char *__restrict__ __format, ...);
# 784 "C:/msys64/ucrt64/include/stdio.h" 3
#pragma GCC diagnostic pop
# 886 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Value)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _set_printf_count_output(int _Value);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_get_printf_count_output)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _get_printf_count_output(void);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, arg3)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __mingw_swscanf(const wchar_t *__restrict__ _Src, const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, Format, argp)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __mingw_vswscanf(const wchar_t *__restrict__ _Str, const wchar_t *__restrict__ Format, va_list argp);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) __mingw_wscanf(const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(Format, argp)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) __mingw_vwscanf(const wchar_t *__restrict__ Format, va_list argp);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __mingw_fwscanf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(fp, Format, argp)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __mingw_vfwscanf(FILE *__restrict__ fp, const wchar_t *__restrict__ Format, va_list argp);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __mingw_fwprintf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) __mingw_wprintf(const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _ArgList)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __mingw_vfwprintf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) __mingw_vwprintf(const wchar_t *__restrict__ _Format, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(s, n, format, arg4)
 */
__attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) __mingw_snwprintf(wchar_t *__restrict__ s, size_t n, const wchar_t *__restrict__ format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__restrict__, arg2, __restrict__, va_list)
 */
__attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) __mingw_vsnwprintf(wchar_t *__restrict__, size_t, const wchar_t *__restrict__, va_list);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__restrict__, arg2, __restrict__, arg4)
 */
__attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) __mingw_swprintf(wchar_t *__restrict__, size_t, const wchar_t *__restrict__, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__restrict__, arg2, __restrict__, va_list)
 */
__attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) __mingw_vswprintf(wchar_t *__restrict__, size_t, const wchar_t *__restrict__, va_list);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, __asm__)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __ms_swscanf(const wchar_t *__restrict__ _Src, const wchar_t *__restrict__ _Format, ...) __asm__("swscanf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, __asm__)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __ms_vswscanf(const wchar_t *__restrict__ _Src, const wchar_t *__restrict__ _Format, va_list) __asm__("vswscanf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, __asm__)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) __ms_wscanf(const wchar_t *__restrict__ _Format, ...) __asm__("wscanf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, __asm__)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) __ms_vwscanf(const wchar_t *__restrict__ _Format, va_list) __asm__("vwscanf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, __asm__)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __ms_fwscanf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, ...) __asm__("fwscanf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, __asm__)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __ms_vfwscanf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, va_list) __asm__("vfwscanf");

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __ms_fwprintf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, __asm__)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) __ms_wprintf(const wchar_t *__restrict__ _Format, ...) __asm__("wprintf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, __asm__)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) __ms_vfwprintf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, va_list _ArgList) __asm__("vfwprintf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, __asm__)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) __ms_vwprintf(const wchar_t *__restrict__ _Format, va_list _ArgList) __asm__("vwprintf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__restrict__, arg2, __restrict__, __asm__)
 */
__attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) __ms_swprintf(wchar_t *__restrict__, size_t, const wchar_t *__restrict__, ...) __asm__("swprintf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__restrict__, arg2, __restrict__, __asm__)
 */
__attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) __ms_vswprintf(wchar_t *__restrict__, size_t, const wchar_t *__restrict__, va_list) __asm__("vswprintf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__restrict__, arg2, __restrict__, __asm__)
 */
__attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) __ms_snwprintf(wchar_t *__restrict__, size_t, const wchar_t *__restrict__, ...) __asm__("snwprintf");
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__restrict__, arg2, __restrict__, __asm__)
 */
__attribute__((__nonnull__(3))) int __attribute__((__cdecl__)) __ms_vsnwprintf(wchar_t *__restrict__, size_t, const wchar_t *__restrict__, va_list) __asm__("vsnwprintf");

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(options, str, len, format, locale, valist)
 */
int __attribute__((__cdecl__)) __stdio_common_vswprintf(unsigned long long options, wchar_t *str, size_t len, const wchar_t *format, _locale_t locale, va_list valist);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(options, file, format, locale, valist)
 */
int __attribute__((__cdecl__)) __stdio_common_vfwprintf(unsigned long long options, FILE *file, const wchar_t *format, _locale_t locale, va_list valist);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(options, input, length, format, locale, valist)
 */
int __attribute__((__cdecl__)) __stdio_common_vswscanf(unsigned long long options, const wchar_t *input, size_t length, const wchar_t *format, _locale_t locale, va_list valist);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(options, file, format, locale, valist)
 */
int __attribute__((__cdecl__)) __stdio_common_vfwscanf(unsigned long long options, FILE *file, const wchar_t *format, _locale_t locale, va_list valist);
# 1080 "C:/msys64/ucrt64/include/stdio.h" 3

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
int __attribute__((__cdecl__)) fwscanf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, arg3)
 */
int __attribute__((__cdecl__)) swscanf(const wchar_t *__restrict__ _Src, const wchar_t *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
int __attribute__((__cdecl__)) wscanf(const wchar_t *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__stream, __format, __local_argv)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) vfwscanf(FILE *__stream, const wchar_t *__format, va_list __local_argv);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__source, __format, __local_argv)
 */
__attribute__((__nonnull__(2))) int __attribute__((__cdecl__)) vswscanf(const wchar_t *__restrict__ __source, const wchar_t *__restrict__ __format, va_list __local_argv);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__format, __local_argv)
 */
__attribute__((__nonnull__(1))) int __attribute__((__cdecl__)) vwscanf(const wchar_t *__format, va_list __local_argv);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
int __attribute__((__cdecl__)) fwprintf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
int __attribute__((__cdecl__)) wprintf(const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _ArgList)
 */
int __attribute__((__cdecl__)) vfwprintf(FILE *__restrict__ _File, const wchar_t *__restrict__ _Format, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
int __attribute__((__cdecl__)) vwprintf(const wchar_t *__restrict__ _Format, va_list _ArgList);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Count, _Format, arg4)
 */
int __attribute__((__cdecl__)) swprintf(wchar_t *__restrict__ _Dest, size_t _Count, const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Count, _Format, _Args)
 */
int __attribute__((__cdecl__)) vswprintf(wchar_t *__restrict__ _Dest, size_t _Count, const wchar_t *__restrict__ _Format, va_list _Args);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(s, n, format, arg4)
 */
int __attribute__((__cdecl__)) snwprintf(wchar_t *__restrict__ s, size_t n, const wchar_t *__restrict__ format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(s, n, format, arg)
 */
int __attribute__((__cdecl__)) vsnwprintf(wchar_t *__restrict__ s, size_t n, const wchar_t *__restrict__ format, va_list arg);
# 1116 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename, _Mode, _ShFlag)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfsopen(const wchar_t *_Filename, const wchar_t *_Mode, int _ShFlag);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
wint_t __attribute__((__cdecl__)) fgetwc(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_fgetwchar)
 */
__attribute__((__dllimport__)) wint_t __attribute__((__cdecl__)) _fgetwchar(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
wint_t __attribute__((__cdecl__)) fputwc(wchar_t _Ch, FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch)
 */
__attribute__((__dllimport__)) wint_t __attribute__((__cdecl__)) _fputwchar(wchar_t _Ch);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
wint_t __attribute__((__cdecl__)) getwc(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(getwchar)
 */
wint_t __attribute__((__cdecl__)) getwchar(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
wint_t __attribute__((__cdecl__)) putwc(wchar_t _Ch, FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch)
 */
wint_t __attribute__((__cdecl__)) putwchar(wchar_t _Ch);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
wint_t __attribute__((__cdecl__)) ungetwc(wint_t _Ch, FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _SizeInWords, _File)
 */
wchar_t *__attribute__((__cdecl__)) fgetws(wchar_t *__restrict__ _Dst, int _SizeInWords, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _File)
 */
int __attribute__((__cdecl__)) fputws(const wchar_t *__restrict__ _Str, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_String)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _getws(wchar_t *_String);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _putws(const wchar_t *_Str);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf(const wchar_t *__restrict__ _Format, ...);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Count, _Format, arg4)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf(wchar_t *__restrict__ _Dest, size_t _Count, const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Count, _Format, _Args)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf(wchar_t *__restrict__ _Dest, size_t _Count, const wchar_t *__restrict__ _Format, va_list _Args);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _vscwprintf(const wchar_t *__restrict__ _Format, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Format, arg3)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _swprintf(wchar_t *__restrict__ _Dest, const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Format, _Args)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf(wchar_t *__restrict__ _Dest, const wchar_t *__restrict__ _Format, va_list _Args);

# 1 "C:/msys64/ucrt64/include/swprintf.inl" 1 3
# 1146 "C:/msys64/ucrt64/include/stdio.h" 2 3
# 1159 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Directory, _FilePrefix)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wtempnam(const wchar_t *_Directory, const wchar_t *_FilePrefix);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _MaxCount, _Format, arg4)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf(const wchar_t *__restrict__ _Src, size_t _MaxCount, const wchar_t *__restrict__ _Format, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_FileHandle, _Mode)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfdopen(int _FileHandle, const wchar_t *_Mode);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename, _Mode)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfopen(const wchar_t *__restrict__ _Filename, const wchar_t *__restrict__ _Mode);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename, _Mode, _OldFile)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfreopen(const wchar_t *__restrict__ _Filename, const wchar_t *__restrict__ _Mode, FILE *__restrict__ _OldFile);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_ErrMsg)
 */
__attribute__((__dllimport__)) void __attribute__((__cdecl__)) _wperror(const wchar_t *_ErrMsg);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Command, _Mode)
 */
__attribute__((__dllimport__)) FILE *__attribute__((__cdecl__)) _wpopen(const wchar_t *_Command, const wchar_t *_Mode);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Filename)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wremove(const wchar_t *_Filename);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buffer)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wtmpnam(wchar_t *_Buffer);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) wint_t __attribute__((__cdecl__)) _fgetwc_nolock(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
__attribute__((__dllimport__)) wint_t __attribute__((__cdecl__)) _fputwc_nolock(wchar_t _Ch, FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
__attribute__((__dllimport__)) wint_t __attribute__((__cdecl__)) _ungetwc_nolock(wint_t _Ch, FILE *_File);
# 1207 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fgetc_nolock(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Char, _File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fputc_nolock(int _Char, FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _getc_nolock(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Char, _File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _putc_nolock(int _Char, FILE *_File);
# 1222 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) void __attribute__((__cdecl__)) _lock_file(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) void __attribute__((__cdecl__)) _unlock_file(FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fclose_nolock(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fflush_nolock(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _ElementSize, _Count, _File)
 */
__attribute__((__dllimport__)) size_t __attribute__((__cdecl__)) _fread_nolock(void *__restrict__ _DstBuf, size_t _ElementSize, size_t _Count, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Offset, _Origin)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fseek_nolock(FILE *_File, long _Offset, int _Origin);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) long __attribute__((__cdecl__)) _ftell_nolock(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Offset, _Origin)
 */
__extension__ __attribute__((__dllimport__)) int __attribute__((__cdecl__)) _fseeki64_nolock(FILE *_File, long long _Offset, int _Origin);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__extension__ __attribute__((__dllimport__)) long long __attribute__((__cdecl__)) _ftelli64_nolock(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _Size, _Count, _File)
 */
__attribute__((__dllimport__)) size_t __attribute__((__cdecl__)) _fwrite_nolock(const void *__restrict__ _DstBuf, size_t _Size, size_t _Count, FILE *__restrict__ _File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _ungetc_nolock(int _Ch, FILE *_File);
# 1244 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Directory, _FilePrefix)
 */
char *__attribute__((__cdecl__)) tempnam(const char *_Directory, const char *_FilePrefix);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(fcloseall)
 */
int __attribute__((__cdecl__)) fcloseall(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_FileHandle, _Format)
 */
FILE *__attribute__((__cdecl__)) fdopen(int _FileHandle, const char *_Format);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(fgetchar)
 */
int __attribute__((__cdecl__)) fgetchar(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) fileno(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(flushall)
 */
int __attribute__((__cdecl__)) flushall(void);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch)
 */
int __attribute__((__cdecl__)) fputchar(int _Ch);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
int __attribute__((__cdecl__)) getw(FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Ch, _File)
 */
int __attribute__((__cdecl__)) putw(int _Ch, FILE *_File);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(rmtmp)
 */
int __attribute__((__cdecl__)) rmtmp(void);
# 1273 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(wptr, mbptr, buflen)
 */
int __attribute__((__cdecl__)) __mingw_str_wide_utf8(const wchar_t *const wptr, char **mbptr, size_t *buflen);
# 1287 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(mbptr, wptr, buflen)
 */
int __attribute__((__cdecl__)) __mingw_str_utf8_wide(const char *const mbptr, wchar_t **wptr, size_t *buflen);
# 1296 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(ptr)
 */
void __attribute__((__cdecl__)) __mingw_str_free(void *ptr);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList, arg4)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnl(int _Mode, const wchar_t *_Filename, const wchar_t *_ArgList, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList, arg4)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnle(int _Mode, const wchar_t *_Filename, const wchar_t *_ArgList, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList, arg4)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnlp(int _Mode, const wchar_t *_Filename, const wchar_t *_ArgList, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList, arg4)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnlpe(int _Mode, const wchar_t *_Filename, const wchar_t *_ArgList, ...);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnv(int _Mode, const wchar_t *_Filename, const wchar_t *const *_ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList, _Env)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnve(int _Mode, const wchar_t *_Filename, const wchar_t *const *_ArgList, const wchar_t *const *_Env);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnvp(int _Mode, const wchar_t *_Filename, const wchar_t *const *_ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList, _Env)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnvpe(int _Mode, const wchar_t *_Filename, const wchar_t *const *_ArgList, const wchar_t *const *_Env);
# 1327 "C:/msys64/ucrt64/include/stdio.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnv(int _Mode, const char *_Filename, const char *const *_ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList, _Env)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnve(int _Mode, const char *_Filename, const char *const *_ArgList, const char *const *_Env);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnvp(int _Mode, const char *_Filename, const char *const *_ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Mode, _Filename, _ArgList, _Env)
 */
__attribute__((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnvpe(int _Mode, const char *_Filename, const char *const *_ArgList, const char *const *_Env);

#pragma pack(pop)

# 1 "C:/msys64/ucrt64/include/sec_api/stdio_s.h" 1 3
# 9 "C:/msys64/ucrt64/include/sec_api/stdio_s.h" 3
# 1 "C:/msys64/ucrt64/include/stdio.h" 1 3
# 10 "C:/msys64/ucrt64/include/sec_api/stdio_s.h" 2 3
# 29 "C:/msys64/ucrt64/include/sec_api/stdio_s.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) clearerr_s(FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _ElementSize, _Count, _File)
 */
size_t __attribute__((__cdecl__)) fread_s(void *_DstBuf, size_t _DstSize, size_t _ElementSize, size_t _Count, FILE *_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Options, _Str, _Len, _Format, _Locale, _ArgList)
 */
int __attribute__((__cdecl__)) __stdio_common_vsprintf_s(unsigned long long _Options, char *_Str, size_t _Len, const char *_Format, _locale_t _Locale, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Options, _Str, _Len, _Format, _Locale, _ArgList)
 */
int __attribute__((__cdecl__)) __stdio_common_vsprintf_p(unsigned long long _Options, char *_Str, size_t _Len, const char *_Format, _locale_t _Locale, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Options, _Str, _Len, _MaxCount, _Format, _Locale, _ArgList)
 */
int __attribute__((__cdecl__)) __stdio_common_vsnprintf_s(unsigned long long _Options, char *_Str, size_t _Len, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Options, _File, _Format, _Locale, _ArgList)
 */
int __attribute__((__cdecl__)) __stdio_common_vfprintf_s(unsigned long long _Options, FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Options, _File, _Format, _Locale, _ArgList)
 */
int __attribute__((__cdecl__)) __stdio_common_vfprintf_p(unsigned long long _Options, FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfscanf_s_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vfscanf(0x0001ULL, _File, _Format, _Locale, _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vfscanf_s(FILE *_File, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfscanf_s_l(_File, _Format, ((void *)0), _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscanf_s_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vscanf_s(const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fscanf_s_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfscanf_s_l(_File, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) fscanf_s(FILE *_File, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfscanf_s_l(_File, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scanf_s_l(const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) scanf_s(const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfscanf_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vfscanf(0, _File, _Format, _Locale, _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscanf_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfscanf_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fscanf_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfscanf_l(_File, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scanf_l(const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfscanf_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsscanf_s_l(const char *_Src, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsscanf(0x0001ULL, _Src, (size_t)-1, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vsscanf_s(const char *_Src, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vsscanf_s_l(_Src, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sscanf_s_l(const char *_Src, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsscanf_s_l(_Src, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) sscanf_s(const char *_Src, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vsscanf_s_l(_Src, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsscanf_l(const char *_Src, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsscanf(0, _Src, (size_t)-1, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sscanf_l(const char *_Src, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsscanf_l(_Src, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _MaxCount, _Format, _Locale, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snscanf_s_l(const char *_Src, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = __stdio_common_vsscanf(0x0001ULL, _Src, _MaxCount, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _MaxCount, _Format, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snscanf_s(const char *_Src, size_t _MaxCount, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = __stdio_common_vsscanf(0x0001ULL, _Src, _MaxCount, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _MaxCount, _Format, _Locale, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snscanf_l(const char *_Src, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = __stdio_common_vsscanf(0, _Src, _MaxCount, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfprintf_s_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vfprintf_s((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vfprintf_s(FILE *_File, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfprintf_s_l(_File, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vprintf_s_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vprintf_s(const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fprintf_s_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfprintf_s_l(_File, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _printf_s_l(const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) fprintf_s(FILE *_File, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfprintf_s_l(_File, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) printf_s(const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _MaxCount, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_c_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsprintf((*__local_stdio_printf_options()), _DstBuf, _MaxCount, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _MaxCount, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_c(char *_DstBuf, size_t _MaxCount, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vsnprintf_c_l(_DstBuf, _MaxCount, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _MaxCount, _Format, _Locale, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_c_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsnprintf_c_l(_DstBuf, _MaxCount, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _MaxCount, _Format, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_c(char *_DstBuf, size_t _MaxCount, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vsnprintf_c_l(_DstBuf, _MaxCount, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_s_l(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsnprintf_s((*__local_stdio_printf_options()), _DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vsnprintf_s(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vsnprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_s(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vsnprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, _Locale, arg6)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_s_l(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsnprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_s(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vsnprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsprintf_s_l(char *_DstBuf, size_t _DstSize, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsprintf_s((*__local_stdio_printf_options()), _DstBuf, _DstSize, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _Size, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vsprintf_s(char *_DstBuf, size_t _Size, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vsprintf_s_l(_DstBuf, _Size, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _Format, _Locale, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sprintf_s_l(char *_DstBuf, size_t _DstSize, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsprintf_s_l(_DstBuf, _DstSize, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _Format, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) sprintf_s(char *_DstBuf, size_t _DstSize, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vsprintf_s_l(_DstBuf, _DstSize, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfprintf_p_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vfprintf_p((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfprintf_p(FILE *_File, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfprintf_p_l(_File, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vprintf_p_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfprintf_p_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vprintf_p(const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfprintf_p_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fprintf_p_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = __stdio_common_vfprintf_p((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fprintf_p(FILE *_File, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfprintf_p_l(_File, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _printf_p_l(const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfprintf_p_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _printf_p(const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfprintf_p_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _MaxCount, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsprintf_p_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsprintf_p((*__local_stdio_printf_options()), _DstBuf, _MaxCount, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _MaxCount, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsprintf_p(char *_Dst, size_t _MaxCount, const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vsprintf_p_l(_Dst, _MaxCount, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _MaxCount, _Format, _Locale, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sprintf_p_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsprintf_p_l(_DstBuf, _MaxCount, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _MaxCount, _Format, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sprintf_p(char *_Dst, size_t _MaxCount, const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vsprintf_p_l(_Dst, _MaxCount, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscprintf_p_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsprintf_p(0x0002ULL, ((void *)0), 0, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscprintf_p(const char *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vscprintf_p_l(_Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scprintf_p_l(const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vscprintf_p_l(_Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scprintf_p(const char *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vscprintf_p_l(_Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfprintf_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vfprintf((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vprintf_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfprintf_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fprintf_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfprintf_l(_File, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _printf_l(const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfprintf_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _MaxCount, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsprintf(0x0001ULL, _DstBuf, _MaxCount, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _MaxCount, _Format, _Locale, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsnprintf_l(_DstBuf, _MaxCount, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsprintf_l(char *_DstBuf, const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vsnprintf_l(_DstBuf, (size_t)-1, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sprintf_l(char *_DstBuf, const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsprintf_l(_DstBuf, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscprintf_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsprintf(0x0002ULL, ((void *)0), 0, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scprintf_l(const char *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vscprintf_l(_Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
# 583 "C:/msys64/ucrt64/include/sec_api/stdio_s.h" 3

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Filename, _Mode)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) fopen_s(FILE **_File, const char *_Filename, const char *_Mode);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Filename, _Mode, _Stream)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) freopen_s(FILE **_File, const char *_Filename, const char *_Mode, FILE *_Stream);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(gets_s, rsize_t)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) gets_s(char *, rsize_t);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) tmpfile_s(FILE **_File);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(tmpnam_s, rsize_t)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) tmpnam_s(char *, rsize_t);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _SizeInWords)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _getws_s(wchar_t *_Str, size_t _SizeInWords);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Options, _Str, _Len, _Format, _Locale, _ArgList)
 */
int __attribute__((__cdecl__)) __stdio_common_vswprintf_s(unsigned long long _Options, wchar_t *_Str, size_t _Len, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Options, _Str, _Len, _MaxCount, _Format, _Locale, _ArgList)
 */
int __attribute__((__cdecl__)) __stdio_common_vsnwprintf_s(unsigned long long _Options, wchar_t *_Str, size_t _Len, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Options, _File, _Format, _Locale, _ArgList)
 */
int __attribute__((__cdecl__)) __stdio_common_vfwprintf_s(unsigned long long _Options, FILE *_File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfwscanf_s_l(FILE *_File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vfwscanf((*__local_stdio_scanf_options()) | 0x0001ULL, _File, _Format, _Locale, _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vfwscanf_s(FILE *_File, const wchar_t *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfwscanf_s_l(_File, _Format, ((void *)0), _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vwscanf_s_l(const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfwscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vwscanf_s(const wchar_t *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfwscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fwscanf_s_l(FILE *_File, const wchar_t *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfwscanf_s_l(_File, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) fwscanf_s(FILE *_File, const wchar_t *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfwscanf_s_l(_File, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _wscanf_s_l(const wchar_t *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfwscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) wscanf_s(const wchar_t *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfwscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vswscanf_s_l(const wchar_t *_Src, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vswscanf((*__local_stdio_scanf_options()) | 0x0001ULL, _Src, (size_t)-1, _Format, _Locale, _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vswscanf_s(const wchar_t *_Src, const wchar_t *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vswscanf_s_l(_Src, _Format, ((void *)0), _ArgList);
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _swscanf_s_l(const wchar_t *_Src, const wchar_t *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vswscanf_s_l(_Src, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _Format, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) swscanf_s(const wchar_t *_Src, const wchar_t *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vswscanf_s_l(_Src, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _MaxCount, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnwscanf_s_l(const wchar_t *_Src, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vswscanf((*__local_stdio_scanf_options()) | 0x0001ULL, _Src, _MaxCount, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _MaxCount, _Format, _Locale, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snwscanf_s_l(const wchar_t *_Src, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsnwscanf_s_l(_Src, _MaxCount, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _MaxCount, _Format, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snwscanf_s(const wchar_t *_Src, size_t _MaxCount, const wchar_t *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vsnwscanf_s_l(_Src, _MaxCount, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfwprintf_s_l(FILE *_File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vfwprintf_s((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vwprintf_s_l(const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfwprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vfwprintf_s(FILE *_File, const wchar_t *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfwprintf_s_l(_File, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vwprintf_s(const wchar_t *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vfwprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, _Locale, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fwprintf_s_l(FILE *_File, const wchar_t *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfwprintf_s_l(_File, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, _Locale, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _wprintf_s_l(const wchar_t *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vfwprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Format, arg3)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) fwprintf_s(FILE *_File, const wchar_t *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfwprintf_s_l(_File, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Format, arg2)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) wprintf_s(const wchar_t *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vfwprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vswprintf_s_l(wchar_t *_DstBuf, size_t _DstSize, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vswprintf_s((*__local_stdio_printf_options()), _DstBuf, _DstSize, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vswprintf_s(wchar_t *_DstBuf, size_t _DstSize, const wchar_t *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vswprintf_s_l(_DstBuf, _DstSize, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _Format, _Locale, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _swprintf_s_l(wchar_t *_DstBuf, size_t _DstSize, const wchar_t *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vswprintf_s_l(_DstBuf, _DstSize, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _Format, arg4)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) swprintf_s(wchar_t *_DstBuf, size_t _DstSize, const wchar_t *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vswprintf_s_l(_DstBuf, _DstSize, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnwprintf_s_l(wchar_t *_DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return __stdio_common_vsnwprintf_s((*__local_stdio_printf_options()), _DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, _ArgList)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnwprintf_s(wchar_t *_DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t *_Format, va_list _ArgList)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _vsnwprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, _Locale, arg6)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snwprintf_s_l(wchar_t *_DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Locale);
  _Ret = _vsnwprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _MaxCount, _Format, arg5)
 */
static __attribute__((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snwprintf_s(wchar_t *_DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t *_Format, ...)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  __builtin_va_list _ArgList;
  int _Ret;
  __builtin_va_start(_ArgList, _Format);
  _Ret = _vsnwprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
  __builtin_va_end(_ArgList);
  return _Ret;
}
# 862 "C:/msys64/ucrt64/include/sec_api/stdio_s.h" 3

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Filename, _Mode)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wfopen_s(FILE **_File, const wchar_t *_Filename, const wchar_t *_Mode);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_File, _Filename, _Mode, _OldFile)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wfreopen_s(FILE **_File, const wchar_t *_Filename, const wchar_t *_Mode, FILE *_OldFile);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _SizeInWords)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wtmpnam_s(wchar_t *_DstBuf, size_t _SizeInWords);

# 912 "C:/msys64/ucrt64/include/sec_api/stdio_s.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_DstBuf, _DstSize, _ElementSize, _Count, _File)
 */
__attribute__((__dllimport__)) size_t __attribute__((__cdecl__)) _fread_nolock_s(void *_DstBuf, size_t _DstSize, size_t _ElementSize, size_t _Count, FILE *_File);
# 1346 "C:/msys64/ucrt64/include/stdio.h" 2 3
# 2 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\SISTEMA_QU1R30N.c" 2
# 1 "C:/msys64/ucrt64/include/string.h" 1 3
# 9 "C:/msys64/ucrt64/include/string.h" 3
# 1 "C:/msys64/ucrt64/include/crtdefs.h" 1 3
# 10 "C:/msys64/ucrt64/include/string.h" 2 3
# 45 "C:/msys64/ucrt64/include/string.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _Val, _MaxCount)
 */
__attribute__((__dllimport__)) void *__attribute__((__cdecl__)) _memccpy(void *_Dst, const void *_Src, int _Val, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf, _Val, _MaxCount)
 */
void *__attribute__((__cdecl__)) memchr(const void *_Buf, int _Val, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf1, _Buf2, _Size)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _memicmp(const void *_Buf1, const void *_Buf2, size_t _Size);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf1, _Buf2, _Size, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _memicmp_l(const void *_Buf1, const void *_Buf2, size_t _Size, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf1, _Buf2, _Size)
 */
int __attribute__((__cdecl__)) memcmp(const void *_Buf1, const void *_Buf2, size_t _Size);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _Size)
 */
void *__attribute__((__cdecl__)) memcpy(void *__restrict__ _Dst, const void *__restrict__ _Src, size_t _Size);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_dest, _numberOfElements, _src, _count)
 */
__attribute__((dllimport)) errno_t __attribute__((__cdecl__)) memcpy_s(void *_dest, size_t _numberOfElements, const void *_src, size_t _count);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _Size)
 */
void *__attribute__((__cdecl__)) mempcpy(void *_Dst, const void *_Src, size_t _Size);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Val, _Size)
 */
void *__attribute__((__cdecl__)) memset(void *_Dst, int _Val, size_t _Size);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _Val, _Size)
 */
void *__attribute__((__cdecl__)) memccpy(void *_Dst, const void *_Src, int _Val, size_t _Size);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf1, _Buf2, _Size)
 */
int __attribute__((__cdecl__)) memicmp(const void *_Buf1, const void *_Buf2, size_t _Size);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val)
 */
char *__attribute__((__cdecl__)) _strset(char *_Str, int _Val);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val, _Locale)
 */
char *__attribute__((__cdecl__)) _strset_l(char *_Str, int _Val, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Source)
 */
char *__attribute__((__cdecl__)) strcpy(char *__restrict__ _Dest, const char *__restrict__ _Source);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Source)
 */
char *__attribute__((__cdecl__)) strcat(char *__restrict__ _Dest, const char *__restrict__ _Source);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
int __attribute__((__cdecl__)) strcmp(const char *_Str1, const char *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
size_t __attribute__((__cdecl__)) strlen(const char *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _MaxCount)
 */
size_t __attribute__((__cdecl__)) strnlen(const char *_Str, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _Size)
 */
void *__attribute__((__cdecl__)) memmove(void *_Dst, const void *_Src, size_t _Size);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _strdup(const char *_Src);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val)
 */
char *__attribute__((__cdecl__)) strchr(const char *_Str, int _Val);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _stricmp(const char *_Str1, const char *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _strcmpi(const char *_Str1, const char *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _stricmp_l(const char *_Str1, const char *_Str2, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
int __attribute__((__cdecl__)) strcoll(const char *_Str1, const char *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _strcoll_l(const char *_Str1, const char *_Str2, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _stricoll(const char *_Str1, const char *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _stricoll_l(const char *_Str1, const char *_Str2, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _strncoll(const char *_Str1, const char *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _strncoll_l(const char *_Str1, const char *_Str2, size_t _MaxCount, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _strnicoll(const char *_Str1, const char *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _strnicoll_l(const char *_Str1, const char *_Str2, size_t _MaxCount, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Control)
 */
size_t __attribute__((__cdecl__)) strcspn(const char *_Str, const char *_Control);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_ErrMsg)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _strerror(const char *_ErrMsg);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(strerror)
 */
char *__attribute__((__cdecl__)) strerror(int);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_String)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _strlwr(char *_String);
/*
 * Uso: Ejecuta strlwr_l de forma segura.
 * Entrada ejemplo: strlwr_l(_String, _Locale)
 */
char *strlwr_l(char *_String, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Source, _Count)
 */
char *__attribute__((__cdecl__)) strncat(char *__restrict__ _Dest, const char *__restrict__ _Source, size_t _Count);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
int __attribute__((__cdecl__)) strncmp(const char *_Str1, const char *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _strnicmp(const char *_Str1, const char *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _strnicmp_l(const char *_Str1, const char *_Str2, size_t _MaxCount, _locale_t _Locale);
/*
 * Uso: Ejecuta strncpy de forma segura.
 * Entrada ejemplo: strncpy(_Dest, _Source, _Count)
 */
char *strncpy(char *__restrict__ _Dest, const char *__restrict__ _Source, size_t _Count);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val, _MaxCount)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _strnset(char *_Str, int _Val, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(str, c, count, _Locale)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _strnset_l(char *str, int c, size_t count, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Control)
 */
char *__attribute__((__cdecl__)) strpbrk(const char *_Str, const char *_Control);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Ch)
 */
char *__attribute__((__cdecl__)) strrchr(const char *_Str, int _Ch);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _strrev(char *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Control)
 */
size_t __attribute__((__cdecl__)) strspn(const char *_Str, const char *_Control);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _SubStr)
 */
char *__attribute__((__cdecl__)) strstr(const char *_Str, const char *_SubStr);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Delim)
 */
char *__attribute__((__cdecl__)) strtok(char *__restrict__ _Str, const char *__restrict__ _Delim);

/*
 * Uso: Ejecuta strtok_r de forma segura.
 * Entrada ejemplo: strtok_r(_Str, _Delim, __last)
 */
char *strtok_r(char *__restrict__ _Str, const char *__restrict__ _Delim, char **__restrict__ __last);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_String)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _strupr(char *_String);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_String, _Locale)
 */
__attribute__((__dllimport__)) char *_strupr_l(char *_String, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _MaxCount)
 */
size_t __attribute__((__cdecl__)) strxfrm(char *__restrict__ _Dst, const char *__restrict__ _Src, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) size_t __attribute__((__cdecl__)) _strxfrm_l(char *__restrict__ _Dst, const char *__restrict__ _Src, size_t _MaxCount, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src)
 */
char *__attribute__((__cdecl__)) strdup(const char *_Src);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
int __attribute__((__cdecl__)) strcmpi(const char *_Str1, const char *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
int __attribute__((__cdecl__)) stricmp(const char *_Str1, const char *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
char *__attribute__((__cdecl__)) strlwr(char *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str, _MaxCount)
 */
int __attribute__((__cdecl__)) strnicmp(const char *_Str1, const char *_Str, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(strncasecmp, arg2, arg3)
 */
int __attribute__((__cdecl__)) strncasecmp(const char *, const char *, size_t);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(strcasecmp, arg2)
 */
int __attribute__((__cdecl__)) strcasecmp(const char *, const char *);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val, _MaxCount)
 */
char *__attribute__((__cdecl__)) strnset(char *_Str, int _Val, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
char *__attribute__((__cdecl__)) strrev(char *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val)
 */
char *__attribute__((__cdecl__)) strset(char *_Str, int _Val);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
char *__attribute__((__cdecl__)) strupr(char *_Str);
# 149 "C:/msys64/ucrt64/include/string.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsdup(const wchar_t *_Str);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Source)
 */
wchar_t *__attribute__((__cdecl__)) wcscat(wchar_t *__restrict__ _Dest, const wchar_t *__restrict__ _Source);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Ch)
 */
wchar_t *__attribute__((__cdecl__)) wcschr(const wchar_t *_Str, wchar_t _Ch);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
int __attribute__((__cdecl__)) wcscmp(const wchar_t *_Str1, const wchar_t *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Source)
 */
wchar_t *__attribute__((__cdecl__)) wcscpy(wchar_t *__restrict__ _Dest, const wchar_t *__restrict__ _Source);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Control)
 */
size_t __attribute__((__cdecl__)) wcscspn(const wchar_t *_Str, const wchar_t *_Control);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
size_t __attribute__((__cdecl__)) wcslen(const wchar_t *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Src, _MaxCount)
 */
size_t __attribute__((__cdecl__)) wcsnlen(const wchar_t *_Src, size_t _MaxCount);
/*
 * Uso: Ejecuta wcsncat de forma segura.
 * Entrada ejemplo: wcsncat(_Dest, _Source, _Count)
 */
wchar_t *wcsncat(wchar_t *__restrict__ _Dest, const wchar_t *__restrict__ _Source, size_t _Count);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
int __attribute__((__cdecl__)) wcsncmp(const wchar_t *_Str1, const wchar_t *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta wcsncpy de forma segura.
 * Entrada ejemplo: wcsncpy(_Dest, _Source, _Count)
 */
wchar_t *wcsncpy(wchar_t *__restrict__ _Dest, const wchar_t *__restrict__ _Source, size_t _Count);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dest, _Source, _Count, _Locale)
 */
wchar_t *__attribute__((__cdecl__)) _wcsncpy_l(wchar_t *__restrict__ _Dest, const wchar_t *__restrict__ _Source, size_t _Count, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Control)
 */
wchar_t *__attribute__((__cdecl__)) wcspbrk(const wchar_t *_Str, const wchar_t *_Control);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Ch)
 */
wchar_t *__attribute__((__cdecl__)) wcsrchr(const wchar_t *_Str, wchar_t _Ch);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Control)
 */
size_t __attribute__((__cdecl__)) wcsspn(const wchar_t *_Str, const wchar_t *_Control);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _SubStr)
 */
wchar_t *__attribute__((__cdecl__)) wcsstr(const wchar_t *_Str, const wchar_t *_SubStr);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Delim, _Ptr)
 */
wchar_t *__attribute__((__cdecl__)) wcstok(wchar_t *__restrict__ _Str, const wchar_t *__restrict__ _Delim, wchar_t **__restrict__ _Ptr);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Delim)
 */
wchar_t *__attribute__((__cdecl__)) _wcstok(wchar_t *__restrict__ _Str, const wchar_t *__restrict__ _Delim);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_ErrNum)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcserror(int _ErrNum);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) __wcserror(const wchar_t *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsicmp(const wchar_t *_Str1, const wchar_t *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsicmp_l(const wchar_t *_Str1, const wchar_t *_Str2, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicmp(const wchar_t *_Str1, const wchar_t *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicmp_l(const wchar_t *_Str1, const wchar_t *_Str2, size_t _MaxCount, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val, _MaxCount)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsnset(wchar_t *_Str, wchar_t _Val, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsrev(wchar_t *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsset(wchar_t *_Str, wchar_t _Val);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_String)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcslwr(wchar_t *_String);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_String, _Locale)
 */
__attribute__((__dllimport__)) wchar_t *_wcslwr_l(wchar_t *_String, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_String)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsupr(wchar_t *_String);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_String, _Locale)
 */
__attribute__((__dllimport__)) wchar_t *_wcsupr_l(wchar_t *_String, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _MaxCount)
 */
size_t __attribute__((__cdecl__)) wcsxfrm(wchar_t *__restrict__ _Dst, const wchar_t *__restrict__ _Src, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _Src, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) size_t __attribute__((__cdecl__)) _wcsxfrm_l(wchar_t *__restrict__ _Dst, const wchar_t *__restrict__ _Src, size_t _MaxCount, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
int __attribute__((__cdecl__)) wcscoll(const wchar_t *_Str1, const wchar_t *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcscoll_l(const wchar_t *_Str1, const wchar_t *_Str2, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsicoll(const wchar_t *_Str1, const wchar_t *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsicoll_l(const wchar_t *_Str1, const wchar_t *_Str2, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsncoll(const wchar_t *_Str1, const wchar_t *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsncoll_l(const wchar_t *_Str1, const wchar_t *_Str2, size_t _MaxCount, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicoll(const wchar_t *_Str1, const wchar_t *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicoll_l(const wchar_t *_Str1, const wchar_t *_Str2, size_t _MaxCount, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
wchar_t *__attribute__((__cdecl__)) wcsdup(const wchar_t *_Str);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
int __attribute__((__cdecl__)) wcsicmp(const wchar_t *_Str1, const wchar_t *_Str2);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2, _MaxCount)
 */
int __attribute__((__cdecl__)) wcsnicmp(const wchar_t *_Str1, const wchar_t *_Str2, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val, _MaxCount)
 */
wchar_t *__attribute__((__cdecl__)) wcsnset(wchar_t *_Str, wchar_t _Val, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
wchar_t *__attribute__((__cdecl__)) wcsrev(wchar_t *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Val)
 */
wchar_t *__attribute__((__cdecl__)) wcsset(wchar_t *_Str, wchar_t _Val);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
wchar_t *__attribute__((__cdecl__)) wcslwr(wchar_t *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str)
 */
wchar_t *__attribute__((__cdecl__)) wcsupr(wchar_t *_Str);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str1, _Str2)
 */
int __attribute__((__cdecl__)) wcsicoll(const wchar_t *_Str1, const wchar_t *_Str2);

# 1 "C:/msys64/ucrt64/include/sec_api/string_s.h" 1 3
# 9 "C:/msys64/ucrt64/include/sec_api/string_s.h" 3
# 1 "C:/msys64/ucrt64/include/string.h" 1 3
# 10 "C:/msys64/ucrt64/include/sec_api/string_s.h" 2 3
# 24 "C:/msys64/ucrt64/include/sec_api/string_s.h" 3
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSize, _Value)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strset_s(char *_Dst, size_t _DstSize, int _Value);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf, _SizeInBytes, _ErrMsg)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strerror_s(char *_Buf, size_t _SizeInBytes, const char *_ErrMsg);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf, _SizeInBytes, _ErrNum)
 */
__attribute__((dllimport)) errno_t __attribute__((__cdecl__)) strerror_s(char *_Buf, size_t _SizeInBytes, int _ErrNum);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Size)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strlwr_s(char *_Str, size_t _Size);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Size, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strlwr_s_l(char *_Str, size_t _Size, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Size, _Val, _MaxCount)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strnset_s(char *_Str, size_t _Size, int _Val, size_t _MaxCount);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Size)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strupr_s(char *_Str, size_t _Size);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Size, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strupr_s_l(char *_Str, size_t _Size, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInChars, _Src, _MaxCount)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) strncat_s(char *_Dst, size_t _DstSizeInChars, const char *_Src, size_t _MaxCount);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInChars, _Src, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strncat_s_l(char *_Dst, size_t _DstSizeInChars, const char *_Src, size_t _MaxCount, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _SizeInBytes, _Src)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) strcpy_s(char *_Dst, rsize_t _SizeInBytes, const char *_Src);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInChars, _Src, _MaxCount)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) strncpy_s(char *_Dst, size_t _DstSizeInChars, const char *_Src, size_t _MaxCount);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInChars, _Src, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _strncpy_s_l(char *_Dst, size_t _DstSizeInChars, const char *_Src, size_t _MaxCount, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Delim, _Context)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) strtok_s(char *_Str, const char *_Delim, char **_Context);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Delim, _Context, _Locale)
 */
__attribute__((__dllimport__)) char *__attribute__((__cdecl__)) _strtok_s_l(char *_Str, const char *_Delim, char **_Context, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _SizeInBytes, _Src)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) strcat_s(char *_Dst, rsize_t _SizeInBytes, const char *_Src);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__always_inline__, _src, _count)
 */
extern __inline__ __attribute__((__always_inline__, __gnu_inline__)) size_t __attribute__((__cdecl__)) strnlen_s(const char *_src, size_t _count)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _src ? strnlen(_src, _count) : 0;
}

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_dest, _numberOfElements, _src, _count)
 */
__attribute__((dllimport)) errno_t __attribute__((__cdecl__)) memmove_s(void *_dest, size_t _numberOfElements, const void *_src, size_t _count);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Delim, _Context)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) wcstok_s(wchar_t *_Str, const wchar_t *_Delim, wchar_t **_Context);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buf, _SizeInWords, _ErrNum)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcserror_s(wchar_t *_Buf, size_t _SizeInWords, int _ErrNum);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Buffer, _SizeInWords, _ErrMsg)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) __wcserror_s(wchar_t *_Buffer, size_t _SizeInWords, const wchar_t *_ErrMsg);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInWords, _Val, _MaxCount)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsnset_s(wchar_t *_Dst, size_t _DstSizeInWords, wchar_t _Val, size_t _MaxCount);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _SizeInWords, _Val)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsset_s(wchar_t *_Str, size_t _SizeInWords, wchar_t _Val);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _SizeInWords)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcslwr_s(wchar_t *_Str, size_t _SizeInWords);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _SizeInWords, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcslwr_s_l(wchar_t *_Str, size_t _SizeInWords, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Size)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsupr_s(wchar_t *_Str, size_t _Size);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Size, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsupr_s_l(wchar_t *_Str, size_t _Size, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _SizeInWords, _Src)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) wcscpy_s(wchar_t *_Dst, rsize_t _SizeInWords, const wchar_t *_Src);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _SizeInWords, _Src)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) wcscat_s(wchar_t *_Dst, rsize_t _SizeInWords, const wchar_t *_Src);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInChars, _Src, _MaxCount)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) wcsncat_s(wchar_t *_Dst, size_t _DstSizeInChars, const wchar_t *_Src, size_t _MaxCount);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInChars, _Src, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsncat_s_l(wchar_t *_Dst, size_t _DstSizeInChars, const wchar_t *_Src, size_t _MaxCount, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInChars, _Src, _MaxCount)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) wcsncpy_s(wchar_t *_Dst, size_t _DstSizeInChars, const wchar_t *_Src, size_t _MaxCount);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Dst, _DstSizeInChars, _Src, _MaxCount, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsncpy_s_l(wchar_t *_Dst, size_t _DstSizeInChars, const wchar_t *_Src, size_t _MaxCount, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _Delim, _Context, _Locale)
 */
__attribute__((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcstok_s_l(wchar_t *_Str, const wchar_t *_Delim, wchar_t **_Context, _locale_t _Locale);
/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _SizeInChars, _Val, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsset_s_l(wchar_t *_Str, size_t _SizeInChars, wchar_t _Val, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(_Str, _SizeInChars, _Val, _Count, _Locale)
 */
__attribute__((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsnset_s_l(wchar_t *_Str, size_t _SizeInChars, wchar_t _Val, size_t _Count, _locale_t _Locale);

/*
 * Uso: Ejecuta __attribute__ de forma segura.
 * Entrada ejemplo: __attribute__(__always_inline__, _src, _count)
 */
extern __inline__ __attribute__((__always_inline__, __gnu_inline__)) size_t __attribute__((__cdecl__)) wcsnlen_s(const wchar_t *_src, size_t _count)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  return _src ? wcsnlen(_src, _count) : 0;
}
# 226 "C:/msys64/ucrt64/include/string.h" 2 3
# 3 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\SISTEMA_QU1R30N.c" 2

# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 1

# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h" 1
# 9 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"

# 9 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_modelos/01_cabeceras_modelos_de_negocios/modelo_operaciones_tienda.h"
/*
 * Uso: Ejecuta modelo_crearDirectorio de forma segura.
 * Entrada ejemplo: modelo_crearDirectorio(texto)
 */
void modelo_crearDirectorio(char *texto);
/*
 * Uso: Ejecuta modelo_crearArchivo de forma segura.
 * Entrada ejemplo: modelo_crearArchivo(texto)
 */
void modelo_crearArchivo(char *texto);

/*
 * Uso: Ejecuta modelo_leer_archivo de forma segura.
 * Entrada ejemplo: modelo_leer_archivo(texto)
 */
void modelo_leer_archivo(char *texto);
/*
 * Uso: Ejecuta modelo_guardar_archivo de forma segura.
 * Entrada ejemplo: modelo_guardar_archivo(texto)
 */
void modelo_guardar_archivo(char *texto);
/*
 * Uso: Ejecuta modelo_agregar_fila de forma segura.
 * Entrada ejemplo: modelo_agregar_fila(texto)
 */
void modelo_agregar_fila(char *texto);
/*
 * Uso: Ejecuta modelo_eliminar_fila de forma segura.
 * Entrada ejemplo: modelo_eliminar_fila(texto)
 */
void modelo_eliminar_fila(char *texto);
/*
 * Uso: Ejecuta modelo_editar_fila de forma segura.
 * Entrada ejemplo: modelo_editar_fila(texto)
 */
void modelo_editar_fila(char *texto);
/*
 * Uso: Ejecuta modelo_editar_celda de forma segura.
 * Entrada ejemplo: modelo_editar_celda(texto)
 */
void modelo_editar_celda(char *texto);
/*
 * Uso: Ejecuta modelo_incrementar_celda de forma segura.
 * Entrada ejemplo: modelo_incrementar_celda(texto)
 */
void modelo_incrementar_celda(char *texto);
/*
 * Uso: Ejecuta modelo_editar_columna_completa de forma segura.
 * Entrada ejemplo: modelo_editar_columna_completa(texto)
 */
void modelo_editar_columna_completa(char *texto);
/*
 * Uso: Ejecuta modelo_eliminar_columna de forma segura.
 * Entrada ejemplo: modelo_eliminar_columna(texto)
 */
void modelo_eliminar_columna(char *texto);
/*
 * Uso: Ejecuta modelo_agregar_columna de forma segura.
 * Entrada ejemplo: modelo_agregar_columna(texto)
 */
void modelo_agregar_columna(char *texto);

/*
 * Uso: Ejecuta modelo_inicializacion de forma segura.
 * Entrada ejemplo: modelo_inicializacion(texto)
 */
void modelo_inicializacion(char *texto);

/*
 * Uso: Ejecuta modelo_leerInventario de forma segura.
 * Entrada ejemplo: modelo_leerInventario(texto)
 */
int modelo_leerInventario(char *texto);
/*
 * Uso: Ejecuta modelo_guardarInventario de forma segura.
 * Entrada ejemplo: modelo_guardarInventario(texto)
 */
void modelo_guardarInventario(char *texto);
/*
 * Uso: Ejecuta modelo_buscarProducto de forma segura.
 * Entrada ejemplo: modelo_buscarProducto(texto)
 */
int modelo_buscarProducto(char *texto);
/*
 * Uso: Ejecuta modelo_agregarProducto de forma segura.
 * Entrada ejemplo: modelo_agregarProducto(texto)
 */
void modelo_agregarProducto(char *texto);
/*
 * Uso: Ejecuta modelo_editarPrecio de forma segura.
 * Entrada ejemplo: modelo_editarPrecio(texto)
 */
int modelo_editarPrecio(char *texto);
/*
 * Uso: Ejecuta modelo_venta de forma segura.
 * Entrada ejemplo: modelo_venta(texto)
 */
int modelo_venta(char *texto);
/*
 * Uso: Ejecuta modelo_compra de forma segura.
 * Entrada ejemplo: modelo_compra(texto)
 */
int modelo_compra(char *texto);

/*
 * Uso: Ejecuta modelo_fechaActual de forma segura.
 * Entrada ejemplo: modelo_fechaActual(texto)
 */
void modelo_fechaActual(char *texto);
# 8 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 2

# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_compu.h" 1

/*
 * Uso: Ejecuta modelo_fechaActual de forma segura.
 * Entrada ejemplo: modelo_fechaActual(texto)
 */
void modelo_fechaActual(char *texto);
/*
 * Uso: Ejecuta modelo_delay_ms de forma segura.
 * Entrada ejemplo: modelo_delay_ms(texto)
 */
void modelo_delay_ms(char *texto);
# 13 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 2
# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_operaciones_textos.h" 1

/*
 * Uso: Ejecuta modelo_split de forma segura.
 * Entrada ejemplo: modelo_split(texto, sep)
 */
char **modelo_split(char *texto, const char *sep);

/*
 * Uso: Ejecuta modelo_free_split de forma segura.
 * Entrada ejemplo: modelo_free_split(a)
 */
void modelo_free_split(char **a);

/*
 * Uso: Ejecuta modelo_texto_a_int_seguro de forma segura.
 * Entrada ejemplo: modelo_texto_a_int_seguro(texto)
 */
int modelo_texto_a_int_seguro(char *texto);
/*
 * Uso: Ejecuta modelo_texto_a_float_seguro de forma segura.
 * Entrada ejemplo: modelo_texto_a_float_seguro(texto)
 */
float modelo_texto_a_float_seguro(char *texto);
# 14 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 2
# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_tex_bas.h" 1

/*
 * Uso: Ejecuta modelo_crearDirectorio de forma segura.
 * Entrada ejemplo: modelo_crearDirectorio(texto)
 */
void modelo_crearDirectorio(char *texto);
/*
 * Uso: Ejecuta modelo_crearArchivo de forma segura.
 * Entrada ejemplo: modelo_crearArchivo(texto)
 */
void modelo_crearArchivo(char *texto);

/*
 * Uso: Ejecuta modelo_leer_archivo de forma segura.
 * Entrada ejemplo: modelo_leer_archivo(texto)
 */
void modelo_leer_archivo(char *texto);
/*
 * Uso: Ejecuta modelo_guardar_archivo de forma segura.
 * Entrada ejemplo: modelo_guardar_archivo(texto)
 */
void modelo_guardar_archivo(char *texto);

/*
 * Uso: Ejecuta modelo_agregar_fila de forma segura.
 * Entrada ejemplo: modelo_agregar_fila(texto)
 */
void modelo_agregar_fila(char *texto);
/*
 * Uso: Ejecuta modelo_eliminar_fila de forma segura.
 * Entrada ejemplo: modelo_eliminar_fila(texto)
 */
void modelo_eliminar_fila(char *texto);
/*
 * Uso: Ejecuta modelo_editar_fila de forma segura.
 * Entrada ejemplo: modelo_editar_fila(texto)
 */
void modelo_editar_fila(char *texto);

/*
 * Uso: Ejecuta modelo_editar_celda de forma segura.
 * Entrada ejemplo: modelo_editar_celda(texto)
 */
void modelo_editar_celda(char *texto);
/*
 * Uso: Ejecuta modelo_incrementar_celda de forma segura.
 * Entrada ejemplo: modelo_incrementar_celda(texto)
 */
void modelo_incrementar_celda(char *texto);

/*
 * Uso: Ejecuta modelo_editar_columna_completa de forma segura.
 * Entrada ejemplo: modelo_editar_columna_completa(texto)
 */
void modelo_editar_columna_completa(char *texto);
/*
 * Uso: Ejecuta modelo_eliminar_columna de forma segura.
 * Entrada ejemplo: modelo_eliminar_columna(texto)
 */
void modelo_eliminar_columna(char *texto);
/*
 * Uso: Ejecuta modelo_agregar_columna de forma segura.
 * Entrada ejemplo: modelo_agregar_columna(texto)
 */
void modelo_agregar_columna(char *texto);
# 15 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 2
# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_modelos/00_cabeceras_modelos_del_sistema/modelo_var_fun_GG.h" 1
# 16 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 2

# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/tex_bas.h" 1

/*
 * Uso: Ejecuta crearDirectorio de forma segura.
 * Entrada ejemplo: crearDirectorio(ruta)
 */
void crearDirectorio(const char *ruta);
/*
 * Uso: Ejecuta crearArchivo de forma segura.
 * Entrada ejemplo: crearArchivo(ruta, cabecera)
 */
void crearArchivo(const char *ruta, const char *cabecera);

/*
 * Uso: Ejecuta leer_archivo de forma segura.
 * Entrada ejemplo: leer_archivo(ruta, l)
 */
int leer_archivo(const char *ruta, char l[][1024]);
/*
 * Uso: Ejecuta guardar_archivo de forma segura.
 * Entrada ejemplo: guardar_archivo(ruta, l, n)
 */
void guardar_archivo(const char *ruta, char l[][1024], int n);

/*
 * Uso: Ejecuta agregar_fila de forma segura.
 * Entrada ejemplo: agregar_fila(ruta, fila)
 */
void agregar_fila(const char *ruta, const char *fila);
/*
 * Uso: Ejecuta eliminar_fila de forma segura.
 * Entrada ejemplo: eliminar_fila(ruta, filaEliminar)
 */
void eliminar_fila(const char *ruta, int filaEliminar);
/*
 * Uso: Ejecuta editar_fila de forma segura.
 * Entrada ejemplo: editar_fila(ruta, fila, nueva)
 */
void editar_fila(const char *ruta, int fila, const char *nueva);

/*
 * Uso: Ejecuta editar_celda de forma segura.
 * Entrada ejemplo: editar_celda(ruta, colBuscar, valorBuscar, colEditar, nuevoValor)
 */
void editar_celda(const char *ruta, int colBuscar, const char *valorBuscar,
                  int colEditar, const char *nuevoValor);

/*
 * Uso: Ejecuta incrementar_celda de forma segura.
 * Entrada ejemplo: incrementar_celda(ruta, colBuscar, valorBuscar, colEditar, inc)
 */
void incrementar_celda(const char *ruta, int colBuscar, const char *valorBuscar,
                       int colEditar, int inc);

/*
 * Uso: Ejecuta editar_columna_completa de forma segura.
 * Entrada ejemplo: editar_columna_completa(ruta, col, nuevo)
 */
void editar_columna_completa(const char *ruta, int col, const char *nuevo);
/*
 * Uso: Ejecuta eliminar_columna de forma segura.
 * Entrada ejemplo: eliminar_columna(ruta, col)
 */
void eliminar_columna(const char *ruta, int col);
/*
 * Uso: Ejecuta agregar_columna de forma segura.
 * Entrada ejemplo: agregar_columna(ruta, nombre)
 */
void agregar_columna(const char *ruta, const char *nombre);
# 19 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 2
# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/operaciones_textos.h" 1

/*
 * Uso: Ejecuta split de forma segura.
 * Entrada ejemplo: split(txt, sep, salida)
 */
int split(const char *txt, const char *sep, char ***salida);

/*
 * Uso: Ejecuta free_split de forma segura.
 * Entrada ejemplo: free_split(a)
 */
void free_split(char **a);

/*
 * Uso: Ejecuta texto_a_float_seguro de forma segura.
 * Entrada ejemplo: texto_a_float_seguro(texto, var_a_retornar)
 */
int texto_a_float_seguro(const char *texto, float *var_a_retornar);

/*
 * Uso: Ejecuta texto_a_int_seguro de forma segura.
 * Entrada ejemplo: texto_a_int_seguro(texto, var_a_retornar)
 */
int texto_a_int_seguro(const char *texto, int *var_a_retornar);
# 20 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 2
# 1 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/var_fun_GG.h" 1
# 21 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\CLASE_QU1R30N.h" 2

extern char *GG_caracter_separacion[];
extern char *GG_caracter_separacion_2[];
extern char *GG_caracter_separacion_funciones_espesificas[];
extern char *GG_caracter_separacion_funciones_espesificas_2[];
extern char *GG_archivos[][2];
extern char *GG_archivos_registros[][2];

extern char **G_caracter_separacion;
extern char *(*G_archivos)[2];
extern char *(*G_archivos_registros)[2];
# 5 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\SISTEMA_QU1R30N.c" 2

char **G_caracter_separacion_funciones_espesificas = GG_caracter_separacion_funciones_espesificas;
char *(*G_archivos)[2] = GG_archivos;
char *(*G_archivos_registros)[2] = GG_archivos_registros;

/*
 * Uso: Ejecuta inicializacion de forma segura.
 * Entrada ejemplo: inicializacion()
 */
void inicializacion()
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  crearArchivo(G_archivos[0][0], G_archivos[0][1]);
  for (int i = 0; i < 2; i++)
    crearArchivo(G_archivos_registros[i][0], G_archivos_registros[i][1]);
}

/*
 * Uso: Ejecuta conmutador de forma segura.
 * Entrada ejemplo: conmutador(texto_prueba)
 */
void conmutador(char *texto_prueba)
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  char **opciones = modelo_split(texto_prueba, G_caracter_separacion_funciones_espesificas
                                                   [0]);
  int n_opciones = 0;
  if (opciones)
  {
    while (opciones[n_opciones])
      n_opciones++;
  }

  if (opciones && n_opciones >= 2 && strcmp(opciones[0], "op_tienda") == 0)
  {
    char **sub_opcion = modelo_split(opciones[1], G_caracter_separacion_funciones_espesificas
                                                      [1]);
    int n_sub = 0;
    if (sub_opcion)
      while (sub_opcion[n_sub])
        n_sub++;

    if (n_sub >= 2)
    {
      if (strcmp(sub_opcion[0], "ventas") == 0)
      {
        modelo_venta(sub_opcion[1]);
      }
      else if (strcmp(sub_opcion[0], "compras") == 0)
      {
        modelo_compra(sub_opcion[1]);
      }
      else if (strcmp(sub_opcion[0], "agregar_producto") == 0)
      {
        modelo_agregarProducto(sub_opcion[1]);
      }
      else
      {
        printf("Opción no válida: %s\n", sub_opcion[0]);
      }
    }

    free_split(sub_opcion);
  }
  else if (opciones && strcmp(opciones[0], "procesos_generales") == 0)
  {
  }
  else if (opciones && strcmp(opciones[0], "procesos_sistema") == 0)
  {
  }

  free_split(opciones);
}

/*
 * Uso: Ejecuta main de forma segura.
 * Entrada ejemplo: main()
 */
int main()
{
  /* Paso a paso: validar entradas, procesar y manejar errores. */
  inicializacion();

  const char *ejemplos[] = {
      "op_tienda|ventas|ABC123|2|SucursalX",
      "op_tienda|compras|XYZ987|5|Proveedor1",
      "op_tienda|agregar_producto|1|Leche|1L|unidad|10|123456|100|50|ProveedorA",

# 85 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\SISTEMA_QU1R30N.c" 3
      ((void *)0)
# 85 "c:\\Users\\qu1r30n\\Documents\\GitHub\\SYSTEMA_QU1R30N\\SISTEMA_QU1R30N.c"
  };

  for (int i = 0; ejemplos[i]; i++)
  {
    printf("Ejecutando comando: %s\n", ejemplos[i]);
  }

  modelo_delay_ms("1000");

  return 0;
}
