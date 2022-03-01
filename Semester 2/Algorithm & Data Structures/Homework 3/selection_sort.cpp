// C program to store time taken by bubble sort,
// insertion sort and selection sort
// for sorting exactly same arrays.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

// Swap utility
void swap(long int *a, long int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Selection sort
void selectionSort(long int arr[], long int n)
{
    long int min_idx;
    for (int i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (long int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            swap(&arr[min_idx], &arr[i]);
        }
    }
}
void saveData(double time[], string filename, int it)
{
    // This variable for read data from file
    ofstream myfile;
    /*Open the file if exist if not exist then make new file of this name ios::app maens that the new data will append in file and
    not remove previous content of file */
    myfile.open(filename);
    // This function will check if the file open then write data from file
    long int n = 10000;
    if (myfile.is_open())
    {
        for (int i = 0; i < it; i++)
        {
            // These lines will write all array data to the file and make a comma separated file
            myfile << n << "," << time[i] << endl;
            n += 10000;
        }
        myfile.close();
    }
    else
    {
        // If there is error while opening file this function will return false
        // cout << "error opening file\n";
    }
}
// Driver code
int main()
{
    long int n = 100;
    int it = 0;
    double tim1[100];

    printf("A_size, Selection\n");
    long int *arr;
    // Performs 10 iterations
    while (it < 100)
    {
        arr = new long int[n];
        // generating n random numbers
        // storing them in arrays a, b, c
        for (int i = 0; i < n; i++)
        {
            long int no = rand() % n + 1;
            arr[i] = no;
        }

        // using clock_t to store time
        clock_t start, end;

        // Selection sort
        start = clock();
        selectionSort(arr, n);
        end = clock();

        tim1[it] = ((double)(end - start));

        // type conversion to long int
        // for plotting graph with integer values
        printf("%li, %li\n", n, (long int)tim1[it]);

        // increases the size of array by 10000
        n += 100;
        it++;
    }
    saveData(tim1, "input.csv", it);

    return 0;
}
