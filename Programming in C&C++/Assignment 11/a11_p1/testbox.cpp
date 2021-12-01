/*
CH-230-A
testbox.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include "Box.h"
using namespace std;
int main()
{
    int n;
    double height, width, depth;
    cout << "Enter number of boxes: ";
    cin >> n;
    int size = 2 * n;
    Box *boxes = new Box[size]; //declaring boxes of size 2n;

    //taking input from user
    for (int i = 0; i < n; i++)
    {
        cin >> height >> width >> depth;
        boxes[i].setHeight(height);
        boxes[i].setWidth(width);
        boxes[i].setDepth(depth);
        //copying object
        boxes[n + i] = Box(boxes[i]);
    }
    //printing objects
    for (int i = 0; i < 2 * n; i++)
    {
        boxes[i].toString(i + 1);
    }
    delete[] boxes;
    return 0;
}
