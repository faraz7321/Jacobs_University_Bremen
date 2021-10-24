/*
CH-230-A
a3_p6.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>

//A function declared to convert KG to Pounds
float to_pounds(int kg, int g);
int main()
{
    int kg, g;
    //Taking input from the user
    scanf("%d", &kg);
    scanf("%d", &g);
    printf("Result of conversion: %lf\n", to_pounds(kg, g));
    return 0;
}
/**
* @brief this function converts kg to pounds
* by taking input in two seperate arguments for kg and g
* @param kg
* @param g
* @return answer in pounds
**/
float to_pounds(int kg, int g)
{
    double result = 0;
    //convert kg and g to single value then multiply it with 2.2
    result = (kg + ((double)g / 1000)) * 2.2;

    return result;
}