// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The output of the code shown below is 30. Since the identifier max is*
 * defined (the condition of #ifndef is true), hence another identifier,*
 * that is, min is defined and its value is equal to 30.                *
 ************************************************************************/ 
#define max 20
int main()
{
    #ifndef max
        #define min 10
    #else
        #define min 30
    #endif
    cout << min << endl;
    return 0;
}