/*
CH-231-1
LinkedList.h
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
using namespace std;

/**
 * @brief Node class
 *
 * @tparam T
 */
template <typename T>
class Node
{
private:
    T data;
    Node<T> *next;
    Node<T> *prev;
    template <typename U>
    friend class LinkedList;

public:
    // constructor
    Node()
    {
        this->next = NULL;
        this->prev = NULL;
    }
};

/**
 * @brief Linked List class
 *
 * @tparam T
 */
template <typename T>
class LinkedList
{
private:
    Node<T> *head;

public:
    // constructor
    LinkedList()
    {
        this->head = NULL;
    }
    // methods
    void add_back(T item);
    void add_front(T item);
    void displayAll();
    int getSize();
    ~LinkedList();
};
template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T> *temp = head;
    cout << "\n----Destructor----\n";
    cout << "Front: " << temp->data << endl;
    for (int i = 0; i < getSize() - 1; i++)
    {
        temp = temp->next;
    }

    cout << "Back: " << temp->data;
    free(head);
}

/**
 * @brief Add a new node at the back of linked lisy
 *
 * @tparam T
 * @param item
 */
template <typename T>
void LinkedList<T>::add_back(T item)
{
    Node<T> *node = new Node<T>[1];
    node->data = item;
    if (head == NULL)
    {
        head = node;
        return;
    }
    Node<T> *temp = head;
    Node<T> *prev;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }
    temp->next = node;
    temp->prev = prev;
}

/**
 * @brief add a new node at the front of linked list
 *
 * @tparam T
 * @param item
 */
template <typename T>
void LinkedList<T>::add_front(T item)
{
    Node<T> *node = new Node<T>[1];
    node->data = item;
    if (head == NULL)
    {
        head = node;
        return;
    }
    head->prev = node;
    node->next = head;
    head = node;
}

/**
 * @brief display data in linked list
 *
 * @tparam T
 */
template <typename T>
void LinkedList<T>::displayAll()
{
    Node<T> *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " | ";
        temp = temp->next;
    }
}
template <typename T>
int LinkedList<T>::getSize()
{
    int size = 0;
    Node<T> *temp = head;
    while (temp != NULL)
    {
        size++;
        temp = temp->next;
    }
    return size;
}