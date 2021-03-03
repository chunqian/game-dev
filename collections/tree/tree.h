#ifndef TREE_H
#define TREE_H

#include "data.h"
#include "linked_list.h"

typedef struct _tree_node_data_ {
	data_t super;
	struct tree_node_data_vtbl const *vptr;
} tree_node_data_t;

tree_node_data_t * tree_node_data_new_empty();
tree_node_data_t * tree_node_data_new();
void tree_node_data_new_dest(tree_node_data_t **dest);
void tree_node_data_free(tree_node_data_t * data);

typedef struct _tree_node_ {
	data_t * data;
	struct _tree_node_ * parent;
	llist_t * children;
} tree_node_t;

#if 0
/**
	creates new empty node
*/
#endif
tree_node_t * tree_node_new();
#if 0
/**
	creates new empty node and add to dest.
*/
#endif
void tree_node_new_dest(tree_node_t ** dest);

#if 0
/**
	deletes node. It will deletes data too
*/
#endif
void tree_node_free(tree_node_t **node);
#if 0
/**
	deletes nodes content. It will deletes data too
*/
#endif
void tree_node_clear(tree_node_t *node);
#if 0
/**
	attach new data to node. Does nothing if data exist.
*/
#endif
void tree_node_attach_data(tree_node_t *node, data_t * data);
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one returned.
*/
#endif
data_t * tree_node_attach_data_override(tree_node_t *node, data_t * data);
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one will
	linked to dest pointer.
*/
#endif
void tree_node_attach_data_override_dest(data_t **dest, tree_node_t *node, data_t * data);
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist.
*/
#endif
tree_node_t * tree_node_copy(tree_node_t * src);
#if 0
/**
	Copy node src and saves result to dest.
*/
#endif
void tree_node_copy_dest(tree_node_t ** dest, tree_node_t * src);
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist.
*/
#endif
data_t * tree_node_detach_data(tree_node_t *node);
#if 0
/**
	removes data from node and add the removed data to dest. If no data attached NULL will added.
*/
#endif
void tree_node_detach_data_dest(data_t ** dest, tree_node_t *node);
#if 0
/**
	Append Child at the end of child nodes. If child is new its new parent is parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_append_child(tree_node_t *parent, tree_node_t ** newchild);
#if 0
/**
	Append Child at beginning of child nodes. If child is new its new parent is parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_prepend_child(tree_node_t *parent, tree_node_t * newchild);
#if 0
/**
	Insert Child before sibling. If child is new its new parent is siblings parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_insert_before_child(tree_node_t * sibling, tree_node_t * newchild);
#if 0
/**
	Insert Child after sibling. If child is new its new parent is siblings parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_insert_after_child(tree_node_t * sibling, tree_node_t * newchild);
#if 0
/**
	Deletes child. If child is valid child of parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child(tree_node_t * parent, tree_node_t * deletechild);
#if 0
/**
	Deletes node before sibling. If child is valid child of siblings parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child_before(tree_node_t * sibling, tree_node_t * deletechild);
#if 0
/**
	Deletes node after sibling. If child is valid child of siblings parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child_after(tree_node_t * sibling, tree_node_t * deletechild);

typedef struct {
	const void * const ref;
	tree_node_t * root;
} tree_t;

#if 0
// create a new tree with root node. root can be null, but the tree has no root. It must then set explicit.
#endif
tree_t * tree_new(tree_node_t * root);

#if 0
/**
*	deletes all nodes and containing data using node_data set free function. Default free function is normal free.
*/
#endif
void tree_free(tree_t * tree);
#endif
