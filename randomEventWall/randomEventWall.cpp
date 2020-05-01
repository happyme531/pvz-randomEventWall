#include "include/randomEventWall.h"
#include "include/logger.h"
#include "../pvzclass/pvzclass/Enums/ZombieType.h"
#include "include/main.h"

randomEventWall::randomEventWall(/* args */) {}
randomEventWall::~randomEventWall() {}

template<class T>
int length(T& arr)
{
	return sizeof(arr) / sizeof(arr[0]);
}

bool randomEventWall::triggerTargetEvent(int event) {
  inGameCenterCaption() << this->randomEvents[event - 1].name;
  this->triggeredEventId = event;
  return this->randomEvents[event - 1].trigger(this);
};

bool randomEventWall::trigger(){
  vector<double> weights;
  double weightSum=0;
  int eventCnt=length(this->randomEvents);
  for(int i=0;i<eventCnt;i++){
    //每个事件的权重
    //..越幸运/不幸,权重越低
    //虽然可能不是很明显
    double thisWeight = 10;
    thisWeight *= ((double)100 / (50 + abs(this->randomEvents[i].luck)));
    thisWeight /= this->randomEvents[i].priorityDen;
    weights.push_back(thisWeight);
    weightSum += thisWeight;
  };
  uniform_real_distribution<double> ran(0, weightSum);
  double target = ran(mt19937rng);
  double target_original=target;
  int i=0;
  for (i = 0; i < eventCnt; i++){
    if(weights[i]>target) break;
    target-=weights[i];
  };
  LOG_VERBOSE(cout<<blue<<"随机事件墙:触发事件"<<i+1<<",总权重"<<weightSum<<",随机权重"<<target_original<<endl);
  return this->triggerTargetEvent(i+1);
};