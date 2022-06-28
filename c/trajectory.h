#ifndef PROJECTTEST_TRAJECTORY_H
#define PROJECTTEST_TRAJECTORY_H

#include "queueList.h"


struct Trajectory {
    struct Queue* points;
};

struct Trajectory* createEmptyTrajectory();

struct Queue* getTrajectoryQueue(struct Trajectory* trajectory);

void addPoint(struct Trajectory* trajectory, struct Point* point);

struct Point* getFirstPointAndRemove(struct Trajectory* trajectory);

struct Point* removeFirstPoint(struct Trajectory* trajectory);

struct Point* getFirstPointWithoutRemove(struct Trajectory* trajectory);

void deleteTrajectory(struct Trajectory** trajectory);

#endif //PROJECTTEST_TRAJECTORY_H
