#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char str[20];
    struct node* next;
};

struct node* insertBegin(struct node* list, char str[])
{
    struct node* new_list;

    new_list = (struct node*)malloc(sizeof(struct node));
    if (new_list == NULL)
    {
        printf("Memory allocation error. \n");
        return list;
    }

    strcpy(new_list->str,str);
    new_list->next = list;

    return new_list;
}

void printList(struct node* list)
{
    struct node* plist;

    plist = (struct node*)malloc(sizeof(struct node));
    if (plist == NULL)
        printf("Memory allocation error. \n");

    for (plist = list; plist; plist = plist->next)
        printf("%s ", plist->str);
    printf("\n");

    free(plist);
}
int main()
{
    int n, i;
    char s[25], line[10];

    //setting our list to be empty
    struct node* list = NULL;

    //reading the number of strings we will have
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &n);

    //reading the n strings
    for (i=0; i<n; i++)
    {
        fgets(s, sizeof(s), stdin);
        s[strlen(s)-1] = '\0';
        list = insertBegin(list, s);
        printList(list);
    }

    return 0;
}
