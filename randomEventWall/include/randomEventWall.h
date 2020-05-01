#pragma once
#include <string.h>
#include <vector>
#include "main.h"

class randomEventWall;

namespace randomEvents {
bool addSun_(randomEventWall* rew);
bool removeSun_(randomEventWall* rew);
bool reverseSun_(randomEventWall* rew);
bool addSomeNormalZombiesAtStartLine_(randomEventWall* rew);
bool addSomeNormalZombiesInLawn_(randomEventWall* rew);
bool removeSomeZombiesInLawn_(randomEventWall* rew);
bool addABalloonZombie_(randomEventWall* rew);
bool generateARandomPlant_(randomEventWall* rew);
bool generateRandomPlants_(randomEventWall* rew);
bool generateRandomPlantsInRow_(randomEventWall* rew);
bool generateRandomPlantsInColumn_(randomEventWall* rew);
};  // namespace randomEvents

class randomEventWall {
 public:
  randomEventWall(/* args */);
  ~randomEventWall();
  bool trigger();
  bool triggerTargetEvent(int event);
  unsigned int triggeredEventId;
  vector<int> runningEvents;

  typedef struct randomEvent {
    //该事件的幸运程度
    short luck;
    //优先级倒数:eg.为2的优先级减半
    float priorityDen;
    //事件名
    string name;
    //触发该事件对应的函数
    bool (*trigger)(randomEventWall* rew);
  } randomEvent_t;

 public:
  //下面是所有的随机事件

  const randomEvent_t addSun = {.luck = 30,
                                .priorityDen = 1,
                                .name = "添加随机阳光",
                                .trigger = &randomEvents::addSun_};
  const randomEvent_t removeSun = {
      .luck = -30,
      .priorityDen = 1,
      .name = "扣除随机阳光",
      .trigger = &randomEvents::removeSun_
      };
  const randomEvent_t reverseSun = {
      .luck = -20,
      .priorityDen = 1.5,
      .name = "反转阳光数值",
      .trigger = &randomEvents::reverseSun_
      };
  const randomEvent_t addSomeNormalZombiesAtStartLine = {
      .luck = -12,
      .priorityDen = 1,
      .name = "在起点生成一些普通僵尸",
      .trigger = &randomEvents::addSomeNormalZombiesAtStartLine_
      };
  const randomEvent_t addSomeNormalZombiesInLawn{
      .luck = -17,
      .priorityDen = 1,
      .name = "在场景中靠右生成一些普通僵尸",
      .trigger = &randomEvents::addSomeNormalZombiesInLawn_
      };
  const randomEvent_t removeSomeZombiesInLawn{
      .luck = 20,
      .priorityDen = 1,
      .name = "移除场景内一些僵尸",
      .trigger = &randomEvents::removeSomeZombiesInLawn_};
  const randomEvent_t addABalloonZombie{
      .luck = -70,
      .priorityDen = 1,
      .name = "生成一个气球僵尸",
      .trigger = &randomEvents::addABalloonZombie_};
  const randomEvent_t generateARandomPlant{
      .luck = 22,
      .priorityDen = 1.5,
      .name = "生成一个随机植物",
      .trigger = &randomEvents::generateARandomPlant_};
  const randomEvent_t generateRandomPlants{
      .luck = 34,
      .priorityDen = 1.5,
      .name = "生成一些随机植物",
      .trigger = &randomEvents::generateRandomPlants_};
  const randomEvent_t generateRandomPlantsInRow{
      .luck = 60,
      .priorityDen = 2,
      .name = "生成一行随机植物",
      .trigger = &randomEvents::generateRandomPlantsInRow_};
  const randomEvent_t generateRandomPlantsInColumn{
      .luck = 60,
      .priorityDen = 2,
      .name = "生成一列随机植物",
      .trigger = &randomEvents::generateRandomPlantsInColumn_};
  /*
  randomEvent_t removePlants;
  randomEvent_t removePlantsInRow;
  randomEvent_t removePlantsInColumn;
  randomEvent_t launchAllLawnMovers;
  randomEvent_t resetAllLawnMovers;
*/
  randomEvent_t (randomEvents[11]) = {addSun,
                                     removeSun,
                                     reverseSun,
                                     addSomeNormalZombiesAtStartLine,
                                     addSomeNormalZombiesInLawn,
                                     removeSomeZombiesInLawn,
                                     addABalloonZombie,
                                     generateARandomPlant,
                                     generateRandomPlants,
                                     generateRandomPlantsInRow,
                                     generateRandomPlantsInColumn/*,
                                     removePlants,
                                     removePlantsInRow,
                                     removePlantsInColumn,
                                     launchAllLawnMovers,
                                     resetAllLawnMovers*/
                                     };
};
