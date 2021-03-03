#include "farray.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void 
assoc_float(void *  array_entry, int newidx ,void *  init_value){
	*((float*)array_entry+newidx) = *(float*)init_value;
}

array_t * 
farray_new(int cnt_i){
	return array1D_new(cnt_i, sizeof(float));
}

array_t * 
farray2D_new(int cnt_i, int cnt_j){
	return array2D_new(cnt_i, cnt_j, sizeof(float));
}

void 
farray_init(array_t *  array, float init_value){
	array_init(array, &init_value, assoc_float);
}

array_error_t 
farray_get(array_t *  array, int index, float *  result){
	return array_get(array, index, assoc_float, result);
}

array_error_t 
farray2D_get(array_t *  array, int i, int j, float *  result){
	return array2D_get(array, i, j, assoc_float, result);
}

array_error_t 
farray_set(array_t *  array, int index, float value){
	return array_set(array, index, &value, assoc_float);
}

array_error_t 
farray2D_set(array_t *  array, int i, int j, float value){
	return array2D_set(array, i, j, &value, assoc_float);
}
