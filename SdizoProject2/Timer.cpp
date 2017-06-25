#include "Timer.h"

Timer::Timer()
{
    //ctor
}

void Timer::start()
{
    tstart = clock();
    measurement = 0;
}


void Timer::stop()
{
    tstop = clock();
    measurement = ((double)(tstop - tstart))/CLOCKS_PER_SEC;
}

double Timer::read()
{
    return measurement;
}
