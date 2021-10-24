/*
CH-230-A
a4_p10.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <math.h>
void proddivpowinv(float a, float b, float *prod, float *div,
                   float *pwr, float *invb);
int main()
{
    float a, b, prod, div, pwr, invb;

    //declaring pointers variables
    float *prod_ptr, *div_ptr, *pwr_ptr, *invb_ptr;

    //initializing pointer variables
    prod_ptr = &prod;
    div_ptr = &div;
    pwr_ptr = &pwr;
    invb_ptr = &invb;

    //taking input from user
    printf("a= ");
    scanf("%f", &a);
    printf("b= ");
    scanf("%f", &b);

    //calling function which will perform operation
    proddivpowinv(a, b, prod_ptr, div_ptr, pwr_ptr, invb_ptr);
    printf("a x b= %f\n", prod);
    printf("a / b= %f\n", div);
    printf("a ^ b= %f\n", pwr);
    printf("1 / b= %f\n", invb);
    return 0;
}
/**
 * @brief this function will calculate product,
 * division, power of a to b and inverse of b
 * 
 * @param a 
 * @param b 
 * @param prod 
 * @param div 
 * @param pwr 
 * @param invb 
 */
void proddivpowinv(float a, float b, float *prod, float *div, float *pwr, float *invb)
{
    //returning by refernece
    *div = (float)a / b;
    *prod = (float)a * b;
    *pwr = (float)pow(a, b);
    *invb = (float)1 / b;
}