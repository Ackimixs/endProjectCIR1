#include "planet.h"



struct Planet* createPlanet(char* name, double weight, double perihelion, double revolutionPeriod, double timeBetween2Point) {
    struct Planet* planet = malloc(sizeof(struct Planet));

    if (!planet) {
        printf("ERROR MALLOC PLANET");
        return NULL;
    }

    planet->name = malloc((strlen(name)+1)*sizeof(char));

    if (planet->name == NULL) {
        printf("ERROR MALLOC NAME PLANET");
        return NULL;
    }

    strcpy(planet->name, name);
    planet->weight = weight;
    planet->trajectory = createEmptyTrajectory();
    planet->perihelion = perihelion;
    planet->revolutionPeriod = revolutionPeriod;
    planet->timeBetween2Point = timeBetween2Point;


    return planet;
}

char* getPlanetName(struct Planet* planet) {
    return planet->name;
}

double getPlanetWeight(struct Planet* planet) {
    return planet->weight;
}

double getTimeBetween2Point(struct Planet* planet) {
    return planet->timeBetween2Point;
}

double getRevolutionPeriod(struct Planet* planet) {
    return planet->revolutionPeriod;
}

struct Trajectory* getTrajectory(struct Planet* planet) {
    return planet->trajectory;
}

double getPlanetPerihelion(struct Planet* planet) {
    return planet->perihelion;
}

//velocity at the perihelion -> v_p = sqrt[(GM/a)*(1+e)/(1-e)] / wikipedia : sqrt[(GM*(1+e))/(a(1-e))]
// G est la constante de gravitation
// M est la masse du Soleil
// a est le demi-grand axe de l'orbite
// e est l'excentricité de l'orbite

double calcVelocityPerihelion(double demiGrandAxe, double eccentricity) {
    return sqrt((G*SUN_WEIGHT*(1+eccentricity)) / (demiGrandAxe*(1-eccentricity)));
}

void init(struct Planet* planet, double semiMajorAxis, double eccentricity) {
    struct Vector* posInit = createVector(planet->perihelion, 0, 0);
    struct Vector* velocityInit = createVector(0 , calcVelocityPerihelion(semiMajorAxis, eccentricity) ,0);

    addPoint(getTrajectory(planet), createPoint(posInit, velocityInit, 0));

}

void deletePlanet(struct Planet** planet) {
    free((*planet)->name);
    deleteTrajectory(&(*planet)->trajectory);
    free(*planet);
    *planet = NULL;
}


struct Vector* calcAceleration(struct Vector* position) {
    return multiplicationVector(position, -((G*SUN_WEIGHT) / pow(normeVector(position), 3)));
}

struct Planet* eulerMethodWithoutRecurence(struct Planet* planet, struct Point* lastPoint) {
    for (int i = 0 ; i < (getRevolutionPeriod(planet)*20); i++) {

        struct Vector* accel = calcAceleration(getPointPosition(lastPoint));

        struct Vector* firstMulti = multiplicationVector(getPointVelocity(lastPoint), getTimeBetween2Point(planet));

        struct Vector* newPos = sumVector(getPointPosition(lastPoint), firstMulti);

        deleteVector(&firstMulti);

        struct Vector* secondMulti = multiplicationVector(accel, getTimeBetween2Point(planet));

        struct Vector* newVelocity = sumVector(getPointVelocity(lastPoint), secondMulti);

        struct Point* newPoint = createPoint(newPos, newVelocity, getPointTIme(lastPoint)+1);

        deleteVector(&secondMulti);

        addPoint(getTrajectory(planet), newPoint);

        lastPoint = newPoint;

        deleteVector(&accel);
    }
    return planet;
}

/*
struct Planet* eulerMethod(struct Planet* planet, struct Point* lastPoint, double numberOfDays) {
    if (getPointTIme(lastPoint) >= numberOfDays) {
        return planet;
    }

    else {
        struct Vector* accel = calcAceleration(getPointPosition(lastPoint));

        struct Vector* newPos = sumVector(getPointPosition(lastPoint), multiplicationVector(getPointVelocity(lastPoint), getTimeBetween2Point(planet)));

        struct Vector* newVelocity = sumVector(getPointVelocity(lastPoint), multiplicationVector(accel, getTimeBetween2Point(planet)));

        struct Point* newPoint = createPoint(newPos, newVelocity, getPointTIme(lastPoint)+1);

        addPoint(getTrajectory(planet), newPoint);

        deleteVector(&accel);

        return eulerMethod(planet, newPoint, numberOfDays);
    }
}
*/
struct Planet* eulerAsymmetricMethodWithoutRecurence(struct Planet* planet, struct Point* lastPoint) {
    for (int i = 0 ; i < (getRevolutionPeriod(planet)); i++) {

        struct Vector* firstMulti = multiplicationVector(getPointVelocity(lastPoint), getTimeBetween2Point(planet));

        struct Vector* newPos = sumVector(getPointPosition(lastPoint), firstMulti);

        deleteVector(&firstMulti);

        struct Vector* accel = calcAceleration(newPos);

        struct Vector* secondMulti = multiplicationVector(accel, getTimeBetween2Point(planet));

        struct Vector* newVelocity = sumVector(getPointVelocity(lastPoint), secondMulti);

        struct Point* newPoint = createPoint(newPos, newVelocity, getPointTIme(lastPoint)+1);

        deleteVector(&secondMulti);

        addPoint(getTrajectory(planet), newPoint);

        lastPoint = newPoint;

        deleteVector(&accel);
    }
    return planet;
}

/*struct Planet* eulerAsymmetricMethod(struct Planet* planet, struct Point* lastPoint) {
    if (getPointTIme(lastPoint) >= numberOfDays) { // it was 36499
        return planet;
    }

    else {

        struct Vector* firstMulti = multiplicationVector(getPointVelocity(lastPoint), getTimeBetween2Point(planet));

        struct Vector* newPos = sumVector(getPointPosition(lastPoint), firstMulti);

        deleteVector(&firstMulti);

        struct Vector* accel = calcAceleration(newPos);

        struct Vector* secondMulti = multiplicationVector(accel, getTimeBetween2Point(planet));

        struct Vector* newVelocity = sumVector(getPointVelocity(lastPoint), secondMulti);

        deleteVector(&secondMulti);

        struct Point* newPoint = createPoint(newPos, newVelocity, getPointTIme(lastPoint)+1);

        addPoint(getTrajectory(planet), newPoint);

        deleteVector(&accel);

        return eulerAsymmetricMethod(planet, newPoint);
    }
}*/

void printTrajectoryFile(struct Trajectory* trajectory, FILE* file) {

    struct Point* point = getFirstPointWithoutRemove(trajectory);

    struct Vector* pointPosition = getPointPosition(point);

    fprintf(file, "\t[[%e, %e, %e],", getVectorX(pointPosition), getVectorY(pointPosition), getVectorZ(pointPosition));

    struct Vector* pointVelocity = getPointVelocity(point);

    fprintf(file, "[%e, %e, %e], %d]", getVectorX(pointVelocity), getVectorY(pointVelocity), getVectorZ(pointVelocity),
            getPointTIme(point));


    //Call this function just to remove the point
    getFirstPointAndRemoveGood(trajectory);
}

void writeFile(struct Planet** planets, int method, char* fileName) {

    char* methodName;

    switch (method) {
        case 1:
            methodName = "euler";
            break;
        case 2:
            methodName = "eulerAsy";
            break;
        case 3:
            methodName = "eulerAsy";
            break;
        case 4:
            methodName = "eulerAsy";
            break;
        default:
            printf("ERROR METHOD WRITE FILE %d", method);
            return;
    }


    // open the file named planets.json
    FILE* file = NULL;

    file = fopen(fileName, "w");

    if (file == NULL) {
        printf("ERROR IMPOSSIBLE TO OPEN FILE : %s", fileName);
        return;
    }

    fputs("{", file);


    // calculate the real number of planet maybe different to NUMBER_PLANET
    int realNumbersOfPlanets = 0;

    for (int i = 0; i < NUMBER_PLANET; ++i) {
        if (planets[i] != NULL) {
            realNumbersOfPlanets++;
        }
    }

    // write every planet
    for (int j = 0; j < realNumbersOfPlanets; j++) {
        if (planets[j] != NULL) {
            fprintf(file,"\"%s-%s\" : [\n", getPlanetName(planets[j]), methodName);

            struct Trajectory* trajectoryPlanet = getTrajectory(planets[j]);

            // -1 because to the last value we don't want ","
            unsigned int sizeL = listSize(getTrajectoryQueue(trajectoryPlanet)->l)-1;
            for (int i = 0; i < sizeL; i++) {

                printTrajectoryFile(trajectoryPlanet, file);

                fputs(",\n", file);

            }

            printTrajectoryFile(trajectoryPlanet, file);


            if (j == realNumbersOfPlanets-1) {
                fputs("]\n}", file);
            }
            else {
                fputs("]\n,\n", file);
            }
        }
    }
    fclose(file);
}

void deleteAllPlanets(struct Planet*** planets) {
    for (int i = 0; i < NUMBER_PLANET; i++) {
        struct Planet* planet = (*planets)[i];
        if (planet != NULL) {
            deletePlanet(&planet);
        }
    }
    free(*planets);
    *planets = NULL;
}

/*
 * MOON
 * Demi grand axe : 384 399 km
 * Perigée 356 700 km => perihelion
 * excentricité 0.05490
 * revolution : 27.321 j
 *
 *DISTANCE MOON −> TERRE
 */


struct Planet* createMoonWithEulerAsy(struct Planet* planet, struct Point* lastPoint) {


    for (int i = 0 ; i < (getRevolutionPeriod(planet)); i++) {

        struct Vector* firstMultiMoon = multiplicationVector(getPointVelocity(lastPoint), getTimeBetween2Point(planet));

        struct Vector* newPosMoon = sumVector(getPointPosition(lastPoint), firstMultiMoon);

        deleteVector(&firstMultiMoon);

        struct Vector* accelMoon = calcAcelerationMoon(newPosMoon);

        struct Vector* secondMultiMoon = multiplicationVector(accelMoon, getTimeBetween2Point(planet));

        struct Vector* newVelocityMoon = sumVector(getPointVelocity(lastPoint), secondMultiMoon);

        struct Point* newPointMoon = createPoint(newPosMoon, newVelocityMoon, getPointTIme(lastPoint)+1);

        deleteVector(&secondMultiMoon);

        addPoint(getTrajectory(planet), newPointMoon);

        lastPoint = newPointMoon;

        deleteVector(&accelMoon);
    }
    return planet;
}





double calcVelocityPerigee(double demiGrandAxeMoon, double eccentricityMoon) {
    return sqrt((G*EARTH_WEIGHT*(1+eccentricityMoon)) / (demiGrandAxeMoon*(1-eccentricityMoon)));
}

void initMoon(struct Planet* planetMoon, double semiMajorAxis, double eccentricity) {
    struct Vector* posInit = createVector(planetMoon->perihelion, 0, 0);
    struct Vector* velocityInit = createVector(0 , calcVelocityPerigee(semiMajorAxis, eccentricity) ,0);

    addPoint(getTrajectory(planetMoon), createPoint(posInit, velocityInit, 0));
}

struct Vector* calcAcelerationMoon(struct Vector* vectorTM) {
    return multiplicationVector(vectorTM, -((G*EARTH_WEIGHT) / pow(normeVector(vectorTM), 3)));

}
