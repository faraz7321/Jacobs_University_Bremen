/*
CH-230-A
a6_p8.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <stdlib.h>

// Declaring structure for list
typedef struct list List;
struct list
{
    int info;
    List *next;
};
//FUNCTIONS FOR STRUCT
List *push_front(List *my_list, int value);
List *push_back(List *my_list, int value);
List *delete_node(List *head);
void print_list(List *my_list);
void dispose_list(List *my_list);

int main()
{
    List *my_list = NULL;
    char ch;
    int x;

    do
    {
        //taking input from user
        scanf(" %c", &ch);
        getchar();
        switch (ch)
        {
        //add the following number
        case 'a':
        {
            scanf("%d", &x);
            my_list = push_back(my_list, x);
            break;
        }
        //inserts at the beginning of the list
        case 'b':
        {
            scanf("%d", &x);
            my_list = push_front(my_list, x);
            break;
        }
        //removes head node
        case 'r':
        {
            my_list = delete_node(my_list);
            break;
        }
        //print list
        case 'p':
        {
            print_list(my_list);
            break;
        }
        //free memory and quit
        case 'q':
        {
            dispose_list(my_list);
            break;
        }

        default:
        {
            printf("Invalid!\n");
            break;
        }
        }
    } while (ch != 'q');

    return 0;
}
/**
 * @brief adding to the list
 * 
 * @param my_list 
 * @param value 
 * @return  List* 
 */
List *push_front(List *my_list, int value)
{
    List *newel;
    newel = (List *)malloc(sizeof(List));
    if (newel == NULL)
    {
        printf(" Error allocating memory \n");
        return my_list;
    }
    newel->info = value;
    newel->next = my_list;
    return newel;
}
/**
 * @brief adding to beginning of list
 * 
 * @param my_list 
 * @param value 
 * @return  List* 
 */
List *push_back(List *my_list, int value)
{
    List *cursor, *newel;
    cursor = my_list;
    newel = (List *)malloc(sizeof(List));
    if (newel == NULL)
    {
        printf(" Error allocating memory \n");
        return my_list;
    }
    newel->info = value;
    newel->next = NULL;
    if (my_list == NULL)
    {
        return newel;
    }
    while (cursor->next != NULL)
    {
        cursor = cursor->next;
    }
    cursor->next = newel;
    return my_list;
}
/**
 * @brief delete head node
 * 
 * @param head 
 * @return  List* 
 */
List *delete_node(List *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    // Move the head pointer to the next node
    List *temp = head;
    head = head->next;
    free(temp); //deleting node
    return head;
}
/**
 * @brief print list
 * 
 * @param my_list 
 */
void print_list(List *my_list)
{
    List *p;
    for (p = my_list; p; p = p->next)
    {
        printf("%d ", p->info);
    }
    printf("\n");
}
/**
 * @brief deallocating memory
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
