/*
CH-230-A
linked_list.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
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