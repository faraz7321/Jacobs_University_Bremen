#include <stdio.h>
float sum(float v[], int x);
float mean(float v[], int x);

int main()
{
    float list[10], ans1, ans2;
    int i = 0, n;
    while (i < 10)
    {
        printf("enter number");
        scanf("%f", &list[i]);
        if (list[i] == -99)
        {
            break;
        }
        i++;
    }
    n = sizeof(list) / sizeof(float);
    printf("%d\n", n);
    ans1 = sum(list, n);
    ans2 = mean(list, n);
    // calculating the sum and mean //
    printf("the sum is %f\n", ans1);
    printf(" the mean is %f\n", ans2);
    return 0;
}

float sum(float v[], int x)
{
    int i = 0;
    float a = 0;
    while (i < x)
    {
        a = a + v[i];
        i++;
    }
    return a;
}

float mean(float v[], int x)
{
    int i = 0;
    float addition = 0, avg = 0;
    while (i < x)
    {
        addition = addition + v[i];
        avg = addition / x;
        // calculating the addition and average //
        i++;
    }
    return avg;
}