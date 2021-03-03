#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

//NEW Version
#if 0
/**
	creates new empty node
*/
#endif
ll_node_t * ll_node_new(){ 
	ll_node_t * newnode = malloc(sizeof(ll_node_t));
	newnode->data = NULL;
	newnode->next = NULL;
	return newnode; 
} 
void ll_node_new_dest(ll_node_t ** dest){
	*dest = ll_node_new();
}

#if 0
/**
	deletes node. It will deletes data too
*/
#endif
void ll_node_free(ll_node_t ** _node){
	ll_node_t * node = *_node;
	if ( node != NULL ) {
		data_t * data = node->data;
		data_free(data);
		free(node);
		*_node = NULL;
	}
}
#if 0
/**
	deletes nodes content. It will deletes data too
*/
#endif
void ll_node_clear(ll_node_t *_node){
	ll_node_t * node = _node;
	data_t * data = node->data;
	data_free(data);
	node->data = NULL;
	node->next = NULL;
}
#if 0
/**
	attach new data to node. Does nothing if data exist.
*/
#endif
void ll_node_attach_data(ll_node_t * _node, data_t * _data){
	ll_node_t * node = _node;
	if(node->data == NULL) {
		node->data = _data;
	}
}
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one returned.
*/
#endif
data_t * ll_node_attach_data_override(ll_node_t * _node, data_t * data){
	ll_node_t * node = _node;
	data_t * olddata = node->data;
	node->data = data;
	return olddata;
}
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one will
	linked to dest pointer.
*/
#endif
void ll_node_attach_data_override_dest(data_t **dest, ll_node_t *node, data_t *data){
	*dest = ll_node_attach_data_override(node, data);
}
#if 0
/**
	Makes copy from src node and data inside. Return the new node with copied data. If src is NULL the return
	Value is NULL too.
*/
#endif
ll_node_t * ll_node_copy(ll_node_t * src){
	ll_node_t * copy = NULL;
	if ( src != NULL ){
		copy = ll_node_new();
		copy->data = data_copy(src->data);
		copy->next = src->next;
	}
	return copy;
}
#if 0
/**
	Copy node src and saves result to dest.
*/
#endif
void ll_node_copy_dest(ll_node_t ** dest, ll_node_t * src) {
	*dest = ll_node_copy(src);
}
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist or data is NULL.
*/
#endif
data_t * ll_node_detach_data(ll_node_t * _node){
	data_t * data = NULL;
	ll_node_t * node = _node;
	if (node != NULL) {
		data = node->data;
		node->data = NULL;
	}
	return data;
}
#if 0
/**
	removes data from node and add the removed data to dest. If no data attached NULL will added.
*/
#endif
void ll_node_detach_data_dest(data_t ** dest, ll_node_t *node){
	*dest = ll_node_detach_data(node);
}

#if 0
/**
#########################################################
######################### List ##########################
#########################################################
*/
#endif

#if 0
/**
	creates new empty list
*/
#endif
llist_t * llist_new(){
	llist_t *newlist = malloc(sizeof(llist_t));
	newlist->start = NULL;
	newlist->end = NULL;
	newlist->len = 0;
	return newlist;
}
void llist_new_dest(llist_t **list){
	*list = llist_new();
}

static void _for_each_node_(llist_t * _list, void (*func)(ll_node_t ** _curnode)) {
	llist_t * list = _list;
	if (list != NULL) {
		ll_node_t * curnode = list->start;
		ll_node_t * tmp = NULL;
		while( curnode != NULL) {
			tmp = curnode->next;
			(*func)(&curnode);
			curnode = tmp;
		}
	}
}

#if 0
/**
 delete complete list.
*/
#endif
void llist_free(llist_t ** _list){
	llist_t * list = *_list;
	if (list != NULL) {
		_for_each_node_(list, ll_node_free);
		list->start = NULL;
		list->end = NULL;
		free(list);
		*_list = NULL;
	}
}

#if 0
/**
 clears whole list complete list. the data will be deleted.
*/
#endif
void llist_clear(llist_t *list){
	if (list != NULL) {
		_for_each_node_(list, ll_node_free );
		list->start = NULL;
		list->end = NULL;
		list->len = 0;
	}
}

#if 0
/**
	Add copy of node at end of list. It should be a new or not in use node. Otherwise there is an undefined behaviour.
*/
#endif
void llist_append_node(llist_t * _list, ll_node_t * _newnode){
	llist_t * list = _list;
	ll_node_t * newnode = _newnode;
	if ( list != NULL && newnode != NULL ) {
		if ( list->start == NULL && list->end == NULL) { 
			list->start = newnode; 
		} else {
			list->end->next = newnode;	
		}
		list->end = newnode;
		++list->len;
	}
}
#if 0
/**
Add element at beginning of list.
*/
#endif
void llist_prepend_node(llist_t * _list, ll_node_t * _newnode){
	llist_t * list = _list;
	ll_node_t * newnode = _newnode;
	if ( list != NULL && newnode != NULL ) {
		if ( list->start == NULL && list->end == NULL) { 
			list->end = newnode;
		} else {
			newnode->next = list->start;	
		}
		list->start = newnode;
		++list->len;
	}
}

#if 0
/**
Search node in list. returns node if found, otherwise NULL.
*/
#endif
static ll_node_t * _find_node_(llist_t * list, ll_node_t * node) {
	ll_node_t * next = list->start;
	ll_node_t * cur = next;
	while(cur != NULL) {
		next = cur->next;
		if ( cur == node ) return node;
		cur = next;
	}
	return NULL;
}

#if 0
/**
Search previous node in list. returns previous node if found, otherwise NULL. Return NULL if there is NO 
previous node found. If usednode contains node the search was success. if not success usednode contains NULL.
*/
#endif
static ll_node_t * _find_prev_node_(llist_t * list, ll_node_t * node, ll_node_t ** usednode) {
	ll_node_t * next = list->start;
	ll_node_t * cur = next;
	ll_node_t * prev = NULL;
	*usednode = NULL;
	while(cur != NULL) {
		next = cur->next;
		if ( cur == node ) {
			*usednode = node;
			return prev;
		}
		prev = cur;
		cur = next;
	}
	return NULL;
}



#if 0
/**
Insert Node after sibling.
*/
#endif
void llist_insert_before(llist_t * _list, ll_node_t * _sibling, ll_node_t * _newnode){
	llist_t * list = _list; 
	ll_node_t * sibling = _sibling; 
	ll_node_t * newnode = _newnode;
	ll_node_t * prev = NULL;
	ll_node_t * used = NULL;
	if (list != NULL && sibling != NULL && newnode != NULL ) {
		prev = _find_prev_node_(list, sibling, &used);
		if ( used == sibling ) {
			if(prev != NULL) {
				prev->next = newnode;		
			} else {
				list->start = newnode;
			}
			newnode->next = sibling;
			++list->len;
		}
	}
}

#if 0
/**
Insert Node before sibling.
*/
#endif
void llist_insert_after(llist_t * _list, ll_node_t * _sibling ,ll_node_t * _newnode){
	llist_t * list = _list; 
	ll_node_t * sibling = _sibling; 
	ll_node_t * newnode = _newnode;
	
	if (list != NULL && sibling != NULL && newnode != NULL && 
		(_find_node_(list, sibling) != NULL)) {
		ll_node_t * tmp = sibling->next;
		sibling->next = newnode;
		newnode->next = tmp;
		if ( tmp == NULL ) {
			list->end = newnode;
		}
		++list->len;
	}
}
#if 0
/**
Delete node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node(llist_t * _list, ll_node_t * _delnode){
	llist_t * list = _list; 
	ll_node_t * delnode = _delnode;
	ll_node_t * prev = NULL;
	ll_node_t * used = NULL;
	if (list != NULL && delnode != NULL ) {
		prev = _find_prev_node_(list, delnode, &used);
		if ( used == delnode ) {
			if(prev != NULL) {
				prev->next = delnode->next;
				if (delnode->next == NULL) {
					list->end = prev;
				}
			} else {
				list->start = delnode->next;
				if (delnode->next == NULL) {
					list->end = NULL;
				}
			}
			ll_node_free(&delnode);
			--list->len;
		}
	}
}
#if 0
/**
delete node after node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node_after(llist_t * _list, ll_node_t * _node){
	llist_t * list = _list; 
	ll_node_t * node = _node;
	ll_node_t * found = NULL;
	ll_node_t * todelete = NULL;
	ll_node_t * overnext = NULL;
	if (list != NULL && node != NULL ) {
		found = _find_node_(list, node);
		if(found != NULL) {
			todelete = found->next;
			if ( todelete != NULL ) {
				overnext = todelete->next;
				if ( overnext != NULL ) {
					found->next = overnext;
				} else {
					list->end = found;
					found->next = NULL;
				}
				ll_node_free(&todelete);
				--list->len;
			}
		} 
	}
}
#if 0
/**
delete node after node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node_before(llist_t * _list, ll_node_t * _node){
	llist_t * list = _list; 
	ll_node_t * node = _node;
	ll_node_t * used = NULL;
	ll_node_t * todelete = NULL;
	ll_node_t * prevprev = NULL;
	if (list != NULL && node != NULL ) {
		todelete = _find_prev_node_(list, node, &used);
		if(used != NULL) {
			prevprev = _find_prev_node_(list, todelete, &used);
			if (used != NULL) {
				//to delete has prev sibling
				if ( prevprev != NULL ) {
					prevprev->next = node;
				} else {
					//to delete is start of list
					list->start = node;
				}
				ll_node_free(&todelete);
				--list->len;
			}
		}
	}
}

#if 0
/**
	Copies(deep copy including data) all node from the list _src. The result is the starting node saved in
	_dest and the count of copied node stored in _copied.
*/
#endif

static void _copy_all_nodes_from_list_(llist_t * _src, ll_node_t ** _dest, ll_node_t ** _end, int * _copied) {
	llist_t * src = _src; 
	ll_node_t ** dest = _dest; 
	ll_node_t ** end = _end;
	int * copied = _copied;
	
	ll_node_t * start = NULL;
	ll_node_t * current = src->start;
	ll_node_t * last = NULL;
	ll_node_t * tmp = NULL;
	
	while(current != NULL) {
		tmp = ll_node_copy(current);
		tmp->next = NULL;
		if ( start == NULL ) {
			start = tmp;
		} else {
			last->next = tmp;
		}
		last = tmp;
		current = current->next;
		++*copied;
	}
	
	*end = last;
	*dest = start;
}

#if 0
/**
	Merges two lists. The first list is the starting list. list2 is the same as before and list one contains copies 
	of elements in list2.
*/
#endif
void llist_append_list(llist_t * _list, llist_t * _list2){
	llist_t * list = _list;
	llist_t * list2 = _list2;
	ll_node_t * startcopy = NULL;
	ll_node_t * endcopy = NULL;
	int copied = 0;
	_copy_all_nodes_from_list_(list2, &startcopy, &endcopy, &copied);
	if ( copied != 0 && startcopy != NULL ) {
		list->len += copied;
		if ( list->end != NULL ) {
			list->end->next = startcopy;
		} else {
			list->start = startcopy;
			
		}
		list->end = endcopy;
	}
}

#if 0
/**
Merges two lists. The second list is the starting list.
*/
#endif
void llist_prepend_list(llist_t * _list, llist_t * _list2){
	llist_t * list = _list;
	llist_t * list2 = _list2;
	ll_node_t * startcopy = NULL;
	ll_node_t * endcopy = NULL;
	int copied = 0;
	_copy_all_nodes_from_list_(list2, &startcopy, &endcopy, &copied);
	if ( copied != 0 && startcopy != NULL ) {
		list->len += copied;
		if ( list->end != NULL ) {
			endcopy->next = list->start;
			list->start = startcopy;
		} else {
			list->start = startcopy;
			list->end = endcopy;
		}
	}
}

static void _search_by_method_(llist_t * _src, llist_t * _dest, bool onlyone,
							   void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata)) {
	llist_t * src = _src; 
	llist_t * dest = _dest;
	ll_node_t * next = src->start;
	if( dest != NULL ) {
		while(next != NULL) {
			void * curdata = NULL;
			if ( next->data ) {
				curdata = next->data->data;
			}
			if((*searchmethod)(curdata, searchdata)) {
				ll_node_t * tmp = ll_node_copy(next);
				tmp->next = NULL;
				llist_append_node(dest, tmp);
				if(onlyone && dest->len == 1) {
					break;
				}
			}
			next = next->next;
		}
	}
}

#if 0
/**
Returns the all found nodes. The result is a linked list with a copy of all found elements. this 
result list will be the response
*/
#endif
llist_t * llist_search_node_all(llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata)) {
	llist_t * result = llist_new();
	if ( list != NULL && searchdata != NULL && searchmethod != NULL) {
		_search_by_method_(list, result, false, searchdata, searchmethod);
	}
	return result;
}
#if 0
/**
Returns the all found nodes. The result is a linked list with a copy of all found elements. The
Resultlist will add to the resultlistpointer.
*/
#endif
void llist_search_node_all_dest(llist_t ** resultlist, llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata)) {
	*resultlist = llist_new();
	if ( list != NULL && searchdata != NULL && searchmethod != NULL) {
		_search_by_method_(list, *resultlist, false, searchdata, searchmethod);
	}
}
#if 0
/**
returns the first node which data comparing functions returns true. The return value is the found node
or NULL if no node was found.
*/
#endif
ll_node_t * llist_search_node_first(llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata)) {
	llist_t result = { NULL, NULL, 0 };
	if ( list != NULL && searchdata != NULL && searchmethod != NULL) {
		_search_by_method_(list, &result, true, searchdata, searchmethod);
	}
	return result.start;
}
#if 0
/**
returns the first node which data comparing functions returns true. The result value is the found node
or NULL if no node was found and will add to the result pointer.
*/
#endif
void llist_search_node_first_dest(ll_node_t ** resultnode,llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata)) {
	llist_t result = { NULL, NULL, 0 };
	if ( list != NULL && searchdata != NULL && searchmethod != NULL) {
		_search_by_method_(list, &result, true, searchdata, searchmethod);
	}
	*resultnode = result.start;
}

#if 0
/**
returns the previous node which data comparing functions returns true. The return value is the found node
or NULL if no node was found.
*/
#endif
ll_node_t * llist_search_previous_node(llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata)) {
	llist_t result = { NULL, NULL, 0 };
	ll_node_t * foundprevnode = NULL;
	ll_node_t * used = NULL;
	if ( list != NULL && searchdata != NULL && searchmethod != NULL) {
		_search_by_method_(list, &result, true, searchdata, searchmethod);
		if ( result.start != NULL ) {
			foundprevnode = _find_prev_node_(list, result.start, &used);
		}
	}
	return foundprevnode;
}
#if 0
/**
returns the previous node which data comparing functions returns true. The result value is the found node
or NULL if no node was found and will add to the result pointer.
*/
#endif
void llist_search_previous_node_dest(ll_node_t ** resultnode,llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata)) {
	*resultnode = llist_search_previous_node(list, searchdata, searchmethod);
}

//OLD Version

linkedlist * 
__alloc_new_linked_list() {
	linkedlist * newlist = malloc(sizeof(linkedlist));
	newlist->len = 0;
	newlist->start = NULL;
	return newlist;
}

element * 
__alloc_new_empty_element() {
	element * newel = malloc(sizeof(element));
	newel->data = NULL;
	newel->next = NULL;
	return newel;
}

void 
__append_new_list_element(linkedlist* const list, void * data) {
	if ( list != NULL ) {
		element * newel = __alloc_new_empty_element();
		newel->data = data;
		if ( list->start == NULL ) {
			list->start = newel;
			list->end = newel;
		} else {
			element * last = list->end;
			last->next = newel;
			list->end = newel;
		}
		list->len++;
	}
}

void 
__clear_whole_list(linkedlist * list, void (*free_func)(void * ptr)) {
	if (list != NULL) {
		element * curelement = list->start;
		element * next;
		for( int i = list->len ; i > 0 ; --i ) {
			next = curelement->next;
			if ( (*free_func) != NULL ) {
				(*free_func)(curelement->data);
			}
			free(curelement);
			curelement = next;
		}
		list->len = 0;
	}
}

void 
__delete_whole_list(linkedlist * list, void (*free_func)(void * ptr)) {
	__clear_whole_list(list,(*free_func));
	free(list);
	list = NULL;
}

element * 
__get_element_by_idx(linkedlist* const list,unsigned int index) {
	if ( index > list->len ) return NULL;
	element * current = list->start; 
	for(unsigned int i = 0; i < list->len ;++i) {
		if (i==index) { 
			break; 
		} else {
			current = current->next;				
		}
	}
	return current;
}

void * 
__get_data_from_idx(linkedlist * const list,unsigned int index) {
	element * found = __get_element_by_idx(list, index);
	return (found != NULL ? found->data : NULL);
}

//void __delete_data_from_idx(linkedlist * const list,unsigned int index) {
	//TODO here we must have the siblings from element to check
	//element * found = __get_element_by_idx(list, index);
	//return (found != NULL ? found->data : NULL);
//}

const struct __linked_list_func linkedlistutils = {
	.get = __get_data_from_idx,
	.new = __alloc_new_linked_list,
	.append = __append_new_list_element,
	.delete = __delete_whole_list,
	//.deleteidx = __delete_data_from_idx,
	.clear = __clear_whole_list
};


