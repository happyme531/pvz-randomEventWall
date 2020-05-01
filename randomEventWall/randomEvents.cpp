#include "include/logger.h"
#include "include/main.h"
#include <algorithm>
#include <thread>
#include "include/randomEventWall.h"

using namespace randomEvents;
using namespace std;

namespace randomEvents {

bool addSun_(randomEventWall* rew) {
  rew->triggeredEventId = 0;
  //随机给予玩家100~600阳光,并且尾数总为0
  uniform_int_distribution<> rint(10, 60);
  unsigned int randomSun = rint(mt19937rng) * 10;
  pvz->Sun = pvz->Sun + randomSun;
  cout << white << "随机事件墙:获得了" << randomSun << "点阳光" << endl;
  //总是成功
  return 1;
};

bool removeSun_(randomEventWall* rew) {
  rew->triggeredEventId = 0;
  //随机扣除玩家100~600阳光
  uniform_int_distribution<> rint(10, 60);
  unsigned int curSun = pvz->Sun;
  if (curSun <= 100) return 0;
  unsigned int randomSun;
  do {
    randomSun = rint(mt19937rng) * 10;
  } while (randomSun >= curSun);  //阳光不应该扣到负数(虽然是可以做到的)
  pvz->Sun = curSun - randomSun;
  cout << white << "随机事件墙:扣除了" << randomSun << "点阳光" << endl;
  return 1;
};

//反转阳光数值，例如:520->052
bool reverseSun_(randomEventWall* rew) {
  rew->triggeredEventId = 0;
  unsigned int curSun = pvz->Sun;
  string curSunStr = to_string(curSun);
  reverse(curSunStr.begin(), curSunStr.end());
  pvz->Sun = atoi(curSunStr.c_str());
  cout << white << "随机事件墙:阳光由" << curSun << "反转至" << curSunStr
       << endl;
  return 1;
};

//在最右端生成1~4个普通僵尸
bool addSomeNormalZombiesAtStartLine_(randomEventWall* rew) {
  //瞬间完成
  rew->triggeredEventId = 0;
  //没错，普通僵尸->普通僵尸,路障僵尸,小鬼僵尸
  uniform_int_distribution<> rint(0, 2);
  uniform_int_distribution<> rint2(0, 5);
  const ZombieType::ZombieType allowedZombies[] = {
      ZombieType::Zombie, ZombieType::ConeheadZombie, ZombieType::Imp};
  //生成1~3个
  int spawnCnt = rint(mt19937rng) + 1;
  for (int i = 0; i < spawnCnt; i++) {
    ZombieType::ZombieType randomZombie = allowedZombies[rint(mt19937rng)];
    int row = rint2(mt19937rng);
    Creater::CreateZombie(randomZombie, row, 9);

    LOG_DEBUG(cout << blue << "随机事件墙:在" << row << "行最右端生成了"
                   << ZombieType::ToString(randomZombie) << endl);
  };
  cout << white << "随机事件墙:在最右端生成了" << spawnCnt << "个普通僵尸";
  return 1;
};

//同上，但是这次范围为正态分布
void addSomeNormalZombiesInLawn_thread(randomEventWall* rew) {
  unsigned int id = rew->triggeredEventId;
  rew->triggeredEventId = 0;
  rew->runningEvents.push_back(id);
  this_thread::sleep_for(chrono::seconds(2));
  //没错，普通僵尸->普通僵尸,路障僵尸,小鬼僵尸
  uniform_int_distribution<> rint(0, 2);
  uniform_int_distribution<> rint2(0, 5);
  normal_distribution<float> rnorm(6.5F, 1.6F);
  const ZombieType::ZombieType allowedZombies[] = {
      ZombieType::Zombie, ZombieType::ConeheadZombie, ZombieType::Imp};
  //生成1~3个
  int spawnCnt = rint(mt19937rng) + 1;
  for (int i = 0; i < spawnCnt; i++) {
    ZombieType::ZombieType randomZombie = allowedZombies[rint(mt19937rng)];
    int row = rint2(mt19937rng);
    int col;
    do {
      col = (int)rnorm(mt19937rng);
    } while (col < 2 || col > 10);  //不会贴脸刷怪
    Creater::CreateZombie(randomZombie, row, col);
    LOG_DEBUG(cout << blue << "随机事件墙:在" << row << "行" << col
                   << "列生成了" << ZombieType::ToString(randomZombie) << endl);
    this_thread::sleep_for(chrono::milliseconds(400));
  };
  cout << white << "随机事件墙:在场景中生成了" << spawnCnt << "个普通僵尸";
  auto iter = find(rew->runningEvents.begin(), rew->runningEvents.end(), id);
  if (iter != rew->runningEvents.end()) rew->runningEvents.erase(iter);
};

bool addSomeNormalZombiesInLawn_(randomEventWall* rew) {
  //当前有一个同样的任务正在运行
  if (find(rew->runningEvents.begin(), rew->runningEvents.end(),
           rew->triggeredEventId) != rew->runningEvents.end()) {
    rew->triggeredEventId = 0;
    return 0;
  };
  thread t(addSomeNormalZombiesInLawn_thread, rew);
  t.detach();
  return 1;
};

bool removeSomeZombiesInLawn_(randomEventWall* rew) {
  rew->triggeredEventId = 0;
  Zombie* allZombies[50];
  int zombieCnt = pvz->GetAllZombies(allZombies);
  if (zombieCnt < 1) return 0;
  uniform_int_distribution<> rint1(1, 6);
  int killCnt;
  do {
    killCnt = rint1(mt19937rng);
  } while (killCnt > zombieCnt);
  vector<unsigned short> temp;
  for (int i = 0; i < zombieCnt; i++) temp.push_back(i);
  // random_shuffle在c++17中移除了
  shuffle(temp.begin(), temp.end(), mt19937rng);
  for (int i = 0; i < killCnt; i++){
    allZombies[temp[i]]->State=3; //3:秒杀
  };
  cout<<blue<<"随机事件墙:清除了"<<killCnt<<"只僵尸"<<endl;
  return 1;
};
bool addABalloonZombie_(randomEventWall* rew) {
  rew->triggeredEventId = 0;
  uniform_int_distribution<> rint(0,5);
  int row=rint(mt19937rng);
  Creater::CreateZombie(ZombieType::BalloonZombie,row,9);
  cout<<blue<<"随机事件墙:在第"<<row<<"行生成了一只气球僵尸"<<endl;
  return 1;  
};

bool generateARandomPlant_(randomEventWall* rew) {
  rew->triggeredEventId = 0;
  uniform_int_distribution<> rint_plant(0, PlantType::CobCannon);  //植物
  uniform_int_distribution<> rint_row(0, 5);
  uniform_int_distribution<> rint_column(0, 8);
  //生成1个
  int row = rint_row(mt19937rng);
  int col = rint_column(mt19937rng);
  PlantType::PlantType rplant = (PlantType::PlantType)rint_plant(mt19937rng);
  Creater::CreatePlant(rplant, row, col);
  cout << blue << "随机事件墙:在" << row << "行" << col << "列生成了" << PlantType::ToString(rplant) << endl;
  return 1;
};

bool generateRandomPlants_thread(randomEventWall* rew){ 
  unsigned int id = rew->triggeredEventId;
  rew->triggeredEventId = 0;
  rew->runningEvents.push_back(id);
  this_thread::sleep_for(chrono::seconds(2));
  uniform_int_distribution<> rint_plant(0, PlantType::CobCannon);  //一行或一列玉米加农炮可能不是什么好事
  uniform_int_distribution<> rint_row(0, 5);
  uniform_int_distribution<> rint_column(0, 8);
  uniform_int_distribution<> rint_cnt(2,6);
  int spawnCnt = rint_cnt(mt19937rng);
  for (int i = 0; i < spawnCnt; i++) {
    int row = rint_row(mt19937rng);
    int col=rint_column(mt19937rng);
    PlantType::PlantType rplant = (PlantType::PlantType)rint_plant(mt19937rng);
    Plant* createdPlant=Creater::CreatePlant(rplant, row, col);
    if(createdPlant->Sleeping) createdPlant->Sleeping=false;
    LOG_DEBUG(cout << blue << "随机事件墙:在" << row << "行" << col<< "列生成了" << PlantType::ToString(rplant) << endl);
    this_thread::sleep_for(chrono::milliseconds(400));
  };
  cout << white << "随机事件墙:在场景中生成了" << spawnCnt << "个植物";
  auto iter = find(rew->runningEvents.begin(), rew->runningEvents.end(), id);
  if (iter != rew->runningEvents.end()) rew->runningEvents.erase(iter);
  return 1; 
};

bool generateRandomPlants_(randomEventWall* rew){ 
   //当前有一个同样的任务正在运行
  if (find(rew->runningEvents.begin(), rew->runningEvents.end(),
           rew->triggeredEventId) != rew->runningEvents.end()) {
    rew->triggeredEventId = 0;
    return 0;
  };
  thread t(generateRandomPlants_thread, rew);
  t.detach();
  return 1;
};

bool generateRandomPlantsInRow_(randomEventWall* rew) {
  rew->triggeredEventId = 0;
  uniform_int_distribution<> rint_plant(0, PlantType::CobCannon-1);  //植物
  uniform_int_distribution<> rint_row(0, 5);
  //生成1个
  int row = rint_row(mt19937rng);
  PlantType::PlantType rplant = (PlantType::PlantType)rint_plant(mt19937rng);
  for (int col = 0; col <= 8; col++) {
    Plant* createdPlant = Creater::CreatePlant(rplant, row, col);
    if (createdPlant->Sleeping) createdPlant->Sleeping = false;
  };
  cout << blue << "随机事件墙:在" << row << "行生成了" << PlantType::ToString(rplant) << endl;
  return 1;
};

bool generateRandomPlantsInColumn_(randomEventWall* rew) { 
  rew->triggeredEventId = 0;
  uniform_int_distribution<> rint_plant(0, PlantType::CobCannon-1);  //植物
  uniform_int_distribution<> rint_col(0, 8);
  //生成1个
  int col = rint_col(mt19937rng);
  PlantType::PlantType rplant = (PlantType::PlantType)rint_plant(mt19937rng);
  for (int row = 0; row <= 5; row++){
    Plant* createdPlant = Creater::CreatePlant(rplant, row, col);
    if (createdPlant->Sleeping) createdPlant->Sleeping = false;
  };
  cout << blue << "随机事件墙:在" << col << "列生成了" << PlantType::ToString(rplant) << endl;
  return 1;
  };
};  // namespace randomEvents
