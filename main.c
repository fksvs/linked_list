#include <stdio.h>
#include <string.h>
#include "list.h"

#define DATA_SIZE 5

int cmp(void *a, void *b)
{
        return strcmp((char *)a, (char *)b);
}

void print_list_next(linked_list *list, iterate *iter){
        struct node *ptr;
        int ind = 0;

        while ((ptr = get_next(iter)) != NULL){
                printf("index %d --> %s\t%p\n", ind, (char *)ptr->data, ptr);
                ind += 1;
        }
        printf("\n");
}

// basic usage of list
int main()
{
        // initialize list
        linked_list *list = init_list();
        
        // add data to head
        add_head(list, "data1", DATA_SIZE, &cmp);
        add_head(list, "data2", DATA_SIZE, &cmp);

        // add data to tail
        add_tail(list, "data3", DATA_SIZE, &cmp);
        add_tail(list, "data4", DATA_SIZE, &cmp);

        // add data to given index
        add_index(list, 2, "data5", DATA_SIZE, &cmp);

        printf("list size = %d\n", list->list_size);

        // get data with iterator
        iterate *iter = init_iterate(list, 0);
        print_list_next(list, iter);
        // delete iterator
        del_iterate(iter);

        // search list with given data
        struct node *ptr;
        if ((ptr = search_data(list, "data3")) != NULL)
                printf("(search) data3 at %p\n", ptr);

        // search list with given index
        if ((ptr = search_index(list, 3)) != NULL)
                printf("(search) index 3 = %s\t%p\n", (char *)ptr->data, ptr);

        // delete data in the head from list
        del_head(list);

        // delete data in the tail from list
        del_tail(list);

        // delete given data from the list
        del_data(list, "data1");

        // delete given index from the list
        del_index(list, 2);

        // delete list completely
        del_list(list);

        return 0;
}
