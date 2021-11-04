/*
CH-230-A
a9_p2.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n;
    double x;
    string s;
    // taking input from user
    cin >> n >> x;
    cin.ignore();
    getline(cin, s);

    // printing
    for (int i = 0; i < n; i++)
    {
        cout << s << ":" << x << endl;
    }
    return 0;
}