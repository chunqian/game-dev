#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

static void _test_tree_node_data_alloc_() {
	#ifdef debug
		printf(">>> tree node data \n");
	#endif
	
	{
		tree_node_data_t * data = tree_node_data_new();
		tree_node_data_free(data);
	}
	
	#ifdef debug
		printf("<<< tree node data \n");
	#endif
}

static void _test_tree_node_data_() {
	#ifdef debug
		printf(">>> tree node data \n");
	#endif
	
	_test_tree_node_data_alloc_();
	
	#ifdef debug
		printf("<<< tree node data \n");
	#endif
}

static void _test_alloc_node_() {
	#ifdef debug
		printf(">>> alloc node\n");
	#endif
	
	{
		tree_node_t * node = NULL;
		tree_node_free(&node);
	}
	
	{
		tree_node_t * node = tree_node_new();
		assert(node->data == NULL);
		assert(node->parent == NULL);
		assert(node->children->start == NULL);
		assert(node->children->end == NULL);
		assert(node->children->len == 0);
		tree_node_free(&node);
		assert(node == NULL);
	}
	
	{
		tree_node_t * node;
		tree_node_new_dest(&node);
		assert(node->data == NULL);
		assert(node->parent == NULL);
		assert(node->children->start == NULL);
		assert(node->children->end == NULL);
		assert(node->children->len == 0);
		tree_node_free(&node);
		assert(node == NULL);
	}
	
	{
		tree_node_t * node = tree_node_new();
		tree_node_t * node1 = tree_node_new();
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int);
		*i = 666;
		data_t * data = data_new((void**)&i, size_int);
		node->parent = node1;
		node->data = data;
		assert(node->data != NULL);
		assert(node->parent != NULL);
		assert(node->children->start == NULL);
		assert(node->children->end == NULL);
		assert(node->children->len == 0);
		tree_node_clear(node);
		assert(node != NULL);
		assert(node->parent == NULL);
		assert(node->data == NULL);
		assert(node->children->start == NULL);
		assert(node->children->end == NULL);
		assert(node->children->len == 0);
		
		tree_node_free(&node);
		tree_node_free(&node1);
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
		tree_node_t * node = tree_node_new();
		tree_node_t * node1 = tree_node_new();
		tree_node_t * child = tree_node_new();
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int);
		*i = 666;
		data_t * data = data_new((void**)&i, size_int);
		node->parent = node1;
		node->data = data;
		tree_node_prepend_child(node, child);
		assert(node->data != NULL);
		assert(node->parent != NULL);
		assert(node->children->len == 1);
		assert(node->children->start->data->data == child);
		assert(node->children->end->data->data == child);
		tree_node_clear(node);
		assert(node != NULL);
		assert(node->parent == NULL);
		assert(node->data == NULL);
		assert(node->children != NULL);
		assert(node->children->len == 0);
		assert(node->children->start == NULL);
		assert(node->children->end == NULL);
		tree_node_free(&node);
		tree_node_free(&node1);
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
		tree_node_t * node = tree_node_new();
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 667;
		
		data_t * data_dest;
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);

		tree_node_attach_data(node, NULL);
		assert(node->data == NULL);
		
		tree_node_attach_data(node, data);
		assert(node->data == data);
		assert(node->data != data2);
		
		tree_node_attach_data(node, data2);
		assert(node->data == data);
		assert(node->data != data2);
		
		data_dest = tree_node_attach_data_override(node, data2);
		assert(node->data != data);
		assert(data_dest == data);
		assert(node->data == data2);
		
		tree_node_attach_data_override_dest(&data_dest, node, data);
		assert(node->data == data);
		assert(data_dest == data2);
		assert(node->data != data2);
		
		tree_node_free(&node);
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
		tree_node_t * node = tree_node_new();
		tree_node_t * node2 = tree_node_new();
		tree_node_t * child = tree_node_new();
		
		node->parent = node2;
		node2->parent = node;
		tree_node_t * node_copy = NULL;
		tree_node_t * node_copy2 = NULL;
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		unsigned int * i2 = malloc(size_int); *i2 = 667;
		unsigned int * i3 = malloc(size_int); *i3 = 668;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * data2 = data_new((void**)&i2, size_int);
		data_t * data3 = data_new((void**)&i3, size_int);
		
		tree_node_attach_data(node, data);
		tree_node_attach_data(node2, data2);
		tree_node_attach_data(child, data3);
		
		tree_node_prepend_child(node, child);
		assert(child->parent == node );
		
		node_copy = tree_node_copy(NULL);
		assert(node_copy == NULL);
		
		node_copy = tree_node_copy(node);
		assert(node_copy != NULL);
		assert(node_copy->data != NULL);
		assert(node_copy->parent != NULL);
		assert(node != node_copy);
		assert(node->data != node_copy->data);
		assert(node->parent == node_copy->parent);
		assert(node->children->len == 1);
		assert(node->children->len == node_copy->children->len);
		assert(node_copy->children->start != NULL);
		assert(node_copy->children->start == node_copy->children->end);
		assert(node_copy->children->start->data != NULL);
		tree_node_t * thedata = (tree_node_t *)node_copy->children->start->data->data;
		tree_node_t * thedata2 = (tree_node_t *)node->children->start->data->data;
		assert(thedata != NULL);
		assert(thedata2 != NULL);
		assert(thedata != thedata2);
		assert(thedata->parent == node_copy );
		assert(thedata2->parent == node);
		assert(node_copy->parent == node2);
		data_t * childdata = thedata->data;
		data_t * childdata2 = thedata2->data; 

		assert(childdata != childdata2);
		assert(childdata->data != childdata2->data);
		assert(*((unsigned int *)childdata->data) == 668);
		assert(*((unsigned int *)childdata->data) == *((unsigned int *)childdata2->data));
		
		tree_node_copy_dest(&node_copy2, NULL);
		assert(node_copy2 == NULL);
		
		tree_node_copy_dest(&node_copy2, node2);
		assert(node_copy2 != NULL);
		assert(node_copy2->data != NULL);
		assert(node_copy2->parent != NULL);
		assert(node2 != node_copy2);
		assert(node2->data != node_copy2->data);
		assert(node2->parent == node_copy2->parent);
		assert(node_copy2->children->start == NULL);
		assert(node_copy2->children->start == node_copy2->children->end);
		
		assert(node_copy2->parent == node);
		
		tree_node_free(&node);
		tree_node_free(&node2);
		tree_node_free(&node_copy);
		tree_node_free(&node_copy2);
			
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
		tree_node_t * node = tree_node_new();
		
		size_t size_int = sizeof(unsigned int);
		unsigned int * i = malloc(size_int); *i = 666;
		
		data_t * data = data_new((void**)&i, size_int);
		data_t * detached;
		
		tree_node_attach_data(node, data);
		assert(node->data == data);

		detached = tree_node_detach_data(node);
		assert(node->data == NULL);
		assert(detached == data);
		
		tree_node_attach_data(node, data);
		assert(node->data == data);
		
		tree_node_detach_data_dest(&detached, node);
		assert(node->data == NULL);
		assert(detached == data);
		
		tree_node_free(&node);
		data_free(detached);		
	}
	
	#ifdef debug
		printf("<<< detach data from node\n");
	#endif
}

static void _test_tree_node_append_child_() {
	
	tree_node_t * _parent = tree_node_new();
	tree_node_t * _newchild = tree_node_new();
	tree_node_t * onlyforcheck = _newchild;
	
	//you will loose rights for child, because the parent will take a look :)
	tree_node_append_child(_parent, &_newchild);
	//if you want it back you must use => _parent->children->end
	assert(_newchild == NULL);
	assert(_parent->children->start->data->data == onlyforcheck);
	
	tree_node_free(&_parent);
}

static void _test_tree_node_() {
	#ifdef debug 
		printf(">>> test tree nodes\n");
	#endif

	_test_tree_node_data_();
	_test_alloc_node_();
	_test_clear_node_();
	_test_attach_data_node_();
	_test_copy_node_();
	_test_detach_data_node_();
	_test_tree_node_append_child_();
	//TODO Continue with prepend and insert methods
	#ifdef debug 
		printf("<<< test tree nodes:\n");
	#endif
}

static void _test_tree_() {
	#ifdef debug 
		printf(">>> test tree\n");
	#endif
	
	
	#ifdef debug 
		printf("<<< test tree:\n");
	#endif
}

int main() {
	#ifdef debug 
		printf(">>> test collections tree:\n");
	#endif
	
	_test_tree_node_();
	_test_tree_();
	
	#ifdef debug 
		printf("<<< test collections tree:\n");
	#endif
	return 0;
}
