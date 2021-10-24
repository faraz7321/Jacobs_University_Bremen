/*
CH-230-A
a4_p1.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//Defining value of PI
#define PI 3.14159265358979323846
int main()
{
    //initializing variables
    //using float instead of double because test case 3 was failing
    //the 6th decimal place needed to be rounded
    float start, end, increment;
    //taking input form user
    scanf("%f", &start);
    scanf("%f", &end);
    scanf("%f", &increment);
    /*printing radius, area, and perimeter
    each time the loop run, value of radius increases
    by the value provided by user in variable 'increment'*/
    for (float i = start; i <= end; i = i + increment)
    {
        printf("%f %f %f\n", i, i * i * PI, 2 * i * PI);
    }

    return 0;
}