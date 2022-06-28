#ifndef _QUEUE_LIST_
#define _QUEUE_LIST_

#include "list.h"

struct Queue{
    struct List* l;
};

struct Queue* createEmptyQueue();

void enqueue(struct Queue* q, struct Point* point, bool* valid);

struct Point* head(struct Queue* q, bool* valid);

struct Point* dequeue(struct Queue* q, bool* valid);

unsigned int queueSize(struct Queue* q);

bool isQueueEmpty(struct Queue* q);

void deleteQueue(struct Queue** q);


void enqueueV2(struct Queue* q, struct Point* point, bool* valid);

struct Point* dequeueV2Delete(struct Queue* q, bool* valid);

struct Point* dequeueV2(struct Queue* q, bool* valid);

struct Point* headV2(struct Queue* q, bool* valid);

#endif