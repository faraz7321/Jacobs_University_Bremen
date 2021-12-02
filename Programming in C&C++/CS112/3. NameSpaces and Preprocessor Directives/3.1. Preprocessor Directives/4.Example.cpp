// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The code shown below illustrates the preprocessor directive #ifndef. *
 * If the identifier checked is not defined, then the statements        *
 * following #ifndef are executed. Here, since the identifier max is not*
 * defined, the statement after #ifndef is executed. Hence the output is*
 * hellohi                                                              *
 ************************************************************************/ 
int main()
{
    #ifndef max
      cout << "hello" << endl;
    #endif
    cout << "hi" << endl;
    return 1;
}
