#ifndef H_SCOBA_DYNARR
#define H_SCOBA_DYNARR

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "logging.h"
#include "memory.h"

#define SCOBA_DYNARR_INITIAL_CAPACITY   8
#define SCOBA_DYNARR_RESIZE_POLICY(cap) ((cap)*2)

#define SCOBA_DYNARR_RESULT_OK      0
#define SCOBA_DYNARR_ERROR_NULLOBJ  128

#define SCOBA_DYNARR_RESIZE_ERROR   1

#define SCOBA_DYNARR_DEFINE_NAMED(name, elementsType) typedef struct {  \
    elementsType* elements;                                             \
    size_t count;                                                       \
    size_t capacity;                                                    \
} name

SCOBA_DYNARR_DEFINE_NAMED(dynarr_voided, void);

uint8_t  scoba_dynarr_resize(void* object, size_t element_size, size_t new_capacity);
#define SCOBA_DYNARR_RESIZE(object, new_capacity) scoba_dynarr_resize((void*)(object), sizeof(*((object)->elements)), new_capacity)

uint8_t scoba_dynarr_init(void* object, size_t element_size, size_t init_capacity);
#define SCOBA_DYNARR_INIT(object, init_capacity) scoba_dynarr_init((void*)(object), sizeof(*((object)->elements)), init_capacity)

uint8_t scoba_dynarr_free(void* object);

uint8_t scoba_dynarr_resize(void* object, size_t element_size, size_t new_capacity) {
    if(!object) {
        SCOBA_LOGWARN(stderr, "Passed NULL as object");
        return SCOBA_DYNARR_ERROR_NULLOBJ;
    }
    dynarr_voided* dynarr = (dynarr_voided*)object;
    if(new_capacity <= dynarr->capacity) return SCOBA_DYNARR_RESULT_OK;
    SCOBA_LOGINFO(stdout, "resizing dynarr object = %p: elements %p, count %zu, capacity %zu; new capacity = %zu", 
            (void*)dynarr, (void*)dynarr->elements, dynarr->count, dynarr->capacity, new_capacity);
    void* temp = scoba_memory_recalloc(dynarr->elements, element_size, new_capacity);

    if(!temp) {
        SCOBA_LOGWARN(stderr, "Cannot realloc the elements in dynarr (%s), %zu -> %zu", strerror(errno), dynarr->capacity, new_capacity);
        return SCOBA_DYNARR_RESIZE_ERROR;
    }

    dynarr->elements = temp;
    dynarr->capacity = new_capacity;

    return SCOBA_DYNARR_RESULT_OK;
}

uint8_t scoba_dynarr_init(void* object, size_t element_size, size_t init_capacity) {
    if(!object) {
        SCOBA_LOGWARN(stderr, "Passed NULL as object");
        return SCOBA_DYNARR_ERROR_NULLOBJ;
    }

    dynarr_voided* dynarr = (dynarr_voided*)object;
    SCOBA_LOGINFO(stdout, "initializing dynarr at %p", (void*)dynarr);
    dynarr->count = 0;
    dynarr->capacity = 0;
    return scoba_dynarr_resize(dynarr, element_size, ((init_capacity == 0) ? SCOBA_DYNARR_INITIAL_CAPACITY : init_capacity));
}

uint8_t scoba_dynarr_free(void* object) {
    if(!object) {
        SCOBA_LOGWARN(stderr, "Passed NULL as object");
        return SCOBA_DYNARR_ERROR_NULLOBJ;
    }
    
    SCOBA_LOGINFO(stdout, "freeing dynarr at %p", object);
    dynarr_voided* dynarr = (dynarr_voided*)object;
    scoba_memory_free(dynarr->elements);
    dynarr->elements = NULL;
    dynarr->count = 0;
    dynarr->capacity = 0;
    return SCOBA_DYNARR_RESULT_OK;
}

/*#define DYNARR_APPEND(object, item) do {\*/
/*    typeof(object) _object = object;\*/
/*    typeof(*(_object->elements)) _item = item; \*/
/*    if(_object) {\*/
/*        LOGWARN(stdout, "Passed NULL as object");\*/
/*        break;\*/
/*    }\*/
/*    LOGINFO(stdout, "appending new item to dynarr object %xp", _object);\*/
/*    if((_object)->count >= (_object)->capacity) {\*/
/*        size_t newCapacity = (_object)->capacity * 2;\*/
/*        LOGINFO(stdout, "resizing dynarr object %xp from %zu to %zu", _object, _object->capacity, newCapacity);\*/
/*        DYNARR_RESIZE(_object, newCapacity);\*/
/*    }\*/
/*    _object->elements[_object->count++] = _item;\*/
/*} while(0)*/
/**/
/*#define DYNARR_INSERT(object, item, index) do{\*/
/*    typeof(object) _object = object;\*/
/*    typeof(*(_object->elements)) _item = item;\*/
/*    size_t _index = index;\*/
/*    if(_object) {\*/
/*        LOGWARN(stdout, "Passed NULL as object");\*/
/*        break;\*/
/*    }\*/
/*    LOGINGO(stdout, "inserting new item into %zu index %xp's dynarr object", _index, _object);\*/
/*    if(_index >= _object->capacity) {\*/
/*        uint32_t multiplier = _index / _object->capacity;\*/
/*        uint32_t exponent = (uint32_t)(log2f(multiplier)) + 1;\*/
/*        multiplier = (uint32_t)(exp2f(multiplier));\*/
/*        uint32_t newCapacity = _object->capacity * multiplier;\*/
/*        LOGINFO(stdout, "resizing dynarr object %xp from %d to %d elements", _object, _object->capacity, newCapacity);\*/
/*        DYNARR_RESIZE(_object, newCapacity);\*/
/*    }\*/
/**/
/**/
/*#define DYNARR_REMOVE(object, index) do {\*/
/*    typeof(object) _object = object;\*/
/*    size_t _index = index;\*/
/*    if(_object) {\*/
/*        LOGWARN(stdout, "Passed NULL as object");\*/
/*        break;\*/
/*    }\*/
/*    if(_index >= _object->count) {\*/
/*        LOGWARN(stdout, "Passed index that bigger than count (%d -> %d)", _index, _object->count);\*/
/*        break;\*/
/*    }\*/
/*    memmove(_object->elements[_index], _object->elements[_index+1], (_object->count--) - _index - 1);\*/
/*} while(0)*/
/**/
/*#define DYNARR_CLEAR(object) (object)->count = 0*/
/**/
/**/
/*#define DYNARR_FIND(object, item)*/
/**/
/*#define DYNARR_SORT(object)*/

/*// Compares two values and return:*/
/*// <= -1, if left 'bigger' than right*/
/*//     0, if left equals right*/
/*// >   1, if right 'bigger' than left*/
/*#define COMPARER(name, type) int (*name)(type left, type right)*/

/*#define DYNARR_SORT_PREDICATE(object, comparer)*/

#endif
