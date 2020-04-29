#pragma once
#include <string.h>
#include "main.h"
typedef struct randomEvent {
  //该事件的幸运程度
  int luck;
  //事件名
  string name;
  //触发该事件对应的函数
  bool (*trigger)(void);

} randomEvent_t;

class randomEventWall {
 public:
  randomEventWall(/* args */);
  ~randomEventWall();
  void trigger(Plant* brokenPlant);

 private:
  static bool addSun_();
  static bool removeSun_();
  static bool reverseSun_();
  static bool addSomeNormalZombiesAtStartLine_();
  static bool addSomeNormalZombiesInLawn_();
  static bool removeSomeZombiesInLawn_();
  static bool addABalloonZombie_();

 public:
  //下面是所有的随机事件
  const randomEvent_t addSun = {
      .luck = 30, .name = "添加随机阳光", .trigger = &addSun_};
  const randomEvent_t removeSun = {
      .luck = -30, .name = "扣除随机阳光", .trigger = &removeSun_};
  const randomEvent_t reverseSun = {
      .luck = -20, .name = "反转阳光数值", .trigger = &reverseSun_};
  const randomEvent_t addSomeNormalZombiesAtStartLine = {
      .luck = -12,
      .name = "在起点生成一些普通僵尸",
      .trigger = &addSomeNormalZombiesAtStartLine_};
  const randomEvent_t addSomeNormalZombiesInLawn{
      .luck = -17,
      .name = "在场景中靠右生成一些普通僵尸",
      .trigger = &addSomeNormalZombiesInLawn_};
  const randomEvent_t removeSomeZombiesInLawn{
      .luck = 20,
      .name = "移除场景内一些僵尸",
      .trigger = &removeSomeZombiesInLawn_};
  const randomEvent_t addABalloonZombie{
      .luck = -70,
      .name = "生成一个气球僵尸",
      .trigger = &addABalloonZombie_}; 
  randomEvent_t generateRandomPlants;
  randomEvent_t generateRandomPlantsInRow;
  randomEvent_t generateRandomPlantsInColumn;
  randomEvent_t removePlants;
  randomEvent_t removePlantsInRow;
  randomEvent_t removePlantsInColumn;
  randomEvent_t launchAllLawnMovers;
  randomEvent_t resetAllLawnMovers;

  randomEvent_t (randomEvents[15]) = {addSun,
                                     removeSun,
                                     reverseSun,
                                     addSomeNormalZombiesAtStartLine,
                                     addSomeNormalZombiesInLawn,
                                     removeSomeZombiesInLawn,
                                     addABalloonZombie,
                                     generateRandomPlants,
                                     generateRandomPlantsInRow,
                                     generateRandomPlantsInColumn,
                                     removePlants,
                                     removePlantsInRow,
                                     removePlantsInColumn,
                                     launchAllLawnMovers,
                                     resetAllLawnMovers};
};
