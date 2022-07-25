#include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct Queue
{
private:
    stack<int> s1, s2; // using stack container

public:
    void enQueue(int x);
    int deQueue();
};
/**
 * @brief add item to queue
 *
 * @param x
 */
void Queue::enQueue(int x)
{
    // Move all elements from s1 to s2
    while (!s1.empty())
    {
        s2.push(s1.top());
        s1.pop();
    }
    // Push item into s1
    s1.push(x);
    // pushing back to s2
    while (!s2.empty())
    {
        s1.push(s2.top());
        s2.pop();
    }
    cout << "Element added to queue\n";
}

/**
 * @brief remove item from queue
 *
 * @return int
 */
int Queue::deQueue()
{
    // if first stack is empty
    if (s1.empty())
    {
        cout << "Queue is Empty\n";
        exit(0);
    }

    // Return top of s1
    int x = s1.top();
    s1.pop();
    cout << "Element removed from queue: ";
    return x;
}

/**
 * @brief driver code
 *
 * @return int
 */
int main()
{
    Queue q;
    // adding elements to queue
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);

    cout << q.deQueue() << '\n';
    cout << q.deQueue() << '\n';
    cout << q.deQueue() << '\n';
    return 0;
}
