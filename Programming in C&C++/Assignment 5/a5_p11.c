/*
CH-230-A
a5_p11.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int prime(int n, int i);
int main()
{
    int x;
    //Taking input from user
    scanf("%d", &x);
    //if function returns 1 then input is prime
    //else input is not a prime number
    if (prime(x, 2) == 1)
    {
        printf("%d is prime\n", x);
    }
    else
    {
        printf("%d is not prime\n", x);
    }
    return 0;
}
/**
 * @brief check if the function is prime or not
 * 
 * @param n 
 * @param i 
 * @return int 
 */
int prime(int n, int i)
{
    //check if the number is exactly divisible by two numbers
    if (n <= 2)
    {
        if (n == 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (n % i == 0)
    {
        return 0;
    }
    if (i * i > n)
    {
        return 1;
    }

    //recursion to check for next divisor
    return prime(n, i + 1);
}