#ifndef _LIST_
#define _LIST_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "point.h"

struct Cell{
    struct Point* point;
    struct Cell* next;
};

struct List{
    unsigned int size;
    struct Cell* head;
    struct Cell* tail;
};

struct Cell* createCell(struct Point* point);

struct List* createEmptyList();

struct Point* getFirst(struct List* l);

void addFirst(struct List* l, struct Point* point);

bool isListEmpty(struct List* l);

struct Point* getItemPos(struct List* l, unsigned int position, bool* valid);

void deleteFirst(struct List* l);

unsigned int listSize(struct List* l);

void addItemPos(struct List* l, struct Point* point, unsigned int position, bool* valid);

void deleteItemPos(struct List* l, unsigned int position, bool* valid);

void deleteList(struct List** l);

struct Point* getFirstAndDelete(struct List* l);

void addLast(struct List* l, struct Point* point);

#endif