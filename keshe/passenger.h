#ifndef PASSENGER_H
#define PASSENGER_H


class passenger
{
public:
    passenger(int weight=-1,int to=-1);
    int weight;
    int to;
};

extern const passenger EMPTY;

#endif // PASSENGER_H
