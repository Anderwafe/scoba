#ifndef H_CLIBS_COLLECTION_DYNARR
#define H_CLIBS_COLLECTION_DYNARR

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "loggingUtils.h"

#define DYNARR_INITIAL_CAPACITY 8

#define DYNARR_DEFINE_NAMED(elementsType, name) typedef struct {\
    elementsType* elements;\
    size_t count;\
    size_t capacity;\
} name

#define DYNARR_RESIZE(object, newCapacity) do { \
    void* temp = realloc(object->elements, newCapacity * sizeof(typeof(*(object->elements)))); \
    if(temp == NULL) { \
        LOGERROR(stderr, errno, "Cannot realloc the elements"); \
        break; \
    } \
    object->elements = (typeof(object->elements))temp; \
    object->capacity = newCapacity; \
    object->count = object->count; 
} while(0)

#define DYNARR_INIT(object) do { \
    assert(object->elements == NULL); \
    DYNARR_RESIZE(object, DYNARR_INITIAL_CAPACITY); \
    \
} while(0)

#define DYNARR_APPEND(object, item) do {\
    if(object->count >= object->capacity) {\

#endif
