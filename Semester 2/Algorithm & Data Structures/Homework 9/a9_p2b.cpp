// C++ implementation of the approach
#include <iostream>
using namespace std;

// A linked list node
class Node
{
public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

// A binary tree node
class treeNode
{
public:
    int data;
    treeNode *left;
    treeNode *right;
    treeNode(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

// Function to print the linked list
void print(Node *head)
{
    if (head == NULL)
    {
        return;
    }
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

// Function to create Linked list from given binary tree
Node *sortedList(Node *head, treeNode *root)
{
    // return head if root is null
    if (root == NULL)
    {
        return head;
    }

    // First make the sorted linked list
    // of the left sub-tree
    head = sortedList(head, root->left);
    Node *newNode = new Node(root->data);
    Node *temp = head;
    Node *prev = NULL;

    // If linked list is empty add the
    // node to the head
    if (temp == NULL)
    {
        head = newNode;
    }
    else
    {

        // Find the correct position of the node
        // in the given linked list
        while (temp != NULL)
        {
            if (temp->data > root->data)
            {
                break;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }

        // Given node is to be attached
        // at the end of the list
        if (temp == NULL)
        {
            prev->next = newNode;
        }
        else
        {

            // Given node is to be attached
            // at the head of the list
            if (prev == NULL)
            {
                newNode->next = temp;
                head = newNode;
            }
            else
            {

                // Insertion in between the list
                newNode->next = temp;
                prev->next = newNode;
            }
        }
    }

    // Now add the nodes of the right sub-tree
    // to the sorted linked list
    head = sortedList(head, root->right);
    return head;
}

// Driver code
int main()
{
    treeNode *root = new treeNode(8);
    root->left = new treeNode(68);
    root->right = new treeNode(34);
    root->left->left = new treeNode(12);
    root->left->right = new treeNode(6);

    Node *head = sortedList(NULL, root);
    print(head);

    return 0;
}
// The insertion on a linked list is O(1) = C.
// So we have O(n * C)
// but sorting is O(n)
// Time Complexity: O(n^2)