#include "vector.h"



struct Vector* createVector(double x, double y, double z) {
    struct Vector* vect = malloc(sizeof(struct Vector));
    if (!vect) {
        printf("ERROR MALLOC");
        return NULL;
    }

    vect->x = x;
    vect->y = y;
    vect->z = z;

    return vect;
}


double getVectorX(struct Vector* vector) {
    return vector->x;
}


double getVectorY(struct Vector* vector) {
    return vector->y;
}


double getVectorZ(struct Vector* vector) {
    return vector->z;
}

void deleteVector(struct Vector** vector) {
    free(*vector);
    (*vector) = NULL;
}

struct Vector* sumVector(struct Vector* firstVector, struct Vector* secondVector) {
    return createVector(getVectorX(firstVector)+getVectorX(secondVector), getVectorY(firstVector)+getVectorY(secondVector), getVectorZ(firstVector)+getVectorZ(secondVector));
}

struct Vector* subtractionVector(struct Vector* firstVector, struct Vector* secondVector) {
    return createVector(getVectorX(firstVector)-getVectorX(secondVector), getVectorY(firstVector)-getVectorY(secondVector), getVectorZ(firstVector)-getVectorZ(secondVector));
}

double distanceVector(struct Vector* firstVector, struct Vector* secondVector) {
    return sqrt(pow((getVectorX(firstVector)-getVectorX(secondVector)), 2) + pow((getVectorY(firstVector)-getVectorY(secondVector)), 2) +
                        pow(getVectorZ(firstVector)-getVectorZ(secondVector), 2));
}

double normeVector(struct Vector* vector) {
    return sqrt(pow(getVectorX(vector), 2) + pow(getVectorY(vector), 2) + pow(getVectorZ(vector), 2));
}

struct Vector* multiplicationVector(struct Vector* vector, double number) {
    return createVector(getVectorX(vector)*number, getVectorY(vector)*number, getVectorZ(vector)*number);
}


void printVector(struct Vector* vector) {
    printf("x : %f\ny : %f\nz : %f\n", getVectorX(vector), getVectorY(vector), getVectorZ(vector));
}
/*
void vectorTest() {
    struct Vector* firstVector = createVector(10, 20, 30);
    struct Vector* secondVector = createVector(25, 45, 52);
    printf("---------  VECTOR TEST -----------\n");
    printf("sum\n");
    printVector(sumVector(firstVector, secondVector));
    printf("subtraction\n");
    printVector(subtractionVector(firstVector, secondVector));
    printf("multiplication\n");
    printVector(multiplicationVector(firstVector, 12));
}*/