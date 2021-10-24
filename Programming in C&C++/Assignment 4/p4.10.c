#include <stdio.h>
#include <math.h>
void proddivpowinv(float a, float b, float *prod, float *div, float *pwr, float *invb)
{
    //returning by refernece
    *div = a / b;
    *prod = a * b;
    *pwr = pow(a, b);
    *invb = (float)1 / b;
}
int main()
{
    float a, b, prod, div, pwr, invb;
    float *prod_ptr, *div_ptr, *pwr_ptr, *invb_ptr;

    prod_ptr = &prod;
    div_ptr = &div;
    pwr_ptr = &pwr;
    invb_ptr = &invb;
    scanf("%f", &a);
    scanf("%f", &b);
    proddivpowinv(a, b, prod_ptr, div_ptr, pwr_ptr, invb_ptr);
    printf("Product of a and b= %f\n", prod);
    printf("a divided by b= %f\n", div);
    printf("a to power b= %f\n", pwr);
    printf("inverse of b= %f\n", invb);
    return 0;
}
