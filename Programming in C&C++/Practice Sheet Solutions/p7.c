#include <stdio.h>
#include <stdlib.h>

int substitute_vowels(char *s, char ch)
{
    //nr will count the number changes
    int nr = 0;

    //walking the string using pointers
    char* i;
    for (i=s; *i!='\0'; i++)
        if (*i == 'a' || *i == 'e' || *i == 'i' || *i == 'o'
             || *i == 'u')
             {
                 *i = ch;
                 nr++;
             }
    return nr;
}
int main()
{
    int n;
    char s[] = "This is a sentence";
    printf("%s\n", s);
    n = substitute_vowels(s, 'o');
    printf("%s\n", s);
    printf("%d\n", n);
    return 0;
}
