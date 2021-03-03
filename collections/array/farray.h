#ifndef FARRAY_H
#define FARRAY_H

#include "array.h"

void assoc_float(void *  array_entry, int newidx ,void *  init_value);

array_t * farray_new(int cnt_i);
array_t * farray2D_new(int cnt_i, int cnt_j);

void farray_init(array_t *  array, float init_value);

array_error_t farray_get(array_t *  array, int index,float *  result);
array_error_t farray2D_get(array_t *  array, int i, int j, float *  result);

array_error_t farray_set(array_t *  array, int index, float value);
array_error_t farray2D_set(array_t *  array, int i, int j, float value);

#endif
