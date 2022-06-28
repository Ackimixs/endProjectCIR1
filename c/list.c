#include "list.h"

struct Cell* createCell(struct Point* point)
{
    struct Cell* c = malloc(sizeof(struct Cell));

    if (c == NULL) {
        printf("ERROR MALLOC CELL");
        return NULL;
    }

    c->point = point;
    c->next = NULL;

    return c;
}

struct List* createEmptyList() {
    struct List* l = malloc(sizeof(struct List));
    if (l == NULL) {
        printf("ERROR MALLOC LIST");
        return NULL;
    }

    l->size = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

void addFirst(struct List* l, struct Point* point) {
    struct Cell* newHead = createCell(point);
    if(isListEmpty(l)){
        l->size++;
        l->head = newHead;
        l->tail = newHead;
    }
    else{
        newHead->next = l->head;
        l->size++;
        l->head = newHead;
    }
}

bool isListEmpty(struct List* l) {
    return l->size == 0;
}

struct Point* getItemPos(struct List* l, unsigned int position, bool* valid) {
    if(position >= l->size || position<0){
        *valid = false;
        return NULL;
    }
    else{
        struct Cell* iterator = l->head;
        *valid = true;
        for(int i=0; i<position;i++) {
            iterator = iterator->next;
        }
        return iterator->point;
    }
}

void deleteFirst(struct List* l) {
    if(!isListEmpty(l)){
        struct Cell* next = (l->head)->next;
        deletePoint(&l->head->point);
        free(l->head);
        l->size--;
        l->head = next;
    }
}

unsigned int listSize(struct List* l) {
    return l->size;
}

void addItemPos(struct List* l, struct Point* point, unsigned int position, bool* valid) {
        struct Cell* iterator = l->head;
        if(position > listSize(l) || position<0){
            *valid = false;
            return;
        }
        if(position==0){
            addFirst(l,point);
            *valid = true;
            return ;
        }
        else {
            for(int i=0; i < (position-1) ;i++)
            {
                iterator=iterator->next;
            }
            struct Cell* newCell = createCell(point);
            newCell->next=iterator->next;
            iterator->next = newCell;
            l->size++;
            *valid= true;
        }
}

void deleteItemPos(struct List* l, unsigned int position, bool* valid) {
    if(isListEmpty(l) || position >= l->size || position<0) {
        *valid = false;
        return ;
    }
    if(position==0) {
        deleteFirst(l);
        *valid = true;
        return ;
    }
    struct Cell* iterator = l->head;
    struct Cell* temp;
    for (int i = 0; i < position - 1; i++) {
        iterator = iterator->next;
    }
    temp = (iterator->next)->next;
    free(iterator->next);
    iterator->next = temp;
    l->size--;
    *valid = true;
}

void deleteList(struct List** l) {
    if(*l == NULL){
        return;
    }
    struct List* tempList = *l;
    int n = listSize(tempList);
    for(int i=0;i< n; i++){
        deleteFirst(tempList);
    }
    free(tempList);
    *l = NULL;
}





void addLast(struct List* l, struct Point* point) {
    struct Cell* newHead = createCell(point);
    if(isListEmpty(l)){
        l->size++;
        l->tail = newHead;
        l->head = newHead;
    }
    else{
        l->tail->next = newHead;
        l->tail = newHead;
        l->size++;
    }
}



struct Point* getFirst(struct List* l) {
    if (!isListEmpty(l)){
        return l->head->point;
    }else {
        return NULL;
    }
}