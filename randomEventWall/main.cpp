#include "include/main.h"
#include "include/randomPlantWall.h"
#include "include/logger.h"
#include "../pvzclass/pvzclass/utils.h"

#define RANDOMEVENTWALL_VERSION 0.1

int logLevel = 5;
using namespace std;
PVZ* pvz = nullptr;
randomPlantWall rpw;

void onPlantRemove(Event* e) {
  Plant* plant = ((EventPlantRemove*)e)->plant;
  rpw.trigger(plant);
};

void onPlantPlant(Event* e){
}

//经典的随机事件墙关卡:向日葵，荷叶，随机墙，随机事件墙
//(向日葵，荷叶，坚果墙，阳光菇)
void initClassicRandomWall() {
  if (logLevel >= LOG_INFO) cout << blue << "修改植物卡槽.." << endl;
  PVZ::CardSlot* cardSlot = pvz->GetCardSlot();
  cardSlot->GetCard(0)->ContentCard = CardType::Sunflower;
  cardSlot->GetCard(1)->ContentCard = CardType::LilyPad;
  cardSlot->GetCard(2)->ContentCard = CardType::Wallnut;
  cardSlot->GetCard(3)->ContentCard = CardType::Sunshroon;
  for (int i = 4; i < cardSlot->CardsCount; i++) {
    cardSlot->GetCard(i)->ContentCard = CardType::None;
  };
  Utils::SetPlantCooldown(PlantType::Wallnut, 800); //时间单位:0.01s
  Utils::SetPlantCost(PlantType::Wallnut, 150);
};

int main() {
  //启动时的输出
  cout << yellow << "===植物大战僵尸 随机事件墙===" << endl;
  cout << yellow << "===by 快乐的我531/hallo1===" << endl;
  cout << green << "随机事件墙版本:" << RANDOMEVENTWALL_VERSION << endl;
  cout << green << "pvzclass版本:" << pvz->Version << endl;
  cout << green << "游戏版本:" << PVZVersion::ToString(pvz->GameVersion)<< endl;
  cout << green << "编译时间: " << __DATE__ << " " << __TIME__ << endl;

  Creater::AsmInit();

  DWORD pid = ProcessOpener::Open();

  if (!pid) {
    cout << red << "找不到游戏进程！" << endl;
    cout << "请按任意键退出...." << endl;
    getchar();
    return 1;
  };
  pvz = new PVZ(pid);
  if (!pvz->BaseAddress) {
    cout << red << "找不到游戏基址！" << endl;
    cout << "请以管理员身份并在进入一个关卡后运行此程序" << endl;
    cout << "请按任意键退出...." << endl;
    getchar();
    return 2;
  };
  if (pvz->GameState != PVZGameState::Playing) {
    cout << white << "等待进入游戏.." << endl;
  }
  while (pvz->GameState != PVZGameState::Playing) {
    Sleep(200);
  }
  initClassicRandomWall();
  EventHandler e(pvz);
  e.RegistryListeners("PlantRemove", onPlantRemove);
  e.RegistryListeners("PlantPlant",onPlantPlant);
  while (pvz->BaseAddress) {
    e.Run();
  };

  // EventHandler end
  delete pvz;
  return 0;
};