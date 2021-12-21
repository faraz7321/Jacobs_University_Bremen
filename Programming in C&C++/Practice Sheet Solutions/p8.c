#include <stdio.h>
#include <stdlib.h>

void total_time(int mins[], int secs[], int n, int *sum_min, int *sum_sec)
{
    //initializing the sums with 0
    *sum_min = 0;
    *sum_sec = 0;

    //going through the 2 arrays and calculating the sums
    for (int i=0; i<n; i++)
    {
        *sum_min = *sum_min + mins[i];
        *sum_sec = *sum_sec + secs[i];
    }

    //Transforming the seconds into minutes
    *sum_min = *sum_min + (*sum_sec / 60);
    *sum_sec = *sum_sec % 60;
}
int main()
{
    int sum1, sum2;
    int a[] = {1, 2, 3};
    int b[] = {30, 40, 50};

    total_time(a, b, 3, &sum1, &sum2);

    printf("%d %d\n", sum1, sum2);

    return 0;
}
