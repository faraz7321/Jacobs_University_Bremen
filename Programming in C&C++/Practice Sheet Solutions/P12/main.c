#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct river
{
    char name[40];
    int length;
    int drainage_area;
};

//comparison function for length
//ascending order
int my_compare(const void *va,const void *vb)
{
    const struct river* a = (const struct river*) va;
    const struct river* b = (const struct river*) vb;
    if (a->length < b->length)
        return -1;
    else if(a->length > b->length)
        return 1;
    return 0;
}

int main()
{
    //declaring and opening the reading and writing file
    FILE *fp, *fc;
    fp = fopen("data.txt", "r");
    fc = fopen("output.txt", "w");

    struct river R[30];
    int nr=-1;
    char line[100];

    //reading the data
    while (!feof(fp))
    {
        nr++;

        //reading a line from the file
        fgets(line, sizeof(line), fp);

        //getting the name from the line
        for(int i=0; i<strlen(line); i++)
            if(line[i]==' ')
            {
                //copying the name from the line
                strncpy(R[nr].name, line, i);
                R[nr].name[i] = '\0';

                //modifying the line, so it doesn't contain
                //the name of the river
                strcpy(line, line+i);
                break;
            }

        //getting the 2 integers from the line
        sscanf(line, "%d %d", &R[nr].length, &R[nr].drainage_area);
    }

    //sorting the list of rivers
    qsort(R, nr, sizeof(struct river), my_compare);

    //printing the list of rivers
    for (int i=0; i<nr; i++)
    {
        fputs(R[i].name, fc);
        fprintf(fc, " %d %d\n", R[i].length, R[i].drainage_area);
    }

    //closing the files
    fclose(fp);
    fclose(fc);
    return 0;
}
