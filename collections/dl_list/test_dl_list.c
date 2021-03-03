#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "dl_list.h"

#ifndef DEBUG_LOG_ARGS
	#if debug != 0
		#define DEBUG_LOG_ARGS(fmt, ...) printf((fmt), __VA_ARGS__)
	#else
		#define DEBUG_LOG_ARGS(fmt, ...)
	#endif
#endif

#ifndef DEBUG_LOG
	#if debug != 0
		#define DEBUG_LOG(msg) printf((msg))
	#else
		#define DEBUG_LOG(msg)
	#endif
#endif

static void test_dl_list_alloc_free() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	assert(list != NULL);
	assert(list->cnt == 0);
	assert(list->first == NULL);
	assert(list->last == NULL);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_append() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	assert(list != NULL);
	assert(list->cnt == 0);
	assert(list->first == NULL);
	assert(list->last == NULL);

	int data1 = 1;
	int data2 = 2;

	dl_list_append(list, (void*)&data1);

	assert(list->cnt == 1);
	assert(list->first != NULL);
	assert(list->last != NULL);
	assert(list->last == list->first);

	assert(list->first->data == &data1);

	assert(list->first->next == NULL);
	assert(list->first->prev == NULL);

	dl_list_append(list, (void*)&data2);

	assert(list->cnt == 2);
	assert(list->first != NULL);
	assert(list->last != NULL);
	assert(list->last != list->first);

	assert(list->first->data == &data1);
	assert(list->last->data == &data2);

	assert(list->first->next->data == &data2);
	assert(list->last->prev->data == &data1);

	assert(list->first->next == list->last);
	assert(list->first->next->next == NULL);
	assert(list->first->next->prev == list->first);
	assert(list->first->prev == NULL);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_prepend() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	assert(list != NULL);
	assert(list->cnt == 0);
	assert(list->first == NULL);
	assert(list->last == NULL);

	int data1 = 1;
	int data2 = 2;

	dl_list_prepend(list, (void*)&data1);

	assert(list->cnt == 1);
	assert(list->first != NULL);
	assert(list->last != NULL);
	assert(list->last == list->first);

	assert(list->first->data == &data1);

	assert(list->first->next == NULL);
	assert(list->first->prev == NULL);

	dl_list_prepend(list, (void*)&data2);

	assert(list->cnt == 2);
	assert(list->first != NULL);
	assert(list->last != NULL);
	assert(list->last != list->first);

	assert(list->first->data == &data2);
	assert(list->last->data == &data1);

	assert(list->first->next->data == &data1);
	assert(list->last->prev->data == &data2);

	assert(list->first->next == list->last);
	assert(list->first->next->next == NULL);
	assert(list->first->next->prev == list->first);
	assert(list->first->prev == NULL);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_insert_prepend() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	assert(list != NULL);
	assert(list->cnt == 0);
	assert(list->first == NULL);
	assert(list->last == NULL);

	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	dl_list_append(list, (void*)&data1);
	dl_list_append(list, (void*)&data2);
	dl_list_append(list, (void*)&data3);

	assert(list->cnt == 3);
	
	assert(list->first != list->last);
	assert(list->first->next->prev == list->first);

	int data4 = 4;
	int data6 = 6;

	dl_list_insert_prepend(list, &data3, &data4);
	dl_list_insert_prepend(list, &data6, &data4);

	assert(list->cnt == 4);
	//assert(test_dl_list_check_chain(list));

	assert(list->first->next->next->data == &data4);
	assert(list->first->next->next->next->prev->data == &data4);

	assert(list->last->prev->data == &data4);

	dl_list_clear(list);

	assert(list->cnt == 0);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_insert_append() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	assert(list != NULL);
	assert(list->cnt == 0);
	assert(list->first == NULL);
	assert(list->last == NULL);

	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	dl_list_append(list, (void*)&data1);
	dl_list_append(list, (void*)&data2);
	dl_list_append(list, (void*)&data3);

	assert(list->cnt == 3);
	//assert(test_dl_list_check_chain(list));

	int data4 = 4;
	int data6 = 6;

	dl_list_insert_append(list, &data2, &data4);
	dl_list_insert_append(list, &data6, &data4);

	assert(list->cnt == 4);
	//assert(test_dl_list_check_chain(list));

	assert(list->first->next->next->data == &data4);
	assert(list->first->next->next->next->prev->data == &data4);

	assert(list->last->prev->data == &data4);

	dl_list_clear(list);

	assert(list->cnt == 0);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_insert_prepend_idx() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	assert(list != NULL);
	assert(list->cnt == 0);
	assert(list->first == NULL);
	assert(list->last == NULL);

	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	dl_list_append(list, (void*)&data1);
	dl_list_append(list, (void*)&data2);
	dl_list_append(list, (void*)&data3);

	assert(list->cnt == 3);
	
	assert(list->first != list->last);
	assert(list->first->next->prev == list->first);

	int data4 = 4;

	dl_list_insert_prepend_idx(list, 2, &data4);
	dl_list_insert_prepend_idx(list, 5, &data4);

	assert(list->cnt == 4);

	assert(list->first->next->next->data == &data4);
	assert(list->first->next->next->next->prev->data == &data4);

	assert(list->last->prev->data == &data4);

	dl_list_clear(list);

	assert(list->cnt == 0);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_insert_append_idx() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	assert(list != NULL);
	assert(list->cnt == 0);
	assert(list->first == NULL);
	assert(list->last == NULL);

	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	dl_list_append(list, (void*)&data1);
	dl_list_append(list, (void*)&data2);
	dl_list_append(list, (void*)&data3);

	assert(list->cnt == 3);

	int data4 = 4;

	dl_list_insert_append_idx(list, 1, &data4);
	dl_list_insert_append_idx(list, 12, &data4);

	assert(list->cnt == 4);

	assert(list->first->next->next->data == &data4);
	assert(list->first->next->next->next->prev->data == &data4);

	assert(list->last->prev->data == &data4);

	dl_list_clear(list);

	assert(list->cnt == 0);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_get() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	dl_list_append(list, (void*)&data1);
	dl_list_append(list, (void*)&data2);
	dl_list_append(list, (void*)&data3);

	assert(list->cnt == 3);

	assert(dl_list_get(list, 0) == &data1);
	assert(dl_list_get(list, 1) == &data2);
	assert(dl_list_get(list, 2) == &data3);

	int data4 = 4;

	dl_list_insert_append_idx(list, 1, &data4);
	assert(dl_list_get(list, 2) == &data4);

	dl_list_clear(list);

	assert(list->cnt == 0);
	assert(dl_list_get(list, 2) == NULL);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_remove() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	dl_list_append(list, (void*)&data1);
	dl_list_append(list, (void*)&data2);
	dl_list_append(list, (void*)&data4);
	dl_list_append(list, (void*)&data3);
	
	assert(list->cnt == 4);


	assert(dl_list_remove(list, 0) == &data1);
	assert(list->cnt == 3);
	assert(dl_list_remove(list, 1) == &data4);
	assert(list->cnt == 2);
	assert(dl_list_remove(list, 0) == &data2);
	assert(list->cnt == 1);
	assert(dl_list_remove(list, 0) == &data3);
	assert(list->cnt == 0);

	dl_list_clear(list);

	assert(list->cnt == 0);
	assert(dl_list_get(list, 2) == NULL);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void my_free_func(void *data) {
	free(data);
}

static void test_dl_list_remove_free() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	dl_list_t* list = dl_list_new();

	int *data1 = malloc(sizeof(int));
	*data1 = 1;
	int *data2 = malloc(sizeof(int));
	*data2 = 2;
	int *data3 = malloc(sizeof(int));
	*data3 = 3;
	int *data4 = malloc(sizeof(int));
	*data4 = 4;

	dl_list_append(list, (void*)data1);
	dl_list_append(list, (void*)data2);
	dl_list_append(list, (void*)data4);
	dl_list_append(list, (void*)data3);
	
	assert(list->cnt == 4);


	dl_list_remove_free(list, 0, my_free_func);
	assert(list->cnt == 3);
	dl_list_remove_free(list, 1, my_free_func);
	assert(list->cnt == 2);
	dl_list_remove_free(list, 0, NULL);
	assert(list->cnt == 1);
	dl_list_remove_free(list, 0, my_free_func);
	assert(list->cnt == 0);

	dl_list_clear(list);

	assert(list->cnt == 0);
	assert(dl_list_get(list, 2) == NULL);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static bool __dl_list_search_int_gt2(void *item, void* searchdata) {
	(void)searchdata;
	return *(int *)item > 2;
}

static bool __dl_list_search_int_lt3(void *item, void* searchdata) {
	(void)searchdata;
	return *(int *)item <= 3;
}

static void test_dl_list_search_once() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);
	
	dl_list_t* list = dl_list_new();

	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	dl_list_append(list, (void*)&data1);
	dl_list_append(list, (void*)&data2);
	dl_list_append(list, (void*)&data4);
	dl_list_append(list, (void*)&data3);
	
	assert(list->cnt == 4);

	assert(hgen_search_once(list, NULL, __dl_list_search_int_gt2) == &data4);

	assert(hgen_search_once_id(list, NULL, __dl_list_search_int_gt2) == 2);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_dl_list_search() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);
	
	dl_list_t* list = dl_list_new();

	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	dl_list_append(list, (void*)&data1);
	dl_list_append(list, (void*)&data2);
	dl_list_append(list, (void*)&data4);
	dl_list_append(list, (void*)&data3);
	
	assert(list->cnt == 4);

	dl_list_t* search_res = hgen_search(list, NULL, __dl_list_search_int_lt3);

	assert(search_res->cnt == 3);
	assert(search_res->first->data == &data1);
	assert(search_res->first->next->data == &data2);
	assert(search_res->first->next->next->data == &data3);

	dl_list_free(&search_res);

	assert(search_res == NULL);

	assert(dl_list_get(list, 0) == &data1);
	assert(dl_list_get(list, 1) == &data2);
	assert(dl_list_get(list, 2) == &data4);

	dl_list_free(&list);

	assert(list == NULL);

	DEBUG_LOG("<<<\n");
}

int main(int argc, char **argv) {
	(void)argc; (void)argv;
	DEBUG_LOG(">> Start taw tests:\n");

	test_dl_list_alloc_free();

	test_dl_list_append();

	test_dl_list_prepend();

	test_dl_list_insert_prepend();

	test_dl_list_insert_append();

	test_dl_list_insert_prepend_idx();

	test_dl_list_insert_append_idx();

	test_dl_list_get();

	test_dl_list_remove();

	test_dl_list_remove_free();

	test_dl_list_search_once();

	test_dl_list_search();

	DEBUG_LOG("<< end taw tests:\n");

	return 0;
}

