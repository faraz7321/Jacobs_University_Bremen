/*
CH-230-A
a13_p7.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <exception>
using namespace std;
void myexception(int n);
string printBool(bool flag);
class OwnException : public exception
{
public:
    // constructors
    OwnException() {}
    OwnException(string str);
    // destructor
    ~OwnException() {}
    // overriding what()
    virtual const char *what() const throw()
    {
        return "OwnException\n";
    }
};

/**
 * @brief Construct a new Own Exception:: Own Exception object
 *
 * @param str
 */
OwnException::OwnException(string str)
{
    cout << str << endl;
}

int main()
{
    // integer exceptoin
    try
    {
        myexception(1);
    }
    catch (char c)
    {
        cerr << "Caught in main: " << c << endl;
    }

    // character exception
    try
    {
        myexception(2);
    }

    catch (int n)
    {
        cerr << "Caught in main: " << n << endl;
    }

    // bool exception
    try
    {
        myexception(3);
    }

    catch (bool b)
    {
        cerr << "Caught in main: " << printBool(b) << endl;
    }

    // default case exception
    try
    {
        myexception(4);
    }

    catch (const OwnException &e)
    {
        cerr << "Caught in main: " << e.what() << endl;
    }

    return 0;
}
void myexception(int n)
{
    if (n == 1)
    {
        throw 'a';
    }
    else if (n == 2)
    {
        throw 12;
    }
    else if (n == 3)
    {
        throw true;
    }
    else
    {
        throw OwnException("Default case exception");
    }
}
string printBool(bool flag)
{
    string str;
    if (flag == true)
    {
        str = "True";
    }
    else
    {
        str = "False";
    }
    return str;
}