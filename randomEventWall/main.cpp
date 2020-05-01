#include "include/main.h"
#include "include/randomPlantWall.h"
#include "include/randomEventWall.h"
#include "include/logger.h"
#include "components/include/cmdline.h"

#include "../pvzclass/pvzclass/utils.h"
#include "../pvzclass/pvzclass/Enums/CaptionStyle.h"

#define RANDOMEVENTWALL_VERSION 0.1


using namespace std;

int logLevel = 5;
int testEvent=0;
bool disableRandomWall=false;
bool disableRandomEventWall=false;
PVZ* pvz = nullptr;
mt19937 mt19937rng(0); 
randomPlantWall rpw;
randomEventWall rew;

template<class T>
int length(T& arr)
{
	return sizeof(arr) / sizeof(arr[0]);
}

void onPlantRemove(Event* e) {
  Plant* plant = ((EventPlantRemove*)e)->plant;
  if (plant->Type == PlantType::Wallnut && !disableRandomWall) rpw.trigger(plant);
  if (plant->Type == PlantType::Sunshroon && !disableRandomEventWall) rew.trigger();
};


//经典的随机事件墙关卡:向日葵，荷叶，随机墙，随机事件墙
//(向日葵，荷叶，坚果墙，阳光菇)
void initClassicRandomWall() {
  if (logLevel >= LOGLEVEL_INFO) cout << blue << "修改植物卡槽.." << endl;
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

int main(int argc, char* argv[], char* env[]) {
  //解决中文乱码问题..?
  SetConsoleOutputCP(65001);
  //解析参数
  cmdline::parser par;
  par.add("version",'v',"显示程序版本");
  par.add("disable-random-event-wall",'\0',"禁用随机事件墙");
  par.add("disable-random-wall",'\0',"禁用随机(植物)墙");
  par.add("hide-banner",'\0',"禁用程序启动时输出的信息");
  par.add("list-events",'\0',"列出所有可用的事件(名称与id)");
  par.add<int>("log-level",'\0',"<等级> 改变日志等级(0~5)",false,5);
  par.add<int>("test-event",'\0',"<事件id> 执行一个事件之后退出",false,0,cmdline::range(1,length(rew.randomEvents)));
 
  par.parse_check(argc,argv);

  testEvent=par.get<int>("test-event");
  logLevel=par.get<int>("log-level");
  
  if(par.exist("version")){
    cout << white << "随机事件墙版本:" << RANDOMEVENTWALL_VERSION << endl;
    cout << white << "pvzclass版本:" << pvz->Version << endl;
    return 0;
  }
  //启动时的输出
  if (!par.exist("hide-banner")) {
    cout << yellow << "===植物大战僵尸 随机事件墙===" << endl;
    cout << yellow << "===by 快乐的我531/hallo1===" << endl;
    cout <<endl;
    cout << blue << "使用--help获得更多选项帮助..." << endl;
    cout <<endl;
    cout << green << "随机事件墙版本:" << RANDOMEVENTWALL_VERSION << endl;
    cout << green << "pvzclass版本:" << pvz->Version << endl;
    cout << green << "编译时间: " << __DATE__ << " " << __TIME__ << endl;
  };

  if (par.exist("list-events")) {
    cout << yellow << "全部事件列表:" << endl;
    for (int i = 0; i < length(rew.randomEvents); i++) {
      cout << white << i + 1 << ":" << rew.randomEvents[i].name << endl;
    };
    return 0;
  };

  disableRandomWall=par.exist("disable-random-wall");
  disableRandomEventWall=par.exist("disable-random-event-wall");

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

  if (!par.exist("hide-banner")) cout << green << "游戏版本:" << PVZVersion::ToString(pvz->GameVersion) << endl;

  if (pvz->GameVersion != PVZVersion::V1_0_0_1051) {
    cout << red << "警告:该游戏版本不受支持,请使用v1.0.0.1051版本!" << endl;
  };
  
  if (pvz->GameState != PVZGameState::Playing) {
    cout << white << "等待进入游戏.." << endl;
  }
  while (pvz->GameState != PVZGameState::Playing) {
    Sleep(200);
  };
  
  mt19937rng.seed((unsigned int)chrono::system_clock::now().time_since_epoch().count());
       

  //现在已经进入游戏了
  if(testEvent){
    cout<<blue<<"触发事件#"<<testEvent<<":"<<rew.randomEvents[testEvent-1].name<<endl;
    bool res = rew.triggerTargetEvent(testEvent);
    while(rew.runningEvents.size()) Sleep(100);
    return res;
  };

  initClassicRandomWall();
  EventHandler e(pvz);
  e.RegistryListeners("PlantRemove", onPlantRemove);
  while (pvz->BaseAddress) {
    e.Run();
  };

  // EventHandler end
  while(rew.runningEvents.size()) Sleep(100);
  cout<<white<<endl;
  delete pvz;
  return 0;
};