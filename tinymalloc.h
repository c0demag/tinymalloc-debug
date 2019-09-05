#ifndef _TINY_MALLOC_H_DEFINED_
#define _TINY_MALLOC_H_DEFINED_

#include <stddef.h>
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

/* public functions. */
void* tmalloc(size_t);
void  tfree(void*);
void* trealloc(void*, size_t);
void* tmemalign(size_t, size_t);
void* tcalloc(size_t, size_t);

/* private functions. */
void* tvalloc(size_t);
void* pvalloc(size_t);
void    cfree(void*);
int     tmalloc_trim(size_t);
size_t  tmalloc_usable_size(void*);
void    tmalloc_stats(void);
int     tmallopt(int, int);
struct tmallinfo mallinfo(void);

/* types. */
typedef struct freelist_entry {
  size_t size;
  struct freelist_entry *next;
} *fle;

/* global variables. */
extern char __tmalloc_start[];
extern fle __tmalloc_freelist;
extern char * __tmalloc_end;

#ifdef __cplusplus
}
#endif

#endif
