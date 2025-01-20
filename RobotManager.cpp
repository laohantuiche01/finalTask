#include <bits/stdc++.h>
#include "RobotManager.h"
#include "Robot.h"
#include "Infantry.h"
#include "Engineer.h"

#define int long long

void RobotManager::processCommand(int time, const std::string &command, const std::vector<int> &params) //处理命令
{
    int teamID = params[0];
    int robotID = params[1];

    if (command == "A") //输入命令为A
    {
        if (destroyedRobots_[teamID].find(robotID) != destroyedRobots_[teamID].end()) //在被击毁的机器人中有
        {
            auto robot = destroyedRobots_[teamID][robotID];
            if (robot->isDestroyed()) //机器人已经被击毁
            {
                robot->setHealth(robot->getMaxHealth()); //重置血量
                robot->resetHeat(); //重置热量
                activeRobots_[teamID][robotID] = std::move(robot); //移动到未被击毁的
                destroyedRobots_[teamID].erase(robotID); //消除被摧毁的
            }
        } else if (activeRobots_[teamID].find(robotID) == activeRobots_[teamID].end()) //在活动的机器人中没找到
        {
            addRobot(teamID, robotID, params[2]); //构建等级为一的步兵机器人
            //std::cout<<activeRobots_.size()<<"\n";
            //std::cout << activeRobots_[teamID].size() << "\n";
            //std::cout << activeRobots_[teamID][robotID]->getId() << "\n";
        }
    } else if (command == "F") {
        if (activeRobots_[teamID].find(robotID) != activeRobots_[teamID].end()) //找到了
        {
            auto robot = activeRobots_[teamID][robotID]; //将找到的机器人储存在临时变量
            if (!robot->isDestroyed()) //没有被击毁
            {
                robot->decreaseHealth(params[2]); //造成伤害
                destroyRobot(teamID, robotID);
            }
        }
    } else if (command == "H") {
        if (activeRobots_[teamID].find(robotID) != activeRobots_[teamID].end()) //找到了
        {
            auto robot = activeRobots_[teamID][robotID]; //拿出来进行操作
            if (dynamic_cast<Infantry *>(robot.get())) //目标机器人为步兵
            {
                auto robots = dynamic_cast<Infantry *>(robot.get());//转换类型
                robots->handleCommand(command, params);//用到步兵中的处理命令
            } else if (dynamic_cast<Engineer *>(robot.get())) //目标为工兵
            {
                auto robots = dynamic_cast<Engineer *>(robot.get());//类型转化
                robots->HeatSet(command, params);//处理
            }
        }
    } else if (command == "U") {
        if (activeRobots_[teamID].find(robotID) != activeRobots_[teamID].end()) //找到了
        {
            auto robot = activeRobots_[teamID][robotID]; //创建操作的对象
            if (dynamic_cast<Infantry *>(robot.get())) //如果是步兵机器人
            {
                auto tempRobot = dynamic_cast<Infantry *>(robot.get()); //转化类型
                tempRobot->handleCommand(command, params); //进行操作
            }
        }
    }
}


void RobotManager::addRobot(int teamId, int robotId, int type) {
    if (type == 0) //如果等级为0,创建步兵机器人
    {
        //activeRobots_[teamId][robotId] = std::make_shared<Infantry>(teamId, robotId, level);
        activeRobots_[teamId].emplace(robotId, std::make_shared<Infantry>(teamId, robotId, 1));
        //std::cout << activeRobots_[teamId].size() << "\n";
    } else if (type == 1) //如果为1,创建工程机器人
    {
        activeRobots_[teamId][robotId] = std::make_shared<Engineer>(teamId, robotId);
        //std::cout << activeRobots_[teamId].size() << "\n";
    }
}

void RobotManager::destroyRobot(int teamId, int id) {
    if (activeRobots_[teamId].find(id) != activeRobots_[teamId].end()) //找到了
    {
        auto robot = activeRobots_[teamId][id]; //拉出来操作
        if (robot->isDestroyed()) //被击毁
        {
            printDestroyedRobotsIntoVector(robot.get());//输出到打印摧毁机器人的列表
            destroyedRobots_[teamId][id] = std::move(robot); //拷贝
            activeRobots_[teamId].erase(id); //擦除
        }
    }
    //std::cout<<"RobotManager::destroyRobot()"<<"\n";
}

bool comp(const Robot &robot1, const Robot &robot2)//sort判断依据
{
    return robot1.getHealth() < robot2.getHealth();
}

void RobotManager::updateRobots(int timeElapsed) //更新热量及血量
{
    // for (auto& [teamId, robots] : activeRobots_)//在不同的队伍中遍历（只遍历活得）
    //     {
    //     for (auto& [robotID, robot] : robots) //在机器人中进行遍历
    //         {
    //         robot->updateHeat(timeElapsed);//更新热量
    //         if (robot->isDestroyed())//被击毁
    //             {
    //             destroyRobot(teamId, robotID);
    //
    //         }
    //     }
    // }
    for (auto &[teamId, robots]: activeRobots_) //在不同的队伍中遍历（只遍历活得）
    {
        auto it = robots.begin();
        while (it != robots.end()) {
            auto nextIt = std::next(it); // 获取下一个元素的迭代器
            auto &[robotID, robot] = *it;
            robot->updateHeat(timeElapsed);
            if (robot->isDestroyed()) {
//              destroyRobot(teamId, robotID); // 删除元素
                tempDestroyRobots_.push_back(*robot);//放到排序中
                destroyedRobots_[teamId][robotID] = std::move(robot); //拷贝
                activeRobots_[teamId].erase(robotID); //擦除
            }
            it = nextIt; // 更新迭代器
        }
    }
    std::sort(tempDestroyRobots_.begin(), tempDestroyRobots_.end(), comp);//排序
    printDestroyRobots_.insert(printDestroyRobots_.end(), tempDestroyRobots_.begin(), tempDestroyRobots_.end());//插入
    tempDestroyRobots_.clear();//清除，以便下一次操作
}

void RobotManager::printDestroyedRobotsIntoVector(const Robot *robot) //输出被击毁的机器人到打印容器
{
    // for (const auto& [teamId, robots] : destroyedRobots_) {
    //     for (const auto& [id, robot] : robots) {
    //         if (robot->isDestroyed()) {
    //             printDestroyRobots_.push_back(*robot);
    //             //std::cout << "D " << teamId << " " << id << "\n";
    //         }
    //     }
    // }
    printDestroyRobots_.push_back(*robot);
}

void RobotManager::printDestroyedRobots() const //打印被摧毁的机器人
{
    for (const auto &robot: printDestroyRobots_) //在vector中输出
    {
        std::cout << "D " << robot.getTeamId() << " " << robot.getId() << "\n";
    }
}


void RobotManager::reviveRobot(int teamId, int id, int type) //复活机器人
{
    if (destroyedRobots_[teamId].find(id) != destroyedRobots_[teamId].end()) {
        auto robot = destroyedRobots_[teamId][id];
        if (robot->isDestroyed()) {
            robot->setHealth(robot->getMaxHealth());
            robot->resetHeat();
            activeRobots_[teamId][id] = std::move(robot);
            destroyedRobots_[teamId].erase(id);
        }
    }
}
