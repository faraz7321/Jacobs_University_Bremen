/*
CH-230-A
a4_p3.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <math.h>
float geometric_mean(float arr[], int num);
float largestnum(float arr[], int num);
float smallestnum(float arr[], int num);
void menu();
int main()
{
    float arr[15], input, sum = 0;
    int count = 0; // counts number of elements in array
    char c;
    //taking input from the user
    printf("Enter Input: ");
    for (int i = 0; i < 15; i++)
    {
        scanf("%f", &input);
        if (input >= 0)
        {
            count++;
            arr[i] = input;
        }
        else
        {
            break;
        }
    }
    menu(); // prints menu screen
    scanf(" %c", &c);
    getchar();
    switch (c)
    {
        //Calculate geometric mean
    case 'm':
    {
        printf("Geometric mean= %f\n", geometric_mean(arr, count));

        break;
    }
    //display largest number in array
    case 'h':
    {
        printf("Largest number= %f\n", largestnum(arr, count));

        break;
    }
    //display smallest number in array
    case 'l':
    {
        printf("Smallest number= %f\n", smallestnum(arr, count));
        break;
    }
    //calculates sum of elements in array
    case 's':
    {
        //calculating sum
        for (int i = 0; i < count; i++)
        {
            sum = sum + arr[i];
        }
        printf("Sum= %f\n", sum);
        break;
    }
    default:
    {
        printf("error\n");
        break;
    }
    }

    return 0;
}
/**
 * @brief display menu
 * 
 */
void menu()
{
    printf(">Press m to calculate GM\n");
    printf(">Press h to print highest number\n");
    printf(">Press l to print smallest number\n");
    printf(">Press s to calculate sum\n");
}
/**
 * @brief calculates geometric mean of elements
 * in the array
 * 
 * @param arr 
 * @param num 
 * @return float 
 */
float geometric_mean(float arr[], int num)
{
    float prod = 1;
    float gm;
    for (int i = 0; i < num; i++)
    {
        prod = prod * arr[i];
    }
    //printf("%f\n", prod);
    gm = pow(prod, (float)1 / num);
    return gm;
}
/**
 * @brief calculate largest element in array
 * 
 * @param arr 
 * @param num 
 * @return float 
 */
float largestnum(float arr[], int num)
{
    float max = arr[0];

    // Traverse array elements
    // from second and compare
    // every element with current max
    for (int i = 1; i < num; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}
/**
 * @brief calculates smallest number in array
 * 
 * @param arr 
 * @param num 
 * @return float 
 */
float smallestnum(float arr[], int num)
{
    float min = arr[0];

    // Traverse array elements
    // from second and compare
    // every element with current min

    for (int i = 1; i < num; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}