/*
CH-230-A
a8_p6.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdio.h>
#include <stdlib.h>
double loadData(char fileName[]);
void saveData(double x, double y);
int main()
{
    double input1 = loadData("input2.txt");
    double input2 = loadData("input1.txt");
    saveData(input1, input2);
    // printf("%lf\n", input1);
}
/**
 * @brief load data from file
 *
 * @param fileName
 * @return double
 */
double loadData(char fileName[])
{
    FILE *fPtr; // file pointer
    double data;

    // loading data from file
    fPtr = fopen(fileName, "r");
    if (fPtr == NULL)
    {
        printf("File is not available \n");
    }
    fscanf(fPtr, "%lf", &data);
    fclose(fPtr);
    return data;
}
/**
 * @brief saves data to the file
 *
 * @param x
 * @param y
 */
void saveData(double x, double y)
{
    FILE *fPtr;
    fPtr = fopen("results.txt", "w");
    /* fopen() return NULL if last operation was unsuccessful */
    if (fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    // writing to file
    fprintf(fPtr, "Sum= %lf\n", x + y);
    fprintf(fPtr, "Difference= %lf\n", x - y);
    fprintf(fPtr, "Product= %lf\n", x * y);
    fprintf(fPtr, "Divison= %lf\n", x / y);
    fclose(fPtr);
    return;
}