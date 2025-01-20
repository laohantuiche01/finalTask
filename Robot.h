#ifndef ROBOT_H
#define ROBOT_H

#include <bits/stdc++.h>

#define int long long


class Robot {
public:
    Robot(int teamId, int id, int maxHealth, int maxHeat) //队伍ID，机器人ID，最大生命值，最大热量
            : teamId_(teamId), id_(id), health_(maxHealth), heat_(0),
              maxHealth_(maxHealth), maxHeat_(maxHeat), deathTime_(-1LL) {
    };

    virtual ~Robot() = default; //析构函数

    [[nodiscard]] virtual bool isDestroyed() const { return health_ <= 0; }

    [[nodiscard]] virtual int getMaxHealth() const { return maxHealth_; };

    [[nodiscard]] virtual int getMaxHeat() const { return maxHeat_; };

    virtual void updateHeat(int timeElapsed) {}

    void resetHeat();//重置热量

    void setHealth(int newHealth);//设置血量

    void decreaseHealth(int damage);//造成伤害

    void resetMaxHealth_(int newMaxHealth);//重置最大血量

    void resetMaxHeat_(int newMaxHeat);//重置最大热量

    void setHeat(int newHeat);//设置新的热量

    //virtual void handleCommand(const std::string &command, const std::vector<int> &params);

    [[nodiscard]] int getTeamId() const { return teamId_; }

    [[nodiscard]] int getId() const { return id_; }

    [[nodiscard]] int getHealth() const { return health_; }

    [[nodiscard]] int getHeat() const { return heat_; }

private:
    int teamId_;//队伍ID
    int id_;//机器人ID
    int health_;//血量
    int heat_;//热量
    int maxHealth_;//最大血量
    int maxHeat_;//最大热量
    int deathTime_;//死亡时间
};


#endif //ROBOT_H
