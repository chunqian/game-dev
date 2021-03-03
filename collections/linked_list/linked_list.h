#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include "data.h"

//New Version

typedef struct _ll_node_ {
	data_t * data;
	struct _ll_node_ * next;
} ll_node_t;

#if 0
/**
	creates new empty node
*/
#endif
ll_node_t * ll_node_new();
#if 0
/**
	creates new empty node and add to dest.
*/
#endif
void ll_node_new_dest(ll_node_t ** dest);

#if 0
/**
	deletes node. It will deletes data too
*/
#endif
void ll_node_free(ll_node_t **node);
#if 0
/**
	deletes nodes content. It will deletes data too
*/
#endif
void ll_node_clear(ll_node_t *node);
#if 0
/**
	attach new data to node. Does nothing if data exist.
*/
#endif
void ll_node_attach_data(ll_node_t *node, data_t * data);
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one returned.
*/
#endif
data_t * ll_node_attach_data_override(ll_node_t *node, data_t * data);
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one will
	linked to dest pointer.
*/
#endif
void ll_node_attach_data_override_dest(data_t **dest, ll_node_t *node, data_t * data);
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist.
*/
#endif
ll_node_t * ll_node_copy(ll_node_t * src);
#if 0
/**
	Copy node src and saves result to dest.
*/
#endif
void ll_node_copy_dest(ll_node_t ** dest, ll_node_t * src);
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist.
*/
#endif
data_t * ll_node_detach_data(ll_node_t *node);
#if 0
/**
	removes data from node and add the removed data to dest. If no data attached NULL will added.
*/
#endif
void ll_node_detach_data_dest(data_t ** dest, ll_node_t *node);


typedef struct {
	ll_node_t * start;
	ll_node_t * end;
	unsigned int len;
} llist_t;

#if 0
/**
	creates new empty list
*/
#endif
llist_t* llist_new();
void llist_new_dest(llist_t **list);
#if 0
/**
 delete complete list.
*/
#endif
void llist_free(llist_t **list);
#if 0
/**
 clears whole list complete list.
*/
#endif
void llist_clear(llist_t *list);
#if 0
/**
Merges two lists. The first list is the starting list.
*/
#endif
void llist_append_list(llist_t * list, llist_t * list2);
#if 0
/**
Add element at end of list.
*/
#endif
void llist_append_node(llist_t * list, ll_node_t * newnode);
#if 0
/**
delete node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node(llist_t * list, ll_node_t * delnode);
#if 0
/**
delete node after node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node_after(llist_t * list, ll_node_t * delnode);
#if 0
/**
delete node after node. Deletes node if it exist in list.
*/
#endif
void llist_delete_node_before(llist_t * list, ll_node_t * delnode);
#if 0
/**
Add element at beginning of list.
*/
#endif
void llist_prepend_node(llist_t * list, ll_node_t * newnode);
#if 0
/**
Merges two lists. The second list is the starting list.
*/
#endif
void llist_prepend_list(llist_t * list, llist_t * list2);
#if 0
/**
Insert Node after sibling.
*/
#endif
void llist_insert_after(llist_t * list, ll_node_t * sibling ,ll_node_t * newnode);

#if 0
/**
Insert Node before sibling.
*/
#endif
void llist_insert_before(llist_t * list, ll_node_t * sibling ,ll_node_t * newnode);
#if 0
/**
Returns the all found nodes. The result is a linked list with a copy of all found elements. this 
result list will be the response
*/
#endif
llist_t * llist_search_node_all(llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
Returns the all found nodes. The result is a linked list with a copy of all found elements. The
Resultlist will add to the resultlistpointer.
*/
#endif
void llist_search_node_all_dest(llist_t ** resultlist, llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
returns the first node which data comparing functions returns true. The return value is the found node
or NULL if no node was found.
*/
#endif
ll_node_t * llist_search_node_first(llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
returns the first node which data comparing functions returns true. The result value is the found node
or NULL if no node was found and will add to the result pointer.
*/
#endif
void llist_search_node_first_dest(ll_node_t ** resultnode,llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
returns the previous node which data comparing functions returns true. The return value is the found node
or NULL if no node was found.
*/
#endif
ll_node_t * llist_search_previous_node(llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));
#if 0
/**
returns the previous node which data comparing functions returns true. The result value is the found node
or NULL if no node was found and will add to the result pointer.
*/
#endif
void llist_search_previous_node_dest(ll_node_t ** resultnode,llist_t * list, 
								void * searchdata, bool (*searchmethod)(void * nodedata, void * searchdata));


//OLD Version

typedef struct __element {
	void * data;
	struct __element * next;
} element;

typedef struct __linked_list {
	element * start;
	element * end;
	unsigned int len;
} linkedlist;

struct __linked_list_func {
	void * 	(*get)(linkedlist* const list,unsigned int index);
	void 	(*append)(linkedlist* const list, void * data);
	linkedlist * (*new)();
	void (*clear)(linkedlist * list, void (*free_func)(void * ptr));
	void (*delete)(linkedlist * list , void (*free_func)(void * ptr));
	//void (*deleteidx)(linkedlist * const list,unsigned int index);
};

extern const struct __linked_list_func linkedlistutils;

#endif
