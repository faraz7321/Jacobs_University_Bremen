// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The below code will result in an error because a macro cannot be     *
 * defined using a simple assignment operator. In the code shown below, *
 * the value of sf is changed to 100 using the assignment operator. This*
 * causes an error.                                                     *                                                   *
 ************************************************************************/ 
#define sf 10
int main()
{
	#undef sf
	int sf=69;
    if(sf==100)
        cout << "good" << endl;
    else
    {
        cout <<sf<<" bad \n" << endl;
        sf = 100;
    }
    cout << sf << endl;
    return 0;
}
