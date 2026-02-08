/* 
   Incluimos el header donde está definida la estructura core_arena
   y los prototipos de las funciones públicas.
*/
//#include "core_memory.h"


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

   El tamaño depende de CORE_ARENA_DEFAULT_SIZE.
*/
static unsigned char core_arena_memoria_default[CORE_ARENA_DEFAULT_SIZE];


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
     ptr   -> valor actual (offset)
     align -> alineación deseada (ej: 8)

   Retorna:
     Nuevo valor alineado correctamente.
*/
static size_t core_align_forward(size_t ptr, size_t align)
{
    /* 
       Calculamos el residuo de ptr dividido por align.
       Si es 0 → ya está alineado.
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
    return ptr;
}


/*
===============================================================================
 INICIALIZACIÓN DEL ARENA CON MEMORIA EXTERNA
===============================================================================
*/

void core_arena_init(core_arena* arena,
                     void* memoria_externa,
                     size_t tamaño)
{
    /*
       Validamos que:
       - arena no sea NULL
       - memoria_externa no sea NULL
       - tamaño no sea 0
    */
    if (arena == NULL || memoria_externa == NULL || tamaño == 0)
        return;

    /*
       Guardamos la dirección base de memoria.
       Se convierte a unsigned char* para operar byte por byte.
    */
    arena->memoria = (unsigned char*)memoria_externa;

    /*
       Guardamos el tamaño total del bloque.
    */
    arena->capacidad = tamaño;

    /*
       Iniciamos el offset en 0.
       Eso significa que el arena está vacío.
    */
    arena->offset = 0;

#if CORE_ARENA_STATS
    /*
       Reiniciamos estadísticas si están activadas.
    */
    arena->max_usado = 0;
    arena->total_allocs = 0;
#endif
}


/*
===============================================================================
 INICIALIZACIÓN CON MEMORIA INTERNA
===============================================================================
*/

void core_arena_init_default(core_arena* arena)
{
    /*
       Llamamos a la función principal,
       usando el bloque estático interno como memoria base.
    */
    core_arena_init(arena,
                    core_arena_memoria_default,
                    CORE_ARENA_DEFAULT_SIZE);
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
size_t core_arena_snapshot(const core_arena* arena)
{
    /*
       Si arena es NULL, retornamos 0 por seguridad.
    */
    if (arena == NULL)
        return 0;

    /*
       Retornamos el offset actual.
    */
    return arena->offset;
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
void core_arena_restore(core_arena* arena, size_t snapshot)
{
    /*
       Validar que arena no sea NULL.
    */
    if (arena == NULL)
        return;

    /*
       Solo restauramos si el snapshot es válido
       (no puede exceder la capacidad total).
    */
    if (snapshot <= arena->capacidad)
        arena->offset = snapshot;
}


/*
===============================================================================
 ASIGNACIÓN NORMAL
===============================================================================
*/

void* core_arena_alloc(core_arena* arena, size_t tamaño)
{
    /*
       Validamos parámetros.
    */
    if (arena == NULL || tamaño == 0)
        return NULL;

    /*
       Alineamos el offset actual para cumplir reglas de CPU.
    */
    size_t offset_alineado =
        core_align_forward(arena->offset, CORE_ARENA_ALIGNMENT);

    /*
       Verificamos que haya espacio suficiente.
    */
    if (offset_alineado + tamaño > arena->capacidad)
        return NULL;

    /*
       Calculamos la dirección final dentro del bloque.
    */
    void* ptr = arena->memoria + offset_alineado;

    /*
       Avanzamos el offset.
    */
    arena->offset = offset_alineado + tamaño;

#if CORE_ARENA_STATS
    /*
       Incrementamos contador de asignaciones.
    */
    arena->total_allocs++;

    /*
       Si este uso supera el pico anterior,
       actualizamos max_usado.
    */
    if (arena->offset > arena->max_usado)
        arena->max_usado = arena->offset;
#endif

    /*
       Retornamos puntero válido.
    */
    return ptr;
}


/*
===============================================================================
 ASIGNACIÓN RÁPIDA (SIN ESTADÍSTICAS)
===============================================================================
*/

void* core_arena_alloc_fast(core_arena* arena, size_t tamaño)
{
    /*
       Validación básica.
    */
    if (arena == NULL || tamaño == 0)
        return NULL;

    /*
       Alineamos offset.
    */
    size_t offset_alineado =
        core_align_forward(arena->offset, CORE_ARENA_ALIGNMENT);

    /*
       Verificamos espacio.
    */
    if (offset_alineado + tamaño > arena->capacidad)
        return NULL;

    /*
       Calculamos dirección.
    */
    void* ptr = arena->memoria + offset_alineado;

    /*
       Avanzamos offset.
    */
    arena->offset = offset_alineado + tamaño;

    /*
       Retornamos puntero.
    */
    return ptr;
}


/*
===============================================================================
 RESET TOTAL
===============================================================================
*/

void core_arena_reset(core_arena* arena)
{
    /*
       Validación.
    */
    if (arena == NULL)
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

size_t core_arena_usado(const core_arena* arena)
{
    /*
       Validación.
    */
    if (arena == NULL)
        return 0;

    /*
       Retornamos bytes usados.
    */
    return arena->offset;
}

size_t core_arena_disponible(const core_arena* arena)
{
    /*
       Validación.
    */
    if (arena == NULL)
        return 0;

    /*
       Retornamos capacidad restante.
    */
    return arena->capacidad - arena->offset;
}
