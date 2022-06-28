#include "list.h"
#include "queueList.h"

struct Queue* createEmptyQueue() {
    struct Queue* q = malloc(sizeof(struct Queue));

    if (q == NULL) {
        printf("ERROR MALLOC QUEUE");
        return NULL;
    }

    q->l = createEmptyList();
    return q;
}

void enqueue(struct Queue* q, struct Point* point, bool* valid) {
    addFirst(q->l,point);
    *valid = true;
}

struct Point* head(struct Queue* q, bool* valid) {
    if(isQueueEmpty(q)){
        *valid = false;
        return NULL;
    }
    struct Cell* iterator = q->l->head;
    int n = queueSize(q);
    for(int i=0;i<n-1;i++){
        iterator = iterator->next;
    }
    *valid =true;
    return iterator->point;
}

struct Point*  dequeue(struct Queue* q, bool* valid) {
    if(isQueueEmpty(q)){
        *valid = false;
        return NULL;
    }
    else{
        int n = queueSize(q)-1;
        struct Point* enqueueValue = getItemPos(q->l,n,valid);
        deleteItemPos(q->l,n,valid);
        *valid = true;
        return enqueueValue;
    }
}

void enqueueV2(struct Queue* q, struct Point* point, bool* valid) {
    addLast(q->l,point);
    *valid = true;
}


struct Point* dequeueV2(struct Queue* q, bool* valid) {
    if(isQueueEmpty(q)){
        *valid = false;
        return NULL;
    }
    else{
        struct Point* p = getFirst(q->l);
        *valid = true;
        return p;
    }
}

struct Point* dequeueV2Delete(struct Queue* q, bool* valid) {
    if(isQueueEmpty(q)){
        *valid = false;
        return NULL;
    }
    else{
        struct Point* p = getFirst(q->l);
        deleteFirst(q->l);
        *valid = true;
        return p;
    }
}

struct Point* headV2(struct Queue* q, bool* valid) {
    if (!isQueueEmpty(q)) {
        *valid = true;
        return getFirst(q->l);
    }
    else {
        *valid = false;
        return NULL;
    }
}

unsigned int queueSize(struct Queue* q) {
    return(listSize(q->l));
}

bool isQueueEmpty(struct Queue* q) {
    return(isListEmpty(q->l));
}

void deleteQueue(struct Queue** q) {
    struct List* temp = (*q)->l;
    deleteList(&temp);
    free(*q);
    *q = NULL;
}
