#include "mainFunction.h"
#include "energetic.h"

void addPlanet(struct Planet** planets, struct Planet* planet, int method) {

    switch (method) {
        case 1:
            eulerMethodWithoutRecurence(planet, getFirstPointWithoutRemove(getTrajectory(planet)));
            break;
        case 2:
            eulerAsymmetricMethodWithoutRecurence(planet, getFirstPointWithoutRemove(getTrajectory(planet)));
            break;
        case -1:
            createMoonWithEulerAsy(planet, getFirstPointWithoutRemove(getTrajectory(planet)));
            break;
        case 3:
            eulerAsymmetricMethodWithoutRecurence(planet, getFirstPointWithoutRemove(getTrajectory(planet)));
            break;
        default:
            printf("ERROR SWITCH METHOD : %d\n", method);
            return;
    }

    for (int i = 0; i < NUMBER_PLANET; i++) {
        if (planets[i] == NULL) {
            planets[i] = planet;
            return;
        }
    }
}

void menu() {


    struct Planet** planets = malloc(NUMBER_PLANET*sizeof(struct Planet));

    for (int i = 0; i < NUMBER_PLANET; i++) {
        planets[i] = NULL;
    }


    printf("-------- SOLAR SYSTEM MENU --------\n");
    printf("Please select your method\n1 - euler\n2 - Euler asymetric\n3 - Energetic\n");

    int userInput;

    scanf("%d", &userInput);

    if (userInput < 1 || userInput > 4) {
        printf("Please enter a value between 1 and 2\n");
        return;
    }

    printf("\nNow select planet you want\n");

    bool mercuryAlreadyChoose = false, venusAlreadyChoose = false, earthAlreadyChoose = false, marsAlreadyChoose = false, jupiterAlreadyChoose = false, saturnAlreadyChoose = false, uranusAlreadyChoose = false, neptuneAlreadyChoose = false, moonAlreadyChoose = false;

    struct Planet* mercuryPlanet, *venusPlanet, *earthPlanet, *marsPlanet, *jupiterPlanet, *saturnPlanet, *uranusPlanet, *neptunePlanet, *moonPlanet;

    bool end = false;

    while (!end) {

        printf("1 - mercury\n2 - venus\n3 - earth\n4 - mars\n5 - jupiter\n6 - saturn\n7 - uranus\n8 - neptune\n");
        if (userInput != 1) {
            printf("9 - Moon\n");
        }
        printf("\n10 - stop\n11 - Quit without saving\n");

        int planetInput;
        scanf("%d", &planetInput);

        switch (planetInput) {
            case 1:

                if (mercuryAlreadyChoose) {
                    printf("you already choose mercury\n");
                    break;
                }

                mercuryPlanet = createPlanet("mercury", MERCURY_WEIGHT, MERCURY_PERIHELION, 87*10, 8640);

                init(mercuryPlanet, MERCURY_SEMI_MAJOR_AXIS, MERCURY_ECCENTRICITY);
                printf("You choose mercury\n");
                addPlanet(planets, mercuryPlanet, userInput);
                mercuryAlreadyChoose = true;
                break;
            case 2:
                if (venusAlreadyChoose) {
                    printf("you already choose venus\n");
                    break;
                }
                venusPlanet = createPlanet("venus", VENUS_WEIGHT, VENUS_PERIHELION, 224*10, 8640);

                init(venusPlanet, VENUS_SEMI_MAJOR_AXIS, VENUS_ECCENTRICITY);
                printf("You choose venus\n");
                addPlanet(planets, venusPlanet, userInput);
                venusAlreadyChoose = true;
                break;
            case 3:
                if (earthAlreadyChoose) {
                    printf("you already choose earth\n");
                    break;
                }
                earthPlanet = createPlanet("earth", EARTH_WEIGHT, EARTH_PERIHELION, 365*10, 8640);

                init(earthPlanet, EARTH_SEMI_MAJOR_AXIS, EARTH_ECCENTRICITY);
                printf("You choose earth\n");
                addPlanet(planets, earthPlanet, userInput);
                earthAlreadyChoose = true;
                break;
            case 4:
                if (marsAlreadyChoose) {
                    printf("you already choose mars\n");
                    break;
                }
                marsPlanet = createPlanet("mars", MARS_WEIGHT, MARS_PERIHELION, 686*10, 8640);

                init(marsPlanet, MARS_SEMI_MAJOR_AXIS, MARS_ECCENTRICITY);
                printf("You choose mars\n");
                addPlanet(planets, marsPlanet, userInput);
                marsAlreadyChoose = true;
                break;
            case 5:
                if (jupiterAlreadyChoose) {
                    printf("you already choose jupiter\n");
                    break;
                }
                jupiterPlanet = createPlanet("jupiter", JUPITER_WEIGHT, JUPITER_PERIHELION, 4332, 86400);

                init(jupiterPlanet, JUPITER_SEMI_MAJOR_AXIS, JUPITER_ECCENTRICITY);
                printf("You choose jupiter\n");
                addPlanet(planets, jupiterPlanet, userInput);
                jupiterAlreadyChoose = true;
                break;
            case 6:
                if (saturnAlreadyChoose) {
                    printf("you already choose saturn\n");
                    break;
                }
                saturnPlanet = createPlanet("saturn", SATURN_WEIGHT, SATURN_PERIHELION, 10759, 86400);

                init(saturnPlanet, SATURN_SEMI_MAJOR_AXIS, SATURN_ECCENTRICITY);
                printf("You choose saturn\n");
                addPlanet(planets, saturnPlanet, userInput);
                saturnAlreadyChoose = true;
                break;
            case 7:
                if (uranusAlreadyChoose) {
                    printf("you already choose uranus\n");
                    break;
                }
                uranusPlanet = createPlanet("uranus", URANUS_WEIGHT, URANUS_PERIHELION, 30685, 86400);

                init(uranusPlanet, URANUS_SEMI_MAJOR_AXIS, URANUS_ECCENTRICITY);
                printf("You choose uranus\n");
                addPlanet(planets, uranusPlanet, userInput);
                uranusAlreadyChoose = true;
                break;
            case 8:
                if (neptuneAlreadyChoose) {
                    printf("you already choose neptune\n");
                    break;
                }
                neptunePlanet = createPlanet("neptune", NEPTUNE_WEIGHT, NEPTUNE_PERIHELION, 60266, 86400);

                init(neptunePlanet, NEPTUNE_SEMI_MAJOR_AXIS, NEPTUNE_ECCENTRICITY);
                printf("You choose neptune\n");
                addPlanet(planets, neptunePlanet, userInput);
                neptuneAlreadyChoose = true;
                break;
            case 10:
                if (planets[0] == NULL) {
                    printf("You don't choose any planet please restart\n");
                    deleteAllPlanets(&planets);
                    return;
                }
                else {
                    printf("your planet(s) is / are generating\n");
                    end = true;
                    break;
                }
            case 11:
                printf("Goodbye !\n");
                deleteAllPlanets(&planets);
                return;
            case 9:
                if (moonAlreadyChoose) {
                    printf("you already choose the moon\n");
                    break;
                }
                moonPlanet = createPlanet("moon", 7.342e+22, 356670000, 27.321*10, 8640);

                initMoon(moonPlanet, 384399000, 0.05490);
                printf("You choose the moon\n");
                addPlanet(planets, moonPlanet, -1);
                moonAlreadyChoose = true;
                break;
            default:
                printf("please enter a value between 1 and 8\n");
                break;
        }
    }

    if (planets[0] == NULL) {
        printf("You don't choose any planet please restart\n");
        deleteAllPlanets(&planets);
        return;
    }

    if (userInput == 3) {
        int realNumberOfWord = 0;

        for (int i = 0; i < NUMBER_PLANET; i++) {
            if (planets[i] != NULL) {
                realNumberOfWord++;
            }
        }
        printf("\n\n\n-------- ENERGETIC ---------\n");
        for (int i = 0; i < realNumberOfWord; i++) {
            double energeticNumber = EnergeticEtude(planets[i]);

            printf("Name : %s, energetic : %e\n", getPlanetName(planets[i]), energeticNumber);
        }

    }
    else {

        char* methodName;

        switch (userInput) {
            case 1:
                methodName = "Euler";
                break;
            case 2:
                methodName = "EulerAsy";
                break;
            case 3:
                methodName = "EulerAsy";
                break;
            case 4:
                methodName = "EulerAsy";
                break;
            default:
                printf("ERROR METHOD WRITE FILE %d", userInput);
                return;
        }

        char fullName[30] = "planets-";

        strcat(fullName, methodName);

        strcat(fullName, ".json");

        writeFile(planets, userInput, fullName);

        printf("Trajectory write in the file %s\n", fullName);
    }


    deleteAllPlanets(&planets);

}