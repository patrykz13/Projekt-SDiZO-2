#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>

class Timer
{
    public:
        Timer();
        void start();
        void stop();
        double read();
        double measurement;
    protected:
    private:
        clock_t tstart;
        clock_t tstop;
};

#endif // STOPWATCH_H
