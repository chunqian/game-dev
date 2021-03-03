#ifndef DL_LIST_H
#define DL_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct __dl_list_item_t {
    void *data;
    struct __dl_list_item_t *next;
    struct __dl_list_item_t *prev;
} dl_list_item_t;

typedef struct {
    uint32_t cnt;
    dl_list_item_t *first;
    dl_list_item_t *last;
} dl_list_t;

typedef void (*EACH_FUNC)(void **data);
typedef void (*EACH_FUNC_DATA)(void **data, void *eachdata);

dl_list_t* dl_list_new();
void dl_list_free(dl_list_t**list);

void dl_list_clear(dl_list_t* list);
void dl_list_append(dl_list_t *list, void *data);
void dl_list_prepend(dl_list_t *list, void *data);
void dl_list_insert_prepend(dl_list_t *list, void *sibling, void *value);
void dl_list_insert_append(dl_list_t *list, void *sibling, void *value);
void dl_list_insert_prepend_idx(dl_list_t *list, uint32_t index, void *value);
void dl_list_insert_append_idx(dl_list_t *list, uint32_t index, void *value);
void* dl_list_get(dl_list_t *list, uint32_t index);
void* dl_list_remove(dl_list_t *list, uint32_t index);
void  dl_list_remove_free(dl_list_t *list, uint32_t index, void (freefunc)(void *data));
void* hgen_search_once(dl_list_t *list, void *search_data, bool (*searchfunc)(void*item, void *search_data));
int   hgen_search_once_id(dl_list_t *list, void *search_data, bool (*searchfunc)(void*item, void *search_data));
dl_list_t* hgen_search(dl_list_t *list, void *search_data, bool (*searchfunc)(void*item, void *search_data));
void  dl_list_each(dl_list_t *list, EACH_FUNC eachfunc);
void  dl_list_each_data(dl_list_t *list, void* eachdata, EACH_FUNC_DATA eachfunc);

#endif
