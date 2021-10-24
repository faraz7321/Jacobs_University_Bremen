/*
CH-230-A
a3_p10.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
//Function prototype
float product(float a, float b);
void productbyref(float a, float b, float *p);
void modifybyref(float *a, float *b);
int main()
{
    float a, b, pro = 0;
    //initialising pointer variables
    float *ptr_a, *ptr_b, *ptr_pro;
    //assigning addresses of variables 'a' and 'b' to pointers
    ptr_a = &a;
    ptr_b = &b;
    ptr_pro = &pro;
    //Taking input from user
    scanf("%f", &a);
    scanf("%f", &b);
    printf("Product= %f\n", product(a, b));

    //calling the function so it can perform operation
    productbyref(a, b, ptr_pro);
    printf("Product by reference= %f\n", pro);

    //calling the function so it can perform operation
    modifybyref(ptr_a, ptr_b);
    printf("Modify by reference:\na= %f\nb= %f", *ptr_a, *ptr_b);

    return 0;
}
/**
 * @brief calculate product of a and b
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float product(float a, float b)
{
    return a * b;
}
/**
 * @brief return product value by reference
 * 
 * @param a 
 * @param b 
 * @param p 
 */
void productbyref(float a, float b, float *p)
{
    *p = a * b;
}
/**
 * @brief modify a and b values by reference
 * 
 * @param a 
 * @param b 
 */
void modifybyref(float *a, float *b)
{
    *a = *a + 3;
    *b = *b + 11;
}