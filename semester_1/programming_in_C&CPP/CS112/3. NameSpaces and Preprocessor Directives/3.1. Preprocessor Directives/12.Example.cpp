// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * Macro definition is global even if it is appears within the function *
 * scope. In this case the macro sf is defined in the function f().     *
 * Hence it results in a compile time error.                            *                                                   *
 ************************************************************************/ 
void f()
{
    #define sf 100
    cout << sf << endl;
}
int main()
{
    #define sf 99;
    f();
    cout << sf << endl;
    return 0;
}
