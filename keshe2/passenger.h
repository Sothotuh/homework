#ifndef PASSENGER_H
#define PASSENGER_H


class passenger
{
public:
	passenger(int weight = -1, int to = -1);
	int weight;//定义乘客的重量
	int to;//定义乘客想要去的楼层
};

extern const passenger EMPTY;

#endif // PASSENGER_H
