#include <iostream>
using namespace std;

/**
 * @brief node class
 *
 */
class Node
{
public:
    int data;
    Node *next = NULL;
};

/**
 * @brief stack class
 *
 */
class Stack
{
private:
    Node *head;
    int size = -1;    // -1 if not set, value otherwise
    int current_size; // unused if size = -1
public:
    /**
     * @brief Construct a new Stack object
     *
     */
    Stack()
    {
        this->head = NULL;
        this->size = 10;
        this->current_size = -1;
    }
    /**
     * @brief Construct a new Stack object
     *
     * @param new_size
     */
    Stack(int new_size)
    {
        this->size = new_size;
    }
    /**
     * @brief print elements
     *
     */
    void print()
    {
        cout << "Elements in list: ";
        Node *root = this->head;
        while (root != NULL)
        {
            cout << root->data << ",";
            root = root->next;
        }
        cout << endl;
    }
    /**
     * @brief push element into list
     *
     * @param x
     */
    void push(int x)
    {
        if (this->current_size == this->size)
        {
            cout << "Stack overflow";
            return;
        }
        Node *node = new Node();
        node->data = x;
        node->next = NULL;
        if (this->head == NULL)
        {
            this->head = node;
        }
        else
        {
            Node *root = this->head;
            while (root->next != NULL)
            {
                root = root->next;
            }
            root->next = node;
        }
        this->current_size += 1;
    }

    bool isEmpty()
    {
        if (this->head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    /**
     * @brief remove top element
     *
     * @return Node*
     */
    Node *pop()
    {
        Node *root = this->head;
        while (root->next->next != NULL)
        {
            root = root->next;
        }
        root->next = NULL;
        cout << "Element popped\n";
        this->current_size -= 1;
    }
};

/**
 * @brief driver code
 *
 * @return int
 */
int main()
{
    Stack *s = new Stack();
    s->push(13);
    s->push(2);
    s->push(6);
    s->push(65);
    s->push(1);

    s->print();
    s->pop();
    s->print();
}