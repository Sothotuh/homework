#include"data.h"
#include"elevator.h"
#include"floor.h"
#include<QDebug>//QT输出文字信息头文件

elevator::elevator(int type, int maxnum, int maxwei) :type(type), maxNum(maxnum), maxWeight(maxwei)
{
	//当初始化电梯信息的时候，创建对应的电梯结构体并初始化电梯的类型、最大载客数和最大载重量信息
	nowNum = nowWeight = nextTime = flag = 0;
	nowFloor = 1;
	for (int i = 0;i < 22;++i)
	{
		can[i] = 1;
	}
}

bool elevator::add(int eFlag)
{
	//装载乘客
	if (nowNum == maxNum)
	{
		can[nowFloor] = 0;
		return 0;
	}
	passenger temp = data::floors[nowFloor].pop(flag, maxWeight - nowWeight, type, eFlag);
	if (temp.to == -1)
	{
		can[nowFloor] = 0;
		return 0;
	}
	if (eFlag == 1)
	{
		vect.push_back(temp);
		nowWeight += temp.weight;
		++nowNum;
		qDebug("时间:%d 电梯%d:当前层数%d,装载乘客:目的%d 重量%d\n", data::clock, type, nowFloor, temp.to, temp.weight);
	}
	return 1;
}

bool elevator::pop(int eFlag)
{
	//卸载乘客
	for (int ti = 0;ti < vect.size();++ti)
	{
		if (vect[ti].to == nowFloor)
		{
			if (eFlag == 1)
			{
				qDebug("时间:%d 电梯%d:当前层数%d,卸载乘客:重量%d\n", data::clock, type, nowFloor, vect[ti].weight);
				nowWeight -= vect[ti].weight;
				--nowNum;
				vect.erase(vect.begin() + ti);
				--ti;
			}
			can[nowFloor] = 1;
			return 1;
		}
	}
	return 0;
}

bool elevator::need()
{
	//空载时判断保持方向
	if (flag == -1)
	{
		for (int ti = nowFloor;ti > -1;--ti)
		{
			if (data::floors[ti].light(flag, type) && can[ti])
			{
				return 1;
			}
		}
	}
	else
	{
		for (int ti = nowFloor;ti < 21;++ti)
		{
			if (data::floors[ti].light(flag, type) && can[ti])
			{
				return 1;
			}
		}
	}
}

bool elevator::haveBack()
{
	//有前向返回要求
	if (flag == -1)
	{
		for (int ti = nowFloor - 1;ti > -1;--ti)
		{
			if (data::floors[ti].light(-flag, type) && can[ti])
			{
				return 1;
			}
		}
	}
	else
	{
		for (int ti = nowFloor + 1;ti < 21;++ti)
		{
			if (data::floors[ti].light(-flag, type) && can[ti])
			{
				return 1;
			}
		}
	}
}

void elevator::dispatch()
{
	//调度
	nextTime = 0;
	if (vect.size() != 0)
	{
		nextTime = 1;
		return;
	}
	for (int i = 0;i < 22;++i)
	{
		can[i] = 1;
	}
	if (flag == 0)
	{
		if (data::floors[nowFloor].light(-1, type) == 1)
		{
			flag = -1;
			nextTime = 5;
		}
		else if (data::floors[nowFloor].light(1, type) == 1)
		{
			flag = 1;
			nextTime = 5;
		}
		else {
			flag = 1;
			if (need() == 1)
			{
				nextTime = 1;
			}
			else if (flag = -1, need() == 1)
			{
				nextTime = 1;
			}
			else
			{
				flag = 1;
				if (haveBack() == 1)
				{
					nextTime = 1;
				}
				else if (flag = -1, haveBack() == 1)
				{
					nextTime = 1;
				}
				else
				{
					flag = 0;
				}
			}
		}
	}
	else if (need() == 1)
	{
		nextTime = 1;
	}
	else if (haveBack() == 1)
	{
		nextTime = 1;
	}
	else
	{
		flag *= -1;
		if (need() == 1)
		{
			nextTime = 5;
		}
		else
		{
			nextTime = 0;
		}
	}
	return;
}

void elevator::run() {//运行一单位时间
	if (nextTime == 0)
	{
		dispatch();
	}
	if (nextTime == 0)
	{
		qDebug("电梯%d:当前层数%d,等待\n", type, nowFloor);
	}
	else if (nextTime <= 4)
	{
		qDebug("电梯%d:当前层数%d,移动向%d,进度%d\n", type, nowFloor, flag, nextTime);
		++nextTime;
		if (nextTime == 5)
		{
			nowFloor += flag;
			if (pop(0))
			{
				nextTime = 6;
			}
			else if (add(0))
			{
				nextTime = 5;
			}
			else
			{
				nextTime = 0;
			}
		}
	}
	else if (nextTime == 5)
	{
		//装载
		if (add(1) == 0)
		{
			nextTime = 0;
			run();
		}
	}
	else
	{
		//卸载
		if (pop(1) == 0)
		{
			nextTime = 5;
			run();
		}
	}
}
