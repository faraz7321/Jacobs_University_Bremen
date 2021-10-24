/*
CH-230-A
a1_p3.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    float result; //the result of the division
    int a = 5;
    //int b = 13.5;
    float b = 13.5;
    result = a / b;
    //printf("the result is %d\n", result); %d --> %f
    printf("the result is %f\n", result);
    return 0;
}
/* There was no compilation error but there was logical error
as the value printed was '0'.
Variable "b" cannot store 13.5 instead it will store 13 and 
ignore the decimal values.
changed the data type of "b" to float
in the print statement I changed format specifier decimal to float
*/