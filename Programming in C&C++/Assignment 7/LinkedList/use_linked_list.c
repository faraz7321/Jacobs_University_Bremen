/*
CH-230-A
use_linked_list.c
Faraz Ahmad
fahmad@jacobs.university.de
 */

#include "linked_list.h"
//#include "linked_list.c"
int main()
{
    List *my_list = NULL;
    char ch;
    int x;

    do
    {
        // taking input from user
        scanf(" %c", &ch);
        getchar();
        switch (ch)
        {
        // add the following number
        case 'a':
        {
            scanf("%d", &x);
            my_list = push_back(my_list, x);
            break;
        }
        // inserts at the beginning of the list
        case 'b':
        {
            scanf("%d", &x);
            my_list = push_front(my_list, x);
            break;
        }
        // removes head node
        case 'r':
        {
            my_list = delete_node(my_list);
            break;
        }
        // print list
        case 'p':
        {
            print_list(my_list);
            break;
        }
        // free memory and quit
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