#ifndef PROJECTTEST_POINT_H
#define PROJECTTEST_POINT_H

#include "vector.h"

struct Point {
    struct Vector* position;
    struct Vector* velocity;
    int time;
};

struct Point* createPoint(struct Vector* position, struct Vector* velocity, int time);

struct Vector* getPointPosition(struct Point* point);

struct Vector* getPointVelocity(struct Point* point);

int getPointTIme(struct Point* point);

void deletePoint(struct Point** point);

#endif //PROJECTTEST_POINT_H