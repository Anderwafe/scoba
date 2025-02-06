#ifndef H_SCOBA_MEMORY
#define H_SCOBA_MEMORY

#include <inttypes.h>
#include "logging.h"

void* memory_malloc(size_t size);
void* memory_calloc(size_t size, size_t count);
void* memory_realloc(void* ptr, size_t size);
void* memory_recalloc(void* ptr, size_t size, size_t count);
void memory_free(void* ptr);

#ifdef __STDC_HOSTED__

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

void memory_free(void* ptr){
    free(ptr);
}

void* memory_malloc(size_t size){
    return malloc(size);
}

void* memory_calloc(size_t size, size_t count){
    return calloc(count, size);
}

void* memory_realloc(void* ptr, size_t size){
    return realloc(ptr, size);
}

#ifdef _DEFAULT_SOURCE
void* memory_recalloc(void* ptr, size_t size, size_t count){
    return reallocarray(ptr, count, size);
}
#else
void* memory_recalloc(void* ptr, size_t size, size_t count){
    if((SIZE_MAX / size) > count) {
        LOGERROR(stderr, 34, "size * count bigger than SIZE_MAX");
        errno = 34;
        return NULL;
    }
    return realloc(ptr, size * count);
}
#endif
#endif

#endif
