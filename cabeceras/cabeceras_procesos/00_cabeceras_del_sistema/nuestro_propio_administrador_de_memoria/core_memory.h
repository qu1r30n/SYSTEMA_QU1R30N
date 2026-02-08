#ifndef CORE_MEMORY_H
#define CORE_MEMORY_H
/* 
   Evita inclusión múltiple del archivo.
   Si ya fue incluido antes, no se vuelve a procesar.
*/

/* 
   size_t es el tipo estándar para tamaños de memoria.
   Está definido en stddef.h.
*/
#include <stddef.h>

/*
===============================================================================
 CONFIGURACIÓN GLOBAL DEL ARENA
===============================================================================
*/

/* 
   Tamaño por defecto del bloque interno.
   Solo se usa si NO pasamos memoria externa.
   Puede modificarse antes de incluir este archivo.
*/
#ifndef CORE_ARENA_DEFAULT_SIZE
#define CORE_ARENA_DEFAULT_SIZE (1024 * 64) /* 64 KB */
#endif

/*
   Alineación por defecto.
   8 bytes es seguro para la mayoría de CPUs modernas.
   Puede aumentarse si se usan tipos más grandes.
*/
#ifndef CORE_ARENA_ALIGNMENT
#define CORE_ARENA_ALIGNMENT 8
#endif

/*
   Activa estadísticas internas del allocator.
   1 = activar
   0 = desactivar (más ligero)
*/
#ifndef CORE_ARENA_STATS
#define CORE_ARENA_STATS 1
#endif

/*
===============================================================================
 ESTRUCTURA PRINCIPAL DEL ARENA
===============================================================================
*/

typedef struct
{
    /* 
       Puntero al bloque base de memoria.
       Puede ser memoria estática o externa.
    */
    unsigned char* memoria;

    /*
       Tamaño total del bloque de memoria.
    */
    size_t capacidad;

    /*
       Offset actual dentro del bloque.
       Indica cuánto se ha usado.
    */
    size_t offset;

#if CORE_ARENA_STATS
    /*
       Máximo pico de uso alcanzado.
    */
    size_t max_usado;

    /*
       Número total de asignaciones realizadas.
    */
    size_t total_allocs;
#endif

} core_arena;

/*
===============================================================================
 PROTOTIPOS DE FUNCIONES
===============================================================================
*/

/* Inicializa arena usando memoria externa */
void core_arena_init(core_arena* arena,void* memoria_externa,size_t tamaño);

/* Inicializa arena usando memoria interna por defecto */
void core_arena_init_default(core_arena* arena);

/* Solicita memoria dentro del arena */
void* core_arena_alloc(core_arena* arena, size_t tamaño);

/* Reinicia el arena (libera todo de golpe) */
void core_arena_reset(core_arena* arena);

/* Devuelve cantidad de memoria usada */
size_t core_arena_usado(const core_arena* arena);

/* Devuelve memoria disponible restante */
size_t core_arena_disponible(const core_arena* arena);

#endif
