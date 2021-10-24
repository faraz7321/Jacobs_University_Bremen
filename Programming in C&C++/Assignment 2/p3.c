/*
CH-230-A
a2_p3.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    int weeks, days, hours;
    long int totalHours;
    printf("Enter number of weeks: ");
    scanf("%d", &weeks);
    printf("Enter number of days: ");
    scanf("%d", &days);
    printf("Enter number of hours: ");
    scanf("%d", &hours);
    //Calculating total number of hours
    totalHours = (weeks * 7 * 24) + (days * 24) + hours;
    printf("\nTotal Number of hours= %ld\n", totalHours);
    return 0;
}