#include "WindGauge.h"
#include <iostream>
WindGauge::WindGauge(int period)
{
    this->period = period;
}

void WindGauge::currentWindSpeed(int speed)
{
    if (history.size() == period)
    {
        history.pop_front();
    }
    history.push_back(speed);
}

int WindGauge::highest() const
{
    int r = *(history.begin());
    std::deque<int>::const_iterator it = history.begin();
    it++;
    for (; it != history.end(); it++)
    {
        if (r < *it)
            r = *it;
    }

    return r;
}

int WindGauge::lowest() const
{
    int r = *(history.begin());
    std::deque<int>::const_iterator it = history.begin();
    it++;
    for (; it != history.end(); ++it)
    {
        if (r > *it)
            r = *it;
    }

    return r;
}

int WindGauge::average() const
{
    int r = 0;
    for (std::deque<int>::const_iterator it = history.begin();
         it != history.end(); ++it)
    {
        r += *it;
    }

    return r / history.size();
}

void WindGauge::DUMP()
{
    std::cout << "\n";
    std::cout << "HIGHEST: " << highest() << "\n";
    std::cout << "LOWEST: " << lowest() << "\n";
    std::cout << "AVERAGE: " << average() << "\n";
}