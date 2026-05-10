/*
Incluimos el header donde está definida la estructura core_arena
y los prototipos de las funciones públicas.
*/
/* LIBRERIAS USADAS EN ESTE ARCHIVO:
 * - ../../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/nuestro_propio_administrador_de_memoria/core_memory.h: Dependencia interna del proyecto
 */
#include "../../../cabeceras/cabeceras_procesos/00_cabeceras_del_sistema/nuestro_propio_administrador_de_memoria/core_memory.h"

/*
===============================================================================
 CONFIGURACIÓN INTERNA DE DEBUG
===============================================================================
*/

/*
Definimos un patrón hexadecimal que se usará para rellenar memoria
cuando se haga reset en modo debug.

0xCD es un patrón clásico usado en depuración (Visual Studio usa algo similar).
Sirve para detectar uso de memoria no inicializada.
*/
#define CORE_DEBUG_PATTERN 0xCD

/*
===============================================================================
 MEMORIA INTERNA ESTÁTICA
===============================================================================
*/

/*
Declaramos un bloque de memoria estático global.

- Vive en la sección de datos del programa.
- No usa malloc.
- Funciona incluso sin sistema operativo.
- Se usa si el usuario llama core_arena_init_default().

El tamanio depende de CORE_ARENA_DEFAULT_SIZE.
*/
unsigned char core_arena_memoria_default[CORE_ARENA_DEFAULT_SIZE];

/*
===============================================================================
 FUNCIÓN INTERNA: ALINEACIÓN
===============================================================================
*/

/*
Ajusta un valor "ptr" al siguiente múltiplo de "align".

Esto es importante porque algunas arquitecturas (ARM, etc.)
requieren que ciertos tipos estén alineados a 4, 8 o más bytes.

Parámetros:
  ptr-> valor actual (offset)
  align -> alineación deseada (ej: 8)




Retorna:
  Nuevo valor alineado correctamente.
*/
size_t core_align_forward(size_t ptr, size_t align)
{
    /*
    Calculamos el residuo de ptr dividido por align.
    Si es 0 ? ya está alineado.
    */
    size_t mod = ptr % align;

    /*
    Si no está alineado,
    sumamos lo que falta para que lo esté.
    */
    if (mod != 0)
        ptr += (align - mod);

    /*
    Retornamos el valor corregido.
    */
    return ptr; // retorna el puntero al bloque de memoria asignado y alineado // ejemplo: 0x...
}

/*
===============================================================================
 INICIALIZACIÓN DEL ARENA CON MEMORIA EXTERNA
===============================================================================
*/

/*
 * Uso: Ejecuta core_arena_init de forma segura.
 * Entrada ejemplo: core_arena_init(arena, memoria_externa, tamanio)
 */
void core_arena_init(core_arena *arena, void *memoria_externa, size_t tamanio)
{
    /*
    Validamos que:
    - arena no sea NULL
    - memoria_externa no sea NULL
    - tamanio no sea 0
    */
    if (arena == NULL || memoria_externa == NULL || tamanio == 0)
        return;

    /*
    Guardamos la dirección base de memoria.
    Se convierte a unsigned char* para operar byte por byte.
    */
    arena->memoria = (unsigned char *)memoria_externa;

    /*
    Guardamos el tamanio total del bloque.
    */
    arena->capacidad = tamanio; // guarda el tamano total del bloque de memoria disponible // ejemplo: 4096

    /*
    Iniciamos el offset en 0.
    Eso significa que el arena está vacío.
    */
    arena->offset = 0;

#if CORE_ARENA_STATS
    /*
    Reiniciamos estadísticas si están activadas.
    */
    arena->max_usado = 0;    // reinicia estadistica de uso maximo // ejemplo: 0
    arena->total_allocs = 0; // reinicia contador de asignaciones // ejemplo: 0
#endif
}

/*
===============================================================================
 INICIALIZACIÓN CON MEMORIA INTERNA
===============================================================================
*/

/*
 * Uso: Ejecuta core_arena_init_default de forma segura.
 * Entrada ejemplo: core_arena_init_default(arena)
 */
void core_arena_init_default(core_arena *arena)
{
    /*
    Llamamos a la función principal,
    usando el bloque estático interno como memoria base.
    */
    core_arena_init(arena, core_arena_memoria_default, CORE_ARENA_DEFAULT_SIZE);
}

/*
===============================================================================
 SNAPSHOT
===============================================================================
*/

/*
Guarda el estado actual del arena.

Devuelve el offset actual.
Luego puedes restaurarlo con core_arena_restore().
*/
size_t core_arena_snapshot(const core_arena *arena)
{
    /*
    Si arena es NULL, retornamos 0 por seguridad.
    */
    if (arena == NULL) // valida que el puntero al arena no sea NULL antes de operar // ejemplo: arena=NULL -> retorna
        return 0;

    /*
    Retornamos el offset actual.
    */
    return arena->offset; // devuelve el offset actual para poder restaurarlo despues (snapshot) // ejemplo: 256
}

/*
===============================================================================
 RESTORE
===============================================================================
*/

/*
Restaura el offset a un snapshot previo.
Esto es como hacer "pop" en una pila de memoria.
*/
/*
 * Uso: Ejecuta core_arena_restore de forma segura.
 * Entrada ejemplo: core_arena_restore(arena, snapshot)
 */
void core_arena_restore(core_arena *arena, size_t snapshot)
{
    /*
    Validar que arena no sea NULL.
    */
    if (arena == NULL) // valida que el puntero al arena no sea NULL antes de operar // ejemplo: arena=NULL -> retorna
        return;

    /*
    Solo restauramos si el snapshot es válido
    (no puede exceder la capacidad total).
    */
    if (snapshot <= arena->capacidad) // verifica que el snapshot sea un offset valido dentro del bloque // ejemplo: 256 <= 4096
        arena->offset = snapshot;     // restaura el offset al punto guardado liberando lo asignado despues // ejemplo: offset=256
}

/*
===============================================================================
 ASIGNACIÓN NORMAL
===============================================================================
*/

/*
 * Uso: Ejecuta core_arena_alloc de forma segura.
 * Entrada ejemplo: core_arena_alloc(arena, tamanio)
 */
void *core_arena_alloc(core_arena *arena, size_t tamanio)
{
    /*
    Validamos parámetros.
    */
    if (arena == NULL || tamanio == 0) // valida que los parametros sean validos antes de asignar memoria // ejemplo: NULL -> retorna NULL
        return NULL;

    /*
    Alineamos el offset actual para cumplir reglas de CPU.
    */
    size_t offset_alineado = core_align_forward(arena->offset, CORE_ARENA_ALIGNMENT);

    /*
    Verificamos que haya espacio suficiente.
    */
    if (offset_alineado + tamanio > arena->capacidad) // verifica que haya espacio suficiente en el bloque antes de asignar // ejemplo: 256+64 > 4096 -> false
        return NULL;

    /*
    Calculamos la dirección final dentro del bloque.
    */
    void *ptr = arena->memoria + offset_alineado; // calcula la direccion de inicio del bloque que se va a retornar // ejemplo: base+256

    /*
    Avanzamos el offset.
    */
    arena->offset = offset_alineado + tamanio; // avanza el offset para que la proxima asignacion empiece despues de esta // ejemplo: 256+64=320

#if CORE_ARENA_STATS
    /*
    Incrementamos contador de asignaciones.
    */
    arena->total_allocs++; // incrementa el contador de asignaciones para estadisticas // ejemplo: total_allocs=5

    /*
    Si este uso supera el pico anterior,
    actualizamos max_usado.
    */
    if (arena->offset > arena->max_usado)
        arena->max_usado = arena->offset; // actualiza el pico de uso maximo del arena // ejemplo: max_usado=320
#endif

    /*
    Retornamos puntero válido.
    */
    return ptr; // retorna el puntero al bloque de memoria asignado y alineado // ejemplo: 0x...
}

/*
===============================================================================
 ASIGNACIÓN RÁPIDA (SIN ESTADÍSTICAS)
===============================================================================
*/

void *core_arena_alloc_fast(core_arena *arena, size_t tamanio)
{
    /*
    Validación básica.
    */
    if (arena == NULL || tamanio == 0) // valida que los parametros sean validos antes de asignar memoria // ejemplo: NULL -> retorna NULL
        return NULL;

    /*
    Alineamos offset.
    */
    size_t offset_alineado = core_align_forward(arena->offset, CORE_ARENA_ALIGNMENT);

    /*
    Verificamos espacio.
    */
    if (offset_alineado + tamanio > arena->capacidad) // verifica que haya espacio suficiente en el bloque antes de asignar // ejemplo: 256+64 > 4096 -> false
        return NULL;

    /*
    Calculamos dirección.
    */
    void *ptr = arena->memoria + offset_alineado; // calcula la direccion de inicio del bloque que se va a retornar // ejemplo: base+256

    /*
    Avanzamos offset.
    */
    arena->offset = offset_alineado + tamanio; // avanza el offset para que la proxima asignacion empiece despues de esta // ejemplo: 256+64=320

    /*
    Retornamos puntero.
    */
    return ptr; // retorna el puntero al bloque de memoria asignado y alineado // ejemplo: 0x...
}

/*
===============================================================================
 RESET TOTAL
===============================================================================
*/

/*
 * Uso: Ejecuta core_arena_reset de forma segura.
 * Entrada ejemplo: core_arena_reset(arena)
 */
void core_arena_reset(core_arena *arena)
{
    /*
    Validación.
    */
    if (arena == NULL) // valida que el puntero al arena no sea NULL antes de operar // ejemplo: arena=NULL -> retorna
        return;

#ifdef CORE_ARENA_DEBUG
    /*
    Si el modo debug está activo,
    rellenamos toda la memoria con el patrón definido.

    Esto ayuda a detectar uso indebido después de reset.
    */
    for (size_t i = 0; i < arena->capacidad; i++)
        arena->memoria[i] = CORE_DEBUG_PATTERN;
#endif

    /*
    Reiniciamos offset a 0.
    */
    arena->offset = 0;
}

/*
===============================================================================
 CONSULTAS DE ESTADO
===============================================================================
*/

/*
 * Uso: Ejecuta core_arena_usado de forma segura.
 * Entrada ejemplo: core_arena_usado(arena)
 */
size_t core_arena_usado(const core_arena *arena)
{
    /*
    Validación.
    */
    if (arena == NULL) // valida que el puntero al arena no sea NULL antes de operar // ejemplo: arena=NULL -> retorna
        return 0;

    /*
    Retornamos bytes usados.
    */
    return arena->offset; // devuelve el offset actual para poder restaurarlo despues (snapshot) // ejemplo: 256
}

/*
 * Uso: Ejecuta core_arena_disponible de forma segura.
 * Entrada ejemplo: core_arena_disponible(arena)
 */
size_t core_arena_disponible(const core_arena *arena)
{
    /*
    Validación.
    */
    if (arena == NULL) // valida que el puntero al arena no sea NULL antes de operar // ejemplo: arena=NULL -> retorna
        return 0;

    /*
    Retornamos capacidad restante.
    */
    return arena->capacidad - arena->offset;
}
