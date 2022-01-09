/*
CH-230-A
linked_list.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include "linked_list.h"
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