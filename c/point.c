#include "point.h"


struct Point* createPoint(struct Vector* position, struct Vector* velocity, int time) {
    struct Point* point = malloc(sizeof(struct Point));
    if(!point) {
        printf("ERROR MALLOC POINT");
        return NULL;
    }

    point->position = position;
    point->velocity = velocity;
    point->time = time;

    return point;
}


struct Vector* getPointPosition(struct Point* point) {
    return point->position;
}

struct Vector* getPointVelocity(struct Point* point) {
    return point->velocity;
}

int getPointTIme(struct Point* point) {
    return point->time;
}

void deletePoint(struct Point** point) {

    struct Vector* pos = (*point)->position;
    struct Vector* vel = (*point)->velocity;

    deleteVector(&pos);
    deleteVector(&vel);

    free(*point);
    *point = NULL;
}