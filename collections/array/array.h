
#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
	ARRAY_ERR_UNDERFLOW = -1,
	ARRAY_ERR_OVERFLOW = 0,
	ARRAY_ERR_OK = 1
} array_error_t;

typedef struct {
	int cnt;
	int size;
} dimension_t;

typedef struct {
	dimension_t * config;
	int size;
	size_t entrysize;
	void * entries;
} array_t;

typedef struct {
	size_t entrysize;
	int length;
	int index;
	array_t * array;
} array_iterator_t;

typedef struct {
	size_t entrysize;
	int length;
	int index_x;
	int index_y;
	array_t * array;
} array_iterator2D_t;

array_t * array_new(int dimensions, int dimension_size, size_t entry_size);
array_t * array1D_new(int cnt_i, size_t entry_size);
array_t * array2D_new(int cnt_i, int cnt_j, size_t entry_size);

array_t * array_copy_deep(array_t *  array);

void array_init(array_t *  array, void *  init_value, void (*assoc_func)(void *  array_entry, int newidx ,void *  init_value));

array_error_t array_get(array_t *  array, int index, void (*assoc_func)(void *  result, int newidx ,void *  value),void *  result);
array_error_t array2D_get(array_t *  array, int i, int j, void (*assoc_func)(void *  result, int newidx ,void *  value), void *  result);

array_error_t array_set(array_t *  array, int index, void *  value, void (*assoc_func)(void *  array_entry, int newidx ,void *  value));
array_error_t array2D_set(array_t *  array, int i, int j, void *  value, void (*assoc_func)(void *  array_entry, int newidx ,void *  value));

array_iterator_t * array_iterator_new(array_t *  array);
bool array_iterator_has_next(array_iterator_t *  iterator);
void * array_iterator_next(array_iterator_t *  iterator);
void array_iterator_free(array_iterator_t *  iterator);

array_iterator2D_t * array_iterator2D_new(array_t *  array);
bool array_iterator2D_has_next(array_iterator2D_t *  iterator);
void * array_iterator2D_next(array_iterator2D_t *  iterator);
void array_iterator2D_free(array_iterator2D_t *  iterator);

void array_free(array_t *  array);

#endif
