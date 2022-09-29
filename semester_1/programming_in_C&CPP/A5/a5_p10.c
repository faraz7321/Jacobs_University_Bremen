/*
CH-230-A
a5_p10.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
void countDown(int n);
int main()
{
    int n;
    scanf("%d", &n);
    countDown(n);
    return 0;
}
void countDown(int n)
{
    /* if n become less than 1
    then return void function*/
    if (n <= 0)
    {
        return;
    }
    else
    {
        printf("%d ", n);

        // calling function in itself for recursion
        countDown(n - 1);
    }
}