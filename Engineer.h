#ifndef ENGINEER_H
#define ENGINEER_H

#include "Robot.h"

#define int long long

class Engineer
        : public Robot {
public:
    Engineer(int teamId, int id) : Robot(teamId, id, 300, 0) {
    }

    void updateHeat(int timeElapsed) override;//更新热量

    void HeatSet(const std::string &command, const std::vector<int> &params);//设置热量
};


#endif //ENGINEER_H
