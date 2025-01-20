#ifndef INFANTRY_H
#define INFANTRY_H

#include "Robot.h"
#include <bits/stdc++.h>

#define int long long

class Infantry
        : public Robot {
public:
    Infantry(int teamId, int id, int level)
            : Robot(teamId, id, getHealthForLevel(level), getHeatForLevel(level)), level_(level) {
    } //构建函数重载
    void handleCommand(const std::string &command, const std::vector<int> &params);//处理H与U命令

    void updateHeat(int timeElapsed) override; //更新热量与伤害

private:
    int level_;//等级（特有的）

    static int getHealthForLevel(int level)//根据等级设置血量上限
    {
        switch (level) {
            case 1:
                return 100;
            case 2:
                return 150;
            case 3:
                return 250;
            default:
                return 100;
        }
    }

    static int getHeatForLevel(int level)//根据等级设置热量上限
    {
        switch (level) {
            case 1:
                return 100;
            case 2:
                return 200;
            case 3:
                return 300;
            default:
                return 100;
        }
    }
};


#endif //INFANTRY_H
