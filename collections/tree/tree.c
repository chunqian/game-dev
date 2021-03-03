#include "tree.h"

struct tree_node_data_vtbl {
	struct data_vtbl super;
	void (* print_children)(tree_node_data_t *data);
};

static void tree_node_data_free_(data_t * data) {
	tree_node_data_t * const _data = (tree_node_data_t *)data;
	printf("//TODO recursive delete of tree_node_t* data and children");
}

static size_t tree_node_data_real_size_(data_t * data) {
	tree_node_data_t * const _data = (tree_node_data_t *)data;
	size_t size = sizeof(tree_node_data_t);
	if (_data)
		size += _data->super.size;
	return size;
}

static void tree_node_data_print_children_(tree_node_data_t *data) {
	printf("CALL: _tree_node_data_print_children_(tree_node_data_t *data)");
}

static data_t * tree_node_data_copy_(data_t * _data) {
	return NULL;
}
static bool tree_node_data_equals_(data_t * _data, data_t *_data2) {
	return false;
}
static void tree_node_data_print_(data_t *data) {
	printf("//TODO tree_node_data_print_(data_t *data)");
}

tree_node_data_t * tree_node_data_new_empty() {
	static struct tree_node_data_vtbl const tndctbl = {
		{&tree_node_data_free_,
		&tree_node_data_copy_,
		&tree_node_data_equals_,
		&tree_node_data_real_size_,
		&tree_node_data_print_},
		&tree_node_data_print_children_
	};
	tree_node_data_t * newdata = malloc(sizeof(tree_node_data_t));
	data_ctor(&newdata->super);
	newdata->super.vptr = (struct data_vtbl*)&tndctbl;
	return newdata;
}
tree_node_data_t * tree_node_data_new() {
	return tree_node_data_new_empty();
}
void tree_node_data_new_dest(tree_node_data_t **dest) {
	*dest = tree_node_data_new();
}

#if 0
//test late binding method call.
#endif
void tree_node_print_children(tree_node_data_t * const _data) {
	tree_node_data_t * const data = _data;
	(*data->vptr->print_children)(data);
}

void tree_node_data_free(tree_node_data_t * _data) {
	tree_node_data_t * data = _data;
	data_free((data_t *)data);
}


#if 0
/**
	creates new empty node
*/
#endif
tree_node_t * tree_node_new() { 
	tree_node_t * newnode = malloc(sizeof(tree_node_t));
	newnode->data = NULL;
	newnode->parent = NULL;
	newnode->children = llist_new();
	return newnode; 
}
#if 0
/**
	creates new empty node and add to dest.
*/
#endif
void tree_node_new_dest(tree_node_t ** dest) { 
	*dest = tree_node_new();
}

static void _free_all_childs_(llist_t * _childs) {
	llist_t * childs = _childs;
	if (childs != NULL && childs->start != NULL) {
		ll_node_t * curnode = childs->start;
		ll_node_t * tmp = NULL;
		while( curnode != NULL) {
			tmp = curnode->next;
			#if 0
				//current child tree node
			#endif
			data_t * ndata = ll_node_detach_data(curnode);
			tree_node_free((tree_node_t **)&ndata->data);
			data_free(ndata);
			curnode = tmp;
		}
	}
}

#if 0
/**
	deletes node. It will deletes data too
*/
#endif
void tree_node_free(tree_node_t **_node) { 
	tree_node_t * node = *_node;
	if ( node != NULL ) {
		//free all children data which are tree_nodes too
		_free_all_childs_(node->children);
		llist_free(&node->children);
		data_t * data = tree_node_detach_data(node);
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
void tree_node_clear(tree_node_t *_node) { 
	tree_node_t * node = _node;
	data_t * data = node->data;
	data_free(data);
	node->data = NULL;
	node->parent = NULL;
	_free_all_childs_(node->children);
	llist_clear(node->children);
}
#if 0
/**
	attach new data to node. Does nothing if data exist.
*/
#endif
void tree_node_attach_data(tree_node_t *_node, data_t * _data) { 
	tree_node_t * node = _node;
	if(node->data == NULL) {
		node->data = _data;
	}
}
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one returned.
*/
#endif
data_t * tree_node_attach_data_override(tree_node_t *_node, data_t * _data) { 
	tree_node_t * node = _node;
	data_t * olddata = node->data;
	node->data = _data;
	return olddata;
}
#if 0
/**
	attach new data to node. If data exist the new data will be attached and then the old one will
	linked to dest pointer.
*/
#endif
void tree_node_attach_data_override_dest(data_t **dest, tree_node_t *node, data_t * data) { 
	*dest = tree_node_attach_data_override(node, data);
}
#if 0
/**
	create copy of tree node.
*/
#endif
tree_node_t * tree_node_copy(tree_node_t * src) { 
	tree_node_t * copy = NULL;
	if ( src != NULL ){
		copy = tree_node_new();
		copy->data = data_copy(src->data);
		copy->parent = src->parent;
		llist_t * childs = src->children;
		if (childs != NULL) {
			ll_node_t * curnode = childs->start;
			ll_node_t * tmp = NULL;
			while( curnode != NULL) {
				tmp = curnode->next;
				#if 0
					//current child tree node
				#endif
				tree_node_t * cctn = (tree_node_t *)curnode->data->data;
				tree_node_t * cctn_cpy = tree_node_copy(cctn);
				cctn_cpy->parent = NULL;
				//append copy to children list.
				tree_node_append_child(copy, &cctn_cpy);
				curnode = tmp;
			}
		}
	}
	return copy;
}
#if 0
/**
	Copy node src and saves result to dest.
*/
#endif
void tree_node_copy_dest(tree_node_t ** dest, tree_node_t * src) { 
	*dest = tree_node_copy(src);
}
#if 0
/**
	removes data from node and return the removed data. Returns null if no data exist.
*/
#endif
data_t * tree_node_detach_data(tree_node_t * _node) { 
	data_t * data = NULL;
	tree_node_t * node = _node;
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
void tree_node_detach_data_dest(data_t ** dest, tree_node_t *node) { 
	*dest = tree_node_detach_data(node);
}

//static data_t * _child_node_data_new_(void **data, size_t size) {
//
//	data_t * newdata = malloc(sizeof(data_t));
//	static struct data_vtbl const vtbl = {
//		&_data_free_,
//		&_data_copy_,
//		&_data_equals_,
//		&_data_real_size_,
//		&_data_print_
//	};
//}

ll_node_t * _create_llist_entry_from_node_(tree_node_t ** node) {
	ll_node_t * childentry = ll_node_new();
	data_t * data = data_new((void**)node, sizeof(tree_node_t));
	ll_node_attach_data(childentry, data);
	return childentry;
}

#if 0
/**
	Append Child at the end of child nodes. If child is new its new parent is parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_append_child(tree_node_t * _parent, tree_node_t ** _newchild) {
	tree_node_t * parent = _parent;
	tree_node_t * newchild = *_newchild;
	*_newchild = NULL;
	if ( newchild != NULL && parent != NULL && 
		(newchild->parent == NULL /* || newchild->treeref == parent->treeref */ )) {
		newchild->parent = parent;
		llist_append_node(parent->children, _create_llist_entry_from_node_(&newchild));
	}
}
#if 0
/**
	Append Child at beginning of child nodes. If child is new its new parent is parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_prepend_child(tree_node_t * _parent, tree_node_t * _newchild) {
	tree_node_t * parent = _parent;
	tree_node_t * newchild = _newchild;
	if ( newchild != NULL && parent != NULL && 
		(newchild->parent == NULL /* || newchild->treeref == parent->treeref */ )) {
		newchild->parent = parent;
		llist_prepend_node(parent->children, _create_llist_entry_from_node_(&newchild));
	}
}

static bool _search_tree_node_equal_ref_(void * nodedata, void * searchdata) {
	return nodedata == searchdata;
}

#if 0
/**
	Insert Child before sibling. If child is new its new parent is siblings parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_insert_before_child(tree_node_t * _sibling, tree_node_t * _newchild) {
	tree_node_t * sibling = _sibling;
	tree_node_t * newchild = _newchild;
	if ( newchild != NULL && sibling != NULL && 
		(newchild->parent == NULL /* || newchild->treeref == parent->treeref */ )) {
		tree_node_t * parent = sibling->parent;
		newchild->parent = parent;
		ll_node_t * found = llist_search_node_first(parent->children, sibling,_search_tree_node_equal_ref_);
		if (found != NULL ) {
			llist_insert_before(parent->children, found, _create_llist_entry_from_node_(&newchild));
		}
	}
}
#if 0
/**
	Insert Child after sibling. If child is new its new parent is siblings parent node. If node had another
	parent from same tree, the parent are changed.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_insert_after_child(tree_node_t * _sibling, tree_node_t * _newchild) {
	tree_node_t * sibling = _sibling;
	tree_node_t * newchild = _newchild;
	if ( newchild != NULL && sibling != NULL && 
		(newchild->parent == NULL /* || newchild->treeref == parent->treeref */ )) {
		tree_node_t * parent = sibling->parent;
		if (parent != NULL) {
			newchild->parent = parent;
			ll_node_t * found = llist_search_node_first(parent->children, sibling,_search_tree_node_equal_ref_);
			if (found != NULL ) {
				llist_insert_after(parent->children, found, _create_llist_entry_from_node_(&newchild));
			}
		}
	}
}
#if 0
/**
	Deletes child. If child is valid child of parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child(tree_node_t * _parent, tree_node_t * _deletechild) {
	tree_node_t * parent = _parent;
	tree_node_t * deletechild = _deletechild;
	if ( deletechild != NULL && parent != NULL /* && newchild->treeref == parent->treeref */) {
		ll_node_t * found = llist_search_node_first(parent->children, deletechild, _search_tree_node_equal_ref_);
		if (found != NULL && deletechild == found->data->data ) {
			tree_node_free(&deletechild);
			llist_delete_node(parent->children, found);
		}
	}
}
#if 0
/**
	Deletes node before sibling. If child is valid child of siblings parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child_before(tree_node_t * _sibling, tree_node_t * _deletechild) {
	tree_node_t * sibling = _sibling;
	tree_node_t * deletechild = _deletechild;
	if ( deletechild != NULL && sibling != NULL /* && newchild->treeref == parent->treeref */) {
		tree_node_t * parent = sibling->parent;
		if (parent != NULL) {
			//CURRENTLY create llist_search_node_previous
			ll_node_t * found = llist_search_previous_node(parent->children, deletechild, _search_tree_node_equal_ref_);
			if (found != NULL && deletechild == found->data->data ) {
				tree_node_free(&deletechild);
				llist_delete_node(parent->children, found);
			}
		}
	}
}
#if 0
/**
	Deletes node after sibling. If child is valid child of siblings parent it will be deleted with data inside.
	
	//TODO: add tree reference protection => only free(not adopted nodes) or node from same tree can added as child.
*/
#endif
void tree_node_delete_child_after(tree_node_t * _sibling, tree_node_t * _deletechild) {
	tree_node_t * sibling = _sibling;
	tree_node_t * deletechild = _deletechild;
	if ( deletechild != NULL && sibling != NULL /* && newchild->treeref == parent->treeref */) {
		tree_node_t * parent = sibling->parent;
		if (parent != NULL) {
			ll_node_t * found = llist_search_node_first(parent->children, deletechild, _search_tree_node_equal_ref_);
			if (found != NULL && found->next != NULL && found->next->data != NULL) {
				ll_node_t * next = found->next;
				tree_node_t * treedata = (tree_node_t *)found->next->data->data;
				tree_node_free(&treedata);
				llist_delete_node(parent->children, next);
			}
		}
	}
}

tree_t * tree_new(tree_node_t * root) {
	size_t tree_size = sizeof(tree_t);
	tree_t * newtree = malloc(tree_size);
	tree_t base = {newtree, root};
	memcpy(newtree, &base, tree_size);
	return newtree;
}

void tree_free(tree_t * tree) {
	tree_node_free(&tree->root);
	free(tree);
}