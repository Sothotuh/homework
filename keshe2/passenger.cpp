#include "passenger.h"

passenger::passenger(int weight, int to)
{
	//当从界面接收到一个乘客信息后，为其创造一个结构体存放该乘客信息
	this->weight = weight;
	this->to = to;
}
