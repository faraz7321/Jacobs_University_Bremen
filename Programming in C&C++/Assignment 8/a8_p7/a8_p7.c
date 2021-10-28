/*
CH-230-A
a8_p7.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Open two files to be merged
    FILE *fPtr1 = fopen("text1.txt", "r");
    FILE *fPtr2 = fopen("text2.txt", "r");

    // Open file to store the result
    FILE *fPtr3 = fopen("merge12.txt", "w");
    char c;

    if (fPtr1 == NULL || fPtr2 == NULL || fPtr3 == NULL)
    {
        puts("Could not open files");
        exit(0);
    }

    // Copy contents of first file to file3.txt
    while ((c = fgetc(fPtr1)) != EOF)
    {
        fputc(c, fPtr3);
    }

    // Copy contents of second file to file3.txt
    while ((c = fgetc(fPtr2)) != EOF)
    {
        fputc(c, fPtr3);
    }
    printf("Successfully saved to file!\n");
    // closing files
    fclose(fPtr1);
    fclose(fPtr2);
    fclose(fPtr3);
    return 0;
}