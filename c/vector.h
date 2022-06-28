#ifndef PROJECTTEST_VECTOR_H
#define PROJECTTEST_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "constant.h"

struct Vector {
    double x;
    double y;
    double z;
};

struct Vector* createVector(double x, double y, double z);

double getVectorX(struct Vector* vector);

double getVectorY(struct Vector* vector);

double getVectorZ(struct Vector* vector);

void deleteVector(struct Vector** vector);

void vectorTest();

double normeVector(struct Vector* vector);

struct Vector* multiplicationVector(struct Vector* vector, double number);

double distanceVector(struct Vector* firstVector, struct Vector* secondVector);

struct Vector* subtractionVector(struct Vector* firstVector, struct Vector* secondVector);

struct Vector* sumVector(struct Vector* firstVector, struct Vector* secondVector);

void printVector(struct Vector* vector);

#endif //PROJECTTEST_VECTOR_H