/*
CH-230-A
a13_p7.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <stdexcept>
using namespace std;
void error(int i);
class OwnException : public exception
{
public:
    string ex = "Default case exception";
    OwnException();
    ~OwnException();
    void what() { cout << "OwnException\n"; }
};
int main()
{
    try
    {
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught in main: " << e.what();
    }

    return 0;
}
void error(int i)
{
    char c = 'a';
    int x = 12;
    bool flag = true;
    OwnException oe;
}