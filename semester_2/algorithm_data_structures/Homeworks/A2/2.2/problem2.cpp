/*
CH-231-1
problem2.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;
void print(deque<float> const &deq, string sep);
int main()
{
    deque<float> A;
    float input;
    do
    {
        cin >> input;
        if (input > 0)
        {
            A.push_back(input);
        }
        else if (input < 0)
        {
            A.push_front(input);
        }

    } while (input != 0);
    cout << "Deque A: ";
    print(A, " ");
    cout << "\n\n";
    for (auto it = A.cbegin(); it != A.cend(); ++it)
    {
        if (*it > 0)
        {
            A.emplace(it, 0.0);
            break;
        }
    }
    print(A, ";");
    cout << endl;
    return 0;
}
/**
 * @brief print content of the deque
 *
 * @param deq
 * @param out
 * @param sep
 */
void print(deque<float> const &deq, string sep)
{
    int size = deq.size();
    int i = 0;
    for (auto it = deq.cbegin(); it != deq.cend(); it++)
    {
        if (i == size - 1)
        {
            cout << *it;
        }
        else
        {
            cout << *it << sep;
        }
        i++;
    }
}