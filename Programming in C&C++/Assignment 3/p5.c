/*
CH-230-A
a3_p5.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//Declaring Functions
double sum(double arr[], int size);
void list(double arr[], int size);
void list_f(double arr[], int size);
double Default(double Sum, int size);
int main()
{
    char c;
    int n, size;
    double Sum;
    //taking input from the user
    printf("Enter a character: ");
    c = getchar();
    getchar();
    printf("Enter size of array: ");
    scanf("%d", &n);
    //to initialize ar array of no more than 100 elements
    if (n >= 100)
    {
        size = 100;
    }
    else
    {
        size = n;
    }
    double arr[size];
    //taking input in array from user
    for (int i = 0; i < size; i++)
    {
        scanf("%lf", &arr[i]);
    }

    switch (c)
    {
        //Calculate Sum
    case 's':
    {
        printf("Sum of all temperatures= %lf\n", sum(arr, size));
        break;
    }
    //List all temperatures which user entered
    case 'p':
    {
        list(arr, size);
        break;
    }
    //List of temperatures in fahrenheit
    case 't':
    {
        list_f(arr, size);
        break;
    }
    //arithmetic mean of teamperatures entered by the user
    default:
    {
        Sum = sum(arr, size);
        printf("Arithmetic mean= %lf\n", Default(Sum, size));
        break;
    }
    }

    return 0;
}
/**
 * @brief This function calculates sum of temperatures
 * stored in an array
 * 
 * @param arr 
 * @param size 
 * @return double 
 */
double sum(double arr[], int size)
{
    double Sum = 0;
    for (int i = 0; i < size; i++)
    {
        Sum = Sum + arr[i];
    }
    return Sum;
}
/**
 * @brief print list of all temperatures in celcius
 * stored in an array
 * 
 * @param arr 
 * @param size 
 */
void list(double arr[], int size)
{
    printf("\nList of all temperatures:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%lf\n", arr[i]);
    }
}
/**
 * @brief print list of all temperatures in fahrenheit
 * stored in an array
 * 
 * @param arr 
 * @param size 
 */
void list_f(double arr[], int size)
{
    double fahrenheit;
    printf("\nList of all temperatures in Fahrenheit:\n");
    for (int i = 0; i < size; i++)
    {
        fahrenheit = ((9 * arr[i]) / 5.0) + 32;
        printf("%lf\n", fahrenheit);
    }
}
/**
 * @brief print mean of temperatures
 * 
 * @param Sum 
 * @param size 
 * @return double 
 */
double Default(double Sum, int size)
{
    double mean;
    mean = (double)Sum / size;
    return mean;
}