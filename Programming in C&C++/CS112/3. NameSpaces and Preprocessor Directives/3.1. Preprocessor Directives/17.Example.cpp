// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * In the code shown below, if the identifier san is defined, then its  *
 * value is redefined and changed to 20. It is then printed. Hence the  *
 * output is 20.                                                        *
 ************************************************************************/ 
#define san 10
main()
{
    #ifdef san
        #define san 20
    #endif
    cout << san << endl;
}