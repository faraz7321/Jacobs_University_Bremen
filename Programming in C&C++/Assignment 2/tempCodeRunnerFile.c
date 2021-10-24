/*
CH-230-A
a2_p4.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    float a, b, h;
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &h);
    printf("square area=%lf\n", a * a);
    printf("rectangle area=%lf\n", a * b);
    printf("triangle area=%lf\n", 0.5 * b * h);
 