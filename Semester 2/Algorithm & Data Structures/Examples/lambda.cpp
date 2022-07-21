#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int v[5] = {1, 5, 2, 4, 3};
    qsort(v, 5, sizeof(int), [] (const void *a, const void *b) -> int { return *(int *)a - *(int *)b; });
    for(int i=0; i<5; i++)
        cout << v[i] << " ";
    cout << endl;
    return 0;
}
