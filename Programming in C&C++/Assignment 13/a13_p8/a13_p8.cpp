#include <iostream>
#include <stdexcept>
using namespace std;
class Garage
{
public:
    Garage();
    ~Garage();
};
class Car : public Garage
{
public:
    Car();
    ~Car();
};
class Motor : public Car
{
public:
    Motor();
    ~Motor();
};

int main()
{

    return 0;
}