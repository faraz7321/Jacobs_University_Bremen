/*
CH-230-A
a2_p9.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    char input;
    scanf("%c", &input);
    getchar();
    /*if the input is ranging between a-z and A-Z
    then it is a letter*/
    if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
    {
        printf("%c", input);
        printf(" is a letter\n");
    }
    /*if the input ranges between 0-9
    then it is a digit*/
    else if ((input >= '0' && input <= '9'))
    {
        printf("%c", input);
        printf(" is a digit\n");
    }
    /*if the input is none of the above
    ie digit or letter then it is some other symbol*/
    else
    {
        printf("%c", input);
        printf(" is some other symbol\n");
    }

    return 0;
}