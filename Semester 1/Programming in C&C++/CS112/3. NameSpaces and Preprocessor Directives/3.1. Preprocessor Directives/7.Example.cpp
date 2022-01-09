// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * Error: hello undeclared. An error is thrown when the code shown below*
 * is executed because before the second call to the printf function,   *
 * the macro hello was undefined using #undef.                          *                                                   *
 ************************************************************************/ 
#define hello 10
int main()
{
    cout << hello << endl;
    #undef hello
    return 0;
}
