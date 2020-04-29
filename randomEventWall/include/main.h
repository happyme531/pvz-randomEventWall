#ifndef MAIN_H
#define MAIN_H
#include "../../pvzclass/pvzclass/events.h"
#include "../../pvzclass/pvzclass/PVZ.h"
#include "../../pvzclass/pvzclass/ProcessOpener.h"
#include "../../pvzclass/pvzclass/Enums/PlantType.h"
#include "../../pvzclass/pvzclass/Enums/PVZGameStateEnum.h"
#include "../../pvzclass/pvzclass/Enums/PVZVersionEnum.h"
#include "../../pvzclass/pvzclass/Creaters.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

extern PVZ* pvz;
extern mt19937 mt19937rng;

#endif