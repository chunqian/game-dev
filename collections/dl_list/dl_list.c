#include "dl_list.h"

static void __dl_list_reset(dl_list_t *list) {
	list->last = NULL;
	list->first = NULL;
	list->cnt = 0;
}

static dl_list_item_t* __dl_list_item_new(void *data) {
	dl_list_item_t* newitem = malloc(sizeof(dl_list_item_t));
	if(newitem) {
		newitem->data = data;
		newitem->next = NULL;
		newitem->prev = NULL;
	}
	return newitem;
}

static void __dl_list_item_free(dl_list_item_t **item) {
	if ( item != NULL && *item != NULL ) {
		dl_list_item_t *to_delete = *item;
		free(to_delete);
		*item = NULL;
	}
}

static void __dl_list_add_first_node(dl_list_t *list, dl_list_item_t* node) {
	list->first = node;
	list->last = node;
}

static void __dl_list_append_node(dl_list_item_t* basenode, dl_list_item_t* newnode) {
	
	newnode->prev = basenode;

	if (basenode->next != NULL) {
		newnode->next = basenode->next;
		basenode->next->prev = newnode;
	} 

	basenode->next = newnode;

}

static void __dl_list_prepend_node(dl_list_item_t* basenode, dl_list_item_t* newnode) {
	
	newnode->next = basenode;

	if (basenode->prev != NULL) {
		newnode->prev = basenode->prev;
		basenode->prev->next = newnode;
	}

	basenode->prev = newnode;

}

static void __dl_list_remove_node(dl_list_t *list, dl_list_item_t* node) {
	
	if (list->cnt == 1) {
		__dl_list_item_free(&node);
		__dl_list_reset(list);
	} else if (list->cnt > 1) {
		if (node->prev == NULL) {
			list->first = node->next;
			list->first->prev = NULL;
		} else if (node->next == NULL) {
			node->prev->next = NULL;
			list->last = node->prev;
		} else {
			dl_list_item_t* next = node->next;
			dl_list_item_t* prev = node->prev;
			prev->next = next;
			next->prev = prev;
		}
		__dl_list_item_free(&node);
		--list->cnt;
	}

}

static dl_list_item_t* __search_node_by_data(dl_list_t *list, void *data) {
	dl_list_item_t* result = NULL;
	dl_list_item_t* cur_node = list->first;

	while(cur_node != NULL) {
		if ( cur_node->data == data ) {
			result = cur_node;
			break;
		}
		cur_node = cur_node->next;
	}

	return result;
}

static dl_list_item_t* __search_node_by_idx(dl_list_t *list, uint32_t idx) {
	dl_list_item_t* result = NULL;
	dl_list_item_t* cur_node = list->first;

	if (idx < list->cnt) {
		
		uint32_t cur_idx = -1;

		while(cur_node != NULL) {
			++cur_idx;
			if ( cur_idx == idx ) {
				result = cur_node;
				break;
			}
			cur_node = cur_node->next;
		}
	}

	return result;
}

static void __dl_list_clear(dl_list_t* list) {
	dl_list_item_t* cur_item = list->first;
	dl_list_item_t* tmp_item = NULL;

	while(cur_item != NULL) {
		tmp_item = cur_item->next;
		__dl_list_item_free(&cur_item);
		cur_item = tmp_item;
	}

	__dl_list_reset(list);
}

#if 0
//###############################################################################################################
//Eof private Section
//###############################################################################################################
#endif

dl_list_t* dl_list_new() {
	dl_list_t *newlist = malloc(sizeof(dl_list_t));
	if ( newlist ) {
		__dl_list_reset(newlist);
	}

	return newlist;
}

void dl_list_free(dl_list_t**list) {  
	if ( list != NULL && *list != NULL ) {
		dl_list_t *to_delete = *list;
		
		__dl_list_clear(to_delete);

		free(to_delete);
		*list = NULL;
	}
}

void dl_list_clear(dl_list_t* list) {
	__dl_list_clear(list);
}

void dl_list_append(dl_list_t *list, void *data) { 
	if (list != NULL) {
		dl_list_item_t* newitem = __dl_list_item_new(data);

		if (list->cnt == 0) {
			__dl_list_add_first_node(list, newitem);
		} else {
			__dl_list_append_node(list->last, newitem);
			list->last = newitem;
		}

		++list->cnt;
	}
}

void dl_list_prepend(dl_list_t *list, void *data) {  

	if (list != NULL) {
		dl_list_item_t* newitem = __dl_list_item_new(data);

		if (list->cnt == 0) {
			__dl_list_add_first_node(list, newitem);
		} else {
			__dl_list_prepend_node(list->first, newitem);
			list->first = newitem;
		}

		++list->cnt;
	}

}

void dl_list_insert_prepend(dl_list_t *list, void *sibling, void *value) {  
	if ( list != NULL ) {
		dl_list_item_t* sibl_node = __search_node_by_data(list, sibling);
		if (sibl_node != NULL) {
			dl_list_item_t* newitem = __dl_list_item_new(value);

			__dl_list_prepend_node(sibl_node, newitem);

			++list->cnt;
		}
	}
}

void dl_list_insert_append(dl_list_t *list, void *sibling, void *value) {  
	if ( list != NULL ) {
		dl_list_item_t* sibl_node = __search_node_by_data(list, sibling);
		if (sibl_node != NULL) {
			dl_list_item_t* newitem = __dl_list_item_new(value);

			__dl_list_append_node(sibl_node, newitem);
			
			++list->cnt;
		}
	}
}

void dl_list_insert_prepend_idx(dl_list_t *list, uint32_t index, void *value) {  
	if ( list != NULL ) {
		dl_list_item_t* found = __search_node_by_idx(list, index);

		if (found != NULL) {
			dl_list_item_t* newitem = __dl_list_item_new(value);

			__dl_list_prepend_node(found, newitem);

			++list->cnt;
		}

	}	
}

void dl_list_insert_append_idx(dl_list_t *list, uint32_t index, void *value) {  
	if ( list != NULL ) {
		dl_list_item_t* found = __search_node_by_idx(list, index);

		if (found != NULL) {
			dl_list_item_t* newitem = __dl_list_item_new(value);

			__dl_list_append_node(found, newitem);

			++list->cnt;
		}

	}	
}

void* dl_list_get(dl_list_t *list, uint32_t index) { 
	void *result = NULL;

	if ( list != NULL ) {
		dl_list_item_t* found = __search_node_by_idx(list, index);
		if (found) {
			result = found->data;
		}
	}

	return result;
}



void* dl_list_remove(dl_list_t *list, uint32_t index) {  
	void *result = NULL;

	if ( list != NULL ) {
		dl_list_item_t* found = __search_node_by_idx(list, index);
		if (found) {
			result = found->data;
			__dl_list_remove_node(list, found);
		}
	}

	return result;
}

void dl_list_remove_free(dl_list_t *list, uint32_t index, void (freefunc)(void *data)) {  
	
	if ( list != NULL ) {
		dl_list_item_t* found = __search_node_by_idx(list, index);
		if (found) {

			if(freefunc != NULL) {
				freefunc(found->data);
			} else {
				free(found->data);
			}
			__dl_list_remove_node(list, found);
		}
	}

}

void* hgen_search_once(dl_list_t *list, void *search_data, bool (*searchfunc)(void*item, void *search_data)) {  
	void *result = NULL;

	dl_list_item_t* cur_node = list->first;

	while(cur_node != NULL) {
		if ( searchfunc(cur_node->data, search_data) ) {
			result = cur_node->data;
			break;
		}
		cur_node = cur_node->next;
	}

	return result; 
}

int hgen_search_once_id(dl_list_t *list, void *search_data, bool (*searchfunc)(void*item, void *search_data)) {
	int result = -1;
	bool found = false;

	dl_list_item_t* cur_node = list->first;

	while(cur_node != NULL) {
		++result;
		if ( searchfunc(cur_node->data, search_data) ) {
			found = true;
			break;
		}
		cur_node = cur_node->next;
	}

	return (found ? result : -1 ); 
}

dl_list_t* hgen_search(dl_list_t *list, void *search_data, bool (*searchfunc)(void*item, void *search_data)) {  
	dl_list_t *result = dl_list_new();

	dl_list_item_t* cur_node = list->first;

	while(cur_node != NULL) {
		if ( searchfunc(cur_node->data, search_data) ) {
			dl_list_append(result, cur_node->data);
		}
		cur_node = cur_node->next;
	}

	return result; 
}

void dl_list_each(dl_list_t *list, EACH_FUNC eachfunc) {

	dl_list_item_t* cur_node = list->first;

	while(cur_node != NULL) {

		eachfunc(&cur_node->data);
		
		cur_node = cur_node->next;
	
	}

}

void  dl_list_each_data(dl_list_t *list, void* eachdata, EACH_FUNC_DATA eachfunc) {
	dl_list_item_t* cur_node = list->first;

	while(cur_node != NULL) {

		eachfunc(&cur_node->data, eachdata);
		
		cur_node = cur_node->next;
	
	}
}