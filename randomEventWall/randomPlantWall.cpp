#include "include/randomPlantWall.h"
#include "include/main.h"
#include "include/logger.h"

extern PVZ* pvz;

randomPlantWall::randomPlantWall() {}
randomPlantWall::~randomPlantWall() {}


void randomPlantWall::trigger(Plant* brokenPlant){
    if (brokenPlant->Type == PlantType::Wallnut) {
    srand(GetTickCount());
    //注意:从模仿者开始的植物都不是正常植物
    uniform_int_distribution<> rint(0,PlantType::CobCannon);
    int spawnIncomplete=1;
    do{
    PlantType::PlantType randomPlant =(PlantType::PlantType)rint(mt19937rng);
    Plant* createdPlant=Creater::CreatePlant(randomPlant, brokenPlant->Row, brokenPlant->Column);
    createdPlant->Sleeping=false;
    if (logLevel >= LOG_INFO) cout << blue << "随机墙:生成了" << PlantType::ToString(randomPlant)<< endl;
    spawnIncomplete=0;
    }while(spawnIncomplete);
    
  };
};