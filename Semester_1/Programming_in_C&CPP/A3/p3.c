/*
CH-230-A
a3_p3.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//Function prototype
float convert(int cm);
int main()
{
    int cm;
    scanf("%d", &cm);
    printf("Result of conversion: %lf\n", convert(cm));
    return 0;
}
/**
 * @brief this function converts cm to km
 * 
 * @param cm 
 * @return float 
 */
float convert(int cm)
{
    float result;
    result = (float)cm / 100000; //cm x 10^-5
    return result;
}