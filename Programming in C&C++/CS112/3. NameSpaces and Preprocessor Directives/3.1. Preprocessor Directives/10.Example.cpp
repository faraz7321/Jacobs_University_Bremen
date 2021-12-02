// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The output of the code shown below is 25. This is because the        *
 * arithmetic statement takes the form of: 25/5*5 (which is equal to    *
 * 25). If the macro had been defined as #define sqr(x) (x*x), the      *
 * output would have been 1.                                            *                                                   *
 ************************************************************************/ 
#define sqr(x) x*x
int main()
{
    int a1 = 25 / (sqr(5));
    cout << a1 << endl;
    cout<<sqr(5);
    return 0;
}
