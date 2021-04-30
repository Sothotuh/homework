#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "passenger.h"

#include<QVector>

class elevator
{
public:
    int type;//电梯类型（序号）
    int maxNum;
    int nowNum;//当前乘员
    int maxWeight;
    int nowWeight;//当前载重
    int nowFloor;//当前楼层
    int nextTime;//0 无动作，1-4运行，5装载,6卸载
    int flag;//方向-1 0 1
    bool can[25];
    QVector<passenger>vect;
    
    
    elevator();
    elevator(int,int,int);
    
    bool add(int);//装载乘客
    bool pop(int);//卸载乘客
    bool need();//空载时判断保持方向
    bool haveBack();//有前向返回要求
    void dispatch();//调度
    void run();//运行一单位时间
};

#endif // ELEVATOR_H
