#include "trajectory.h"

struct Trajectory* createEmptyTrajectory() {
    struct Trajectory* trajectory = malloc(sizeof(struct Trajectory));

    if (trajectory == NULL) {
        printf("ERROR MALLOC TRAJECTORY");
        return NULL;
    }

    trajectory->points = createEmptyQueue();
    return trajectory;
}

struct Queue* getTrajectoryQueue(struct Trajectory* trajectory) {
    return trajectory->points;
}

void addPoint(struct Trajectory* trajectory, struct Point* point) {
    bool valid;
    enqueueV2(getTrajectoryQueue(trajectory), point, &valid);
}

struct Point* getFirstPointAndRemove(struct Trajectory* trajectory) {
    bool valid;
    return dequeueV2(getTrajectoryQueue(trajectory), &valid);
}

struct Point* getFirstPointAndRemoveGood(struct Trajectory* trajectory) {
    bool valid;
    return dequeueV2Delete(getTrajectoryQueue(trajectory), &valid);
}

struct Point* getFirstPointWithoutRemove(struct Trajectory* trajectory) {
    bool valid;
    return headV2(trajectory->points, &valid);
}

void deleteTrajectory(struct Trajectory** trajectory) {
    deleteQueue(&(*trajectory)->points);
    free(*trajectory);
    *trajectory = NULL;
}

