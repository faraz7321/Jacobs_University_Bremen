/*
CH-231-1
problem4.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void print(vector<int> myvector);
int main()
{
    vector<int> myvector;
    for (int i = 1; i <= 30; i++)
    {
        myvector.push_back(i);
    }
    myvector.push_back(5);

    reverse(myvector.begin(), myvector.end());
    cout << "Reverse vector: ";
    print(myvector);

    cout << "After replace: ";
    replace(myvector.begin(), myvector.end(), 5, 129);
    print(myvector);
    return 0;
}
void print(vector<int> myvector)
{
    vector<int>::const_iterator pos;

    // printing contents of vector using iterator
    for (pos = myvector.begin(); pos != myvector.end(); ++pos)
    {
        cout << *pos << " ";
    }
    cout << endl
         << endl;
}