#ifndef H_SCOBA_DYNARR
#define H_SCOBA_DYNARR

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "logging.h"
#include "memory.h"

#define DYNARR_INITIAL_CAPACITY 8

#define DYNARR_DEFINE_NAMED(elementsType, name) typedef struct {\
    elementsType* elements;\
    size_t count;\
    size_t capacity;\
} name

typedef struct {
    void* elements;
    size_t count;
    size_t capacity;
} void_dynarr;

#define DYNARR_RESIZE(object, newCapacity) do { \
    typeof(object) _object = object; \
    size_t _newCapacity = newCapacity;\
    if(!_object) {\
        LOGWARN(stdout, "Passed NULL as object");\
        break;\
    }\
    if(_newCapacity <= _object->capacity) break; \
    LOGINFO(stdout, "resizing dynarr object = %xp; newCapacity = %zu", _object, _newCapacity);\
    void* temp = memory_recalloc(_object->elements, sizeof(typeof(*((_object)->elements))), _newCapacity);\
    if(temp == NULL) { \
        LOGWARN(stderr, "Cannot realloc the elements in dynarr (because '%s'), %d -> %d", strerror(errno), _object->capacity, _newCapacity); \
        break; \
    } \
    (_object)->elements = (typeof((_object)->elements))temp; \
    (_object)->capacity = (_newCapacity); \
} while(0)

int8_t dynarr_resize(void* object, size_t element_size, size_t new_capacity) {
    if(!object) {
        LOGWARN(stdout, "Passed NULL as object");
        return 0;
    }
    
    void_dynarr* dynarr = (void_dynarr*)object;
    if(new_capacity <= dynarr->capacity) break;
    LOGINFO(stdout, "resizing dynarr object = %xp; new capacity = %zu", dynarr, new_capacity);
    void* temp = memory_recalloc(_object->elements, sizeof(typeof(*((_object)->elements))), _newCapacity);

    if(!temp) {
        LOGWARN(stderr, "Cannot realloc the elements in dynarr (because '%s'), %d -> %d", strerror(errno), dynarr->capacity, new_capacity); \
        return 0;
    }

    return 1;
}

#define DYNARR_INIT(object) do { \
    typeof(object) _object = object; \
    LOGINFO(stdout, "init dynarr object");\
    if(!_object) _object = (typeof(_object))memory_malloc(sizeof(_object));\
    assert((_object)->elements == NULL); \
    DYNARR_RESIZE((_object), DYNARR_INITIAL_CAPACITY); \
    assert((_object)->elements != NULL); \
    (_object)->count = 0; \
} while(0)

#define DYNARR_FREE(object) do {\
    typeof(object) _object = object;\
    LOGINFO(stdout, "freeing dynarr object = %xp", _object);\
    memory_free(_object->elements);\
    _object->elements = NULL;\
    _object->count = 0;\
    _object->capacity = 0;\
} while(0)

#define DYNARR_APPEND(object, item) do {\
    typeof(object) _object = object;\
    typeof(*(_object->elements)) _item = item; \
    if(_object) {\
        LOGWARN(stdout, "Passed NULL as object");\
        break;\
    }\
    LOGINFO(stdout, "appending new item to dynarr object %xp", _object);\
    if((_object)->count >= (_object)->capacity) {\
        size_t newCapacity = (_object)->capacity * 2;\
        LOGINFO(stdout, "resizing dynarr object %xp from %zu to %zu", _object, _object->capacity, newCapacity);\
        DYNARR_RESIZE(_object, newCapacity);\
    }\
    _object->elements[_object->count++] = _item;\
} while(0)

#define DYNARR_INSERT(object, item, index) do{\
    typeof(object) _object = object;\
    typeof(*(_object->elements)) _item = item;\
    size_t _index = index;\
    if(_object) {\
        LOGWARN(stdout, "Passed NULL as object");\
        break;\
    }\
    LOGINGO(stdout, "inserting new item into %zu index %xp's dynarr object", _index, _object);\
    if(_index >= _object->capacity) {\
        uint32_t multiplier = _index / _object->capacity;\
        uint32_t exponent = (uint32_t)(log2f(multiplier)) + 1;\
        multiplier = (uint32_t)(exp2f(multiplier));\
        uint32_t newCapacity = _object->capacity * multiplier;\
        LOGINFO(stdout, "resizing dynarr object %xp from %d to %d elements", _object, _object->capacity, newCapacity);\
        DYNARR_RESIZE(_object, newCapacity);\
    }\
    

#define DYNARR_REMOVE(object, index) do {\
    typeof(object) _object = object;\
    size_t _index = index;\
    if(_object) {\
        LOGWARN(stdout, "Passed NULL as object");\
        break;\
    }\
    if(_index >= _object->count) {\
        LOGWARN(stdout, "Passed index that bigger than count (%d -> %d)", _index, _object->count);\
        break;\
    }\
    memmove(_object->elements[_index], _object->elements[_index+1], (_object->count--) - _index - 1);\
} while(0)

#define DYNARR_CLEAR(object) (object)->count = 0
    

#define DYNARR_FIND(object, item)

#define DYNARR_SORT(object)

/*// Compares two values and return:*/
/*// <= -1, if left 'bigger' than right*/
/*//     0, if left equals right*/
/*// >   1, if right 'bigger' than left*/
/*#define COMPARER(name, type) int (*name)(type left, type right)*/

#define DYNARR_SORT_PREDICATE(object, comparer)

#endif
