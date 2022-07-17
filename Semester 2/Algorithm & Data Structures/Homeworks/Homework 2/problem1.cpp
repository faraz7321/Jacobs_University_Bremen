/*
CH-231-1
problem1.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
using namespace std;
void print(list<int> const &list, ostream &out, string sep);
void move(list<int> &list);
int main()
{
    // creating two integer lists
    list<int> A;
    list<int> B;
    // taking input from user
    int input;
    do
    {
        cin >> input;
        if (input > 0)
        {
            A.push_back(input);
            B.push_front(input);
        }

    } while (input > 0);

    cout << "List A: ";
    print(A, cout, " ");

    // saving list b to .txt
    ofstream myfile("listB.txt");
    print(B, myfile, " ");

    cout << endl
         << endl;
    // moving front to end
    move(A);
    move(B);
    cout << "Modified List A: ";
    print(A, cout, ", ");
    cout << endl;
    cout << "Modified List B: ";
    print(B, cout, ", ");

    cout << endl
         << endl;
    // merge B into A
    A.merge(B);
    A.sort(); // sorting in accending order
    print(A, cout, " ");
    return 0;
}
/**
 * @brief print content of the list
 *
 * @param list
 * @param out
 * @param sep
 */
void print(list<int> const &list, ostream &out, string sep)
{
    int size = list.size();
    int i = 0;
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        if (i == size - 1)
        {
            out << *it;
        }
        else
        {
            out << *it << sep;
        }
        i++;
    }
}
/**
 * @brief move front to end of the list
 *
 * @param list
 */
void move(list<int> &list)
{
    int x = list.front();
    list.insert(list.cend(), x);
    list.pop_front();
}