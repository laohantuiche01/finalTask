#include <bits/stdc++.h>
#include "RobotManager.h"

#undef int

int main() {
    long long N;
    RobotManager robotManager;
    std::cin >> N;
    long long currentTime = 0;//用于寻找时间差
    for (long long i = 1; i <= N; i++) //循环，有几条命令
    {
        long long Time;
        std::string commend;//储存命令
        std::vector<long long> current(3);//储存参数
        std::cin >> Time >> commend;
        for (long long j = 0; j <= 2; j++) {
            std::cin >> current[j];
        }
        robotManager.updateRobots(Time - currentTime); //传入时间差
        robotManager.processCommand(Time, commend, current); //进行操作
        //robotManager.printDestroyedRobotsIntoVector();//更新被摧毁容器
        currentTime = Time; //更新当前时间
    }
    robotManager.printDestroyedRobots();//输出
    return 0;
}
