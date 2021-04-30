#include "data.h"

int data::clock = 0;//时间初始化为0

class passenger data::empty = passenger(-1, -1);//定义按了电梯键却没有上电梯或被其他电梯接走的乘客

class floor data::floors[21] =
{
	//定义各个楼层对应的结构体
	floor(0),
	floor(1),
	floor(2),
	floor(3),
	floor(4),
	floor(5),
	floor(6),
	floor(7),
	floor(8),
	floor(9),
	floor(10),
	floor(11),
	floor(12),
	floor(13),
	floor(14),
	floor(15),
	floor(16),
	floor(17),
	floor(18),
	floor(19),
	floor(20)
};

class elevator data::elevators[4] =
{
	//初始化各个电梯的电梯类型，最大载客数，最大载重量
	elevator(1,10,800),
	elevator(2,10,800),
	elevator(3,10,800),
	elevator(4,20,2000)
};

