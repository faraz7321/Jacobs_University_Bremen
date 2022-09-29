/*
CH-230-A
a8_p9.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdio.h>
#include <stdlib.h>

void output();

int main()
{
    FILE **fPtr; // pointer array to store file pointers
    FILE *fPtr2; // pointer for output.txt
    int n;       // number of files to read
    scanf("%d", &n);
    char c, **input;
    // 2D char array or 1D string array
    input = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        input[i] = malloc((30 + 1) * sizeof(char));
    }
    // taking input from user to open which files
    for (int i = 0; i < n; i++)
    {
        scanf(" %[^\n]%*c", input[i]);
    }

    // making file pointer array and assigning
    // each index of array to file names
    fPtr = malloc(sizeof(FILE *) * n);
    if (fPtr != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fPtr[i] = fopen(input[i], "r");
            if (fPtr[i] == NULL)
            {
                puts("Could not open file");
                exit(0);
            }
        }
    }
    else
    {
        printf("Error: No enough memory\n");
        getchar();
        return 1;
    }

    // too lazy to make functions :(

    // deallocating memory
    for (int i = 0; i < n; i++)
    {
        free(input[i]);
    }
    free(input);

    // writing to output.txt
    printf("Concating the contents of %d files ...\n", n);
    fPtr2 = fopen("output.txt", "w");
    if (fPtr2 == NULL)
    {
        puts("Could not open file");
        exit(0);
    }
    int i = 0;
    while (n > 0)
    {
        // copying content of fPtr[i] to output.txt
        while ((c = fgetc(fPtr[i])) != EOF)
        {
            fputc(c, fPtr2);
        }
        n--;
        i++;
        fputc('\n', fPtr2);
    }
    // closing files
    for (int i = 0; i < n; i++)
    {
        fclose(fPtr[i]);
    }
    fclose(fPtr2);

    output();

    return 0;
}
/**
 * @brief shows content of output.txt
 *
 */
void output()
{
    printf("The result is:\n");
    char ch;
    FILE *fPtr;
    fPtr = fopen("output.txt", "r");
    if (fPtr == NULL)
    {
        puts("Could not open file");
        return;
    }
    // printing to console
    while ((ch = fgetc(fPtr)) != EOF)
    {
        printf("%c", ch);
    }
    fclose(fPtr);
    printf("The result was written into output.txt\n");
}