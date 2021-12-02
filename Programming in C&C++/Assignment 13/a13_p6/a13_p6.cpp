/*
CH-230-A
a13_p6.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
int main()
{
    // initializing vector
    vector<int> *v = new vector<int>;
    for (int i = 0; i < 20; i++)
    {
        v->push_back(20);
    }
    // accessing 21th element
    try
    {
        cout << v->at(20);
    }
    catch (const out_of_range &oor)
    {
        cerr << "Out of Range error: " << oor.what() << '\n';
    }
    // deallocating memory
    delete v;
    return 0;
}