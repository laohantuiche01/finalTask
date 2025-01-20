
#include "Engineer.h"

void Engineer::updateHeat(int timeElapsed) {
    int tempHeat = getHeat(); //储存原来的热量
    setHeat(std::max(0LL, tempHeat - timeElapsed)); //重置热量值
    if (tempHeat > 0) //之前的热量大于最大热量值
    {
        int tempHeatNum = std::min(timeElapsed, tempHeat - getMaxHeat()); //找时间差与热量差 找出应该扣多少血
        decreaseHealth(tempHeatNum); //扣血
//std::cout << tempHeatNum << std::endl;
    }
}

void Engineer::HeatSet(const std::string &command, const std::vector<int> &params) {
    int tempheat = getHeat();
    tempheat += params[2];
    setHeat(tempheat);
}