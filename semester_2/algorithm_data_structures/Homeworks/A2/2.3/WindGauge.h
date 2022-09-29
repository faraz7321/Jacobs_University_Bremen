#ifndef H_WIND_GAUGE
#define H_WIND_GAUGE

#include <deque>

class WindGauge
{
public:
    WindGauge(int period = 12);
    void currentWindSpeed(int speed);
    int highest() const;
    int lowest() const;
    int average() const;

    // THE DUMP FUNCTIION
    void DUMP();

private:
    std::deque<int> history;
    unsigned int period;
};

#endif