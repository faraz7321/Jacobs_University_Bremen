/*
CH-231-1
problem5.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include <set>
#include <ctime>
using namespace std;
int draw();
void print(set<int> myset);
bool check(set<int> s, int x);
int main()
{
    // initializing with local time
    srand((unsigned)time(NULL));

    // container to store random numbers
    set<int> myset;
    int random;
    // storing 6 random numbers in set
    while (myset.size() != 6)
    {
        random = draw();
        if (!check(myset, random))
        {
            myset.insert(random);
        }
    }
    // print contents of set
    print(myset);
    return 0;
}

/**
 * @brief creates a random number
 *
 * @return int
 */
int draw()
{
    int random = (rand() % 49) + 1;
    return random;
}

/**
 * @brief print contents of the set
 *
 * @param myset
 */
void print(set<int> myset)
{
    for (auto it = myset.begin(); it != myset.end(); it++)
    {
        cout << *it << endl;
    }
}
/**
 * @brief checks if a value is already present
 * in the set or not
 *
 * @param s
 * @param x
 * @return true
 * @return false
 */
bool check(set<int> s, int x)
{
    bool flag = false;

    if (s.find(x) != s.end())
    {
        flag = true;
        cout << x << "repeat" << endl;
    }

    return flag;
}
