#include "include/randomPlantWall.h"
#include "include/main.h"
#include "include/logger.h"

extern PVZ* pvz;

randomPlantWall::randomPlantWall() {}
randomPlantWall::~randomPlantWall() {}

void randomPlantWall::trigger(Plant* brokenPlant){
    if (brokenPlant->Type == PlantType::Wallnut) {
    srand(GetTickCount());
    int spawnIncomplete=1;
    do{
    PlantType::PlantType randomPlant =(PlantType::PlantType)((rand() % (PlantType::LeftRepeater + 1)));
    if(randomPlant==PlantType::Imitater) continue; //生成模仿者会造成游戏崩溃
    Plant* createdPlant=Creater::CreatePlant(randomPlant, brokenPlant->Row, brokenPlant->Column);
    createdPlant->Sleeping=false;
    if (logLevel >= LOG_INFO) cout << blue << "随机墙:生成了" << PlantType::ToString(randomPlant)<< endl;
    spawnIncomplete=0;
    }while(spawnIncomplete);
    
  };
};