#ifndef H_SCOBA_DELEGATE
#define H_SCOBA_DELEGATE

#include <stdint.h>

#include "dynarr.h"

#define SCOBA_DELEGATE_APPEND(object, item)         SCOBA_DYNARR_APPEND(object, item)
#define SCOBA_DELEGATE_INSERT(object, item, idx)    SCOBA_DYNARR_INSERT(object, item, idx)
#define SCOBA_DELEGATE_REMOVE(object, item, idx)    SCOBA_DYNARR_REMOVE(object, item, idx)
#define SCOBA_DELEGATE_CLEAR(object)                SCOBA_DYNARR_CLEAR(object)

#define SCOBA_DECLARE_DELEGATE(delegate_type_name, ...)                     \
typedef struct {                                                            \
    typedef void (*items[])(__VA_ARGS__);                                   \
    size_t count;                                                           \
    size_t capacity;                                                        \
} delegate_type_name;

typedef void (*scoba_delegate_type)(void*);

struct scoba_default_delegate {
    scoba_delegate_type* items;
    size_t count;
    size_t capacity;
}

#define SCOBA_DELEGATE_EXECUTE_ALL(delegate, ...)           \
for(size_t __idx = 0; __idx < (delegate).count; ++__idx) {  \
    (delegate).items[__idx](__VA_ARGS__);                   \
}

void
scoba_default_delegate_execute_all(struct scoba_default_delegate delegate, void* args) {
    for(size_t idx = 0; idx < delegate; ++idx) {
        delegate.items[idx](args);
    }
}

#define SCOBA_DELEGATE_EXECUTE(delegate, which, ...) (delegate).items[which](__VA_ARGS__)

void
scoba_default_delegate_execute(struct scoba_default_delegate delegate, size_t which, void* args) {
    delegate.items[which](args);
}

#endif //H_SCOBA_DELEGATE
