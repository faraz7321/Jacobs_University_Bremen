/*
CH-230-A
a6_p9.c
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
int size = 0;
//FUNCTIONS FOR STRUCT
List *push_front(List *my_list, int value);
List *push_back(List *my_list, int value);
List *push_position(List *my_list, int pos, int value);
List *delete_node(List *head);
List *Reverse(List *my_list);
void print_list(List *my_list);
void dispose_list(List *my_list);
int main()
{
    List *my_list = NULL;
    char ch;
    int x1, x2;

    //begin:
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
            scanf("%d", &x1);
            my_list = push_back(my_list, x1);
            //goto begin;
            break;
        }
        //inserts at the beginning of the list
        case 'b':
        {
            scanf("%d", &x1);
            my_list = push_front(my_list, x1);
            //goto begin;
            break;
        }
        //removes head node
        case 'r':
        {
            my_list = delete_node(my_list);
            //goto begin;
            break;
        }
        //reverses the order of linked list
        case 'R':
        {
            my_list = Reverse(my_list);
            //goto begin;
            break;
        }
        //add an element at a position
        case 'i':
        {
            scanf("%d", &x1);
            scanf("%d", &x2);
            //printf("to func\n");
            my_list = push_position(my_list, x1, x2);
            //goto begin;
            break;
        }
        //print list
        case 'p':
        {
            print_list(my_list);
            //goto begin;
            break;
        }
        //free memory and quit
        case 'q':
        {
            printf("clearing memory...\n\n");
            dispose_list(my_list);
            printf("Memory cleared. Press any key to exit...\n");
            break;
        }

        default:
        {
            printf("Invalid!\n");
            //goto begin;
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
    size++;
    my_list = newel;
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
    size++;
    free(newel);
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
    size--;
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
 * @brief add an element to that position
 * 
 * @param my_list 
 * @param pos 
 * @param value 
 * @return  List* 
 */
List *push_position(List *my_list, int pos, int value)
{
    int i = 0;
    List *prev;
    List *pcurr;
    List *pnew;
    if (pos < 1 || pos > size + 1)
    {
        printf("Invalid position!\n");
    }
    else
    {
        pnew = malloc(sizeof(List));
        pnew->info = value;

        // find the correct place to insert
        prev = NULL;
        for (pcurr = my_list; pcurr != NULL; pcurr = pcurr->next, i += 1)
        {
            if (i >= pos)
                break;
            prev = pcurr;
        }

        // link up the element that will follow the new node
        pnew->next = pcurr;

        // insert into middle or end of list
        if (prev != NULL)
        {
            prev->next = pnew;
        }

        // insert into empty list or _before_ the first node
        else
        {
            my_list = pnew;
        }
    }
    free(pnew);
    return my_list;
}

/**
 * @brief freeing memory
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
/**
 * @brief reverse the elements of the list
 * 
 * @param my_list 
 * @return List* 
 */
List *Reverse(List *my_list)
{
    List *current = my_list;
    List *prev = NULL, *next = NULL;

    while (current != NULL)
    {
        // Store next
        next = current->next;

        // Reverse current node's pointer
        current->next = prev;

        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    my_list = prev;
    return my_list;
}
