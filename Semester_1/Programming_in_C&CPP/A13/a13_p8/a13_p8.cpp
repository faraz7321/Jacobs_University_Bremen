/*
CH-230-A
a13_p8.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <exception>
using namespace std;

/**
 * @brief PARENT CLASS
 *
 */
class Motor
{
public:
    // constructor
    Motor() {}
    // destructor
    ~Motor() {}
    const char *what() const throw()
    {
        return "This motor has problems";
    }
};

/**
 * @brief A CAR HAS-A MOTOR
 *
 */
class Car : public Motor
{
public:
    // constructor
    Car() {}
    // destructor
    ~Car() {}
};

/**
 * @brief A GARAGE HAS-A CAR
 *
 */
class Garage : public Car
{
public:
    // constructors
    Garage()
    try : Car()
    {
        throw Garage("The car in this garage has problems with the motor");
    }
    catch (Motor &m)
    {
        // error message
        cerr << m.what() << endl;
    }
    Garage(string str)
    {
        cout << str << endl;
    }
};

int main()
{
    try
    {
        // creating instance of Garage
        Garage garage;
    }
    // from the body of the Garage
    catch (Garage &g)
    {
        cout << "Caught in main: " << g.what() << endl;
    }

    return 0;
}