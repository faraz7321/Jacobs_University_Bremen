/*
CH-230-A
a8_p5.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void saveData(int sum, char fileName[]);
int main()
{
    FILE *fPtr; // file pointer
    char arr[2], ch;
    int i = 0;

    // loading data from file
    fPtr = fopen("chars.txt", "r");
    if (fPtr == NULL)
    {
        printf("File is not available \n");
    }
    else
    {
        // stores data into array
        while ((ch = fgetc(fPtr)) != EOF)
        {
            arr[i] = ch;
            i++;
        }
    }
    fclose(fPtr);
    int x = arr[0], y = arr[1];
    int sum = x + y; // sum of ASCII
    saveData(sum, "codesum.txt");
    printf("\n%d\n", sum);

    return 0;
}
/**
 * @brief saves the data into txt file
 *
 * @param sum
 */
void saveData(int sum, char fileName[])
{
    FILE *fPtr;
    int i, n = log10(sum) + 1;
    char *numberArray = calloc(n, sizeof(char));
    fPtr = fopen(fileName, "w");
    /* fopen() return NULL if last operation was unsuccessful */
    if (fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    for (i = n - 1; i >= 0; --i, sum /= 10)
    {
        numberArray[i] = (sum % 10) + '0';
    }
    fputs(numberArray, fPtr);
    fclose(fPtr);
    free(numberArray);
    return;
}
