#include <stdlib.h>
#include <string.h>
#include "list.h"

linked_list *init_list(){
    linked_list *list=malloc(sizeof(linked_list));
    list->head=NULL;
    list->tail=NULL;
    list->list_size=0;

    return list;
}

struct node *init_node(void *data,size_t data_size,\
        int (*cmp)(void *a,void *b)){
    struct node *ptr=malloc(sizeof(struct node));

    ptr->data=malloc(data_size);
    memcpy(ptr->data,data,data_size);
    ptr->data_size=data_size;
    ptr->cmp=cmp;
    ptr->prev=NULL;
    ptr->next=NULL;

    return ptr;
}

struct node *add_head(linked_list *list,\
        void *data,size_t data_size,\
        int (*cmp)(void *a,void *b)){
    struct node *ptr=init_node(data,data_size,cmp);

    if (list->head==NULL){
        list->head=ptr;
        list->tail=ptr;
    }
    else{
        ptr->next=list->head;
        list->head->prev=ptr;
        list->head=ptr;
    }
    list->list_size+=1;
    return ptr;
}

struct node *add_tail(linked_list *list,\
        void *data,size_t data_size,\
        int (*cmp)(void *a,void *b)){
    struct node *ptr=init_node(data,data_size,cmp);

    if (list->head==NULL){
        list->head=ptr;
        list->tail=ptr;
    }
    else{
        list->tail->next=ptr;
        ptr->prev=list->tail;
        list->tail=ptr;
    }
    list->list_size+=1;
    return ptr;
}

struct node *add_index(linked_list *list,int index,\
        void *data,size_t data_size,\
        int (*cmp)(void *a,void *b)){
    struct node *temp=list->head,*ptr;
    int ind=0;

    if (index==0 || index<0)
        add_head(list,data,data_size,cmp);
    else if (index > (list->list_size-1))
        add_tail(list,data,data_size,cmp);
    else if (index == (list->list_size-1)){
        ptr=init_node(data,data_size,cmp);
        ptr->next=list->tail;
        ptr->prev=list->tail->prev;
        list->tail->prev->next=ptr;
        list->tail->prev=ptr;
        list->list_size+=1;
    }
    else if (index>0 && index<list->list_size){
        ptr=init_node(data,data_size,cmp);
        while (ind!=index){
            temp=temp->next;
            ind+=1;
        }
        ptr->next=temp;
        ptr->prev=temp->prev;
        temp->prev->next=ptr;
        temp->prev=ptr;
        list->list_size+=1;
    }
    return ptr;
}

void del_node(struct node *ptr){
    free(ptr->data);
    free(ptr);
}

void del_list(linked_list *list){
    struct node *ptr,*temp=list->head;
    int ind;

    for (ind=0;ind < list->list_size;ind+=1){
        ptr=temp;
        temp=temp->next;
        del_node(ptr);
    }
    free(list);
}

void del_head(linked_list *list){
    struct node *ptr=list->head;

    if (list->head!=NULL){
        if (list->head->next!=NULL){
            list->head=list->head->next;
            list->head->prev=NULL;
        }
        list->list_size-=1;
        del_node(ptr);
    }
}

void del_tail(linked_list *list){
    struct node *ptr=list->tail;

    if (list->tail!=NULL){
        if (list->tail->prev!=NULL){
            list->tail=list->tail->prev;
            list->tail->next=NULL;
        }
        list->list_size-=1;
        del_node(ptr);
    }
}

void del_data(linked_list *list,void *data){
    struct node *ptr=list->head;
    int ind;

    if (list->head->cmp(list->head->data,data)==0)
        del_head(list);
    else if (list->tail->cmp(list->tail->data,data)==0)
        del_tail(list);
    else{
        for (ind=0;ind<list->list_size;ptr=ptr->next,ind+=1){
            if (ptr->cmp(ptr->data,data)==0){
                ptr->next->prev=ptr->prev;
                ptr->prev->next=ptr->next;
                list->list_size-=1;
                del_node(ptr);
                break;
            }
        }
    }
}

void del_index(linked_list *list,int index){
    struct node *temp,*ptr=list->head;
    int ind=0;

    if (index==0 || index<0)
        del_head(list);
    else if (index>list->list_size-1)
        del_tail(list);
    else if (index==list->list_size-1)
        del_tail(list);
    else if (index>0 && index<list->list_size){
        while (ind!=index){
            ind+=1;
            ptr=ptr->next;
        }
        temp=ptr;
        ptr->next->prev=ptr->prev;
        ptr->prev->next=ptr->next;
        list->list_size-=1;
        del_node(temp);
    }
}

struct node *search_data(linked_list *list,void *data){
    struct node *ptr=list->head;
    int ind;

    for (ind=0;ind<list->list_size;ind+=1,ptr=ptr->next){
        if (ptr->cmp(ptr->data,data)==0)
            return ptr;
    }
    return NULL;
}

struct node *search_index(linked_list *list,int index){
    struct node *ptr=list->head;
    int ind=0;

    if (index==0)
        return list->head;
    else if (index==list->list_size-1)
        return list->tail;
    else if (index>0 && index<list->list_size){
        while (ind!=index){
            ind+=1;
            ptr=ptr->next;
        }
        return ptr;
    }
    return NULL;
}

iterate *init_iterate(linked_list *list,int pos){
    if (pos==0 || pos==-1 || (pos>0 && pos<list->list_size)){
        iterate *ptr=malloc(sizeof(iterate));
        if (pos==0)
            ptr->cur=list->head;
        else if (pos==-1)
            ptr->cur=list->tail;
        else if (pos>0 && pos<list->list_size)
            ptr->cur=search_index(list,pos);
        return ptr;
    }
    return NULL;
}

void del_iterate(iterate *ptr){
    free(ptr);
}

struct node *get_next(iterate *ptr){
    if (ptr->cur!=NULL){
        struct node *temp=ptr->cur;
        ptr->cur=ptr->cur->next;
        return temp;
    }
    return NULL;
}

struct node *get_prev(iterate *ptr){
    if (ptr->cur!=NULL){
        struct node *temp=ptr->cur;
        ptr->cur=ptr->cur->prev;
        return temp;
    }
    return NULL;
}
