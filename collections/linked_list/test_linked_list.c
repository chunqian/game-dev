#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

static void _test_old_list() {
	#ifdef debug
		printf(">>> old linked list\n");
	#endif
	linkedlist * list = linkedlistutils.new();
	
	unsigned char * databla = calloc(12 ,sizeof(unsigned char));
	memcpy(databla ,"test huhu!!", 12);
	linkedlistutils.append(list, databla);

	databla = calloc(12 ,sizeof(unsigned char));
	memcpy(databla ,"test haha!!", 12);
	linkedlistutils.append(list, databla);
	
	databla = calloc(12 ,sizeof(unsigned char));
	memcpy(databla ,"test hehe!!", 12);
	linkedlistutils.append(list, databla);
	
	databla = calloc(12 ,sizeof(unsigned char));
	memcpy(databla ,"test hoho!!", 12);
	linkedlistutils.append(list, databla);
	
	#ifdef debug 
	{
		printf("cnt elements: %i\n", list->len);
		element * curelement;
		for( curelement = list->start; curelement != NULL ; curelement = curelement->next ) {
			printf("element: %s\n", curelement->data);
		}
	}
	#endif
	
	void *data = linkedlistutils.get(list,2);
	assert(data != NULL);
	#ifdef debug
		printf("data idx: 2 = %s\n", data);
	#endif
	
	data = linkedlistutils.get(list,3);
	assert(data != NULL);
	#ifdef debug
		printf("data idx: 3 = %s\n", data);
	#endif
	
	data = linkedlistutils.get(list,12);
	assert(data == NULL);
	#ifdef debug
		printf("data idx: 12 = %s\n", data);
	#endif
	linkedlistutils.clear(list, free);
	#ifdef debug
		printf("clear list: size = %i\n", list->len);
	
		if ( list->len == 0 ) {
			printf("now list is empty\n");
		}

		printf("delete list\n");
	#endif
	linkedlistutils.delete(list, free);
	
	#if 0
		// test linked list with local primitive
	#endif
	
	list = linkedlistutils.new();
	for ( unsigned int i = 0; i < 12; linkedlistutils.append(list, (int*)++i) );
	
	#ifdef debug 
	{
		printf("unsigned int elements: %i\n", list->len);
		element * curelement;
		for( curelement = list->start; curelement != NULL ; curelement = curelement->next ) {
			printf("unsigned int: %i\n", curelement->data);
		}
	}
	#endif
	
	linkedlistutils.delete(list, NULL);
	#ifdef debug
		printf("<<< old linked list nodes\n");
	#endif
}

static void _test_alloc_node_() {
	#ifdef debug
		printf(">>> alloc node\n");
	#endif
	
	{
		ll_node_t * node = NULL;
		ll_node_free(&node);
	}
	
	{
		ll_node_t * node = ll_node_new();
		assert(node->data == NULL);
		assert(node->next == NULL);
		ll_node_free(&node);
		assert(node == NULL);
	}
	
	{
		ll_node_t * node;
		ll_node_new_dest(&node);
		assert(node->data == NULL);
		assert(node->next == NULL);
		ll_node_free(&node);
		assert(node == NULL);
	}
	
	{
		ll_node_t * node = ll_node_new();
		ll_node_t * node1 = ll_node_new();
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int);
		*i = 666;
		data_t * data = data_new((void**)&i, size_int);
		node->next = node1;
		node->data = data;
		assert(node->data != NULL);
		assert(node->next != NULL);
		ll_node_clear(node);
		assert(node != NULL);
		assert(node->next == NULL);
		assert(node->data == NULL);
		
		ll_node_free(&node);
		ll_node_free(&node1);
	}
	
	#ifdef debug
		printf("<<< alloc node\n");
	#endif
}

static void _test_clear_node_() {
	#ifdef debug
		printf(">>> clear node\n");
	#endif
	
	{
		ll_node_t * node = ll_node_new();
		ll_node_t * node1 = ll_node_new();
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int);
		*i = 666;
		data_t * data = data_new((void**)&i, size_int);
		node->next = node1;
		node->data = data;
		assert(node->data != NULL);
		assert(node->next != NULL);
		ll_node_clear(node);
		assert(node != NULL);
		assert(node->next == NULL);
		assert(node->data == NULL);
		ll_node_free(&node);
		ll_node_free(&node1);
	}
	
	#ifdef debug
		printf("<<< clear node\n");
	#endif
}

static void _test_attach_data_node_() {
		#ifdef debug
		printf(">>> attach data to node\n");
	#endif
	
	{
		ll_node_t * node = ll_node_new();
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 667;
		
		data_t * data_dest;
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);

		ll_node_attach_data(node, NULL);
		assert(node->data == NULL);
		
		ll_node_attach_data(node, data);
		assert(node->data == data);
		assert(node->data != data2);
		
		ll_node_attach_data(node, data2);
		assert(node->data == data);
		assert(node->data != data2);
		
		data_dest = ll_node_attach_data_override(node, data2);
		assert(node->data != data);
		assert(data_dest == data);
		assert(node->data == data2);
		
		ll_node_attach_data_override_dest(&data_dest, node, data);
		assert(node->data == data);
		assert(data_dest == data2);
		assert(node->data != data2);
		
		ll_node_free(&node);
		data_free(data2);
	}
	
	#ifdef debug
		printf("<<< attach data to node\n");
	#endif
}

static void _test_copy_node_() {
	#ifdef debug
		printf(">>> copy node\n");
	#endif
	
	{
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		node->next = node2;
		node2->next = node;
		ll_node_t * node_copy = NULL;
		ll_node_t * node_copy2 = NULL;
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 667;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);

		ll_node_attach_data(node, data);
		ll_node_attach_data(node2, data2);
		
		node_copy = ll_node_copy(NULL);
		assert(node_copy == NULL);
		
		node_copy = ll_node_copy(node);
		assert(node_copy != NULL);
		assert(node_copy->data != NULL);
		assert(node_copy->next != NULL);
		assert(node != node_copy);
		assert(node->data != node_copy->data);
		assert(node->next == node_copy->next);
		assert(node_copy->next == node2);
		
		ll_node_copy_dest(&node_copy2, NULL);
		assert(node_copy2 == NULL);
		
		ll_node_copy_dest(&node_copy2, node2);
		assert(node_copy2 != NULL);
		assert(node_copy2->data != NULL);
		assert(node_copy2->next != NULL);
		assert(node2 != node_copy2);
		assert(node2->data != node_copy2->data);
		assert(node2->next == node_copy2->next);
		assert(node_copy2->next == node);
		
		ll_node_free(&node);
		ll_node_free(&node2);
		ll_node_free(&node_copy);
		ll_node_free(&node_copy2);
			
	}
	
	#ifdef debug
		printf("<<< copy node\n");
	#endif
}

static void _test_detach_data_node_() {
	#ifdef debug
		printf(">>> detach data from node\n");
	#endif
	
	{
		ll_node_t * node = ll_node_new();
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * detached;
		
		ll_node_attach_data(node, data);
		assert(node->data == data);

		detached = ll_node_detach_data(node);
		assert(node->data == NULL);
		assert(detached == data);
		
		ll_node_attach_data(node, data);
		assert(node->data == data);
		
		ll_node_detach_data_dest(&detached, node);
		assert(node->data == NULL);
		assert(detached == data);
		
		ll_node_free(&node);	
		data_free(detached);
	}
	
	#ifdef debug
		printf("<<< detach data from node\n");
	#endif
}

static void _test_ll_nodes() {
	#ifdef debug
		printf(">>> linked list nodes\n");
	#endif
	
	_test_alloc_node_();
	_test_clear_node_();
	_test_attach_data_node_();
	_test_copy_node_();
	_test_detach_data_node_();
	
	#ifdef debug
		printf("<<< linked list nodes\n");
	#endif
}

static void _test_alloc_list_() {
	#ifdef debug
		printf(">>> alloc linked list\n");
	#endif
	
	{
		#ifdef debug
			printf(">>> free empty list \n");
		#endif
		llist_t * list = llist_new();
		llist_t * list2 = NULL;
		llist_new_dest(&list2);
		
		llist_free(&list);
		llist_free(&list2);
		
		assert(list == NULL);
		assert(list2 == NULL);
		
		#ifdef debug
			printf("<<< free empty list \n");
		#endif
	}
	
	{
		#ifdef debug
			printf(">>> clear empty list \n");
		#endif
		llist_t * list = llist_new();
		llist_t * list2 = NULL;
		llist_new_dest(&list2);
		
		llist_clear(list);
		llist_clear(list2);
		
		assert(list != NULL);
		assert(list2 != NULL);
		
		llist_free(&list);
		llist_free(&list2);
		
		assert(list == NULL);
		assert(list2 == NULL);
		
		#ifdef debug
			printf("<<< clear empty list \n");
		#endif
	}
	
	#ifdef debug
		printf("<<< alloc linked list\n");
	#endif
}

static void _test_add_node_list_() {
	#ifdef debug
		printf(">>> add node to linked list\n");
	#endif
	
	{
		#ifdef debug
			printf(">>> append \n");
		#endif
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 666;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);
		
		ll_node_attach_data(node, data);
		ll_node_attach_data(node2, data2);
		
		llist_t * list = llist_new();
		llist_append_node(list, node);
		llist_append_node(list, node2);
		
		assert(list->len == 2);
		assert(list->start != NULL);
		assert(list->start == node);
		assert(list->start->next == node2);
		assert(list->end != NULL);
		assert(list->end == node2);
		assert(list->end->next == NULL);
		
		llist_free(&list);
		assert(list == NULL);
		
		#ifdef debug
			printf("<<< append \n");
		#endif
	}
	
	{
		#ifdef debug
			printf(">>> prepend \n");
		#endif
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 666;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);
		
		ll_node_attach_data(node, data);
		ll_node_attach_data(node2, data2);
		
		llist_t * list = llist_new();
		llist_prepend_node(list, node);
		llist_prepend_node(list, node2);
		
		assert(list->len == 2);
		assert(list->start != NULL);
		assert(list->start == node2);
		assert(list->start->next == node);
		assert(list->end != NULL);
		assert(list->end == node);
		assert(list->end->next == NULL);
		
		llist_free(&list);
		assert(list == NULL);
		
		#ifdef debug
			printf("<<< prepend \n");
		#endif
	}
	
	#ifdef debug
		printf("<<< add node to linked list\n");
	#endif
}

static void _test_insert_list_() {
	#ifdef debug
		printf(">>> insert node to linked list\n");
	#endif
	
	{
		#ifdef debug
			printf(">>> after \n");
		#endif
		
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		ll_node_t * node3 = ll_node_new();
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 667;
		unsigned int * i3 = malloc(size_int); *i3 = 668;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);
		data_t * data3 = data_new((void**)&i3, size_int);
		
		ll_node_attach_data(node, data);
		ll_node_attach_data(node2, data2);
		ll_node_attach_data(node3, data3);
		
		llist_t * list = llist_new();
		
		llist_insert_after(NULL, NULL, NULL);
		llist_insert_after(list, NULL, NULL);
		assert(list != NULL);
		assert(list->start == NULL);
		assert(list->end == NULL);		
		assert(list->len == 0);
		
		llist_insert_after(list, node, NULL);
		assert(list != NULL);
		assert(list->start == NULL);
		assert(list->end == NULL);		
		assert(list->len == 0);
		
		llist_insert_after(list, node, node2);
		assert(list != NULL);
		assert(list->start == NULL);
		assert(list->end == NULL);		
		assert(list->len == 0);
		
		llist_append_node(list, node);
		assert(list != NULL);
		assert(list->start == node);
		assert(list->end == node);		
		assert(list->len == 1);
		
		llist_insert_after(list, node, node2);
		assert(list != NULL);
		assert(list->start == node);
		assert(node->next == node2);
		assert(list->end == node2);		
		assert(list->len == 2);
		
		llist_insert_after(list, node, node3);
		assert(list != NULL);
		assert(list->start == node);
		assert(node->next == node3);
		assert(node3->next == node2);
		assert(list->end == node2);		
		assert(list->len == 3);
		
		llist_free(&list);
		
		#ifdef debug
			printf("<<< after \n");
		#endif
	}
	
	{
		#ifdef debug
			printf(">>> before \n");
		#endif

		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		ll_node_t * node3 = ll_node_new();
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 667;
		unsigned int * i3 = malloc(size_int); *i3 = 668;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);
		data_t * data3 = data_new((void**)&i3, size_int);
		
		ll_node_attach_data(node, data);
		ll_node_attach_data(node2, data2);
		ll_node_attach_data(node3, data3);
		
		llist_t * list = llist_new();
		
		llist_insert_before(NULL, NULL, NULL);
		llist_insert_before(list, NULL, NULL);
		assert(list != NULL);
		assert(list->start == NULL);
		assert(list->end == NULL);		
		assert(list->len == 0);
		
		llist_insert_before(list, node, NULL);
		assert(list != NULL);
		assert(list->start == NULL);
		assert(list->end == NULL);		
		assert(list->len == 0);
		
		llist_insert_before(list, node, node2);
		assert(list != NULL);
		assert(list->start == NULL);
		assert(list->end == NULL);		
		assert(list->len == 0);
		
		llist_append_node(list, node);
		assert(list != NULL);
		assert(list->start == node);
		assert(list->end == node);		
		assert(list->len == 1);
		
		llist_insert_before(list, node, node2);
		assert(list != NULL);
		assert(list->start == node2);
		assert(node2->next == node);
		assert(list->end == node);		
		assert(list->len == 2);
		
		llist_insert_before(list, node, node3);
		assert(list != NULL);
		assert(list->start == node2);
		assert(node2->next == node3);
		assert(node3->next == node);
		assert(list->end == node);		
		assert(list->len == 3);
		
		llist_free(&list);
		
		#ifdef debug
			printf("<<< before \n");
		#endif
	}
	
	#ifdef debug
		printf("<<< insert node to linked list\n");
	#endif
}


static void _test_del_node_list_() {
	#ifdef debug
		printf(">>> delete node linked list\n");
	#endif
	
	{
		#ifdef debug
			printf(">>> direct \n");
		#endif
		llist_t * list = llist_new();
		
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		ll_node_t * node3 = ll_node_new();
		
		llist_append_node(list, node);
		llist_append_node(list, node2);
		llist_append_node(list, node3);
		
		assert(list != NULL);
		assert(list->start == node);
		assert(list->end == node3);
		assert(list->len == 3);
		assert(node->next == node2);
		assert(node2->next == node3);
		assert(node3->next == NULL);
		
		llist_delete_node(list, node2);
		assert(list->start == node);
		assert(list->end == node3);
		assert(list->len == 2);
		assert(node->next == node3);
		assert(node3->next == NULL);
		
		llist_delete_node(list, node3);
		assert(list->start == node);
		assert(list->end == node);
		assert(list->len == 1);
		assert(node->next == NULL);
		
		llist_delete_node(list, node);
		assert(list->start == NULL);
		assert(list->end == NULL);
		assert(list->len == 0);
		
		llist_free(&list);
		
		#ifdef debug
			printf("<<< direct \n");
		#endif
	}
	
	{
		#ifdef debug
			printf(">>> after \n");
		#endif
		llist_t * list = llist_new();
		
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		ll_node_t * node3 = ll_node_new();
		
		llist_append_node(list, node);
		llist_append_node(list, node2);
		llist_append_node(list, node3);
		
		assert(list != NULL);
		assert(list->start == node);
		assert(list->end == node3);
		assert(list->len == 3);
		assert(node->next == node2);
		assert(node2->next == node3);
		assert(node3->next == NULL);
		
		llist_delete_node_after(list, node2);
		assert(list->start == node);
		assert(list->end == node2);
		assert(list->len == 2);
		assert(node->next == node2);
		assert(node2->next == NULL);
		
		llist_delete_node_after(list, node2);
		assert(list->start == node);
		assert(list->end == node2);
		assert(list->len == 2);
		assert(node->next == node2);
		assert(node2->next == NULL);
		
		llist_delete_node_after(list, node);
		assert(list->start == node);
		assert(list->end == node);
		assert(list->len == 1);
		
		llist_delete_node_after(list, node);
		assert(list->start == node);
		assert(list->end == node);
		assert(list->len == 1);
		
		llist_free(&list);
		
		#ifdef debug
			printf("<<< after \n");
		#endif
	}
	
		{
		#ifdef debug
			printf(">>> before \n");
		#endif
		llist_t * list = llist_new();
		
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		ll_node_t * node3 = ll_node_new();
		
		llist_append_node(list, node);
		llist_append_node(list, node2);
		llist_append_node(list, node3);
		
		assert(list != NULL);
		assert(list->start == node);
		assert(list->end == node3);
		assert(list->len == 3);
		assert(node->next == node2);
		assert(node2->next == node3);
		assert(node3->next == NULL);
		
		llist_delete_node_before(list, node2);
		assert(list->start == node2);
		assert(list->end == node3);
		assert(list->len == 2);
		assert(node2->next == node3);
		assert(node3->next == NULL);
		
		llist_delete_node_before(list, node2);
		assert(list->start == node2);
		assert(list->end == node3);
		assert(list->len == 2);
		assert(node2->next == node3);
		assert(node3->next == NULL);
		
		llist_delete_node_before(list, node3);
		assert(list->start == node3);
		assert(list->end == node3);
		assert(list->len == 1);
		
		llist_delete_node_before(list, node3);
		assert(list->start == node3);
		assert(list->end == node3);
		assert(list->len == 1);
		
		llist_delete_node_before(list, node);
		assert(list->start == node3);
		assert(list->end == node3);
		assert(list->len == 1);
		
		llist_free(&list);
		
		#ifdef debug
			printf("<<< before \n");
		#endif
	}
	
	#ifdef debug
		printf("<<< delete node linked list\n");
	#endif
}

static void _test_append_list_() {
	#ifdef debug
		printf(">>> list append to list\n");
	#endif
	
	{
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		ll_node_t * node3 = ll_node_new();
		ll_node_t * node4 = ll_node_new();
		ll_node_t * node5 = ll_node_new();
		ll_node_t * node6 = ll_node_new();
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 667;
		unsigned int * i3 = malloc(size_int); *i3 = 668;
		unsigned int * i4 = malloc(size_int); *i4 = 669;
		unsigned int * i5 = malloc(size_int); *i5 = 670;
		unsigned int * i6 = malloc(size_int); *i6 = 671;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);
		data_t * data3 = data_new((void**)&i3, size_int);
		data_t * data4 = data_new((void**)&i4, size_int);
		data_t * data5 = data_new((void**)&i5, size_int);
		data_t * data6 = data_new((void**)&i6, size_int);
		
		ll_node_attach_data(node, data);
		ll_node_attach_data(node2, data2);
		ll_node_attach_data(node3, data3);
		ll_node_attach_data(node4, data4);
		ll_node_attach_data(node5, data5);
		ll_node_attach_data(node6, data6);
		
		llist_t * list = llist_new();
		llist_t * list2 = llist_new();
		llist_append_node(list, node);
		llist_append_node(list, node2);
		llist_append_node(list, node3);
		llist_append_node(list2, node4);
		llist_append_node(list2, node5);
		llist_append_node(list2, node6);
		
		llist_append_list(list, list2);
		assert(list2->len == 3);
		assert(list2->start == node4);
		assert(node4->next == node5);
		assert(node5->next == node6);
		assert(list2->end == node6);
		
		assert(list->len == 6);
		assert(list->start == node);
		assert(node->next == node2);
		assert(node2->next == node3);
		assert(node3->next != NULL);
		assert(node3->next->next != NULL);
		assert(node3->next->next->next != NULL);
		assert(node3->next->next->next == list->end);
		
		llist_free(&list2);
		llist_free(&list);
		
	}
	
	#ifdef debug
		printf("<<< list append to list\n");
	#endif
}

static void _test_prepend_list_() {
	#ifdef debug
		printf(">>> list prepend to list\n");
	#endif
	
	{
		ll_node_t * node = ll_node_new();
		ll_node_t * node2 = ll_node_new();
		ll_node_t * node3 = ll_node_new();
		ll_node_t * node4 = ll_node_new();
		ll_node_t * node5 = ll_node_new();
		ll_node_t * node6 = ll_node_new();
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 667;
		unsigned int * i3 = malloc(size_int); *i3 = 668;
		unsigned int * i4 = malloc(size_int); *i4 = 669;
		unsigned int * i5 = malloc(size_int); *i5 = 670;
		unsigned int * i6 = malloc(size_int); *i6 = 671;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);
		data_t * data3 = data_new((void**)&i3, size_int);
		data_t * data4 = data_new((void**)&i4, size_int);
		data_t * data5 = data_new((void**)&i5, size_int);
		data_t * data6 = data_new((void**)&i6, size_int);
		
		ll_node_attach_data(node, data);
		ll_node_attach_data(node2, data2);
		ll_node_attach_data(node3, data3);
		ll_node_attach_data(node4, data4);
		ll_node_attach_data(node5, data5);
		ll_node_attach_data(node6, data6);
		
		llist_t * list = llist_new();
		llist_t * list2 = llist_new();
		llist_append_node(list, node);
		llist_append_node(list, node2);
		llist_append_node(list, node3);
		llist_append_node(list2, node4);
		llist_append_node(list2, node5);
		llist_append_node(list2, node6);
		
		llist_prepend_list(list, list2);
		assert(list2->len == 3);
		assert(list2->start == node4);
		assert(node4->next == node5);
		assert(node5->next == node6);
		assert(list2->end == node6);
		
		assert(list->len == 6);
		assert(list->start != NULL);
		assert(list->start != NULL);
		assert(list->start->next != NULL);
		assert(list->start->next->next != NULL);
		assert(list->start->next->next->next == node);
		assert(node->next == node2);
		assert(node2->next == node3);
		assert(node3->next == NULL);
		assert(list->end == node3);
		
		llist_free(&list2);
		llist_free(&list);
		
	}
	
	#ifdef debug
		printf("<<< list prepend to list\n");
	#endif
}

static bool _ui_llist_cmp_lt_(void * nodedata, void * searchdata) {
	if ( nodedata != NULL &&  searchdata != NULL ) {	
		unsigned int node_val = *(unsigned int*)nodedata;
		unsigned int search_val = *(unsigned int*)searchdata;
		return node_val <= search_val;
	}
	return false;
}

static bool _ui_llist_cmp_gt_(void * nodedata, void * searchdata) {
	if ( nodedata != NULL &&  searchdata != NULL ) {	
		unsigned int node_val = *(unsigned int*)nodedata;
		unsigned int search_val = *(unsigned int*)searchdata;
		return node_val >= search_val;
	}
	return false;
}

static bool _ui_llist_cmp_ne_(void * nodedata, void * searchdata) {
	if ( nodedata != NULL &&  searchdata != NULL ) {	
		unsigned int node_val = *(unsigned int*)nodedata;
		unsigned int search_val = *(unsigned int*)searchdata;
		return node_val != search_val;
	}
	return false;
}

static void _test_search_list_() {
	#ifdef debug
		printf(">>> search list\n");
	#endif
	
	ll_node_t * node = ll_node_new();
	ll_node_t * node2 = ll_node_new();
	ll_node_t * node3 = ll_node_new();
	ll_node_t * node4 = ll_node_new();
	ll_node_t * node5 = ll_node_new();
	ll_node_t * node6 = ll_node_new();
	
	size_t size_int = sizeof(unsigned int);
	unsigned int * i = malloc(size_int); *i = 666;
	unsigned int * i2 = malloc(size_int); *i2 = 667;
	unsigned int * i3 = malloc(size_int); *i3 = 668;
	unsigned int * i4 = malloc(size_int); *i4 = 669;
	unsigned int * i5 = malloc(size_int); *i5 = 670;
	unsigned int * i6 = malloc(size_int); *i6 = 671;
	unsigned int search = 0;
	data_t * data = data_new((void**)&i, size_int);
	data_t * data2 = data_new((void**)&i2, size_int);
	data_t * data3 = data_new((void**)&i3, size_int);
	data_t * data4 = data_new((void**)&i4, size_int);
	data_t * data5 = data_new((void**)&i5, size_int);
	data_t * data6 = data_new((void**)&i6, size_int);
	
	ll_node_attach_data(node, data);
	ll_node_attach_data(node2, data2);
	ll_node_attach_data(node3, data3);
	ll_node_attach_data(node4, data4);
	ll_node_attach_data(node5, data5);
	ll_node_attach_data(node6, data6);
	
	llist_t * list = llist_new();
	llist_append_node(list, node);
	llist_append_node(list, node2);
	llist_append_node(list, node3);
	llist_append_node(list, node4);
	llist_append_node(list, node5);
	llist_append_node(list, node6);
	
	{
		#ifdef debug
			printf(">>> find all matches\n");
		#endif
		
		search = 666;
		llist_t * result = llist_search_node_all(list, &search, _ui_llist_cmp_ne_);
		assert(result->len == 5);
		assert(*(unsigned int*)result->start->data->data == 667);
		assert(*(unsigned int*)result->start->next->data->data == 668);
		assert(*(unsigned int*)result->start->next->next->data->data == 669);
		assert(*(unsigned int*)result->start->next->next->next->data->data == 670);
		assert(*(unsigned int*)result->start->next->next->next->next->data->data == 671);
		llist_free(&result);
		
		search = 669;
		llist_search_node_all_dest(&result, list, &search, _ui_llist_cmp_lt_);
		assert(result->len == 4);
		assert(*(unsigned int*)result->start->data->data == 666);
		assert(*(unsigned int*)result->start->next->data->data == 667);
		assert(*(unsigned int*)result->start->next->next->data->data == 668);
		assert(*(unsigned int*)result->start->next->next->next->data->data == 669);
		
		llist_free(&result);
		
		#ifdef debug
			printf("<<< find all matches\n");
		#endif
	}
	
	{
		#ifdef debug
			printf(">>> find first match\n");
		#endif
		search = 666;
		ll_node_t * result = llist_search_node_first(list, &search, _ui_llist_cmp_ne_);
		assert(result != NULL);
		assert(*(unsigned int*)result->data->data == 667);
		assert(result->next == NULL);
		
		ll_node_free(&result);
		
		search = 669;
		llist_search_node_first_dest(&result, list, &search, _ui_llist_cmp_gt_);
		assert(result != NULL);
		assert(*(unsigned int*)result->data->data == 669);
		assert(result->next == NULL);
		
		ll_node_free(&result);
		
		#ifdef debug
			printf("<<< find first match\n");
		#endif
	}
	
	llist_free(&list);
	
	#ifdef debug
		printf("<<< search list\n");
	#endif
}

static void _test_ll_list() {
	#ifdef debug
		printf(">>> linked list\n");
	#endif
	
	_test_alloc_list_();
	_test_add_node_list_();
	_test_insert_list_();
	_test_del_node_list_();
	_test_append_list_();
	_test_prepend_list_();
	_test_search_list_();
	
	#ifdef debug
		printf("<<< linked list\n");
	#endif
}

static void _test_new_list() {
	_test_ll_nodes();
	_test_ll_list();
}

int main() {
	#ifdef debug 
		printf("test collections linked list:\n");
	#endif
	
	_test_old_list();
	_test_new_list();

	return 0;
}
