#ifndef H_SCOBA_DYNARR
#define H_SCOBA_DYNARR

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include "logging.h"
#include "memory.h"

#define DYNARR_INITIAL_CAPACITY 8

#define DYNARR_DEFINE_NAMED(elementsType, name) typedef struct {\
    elementsType* elements;\
    size_t count;\
    size_t capacity;\
} name

#define DYNARR_RESIZE(object, newCapacity) do { \
    typeof(object) _object = object; \
    typeof(newCapacity) _newCapacity = newCapacity;\
    LOGINFO(stdout, "object = %xp; newCapacity = %zu", _object, _newCapacity);\
    void* temp = memory_recalloc(_object->elements, sizeof(typeof(*((_object)->elements))), _newCapacity);\
    if(temp == NULL) { \
        LOGERROR(stderr, errno, "Cannot realloc the elements, %d -> %d", _object->capacity, _newCapacity); \
        exit(EXIT_FAILURE); \
    } \
    (_object)->elements = (typeof((_object)->elements))temp; \
    (_object)->capacity = (_newCapacity); \
    (_object)->count = (_object)->count;\
} while(0)

#define DYNARR_INIT(object) do { \
    typeof(object) _object = object; \
    LOGINFO(stdout, "object = %xp", _object);\
    assert((_object)->elements == NULL); \
    DYNARR_RESIZE((_object), DYNARR_INITIAL_CAPACITY); \
    assert((_object)->elements != NULL); \
    (_object)->count = 0; \
    (_object)->capacity = DYNARR_INITIAL_CAPACITY; \
} while(0)

#define DYNARR_FREE(object) do {\
    typeof(object) _object = object;\
    LOGINFO(stdout, "object = %xp", _object);\
    memory_free(_object->elements);\
    _object->count = 0;\
    _object->capacity = 0;\
} while(0)

#define DYNARR_APPEND(object, item) do {\
    typeof(item) _item = item; \
    typeof(object) _object = object;\
    if((_object)->count >= (_object)->capacity) {\
        size_t newCapacity = (_object)->capacity * (_object->count / _object->capacity + 1);\
        DYNARR_RESIZE(_object, newCapacity);\
    }\
    _object->elements[_object->count++] = _item;\
} while(0)

#define DYNARR_INSERT(object, item, index) do{\
    typeof(object) _object = object;\
    typeof(item) _item = item;\
    typeof(index) _index = index;\
    if(_object->count >= _index) {\
        DYNARR_APPEND(_object, 0)\
        memmove(_object->elements+_index, _object->elements+_index+1, _object

#define DYNARR_REMOVE(object, index)

#define DYNARR_CLEAR(object) (object)->count = 0
    

#define DYNARR_FIND(object, item)

#define DYNARR_SORT(object)

// Compares two values and return:
// <= -1, if left 'bigger' than right
//     0, if left equals right
// >   1, if right 'bigger' than left
#define COMPARER(name, type) int (*name)(type left, type right)

#define DYNARR_SORT_PREDICATE(object, comparer)

#endif
