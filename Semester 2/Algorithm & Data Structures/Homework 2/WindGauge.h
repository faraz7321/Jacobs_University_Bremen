/*
CH-231-1
WindGauge.h
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
using namespace std;
class WindGauge
{
public:
    WindGauge(int period = 12);
    void currentWindSpeed(int speed);
    int highest() const;
    int lowest() const;
    int average() const;

private:
    // add properties and/or method(s) here
};
