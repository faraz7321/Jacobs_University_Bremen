
/*
CH-230-A
a7_p3.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include "linked_list.h"
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