/*
CH-231-1
testLinkedList.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
    // creating integer linked list
    LinkedList<int> list;

    list.add_back(4);
    list.add_back(4);
    list.add_back(4);
    list.add_front(5);
    list.add_back(6);
    list.displayAll();
    return 0;
}