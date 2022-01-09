/*
CH-230-A
a2_p4.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//#include <math.h>
int main()
{
    float a, b, h;
    //Taking input of bases and height from user
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &h);
    float square, rectangle, triangle, trapezoid;
    //calculating areas
    square = a * a;
    rectangle = a * b;
    triangle = 0.5 * a * h;
    trapezoid = 0.5 * (a + b) * h;
    printf("square area=%lf\n", square);
    printf("rectangle area=%lf\n", rectangle);
    printf("triangle area=%lf\n", triangle);
    printf("trapezoid area=%lf\n", trapezoid);

    return 0;
}