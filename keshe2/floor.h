#ifndef FLOOR_H
#define FLOOR_H

#include<QVector>
#include"passenger.h"


class floor
{
public:
	int myFloor;//定义当前楼层
	int nextUp;//定义下一个上升楼层
	int nextDown;//定义下一个下降楼层
	QVector<passenger>up;
	QVector<passenger>down;

	floor(int);
	void add(passenger&);//增加一名乘客
	void add(int, int);//增加一名乘客
	passenger pop(int, int, int, int);//弹出一名乘客
	int wait(int);//等待
	bool can(int);
	bool light(int, int);//查询是否有等待
	bool order(int, int);//预约
};


#endif // FLOOR_H
