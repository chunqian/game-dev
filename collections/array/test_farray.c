#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "farray.h"

int 
main() {
	#ifdef debug 
		printf("test collections float array:\n");
	#endif
	
	array_t * oneD = farray_new(10);
	array_t * twoD = farray2D_new(5,5);
	
	farray_init(oneD, 5.f);
	farray_init(twoD, 15.f);

	array_error_t farray_res;
	
	farray_res = farray_set(oneD, 8, 100.f);
	assert(farray_res == ARRAY_ERR_OK);
	
	farray_res = farray2D_set(twoD, 3, 3, 101.f);
	assert(farray_res == ARRAY_ERR_OK);
	
	float getresult;

	farray_res = farray_get(oneD, 2, &getresult);
	assert(farray_res == ARRAY_ERR_OK);
	assert(getresult == 5.f);
	
	farray_res = farray2D_get(twoD, 1, 3, &getresult);
	assert(farray_res == ARRAY_ERR_OK);
	assert(getresult == 15.f);
	
	farray_res = farray_get(oneD, 8, &getresult);
	assert(farray_res == ARRAY_ERR_OK);
	assert(getresult == 100.f);
	
	farray_res = farray2D_get(twoD, 3, 3, &getresult);
	assert(farray_res == ARRAY_ERR_OK);
	assert(getresult == 101.f);

	farray_res = farray_get(oneD, 44, &getresult);
	assert(farray_res == ARRAY_ERR_OVERFLOW);
	
	farray_res = farray2D_get(twoD, 34, 3, &getresult);
	assert(farray_res == ARRAY_ERR_OVERFLOW);
	
	farray_res = farray_get(oneD, -44, &getresult);
	assert(farray_res == ARRAY_ERR_UNDERFLOW);
	
	farray_res = farray2D_get(twoD, -34, 3, &getresult);
	assert(farray_res == ARRAY_ERR_UNDERFLOW);
	
	array_free(oneD);
	array_free(twoD);
	
	#ifdef debug 
		printf("EO test collections float array:\n");
	#endif
	
	return 0;
}
