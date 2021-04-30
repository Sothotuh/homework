#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "passenger.h"
#include<QVector>

class elevator
{
public:
	int type;//电梯类型（序号）
	int maxNum;//最大载客数
	int nowNum;//目前载客数
	int maxWeight;//最大载重量
	int nowWeight;//目前载重量
	int nowFloor;//目前楼层
	int nextTime;//运行状态，具体为：0：无动作；1-4：运行；5：装载；6：卸载
	int flag;//运行方向，具体为：0：停止；-1：下楼；1：上楼
	bool can[22];//能够到达的楼层，具体为：true:能到达；false:不能到达
	QVector<passenger>vect;

	elevator(int, int, int);//电梯初始化函数声明
	bool add(int);//装载乘客函数声明
	bool pop(int);//卸载乘客函数声明
	bool need();//空载时判断保持方向函数声明
	bool haveBack();//有前向返回要求函数声明
	void dispatch();//调度函数声明
	void run();//运行一单位时间函数声明
};

#endif // ELEVATOR_H
