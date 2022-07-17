/*
CH-231-1
testStack.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include "Stack.h"
using namespace std;
int main(int argc, char **argv)
{
    int x;
    string str;
    Stack<int> integer_stack;
    Stack<string> string_stack;
    // Stack<string> string_stack2(string_stack);

    integer_stack.push(2);
    integer_stack.push(54);
    integer_stack.push(255);

    string_stack.push("my");
    string_stack.push("name");
    string_stack.push("is");
    string_stack.push("Faraz");

    cout << "Top element in int stack is " << integer_stack.back() << endl
         << "Number of entries in int stack: " << integer_stack.getNumEntries() << endl
         << "Top element in string stack is " << string_stack.back() << endl
         << "Number of entries in string stack: " << string_stack.getNumEntries() << endl;

    if (integer_stack.pop(x))
    {
        cout << "\n"
             << x << " is removed from stack" << endl;
    }

    if (string_stack.pop(str))
    {
        cout << str << " is removed from stack " << endl;
    }

    cout << "\nTop element in int stack is " << integer_stack.back() << endl
         << "Number of entries in int stack: " << integer_stack.getNumEntries() << endl
         << "Top element in string stack is " << string_stack.back() << endl
         << "Number of entries in string stack: " << string_stack.getNumEntries() << endl;

    // cout << "copy:" << string_stack2.back();
}
