
#include "Robot.h"

void Robot::resetHeat() { heat_ = 0; }//重置热量

void Robot::setHealth(int newHealth) //设置血量
{
    health_ = std::min(maxHealth_, newHealth);
}

void Robot::decreaseHealth(int damage) //造成伤害
{
    health_ = std::max(0LL, health_ - damage);
}

void Robot::resetMaxHealth_(int newMaxHealth) //重置最大血量
{
    maxHealth_ = newMaxHealth;
}

void Robot::resetMaxHeat_(int newMaxHeat) //重置最大热量
{
    maxHeat_ = newMaxHeat;
}

void Robot::setHeat(int newHeat) //设置新的热量
{
    heat_ = newHeat;
}