#include "energetic.h"


double EnergeticEtude(struct Planet* planet) {

    double size = getRevolutionPeriod(planet);

    double arrayEm[(int) size];

    for (int i = 0; i < size; i++) {
        struct Point* p = getFirstPointAndRemove(getTrajectory(planet));
        double distance = normeVector(getPointPosition(p));
        double Epp = calcEpp(getPlanetWeight(planet), distance);

        double Ec = calcEc(getPlanetWeight(planet), normeVector(getPointVelocity(p)));

        arrayEm[i] = (Ec + Epp);

        removeFirstPoint(getTrajectory(planet));
    }

    double ratio = 0;

    int i;
    for (i = 0; i < size-1; i++) {
        ratio += arrayEm[i+1] / arrayEm[i];
    }

    ratio = ratio / i;

    return ratio;
}

double calcEpp(double weight, double distance) {
    return (0.5)*((G*weight*SUN_WEIGHT)/(distance*distance));
}

double calcEc(double weight, double speed) {
    return (0.5)*(weight*speed*speed);
}