#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool password_checker(char password[])
{
    if (strlen(password) < 8)
        return false;
    else
    {
        int i, nr = 0;
        for (i=0; i<strlen(password); i++)
            if (password[i]>='0' && password[i]<='9')
                nr++;
        if (nr >= 3)
            return true;
        else
            return false;
    }
}
int main()
{
    char password[100];
    fgets(password, sizeof(password), stdin);

    if( password_checker(password) )
        printf("TRUE\n");
    else
        printf("FALSE\n");
    return 0;
}
