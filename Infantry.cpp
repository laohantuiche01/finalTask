
#include "Infantry.h"

void Infantry::handleCommand(const std::string &command, const std::vector<int> &params) {
    if (command == "U") //如果是U
    {
        int targetLevel = params[2]; //设定等级
        level_ = std::max(level_, targetLevel); //传入参数,选取最大值
        resetMaxHealth_(getHealthForLevel(level_)); //通过函数修改robot的类
        setHealth(getMaxHealth());
        resetMaxHeat_(getHeatForLevel(level_)); //
        //std::cout<<"Infantry::handleCommand()"<<std::endl;
    } else if (command == "H") //如果是H
    {
        int tempheat = getHeat();
        tempheat += params[2];
        setHeat(tempheat);
        //std::cout << tempheat << std::endl;
    }
}

void Infantry::updateHeat(int timeElapsed) //更新热量与伤害
{
    int tempHeat = getHeat(); //储存原来的热量
    setHeat(std::max(0LL, tempHeat - timeElapsed)); //重置热量值
    if (tempHeat > getHeat()) //之前的热量大于最大热量值
    {
        int tempHeatNum = std::min(timeElapsed, tempHeat - getMaxHeat()); //找时间差与热量差 找出应该扣多少血
        decreaseHealth(tempHeatNum); //扣血
//std::cout << tempHeatNum << std::endl;
    }
//std::cout << tempHeat << std::endl;
// setHeat( std::max(0, getHeat() - timeElapsed));
// if (getHeat()> getMaxHealth()) {
//     decreaseHealth(timeElapsed);
// }
}