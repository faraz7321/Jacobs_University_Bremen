#include <stdio.h>
#include <stdlib.h>
typedef struct node List; // type definition of struct node as List
// Struct declaration
struct node
{
    char data;
    List *next;
    List *prev;
};
// FUNCTIONS FOR DOUBLY LINKED LIST
void push(List **my_list_ref, char new_data);
void print_list(List *list);
void print_reverse(List *my_list);
void dispose_list(List *my_list);
List *delete_item(List *my_list, char x);

int main()
{
    List *my_list = NULL; // List variable
    char selection;
    char input;

    do
    {
        // taking input from user
        scanf(" %c", &selection);
        getchar();
        switch (selection)
        {
        // add a character in the beginning
        case '1':
        {
            scanf("%c", &input);
            push(&my_list, input);
            break;
        }
        // Remove character
        case '2':
        {
            scanf("%c", &input);
            my_list = delete_item(my_list, input);

            break;
        }
        // Print list
        case '3':
        {
            print_list(my_list);
            break;
        }
        // print list backwards
        case '4':
        {
            print_reverse(my_list);
            printf("\n");
            break;
        }
        // free memory and quit
        case '5':
        {
            dispose_list(my_list);
            exit(0);
            break;
        }

        default:
        {
            printf("Invalid!\n");
            break;
        }
        }
    } while (selection != '0');
    return 0;
}
/**
 * @brief add an element at the beginning
 *
 * @param my_list_ref
 * @param new_data
 */
void push(List **my_list_ref, char new_data)
{
    List *new_node = (List *)malloc(sizeof(List));
    new_node->data = new_data;
    new_node->next = (*my_list_ref);
    new_node->prev = NULL;
    if ((*my_list_ref) != NULL)
    {
        (*my_list_ref)->prev = new_node;
    }
    (*my_list_ref) = new_node; // adding element
}
/**
 * @brief delete character from list according to input
 *
 * @param my_list
 * @param x
 * @return List*
 */
List *delete_item(List *my_list, char x)
{
    List *iter = my_list; // iterator for my_list
    int count = 0;

    if (iter == NULL)
    {
        // printf("The element is not in the list!\n");
        return my_list;
    }
    // deletes first element if found
    if (iter->data == x)
    {
        my_list = my_list->next;
        count++;
        // return my_list;
    }
    // deleting for chars if found in the list
    while (iter->next != NULL)
    {
        if (iter->next->data == x)
        {
            iter->next = iter->next->next;
            count++;
        }
        iter = iter->next;
    }
    if (count == 0)
    {
        printf("The element is not in the list!\n");
    }
    else
    {
        return my_list;
    }
    return my_list;
}
/**
 * @brief prints all elements of the list
 *
 * @param my_list
 */
void print_list(List *my_list)
{
    List *p;
    for (p = my_list; p; p = p->next)
    {
        printf("%c ", p->data);
    }
    printf("\n");
}
/**
 * @brief Prints all the elements of the list backwards
 *
 * @param my_list
 */
void print_reverse(List *my_list)
{
    if (my_list == NULL)
    {
        // printf("\n");
        return;
    }

    // print the list after head node
    print_reverse(my_list->next);

    // After everything else is printed, print head
    printf("%c ", my_list->data);
}
/**
 * @brief deallocates and free the memory
 *
 * @param my_list
 */
void dispose_list(List *my_list)
{
    List *nextelem;
    while (my_list != NULL)
    {
        nextelem = my_list->next;
        free(my_list);
        my_list = nextelem;
    }
}