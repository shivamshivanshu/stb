#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>

typedef void *(*vec_alloc_fn)(void *ctx, size_t bytes);
typedef void (*vec_dealloc_fn)(void *ctx, void *ptr, size_t bytes);

struct vector {
    unsigned char *data;
    size_t len;
    size_t cap;
    size_t elem_size;
    vec_alloc_fn alloc;
    vec_dealloc_fn dealloc;
    void *alloc_ctx;
};

/* elem_size must be positive. Pass both callbacks as NULL for malloc/free. */
bool vec_init(struct vector *vec, size_t elem_size,
              vec_alloc_fn alloc, vec_dealloc_fn dealloc, void *ctx);

void vec_destroy(struct vector *vec);
void vec_clear(struct vector *vec);

/* Replace the contents with count copies of value. */
bool vec_assign(struct vector *vec, size_t count, const void *value);
bool vec_push_back(struct vector *vec, const void *elem);
bool vec_pop_back(struct vector *vec);

/* Copy one element into out. Return false if idx is out of bounds. */
bool vec_at(const struct vector *vec, size_t idx, void *out);

/* Insert before idx. idx == len appends. */
bool vec_insert(struct vector *vec, size_t idx, const void *elem);
bool vec_erase(struct vector *vec, size_t idx);

bool vec_empty(const struct vector *vec);
size_t vec_size(const struct vector *vec);
size_t vec_capacity(const struct vector *vec);

bool vec_reserve(struct vector *vec, size_t elem_count);
bool vec_shrink_to_fit(struct vector *vec);

#endif
