/*
CH-230-A
a8_p8.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;
    char ch;
    int in_word = 0;
    int word_count = 1;

    // opening file
    file = fopen("text.txt", "r");

    /* Check if file opened successfully */
    if (file == NULL)
    {
        printf("\nUnable to open file.\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Logic to count words.
     * checks if previous char is repeated
     * for eg 2 spaces or newlines togather
     */
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == ' ' || ch == '\t' || ch == '\0' || ch == '\n')
        {
            if (in_word)
            {
                in_word = 0;
                word_count++;
            }
        }
        else
        {
            in_word = 1;
        }
    }
    printf("The file contains %d words\n", word_count);

    // Close file
    fclose(file);

    return 0;
}