#ifndef H_SCOBA_MEMORY
#define H_SCOBA_MEMORY

#include <stdint.h>
#include "logging.h"

#define SCOBA_MEMORY_RECALLOC_OVERFLOW 1

void* scoba_memory_malloc(size_t size);
void* scoba_memory_calloc(size_t size, size_t count);
void* scoba_memory_realloc(void* ptr, size_t size);
void* scoba_memory_recalloc(void* ptr, size_t size, size_t count);
void  scoba_memory_free(void* ptr);

#ifdef __STDC_HOSTED__

#include <stdlib.h>
#include <errno.h>

void scoba_memory_free(void* ptr){
    free(ptr);
}

void* scoba_memory_malloc(size_t size){
    return malloc(size);
}

void* scoba_memory_calloc(size_t size, size_t count){
    return calloc(count, size);
}

void* scoba_memory_realloc(void* ptr, size_t size){
    return realloc(ptr, size);
}

#ifdef _DEFAULT_SOURCE
void* scoba_memory_recalloc(void* ptr, size_t size, size_t count){
    return reallocarray(ptr, count, size);
}
#else
void* scoba_memory_recalloc(void* ptr, size_t size, size_t count){
    if((SIZE_MAX / size) <= count) {
        SCOBA_LOGERROR(stderr, "[%s] cannot recalloc: size * count bigger than SIZE_MAX", strerror(34));
        errno = 34;
        return NULL;
    }
    return realloc(ptr, size * count);
}
#endif
#endif

#endif
