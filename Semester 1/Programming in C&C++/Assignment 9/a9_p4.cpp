/*
CH-230-A
a9_p4.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
// overloaded functions
int mycount(int x, int y);
int mycount(char c, string line);
int main()
{
    int x, y;
    char c;
    string line;

    cout << "Enter two numbers: " << endl;
    cin >> x >> y;

    cout << "Enter a string: ";
    cin.ignore();
    getline(cin, line);

    cout << "Enter a character: ";
    cin >> c;

    cout << "Difference of two number: " << mycount(x, y) << endl;
    cout << c << " occurs " << mycount(c, line) << " times in \"" << line << "\"\n";
    return 0;
}
/**
 * @brief calculates difference of 2 numbers
 *
 * @param x
 * @param y
 * @return int
 */
int mycount(int x, int y)
{
    return y - x;
}
/**
 * @brief counts occuerences of char in string
 *
 * @param c
 * @param line
 * @return int
 */
int mycount(char c, string line)
{
    int count = 0;
    int len = line.size();
    for (int i = 0; i < len; i++)
    {
        if (c == line[i])
        {
            count++;
        }
    }
    return count;
}