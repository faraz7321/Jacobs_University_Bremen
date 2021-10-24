/*
CH-230-A
a7_p6.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct person Person;
struct person
{
    char name[20];
    int age;
};
// Struct Functions declaration
Person get_data();
void bubblesort(Person *struct_array, size_t n, int cmp(const Person *p1, const Person *p2));
int cmp_by_name(const Person *p1, const Person *p2);
int cmp_by_age(const Person *p1, const Person *p2);

int main()
{
    int n;
    scanf("%d", &n);
    Person *struct_array;
    struct_array = (Person *)malloc(n * sizeof(Person));
    // taking input from user
    for (int i = 0; i < n; i++)
    {
        struct_array[i] = get_data();
    }
    bubblesort(struct_array, n, cmp_by_name);
    printf("\n");
    bubblesort(struct_array, n, cmp_by_age);
    return 0;
}

/**
 * @brief Get the data object
 *
 * @return Person
 */
Person get_data()
{
    char str[20];
    Person thisdata;
    // printf("name:\n");
    scanf(" %[^\n]%*c", str);
    strcpy(thisdata.name, str);
    // printf("age: \n");
    scanf("%d", &thisdata.age);
    return thisdata;
}
/**
 * @brief name comparison
 *
 * @param p1
 * @param p2
 * @return int
 */
int cmp_by_name(const Person *p1, const Person *p2)
{
    int str_cmp = strcmp(p1->name, p2->name);
    int int_cmp = (p2->age < p1->age) - (p1->age < p2->age);

    return str_cmp != 0 ? str_cmp : int_cmp;
}

/**
 * @brief age comparison
 *
 * @param p1
 * @param p2
 * @return int
 */
int cmp_by_age(const Person *p1, const Person *p2)
{
    int str_cmp = strcmp(p1->name, p2->name);
    int int_cmp = (p2->age < p1->age) - (p1->age < p2->age);

    return int_cmp != 0 ? int_cmp : str_cmp;
}
/**
 * @brief bubblesort according to criteria
 *
 * @param struct_array
 * @param n
 * @param cmp
 */
void bubblesort(Person *struct_array, size_t n, int cmp(const Person *p1, const Person *p2))
{
    Person temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {

            if (cmp(&struct_array[j + 1], &struct_array[j]) < 0)
            {
                temp = struct_array[j + 1];
                struct_array[j + 1] = struct_array[j];
                struct_array[j] = temp;
            }
            // else
            //{
            //     temp = struct_array[j];
            //     struct_array[j] = struct_array[j + 1];
            //     struct_array[j + 1] = temp;
            // }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("{%s, %d}; ", struct_array[i].name, struct_array[i].age);
    }
    return;
}