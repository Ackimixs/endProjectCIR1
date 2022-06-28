#ifndef PROJECTTEST_PLANET_H
#define PROJECTTEST_PLANET_H

#include "trajectory.h"

struct Planet {
    char* name;
    double weight;
    struct Trajectory* trajectory;
    double perihelion;
    double revolutionPeriod;
    double timeBetween2Point;
};


/**
 * The function create a planet with his name, weight, trajectory and perihelion
 * @param name ->  the name of the planet
 * @param weight -> the weight of the planet
 * @param perihelion -> the perihelion of the planet
 * @return the planet
 */
struct Planet* createPlanet(char* name, double weight, double perihelion, double revolutionPeriod, double timeBetween2Point);

char* getPlanetName(struct Planet* planet);

double getRevolutionPeriod(struct Planet* planet);

double getPlanetWeight(struct Planet* planet);

double getTimeBetween2Point(struct Planet* planet);

struct Trajectory* getTrajectory(struct Planet* planet);

double getPlanetPerihelion(struct Planet* planet);

double calcVelocityPerihelion(double demiGrandAxe, double eccentricity);

void init(struct Planet* planet, double semiMajorAxis, double eccentricity);

void writeFile(struct Planet** planets, int method, char* fileName);

void deletePlanet(struct Planet** planet);

void deleteAllPlanets(struct Planet*** planets);


/**
 * @param planet -> planet to execute the euler method
 * @param lastPoint -> the first point of the planet
 * @return the planet of all his trajectory
 */
struct Planet* eulerMethodWithoutRecurence(struct Planet* planet, struct Point* lastPoint);

// Asymetric method
struct Planet* eulerAsymmetricMethodWithoutRecurence(struct Planet* planet, struct Point* lastPoint);


// recurence method that not work
//struct Planet* eulerMethod(struct Planet* planet, struct Point* lastPoint;

//struct Planet* eulerAsymmetricMethod(struct Planet* planet, struct Point* lastPoint);



//MOON
struct Vector* calcAcelerationMoon(struct Vector* positionMoon);

double calcVelocityPerigee(double demiGrandAxeMoon, double eccentricityMoon);

struct Planet* createMoonWithEulerAsy(struct Planet* planet, struct Point* lastPoint);

void initMoon(struct Planet* planetMoon, double semiMajorAxis, double eccentricity);

#endif //PROJECTTEST_PLANET_H
