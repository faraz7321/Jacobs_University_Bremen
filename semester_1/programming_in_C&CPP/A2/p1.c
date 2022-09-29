/*
CH-230-A
a2_p1.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    double input1, input2;
    //Taking input in double variables from user
    scanf("%lf %lf", &input1, &input2);
    double sum = input1 + input2;
    printf("sum of doubles=%lf\n", sum);
    printf("difference of doubles=%lf\n", input1 - input2);
    printf("square=%lf\n", input1 * input1);
    int input3, input4;
    //Taking input in int variables from user
    scanf("%d %d", &input3, &input4);
    printf("sum of integers=%d\n", input3 + input4);
    printf("product of integers=%d\n", input3 * input4);
    char c_input1, c_input2;
    int c = 0;
    /*ENTER is also a character input in getchar()
    so to ignore that input in our case i used this method
    ASCII is saved in int c and later stored in char variable
    only if the entered input is other than ENTER or SPACE*/
    while ((c = getchar())) //parentheses around assignment used as truth value
    {
        if (c == '\n' || c == ' ') //ignoring ENTER AND SPACE input
        {
            continue;
        }
        if (c_input1 == '\0')
        {
            c_input1 = c;
            continue;
        }
        c_input2 = c;
        break;
    }
    //scanf("%c", &c_input2);
    //Printing ACSII values of chars
    printf("sum of chars=%d\n", c_input1 + c_input2);
    printf("product of chars=%d\n", c_input1 * c_input2);
    //Printing chars
    printf("sum of chars=%c\n", c_input1 + c_input2);
    printf("product of chars=%c\n", c_input1 * c_input2);
    return 0;
}