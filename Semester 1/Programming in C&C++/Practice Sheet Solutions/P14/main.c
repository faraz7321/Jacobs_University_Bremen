#include <stdio.h>
#include <stdlib.h>

int main()
{
    //declare and open the binary!! writing file
    FILE *fc;
    fc = fopen("generate.txt", "wb");
    if (fc == NULL)
        exit(1);

    char sp=' ', en = '\n';
    for (char ch='a'; ch<='j'; ch++)
       {
           fwrite(&ch, sizeof(ch), 1, fc);
           fwrite(&sp, sizeof(ch), 1, fc);
           fwrite(&ch, sizeof(ch), 1, fc);
           fwrite(&ch, sizeof(ch), 1, fc);
           fwrite(&en, sizeof(ch), 1, fc);
       }

    fprintf(fc, "\n\n");

    char arr[5];
    //arr[0] = arr[2] = arr[3] = 'a';
    arr[1] = ' ';
    arr[4] = '\n';

    for (int i=0; i<10; i++)
    {
        arr[0] = 'a' + i;
        arr[2] = 'a' + i;
        arr[3] = 'a' + i;
        fwrite(arr, sizeof(char), 5, fc);
    }
    return 0;
}
