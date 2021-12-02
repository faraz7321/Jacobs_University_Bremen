// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The output of the code shown below is 100. If the identifier hello is*
 * defined, then it is undefined and redefined. It’s new value is 100.  *
 * If the identifier was not defined, it would be defined with a value  *
 * of 200.                                                              *                                                   *
 ************************************************************************/ 
#define hello 10
int main()
{
    #ifdef hello
        #undef hello
        #define hello 100
    #else
        #define hello 200
    #endif
    cout << hello << endl;
    return 0;
}