/*
CH-230-A
a5_p7.c
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 100
int main()
{
    //declaring static arrays
    char str1[MAX_LENGTH], str2[MAX_LENGTH];

    //taking input from the user
    fgets(str1, MAX_LENGTH, stdin);
    fgets(str2, MAX_LENGTH, stdin);

    //removing \n from last index of str1
    str1[strcspn(str1, "\n")] = 0;
    strcat(str1, str2); //concatenating str1 and str2

    //declaring third array (dynamically)
    char *str3 = (char *)malloc(strlen(str1) * sizeof(char));
    strcpy(str3, str1); //copying str1 into str3

    printf("Result of concatenation: %s", str3);
    return 0;
}