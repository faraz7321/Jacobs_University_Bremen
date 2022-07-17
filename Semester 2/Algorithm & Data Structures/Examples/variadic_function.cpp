#include <iostream>
#include <cstdarg>

using namespace std;

double average(int count, ...)
{
    va_list ap;
    int j;
    double sum = 0;
 
    va_start(ap, count); /* Requires the last fixed parameter (to get the address) */
    for (j = 0; j < count; j++) {
        sum += va_arg(ap, double); /* Increments ap to the next argument. */
    }
    va_end(ap);
 
    return sum / count;
}

int main()
{
    cout << average(4, 1.0, 2.0, 3.0, 4.0) << endl;
    cout << average(2, 3.0, 5.0) << endl;
    cout << average(5, 3.2, 3.2, 3.2, 3.2, 3.2) << endl;
    return 0;
}
