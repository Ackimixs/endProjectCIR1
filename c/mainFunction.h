#ifndef PROJECTTEST_MAINFUNCTION_H
#define PROJECTTEST_MAINFUNCTION_H

#include "planet.h"

/**
 * @param planets -> the planet list
 * @param planet -> the planet to add in the planet list
 * @param method -> 1 - euluer / 2 -> euler asymetric
 */
void addPlanet(struct Planet** planets, struct Planet* planet, int method);

/**
 * Menu to simplify the main
 *
 */
void menu();

#endif //PROJECTTEST_MAINFUNCTION_H
