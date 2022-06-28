#ifndef PROJECTTEST_ENERGETIC_H
#define PROJECTTEST_ENERGETIC_H

#include "planet.h"

/**
 * Function to calcule the energetic ration of the planet with Ec = Epp + Ec
 * @param planet -> the planet to calcule the Em ration
 * @return the Energetic result. 1 is good, not 1 is not good
 */
double EnergeticEtude(struct Planet* planet);

/**
 * Calculates the Ep of any point of any planet
 * @param weight -> weight of the planet
 * @param distance -> distance between the planet and the sun
 * @return the Epp of a certain point of any planet with the sun
 */
double calcEpp(double weight, double distance);

/**
 * Calculate the kinetic energy of any point of any planet
 * @param weight -> weight of the planet
 * @param speed -> speed of the planet at a certain point
 * @return the kinetic energy
 */
double calcEc(double weight, double speed);



#endif //PROJECTTEST_ENERGETIC_H
