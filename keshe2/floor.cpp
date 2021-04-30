#include "floor.h"
#include "data.h"

floor::floor(int temp)
{
	//楼层结构体初始化
	this->myFloor = temp;
	nextUp = nextDown = 0;
}
void floor::add(passenger& temp)
{
	//增加一名乘客
	if (temp.to > myFloor)
	{
		up.push_back(temp);
	}
	else
	{
		down.push_back(temp);
	}
	return;
}

void floor::add(int weight, int to)
{
	//增加一名乘客
	if (to > myFloor)
	{
		up.push_back(passenger(weight, to));
	}
	else
	{
		down.push_back(passenger(weight, to));
	}
}

passenger floor::pop(int upDown, int weight, int id, int eFlag)
{
	//弹出一名乘客
	if (upDown == -1)
	{
		for (int ti = 0;ti < down.size();++ti)
		{
			if (down[ti].weight <= weight && (!(id == 2 && (down[ti].to & 1 == 0)) || id == 3 && (down[ti].to & 1 != 0)))
			{
				passenger temp = down[ti];
				nextDown = 0;
				if (eFlag == 1)
				{
					down.erase(down.begin() + ti);
				}
				return temp;
			}
		}
	}
	else
	{
		for (int ti = 0;ti < up.size();++ti)
		{
			if (up[ti].weight <= weight && (!(id == 2 && (up[ti].to & 1 == 0)) || id == 3 && (up[ti].to & 1 != 0)))
			{
				passenger temp = up[ti];
				nextUp = 0;
				if (eFlag == 1)
				{
					up.erase(up.begin() + ti);
				}
				return temp;
			}
		}
	}
	return data::empty;
}

int floor::wait(int flag = 0)
{
	//等待
	if (flag == 1)
	{
		return up.size();
	}
	else if (flag == -1)
	{
		return down.size();
	}
	else
	{
		return up.size() + down.size();
	}
}

bool floor::can(int id)
{
	//当前楼层能到达的电梯与否
	if (id == 2 && (myFloor & 1 == 0) || (id == 3 && (myFloor & 1 != 0)))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool floor::light(int flag, int id)
{
	//是否有等待
	if (flag == -1)
	{
		if (can(id) == 0)
		{
			return 0;
		}
		order(flag, id);
		return down.size() && (nextDown == 0 || nextDown == id);
	}
	if (can(id) == 0)
	{
		return 0;
	}
	order(flag, id);
	return up.size() && (nextUp == 0 || nextUp == id);
}

bool floor::order(int flag, int id)
{
	//预约
	if (flag == -1 && down.size() && nextDown == 0)
	{
		return nextDown = id;
	}
	else if (flag == 1 && up.size() && nextUp == 0)
	{
		return nextUp = id;
	}
	else
	{
		return 0;
	}
}
