/*
CH-230-A
linked_list.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdlib.h>
#include <stdio.h>
/* *********************************************************
 *                                                         *
 * A simply linked list is linked from node structures     *
 * whose size can grow as needed . Adding more elements    *
 * to the list will just cause it to grow and removing     *
 * elements will cause it to shrink .                      *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - -   *
 * struct list                                             *
 * used to hold the information for a node of a            *
 * simply linked list                                      *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - -   *
 * Function declaration ( routines )                       *
 *                                                         *
 * push_front -- add an element in the beginning           *
 * push_back -- add an element in the end                  *
 * dispose_list -- remove all the elements                 *
 * print_list -- print all elements                        *
 * delete_node -- delete first element                     *
 * ...                                                     *
 ******************************************************** */
typedef struct list List;
struct list
{
    int info;
    List *next;
};
List *push_front(List *my_list, int value);
List *push_back(List *my_list, int value);
List *delete_node(List *head);
void print_list(List *my_list);
void dispose_list(List *my_list);