#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"

void 
assoc_int(void * array_entry, int newidx ,void * init_value) {
	*((int*)array_entry+newidx) = *(int*)init_value;
}

void 
assoc_float(void * array_entry, int newidx ,void * init_value) {
	*((float*)array_entry+newidx) = *(float*)init_value;
}

int 
main() {
	#ifdef debug 
		printf("test collections array:\n");
	#endif
	#if 0
		//test array allocation 1D and 2D
	#endif
	
	array_t * oneD;
	array_t * twoD;
	
	oneD = array_new(1, 5, sizeof(int));
	twoD = array_new(2, 10, sizeof(float));
	
	assert(oneD->config->cnt == 1);
	assert(oneD->config->size == 5);
    
	assert(twoD->config->cnt == 2);
	assert(twoD->config->size == 10);
	
	array_free(oneD);
	array_free(twoD);
	
	oneD = array1D_new(5, sizeof(int));
	twoD = array2D_new(2, 10, sizeof(float));
	
	assert(oneD->config->cnt == 1);
	assert(oneD->config->size == 5);
	
	assert(twoD->config->cnt == 2);
	assert(twoD->config->size == 10);
	
	array_free(oneD);
	array_free(twoD);

	oneD = array1D_new(2, sizeof(int));
	twoD = array2D_new(2, 2, sizeof(float));
	
	int charinit = 3000;
	float doubleinit = 2.5;
    
	#ifdef debug 
		printf("primitive value: %p\n", &charinit);
	#endif
	array_init(oneD, &charinit, assoc_int);
	array_init(twoD, &doubleinit, assoc_float);
    
	int *iarray = (int*)oneD->entries;
	
	#ifdef debug 
		printf("first addr: %p, val: %i\n", &*iarray, iarray[0]);
	#endif
	assert(iarray[0] == charinit);
	assert(iarray[1] == charinit);
	
	#ifdef debug 
		printf("#####\n");
	#endif
	
	
	float *farray = (float*)twoD->entries;
	
	assert(farray[0] == 2.5);
	assert(farray[1] == 2.5);
	assert(farray[2] == 2.5);
	assert(farray[3] == 2.5);
	
	float newvalue = 34.f;
	array_error_t acresult = array_set(twoD, 2, &newvalue, assoc_float);
	
	float resultfloat;
	
	#ifdef debug 
		printf("result float addr declared: %p\n", &resultfloat);
	#endif
	acresult = array_get(twoD, 2, assoc_float, &resultfloat);
	
	assert(acresult == ARRAY_ERR_OK);
	assert(resultfloat == newvalue);
	
	acresult = array2D_get(twoD, 1, 1, assoc_float, &resultfloat);
	assert(acresult == ARRAY_ERR_OK);
	assert(resultfloat == 2.5f);
	
	acresult = array2D_get(twoD, 0, 1, assoc_float, &resultfloat);
	assert(acresult == ARRAY_ERR_OK);
	assert(resultfloat == newvalue);
	
	float dnewvalue = (2*newvalue);
	acresult = array2D_set(twoD, 0,0, &dnewvalue, assoc_float);
	
	acresult = array2D_get(twoD, 0, 0, assoc_float, &resultfloat);
	assert(acresult == ARRAY_ERR_OK);
	assert(resultfloat == dnewvalue);
	assert(resultfloat == (2*newvalue));
	
	array_iterator_t * it = array_iterator_new(oneD);
	#ifdef debug 
		printf("oneD array contains[");
		while(array_iterator_has_next(it)) {
			int * curvalue = (int *)array_iterator_next(it);
			printf(" %i", *curvalue);
		}
		printf("]\n");
	#endif
	
	array_iterator_free(it);
	
	it = array_iterator_new(twoD);
	#ifdef debug 
		printf("twoD array contains[");
		while(array_iterator_has_next(it)) {
			float * curvalue = (float *)array_iterator_next(it);
			printf(" %f", *curvalue);		
		}
		printf("]\n");
	#endif
	array_iterator_free(it);
	
	array_t * copyoftwoD = array_copy_deep(twoD);
	
	assert(copyoftwoD != twoD);
	assert(copyoftwoD->entries != twoD->entries);
	assert(copyoftwoD->config != twoD->config);
	assert(copyoftwoD->size == twoD->size);
	assert(copyoftwoD->entrysize == twoD->entrysize);
	assert(copyoftwoD->config->cnt == twoD->config->cnt);
	assert(copyoftwoD->config->size == twoD->config->size);
	
	it = array_iterator_new(copyoftwoD);
	#ifdef debug 
		printf("twoD array contains[");
		while(array_iterator_has_next(it)) {
			float * curvalue = (float *)array_iterator_next(it);
			printf(" %f", *curvalue);
		}
		printf("]\n");
	#endif
	array_iterator_free(it);
	
	array_iterator2D_t * it2D = array_iterator2D_new(copyoftwoD);
	#ifdef debug 
		printf("twoD array 2D iterator contains[\n");
		while(array_iterator2D_has_next(it2D)) {
			printf("(x: %i, y: %i, ",it2D->index_x, it2D->index_y);
			float * curvalue = (float *)array_iterator2D_next(it2D);
			printf(" value: %f)\n", *curvalue);	
		}
		printf("]\n");
	#endif
	array_iterator2D_free(it2D);
	
	array_free(copyoftwoD);
	array_free(oneD);
	array_free(twoD);
	
	return 0;
}
