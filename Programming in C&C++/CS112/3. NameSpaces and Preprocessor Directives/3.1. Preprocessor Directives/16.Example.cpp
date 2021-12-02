// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The code shown above illustrates #define, #ifdef, #else, #endif.     *
 * Since the identifier hello is defined (condition of #if is true),    *
 * another identifier names hi is defined and it’s value is 4. If hello *
 * was not defined, then the value of hi would be 5.                    *
 ************************************************************************/ 

int main()
{
    #ifdef hello
        #define hi 4
    #else
        #define hi 5
    #endif
    cout << hi << endl;
    return 0;
}
