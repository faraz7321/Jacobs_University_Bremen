/*
CH-230-A
a1_p1.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>

int main()
{
    double result; //the result of our calculator
    result = (3 + 1) / 5;
    //result = (double)(3 + 1) / 5;  (Another way is Type Casting)
    printf("The value of 4/5 is %lf\n", result);
    return 0;
    /*
    The result will be 0.000 because 4 is divided
    by an integer and the compiler does not round off
    the value of 4/5 which is 0.8 to nearest whole number
    instead it removes the values after 0
    and as the data type is double it gives the answer 0.000 for precision
    to get your desirable answer, 4 should be divided by 5.0(a double value)
    */
    /*
    ***NEW CODE***
    double result; //the result of our calculator
    result = (3 + 1) / 5.0;
    printf("The value of 4/5 is %lf\n", result);
    */
}