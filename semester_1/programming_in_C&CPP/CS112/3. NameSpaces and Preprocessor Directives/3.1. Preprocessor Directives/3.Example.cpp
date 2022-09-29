// standard macro names
#include <iostream>
using namespace std;

/*********************************************************************** 
 * The code shown below results in an error.                           *
 * This is because the preprocessor #endif is missing in the code.     *
 * If the identifier is defined, then the statements following #ifdef  *
 * are executed till #endif is encountered.                            *
 ************************************************************************/ 
#define max 100
int main()
{
    #ifdef max
      cout << "hello";
    #endif
      return 0;
}
