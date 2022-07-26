#include <stddef.h>

#ifndef LIST
#define LIST

struct node {
	void *data;
	size_t data_size;
	int (*cmp)(void *a, void *b);
	struct node *prev;
	struct node *next;
};

typedef struct {
	struct node *head;
	struct node *tail;
	int list_size;
} linked_list;

typedef struct {
	struct node *cur;
} iterate;

linked_list *init_list();
struct node *init_node(void *data, size_t data_size,
		       int (*cmp)(void *a, void *b));
struct node *add_head(linked_list *list, void *data, size_t data_size,
		      int (*cmp)(void *a, void *b));
struct node *add_tail(linked_list *list, void *data, size_t data_size,
		      int (*cmp)(void *a, void *b));
struct node *add_index(linked_list *list, int index, void *data,
		       size_t data_size, int (*cmp)(void *a, void *b));

void del_node(struct node *ptr);
void del_list(linked_list *list);
void del_head(linked_list *list);
void del_tail(linked_list *list);
void del_data(linked_list *list, void *data);
void del_index(linked_list *list, int index);

struct node *search_data(linked_list *list, void *data);
struct node *search_index(linked_list *list, int index);

iterate *init_iterate(linked_list *list, int pos);
void del_iterate(iterate *ptr);
struct node *get_next(iterate *ptr);
struct node *get_prev(iterate *ptr);

#endif
