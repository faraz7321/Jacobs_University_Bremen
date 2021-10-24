/*
CH-230-A
a7_p4.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function Declarations
void fun1(char str[30]);
void fun2(char str[30]);
void fun3(char str[30]);
void fun4();
// Pointer function array
void (*func_ptr[4])(char str[]) = {fun1, fun2, fun3, fun4};

int main()
{
    char str[30];
    int option;
    // taking input from user
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
    while (1)
    {
        // scan index from user
        scanf("%d", &option);
        (*func_ptr[option - 1])(str);
    }

    return 0;
}
/**
 * @brief toUppercase
 *
 * @param str
 */
void fun1(char str[30])
{
    char new_str[30];
    strcpy(new_str, str);
    for (int i = 0; new_str[i] != '\0'; i++)
    {
        /*
         * If current character is lowercase alphabet then
         * convert it to uppercase.
         */
        if (new_str[i] >= 'a' && new_str[i] <= 'z')
        {
            new_str[i] = new_str[i] - 32;
        }
    }
    printf("%s\n", new_str);
    return;
}
/**
 * @brief toLowercase
 *
 * @param str
 */
void fun2(char str[30])
{
    char new_str[30];
    strcpy(new_str, str);
    for (int i = 0; new_str[i] != '\0'; i++)
    {
        /*
         * If current character is uppercase alphabet then
         * convert it to lowercase.
         */
        if (new_str[i] >= 'A' && new_str[i] <= 'Z')
        {
            new_str[i] = new_str[i] + 32;
        }
    }
    printf("%s\n", new_str);
    return;
}
/**
 * @brief converts uppercase char to lowercase
 * and lower case char to uppercase
 *
 * @param str
 */
void fun3(char str[30])
{
    char new_str[30];
    strcpy(new_str, str);
    for (int i = 0; new_str[i] != '\0'; i++)
    {
        /*
         * If current character is lowercase alphabet then
         * convert it to uppercase.
         * else If current character is uppercase alphabet then
         * convert it to lowercase.
         */
        if (new_str[i] >= 'A' && new_str[i] <= 'Z')
        {
            new_str[i] = new_str[i] + 32;
        }
        else if (new_str[i] >= 'a' && new_str[i] <= 'z')
        {
            new_str[i] = new_str[i] - 32;
        }
    }
    printf("%s\n", new_str);
    return;
}
/**
 * @brief exit program
 *
 */
void fun4()
{
    exit(0);
}