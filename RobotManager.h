#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H
#define int long long

#include <bits/stdc++.h>
#include <vector>

#include "Robot.h"


class RobotManager {
public:
    void processCommand(int time, const std::string &command, const std::vector<int> &params);//处理命令

    void updateRobots(int timeElapsed);//更新热量

    void printDestroyedRobotsIntoVector(const Robot *robot);//将摧毁的机器人打印到输出列表

    void printDestroyedRobots() const;//打印出被摧毁过的机器人

private:
    std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Robot> > > activeRobots_;//活动的机器人
    std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Robot> > > destroyedRobots_;//被摧毁的机器人
    std::vector<Robot> printDestroyRobots_;//打印被摧毁的机器人
    std::vector<Robot> tempDestroyRobots_;//临时储存（应对一个周期烫死俩的情况）

    void addRobot(int teamId, int id, int type);//加机器人

    void reviveRobot(int teamId, int id, int type);//复活机器人

    void destroyRobot(int teamId, int id);//摧毁机器人
};


#endif //ROBOTMANAGER_H
