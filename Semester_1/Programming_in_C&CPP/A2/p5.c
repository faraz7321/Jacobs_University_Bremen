/*
CH-230-A
a2_p5.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    int a;
    printf("Enter an integer: ");
    scanf("%d", &a);
    printf("You entered %d\n", a);
    int *ptr_a;
    //initializing a pointer pointing to variable 'a'
    ptr_a = &a;
    printf("Address contained in pointer: %p\n", (void *)ptr_a);
    //adding 5 to the value of 'a' which was provided by user
    *ptr_a = *ptr_a + 5;
    printf("New Value(increment of 5): %d\n", *ptr_a);
    /*address of pinter does not change as it is still
    pointing to same address ie address of 'a'*/
    printf("Address of pointer: %p\n", (void *)ptr_a);
    return 0;
}