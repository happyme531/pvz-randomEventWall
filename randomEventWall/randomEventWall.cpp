#include <algorithm>
#include "include/randomEventWall.h"
#include "include/logger.h"
#include "../pvzclass/pvzclass/Enums/ZombieType.h"
#include "include/main.h"

randomEventWall::randomEventWall(/* args */) {}
randomEventWall::~randomEventWall() {}

bool randomEventWall::addSun_() {
  //随机给予玩家100~600阳光,并且尾数总为0
  uniform_int_distribution<> rint(10,60);
  unsigned int randomSun = rint(mt19937rng) * 10;
  pvz->Sun = pvz->Sun + randomSun;
  cout << white << "随机事件墙:获得了" << randomSun << "点阳光" << endl;
  //总是成功
  return 1;
};

bool randomEventWall::removeSun_() {
  //随机扣除玩家100~600阳光
  uniform_int_distribution<> rint(10,60);
  unsigned int curSun = pvz->Sun;
  if (curSun <= 100) return 0;
  unsigned int randomSun;
  do {
    randomSun = rint(mt19937rng) * 10;
  } while (randomSun >= curSun); //阳光不应该扣到负数(虽然是可以做到的)
  pvz->Sun = curSun - randomSun;
  cout << white << "随机事件墙:扣除了" << randomSun << "点阳光" << endl;
  return 1;
};

//反转阳光数值，例如:520->052
bool randomEventWall::reverseSun_() {
  unsigned int curSun = pvz->Sun;
  string curSunStr = to_string(curSun);
  reverse(curSunStr.begin(), curSunStr.end());
  pvz->Sun = atoi(curSunStr.c_str());
  cout << white << "随机事件墙:阳光由" << curSun << "反转至" << curSunStr << endl;
  return 1;
};

//在最右端生成1~4个普通僵尸
bool randomEventWall::addSomeNormalZombiesAtStartLine_() {
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
    Creater::CreateZombie(randomZombie, row, 10);
    if (logLevel >= LOG_DEBUG)
      cout << blue << "随机事件墙:在" << row << "行最右端生成了" << ZombieType::ToString(randomZombie) << endl;
  };
  cout << white << "随机事件墙:在最右端生成了" << spawnCnt << "个普通僵尸";
  return 1;
};

//同上，但是这次范围为正态分布
bool randomEventWall::addSomeNormalZombiesInLawn_() { 
  //没错，普通僵尸->普通僵尸,路障僵尸,小鬼僵尸
  uniform_int_distribution<> rint(0, 2);
  uniform_int_distribution<> rint2(0, 5);
  normal_distribution<float> rnorm(6,1.7);
  const ZombieType::ZombieType allowedZombies[] = {
      ZombieType::Zombie, ZombieType::ConeheadZombie, ZombieType::Imp};
  //生成1~3个
  int spawnCnt = rint(mt19937rng) + 1;
  for (int i = 0; i < spawnCnt; i++) {
    ZombieType::ZombieType randomZombie = allowedZombies[rint(mt19937rng)];
    int row = rint2(mt19937rng);
    int col;
    do{
      col=(int)rnorm(mt19937rng);
    }while(col<2||col>10); //不会贴脸刷怪
    Creater::CreateZombie(randomZombie, row, col);
    if (logLevel >= LOG_DEBUG)
      cout << blue << "随机事件墙:在" << row << "行"<<col<<"列生成了" << ZombieType::ToString(randomZombie) << endl;
  };
  cout << white << "随机事件墙:在场景中生成了" << spawnCnt << "个普通僵尸";
  return 1;  
  };

bool randomEventWall::removeSomeZombiesInLawn_() { 
  
  return 1; 
  };
bool randomEventWall::addABalloonZombie_() { return 1; };
