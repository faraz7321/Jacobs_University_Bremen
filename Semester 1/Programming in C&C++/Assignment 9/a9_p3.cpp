/*
CH-230-A
a9_p3.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
using namespace std;
float absolute(float x);
int main()
{
    float x;
    cin >> x;            // input
    cout << absolute(x); // output
    return 0;
}
/**
 * @brief calculates and return absolute value of a float
 *
 * @param x
 * @return float
 */
float absolute(float x)
{
    if (x < 0)
    {
        x = x * -1;
    }
    return x;
}