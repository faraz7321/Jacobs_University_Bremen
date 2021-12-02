// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The macro ‘a’ is redefined in the code shown above. Hence the value  *
 * of a, which is initially 2, is redefined to 5. The value stored in   *
 * ‘r’ is the result of the expression (a*2), which is equal to 10.     *
 * Hence the output of this code will be 10.                            *                                                   *
 ************************************************************************/ 
#define a 2
int main()
{
    int r;
    #define a 5
    r=a*2;
    cout << r << endl;
    return 0;
}