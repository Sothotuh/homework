#ifndef DATA_H
#define DATA_H

#include "elevator.h"
#include "floor.h"
#include "passenger.h"



class data
{
public:
    static int clock;
    static class elevator elevators[4];
    static class floor floors[21];
    static class passenger empty;
    
    data();
    
    
};

#endif // DATA_H
