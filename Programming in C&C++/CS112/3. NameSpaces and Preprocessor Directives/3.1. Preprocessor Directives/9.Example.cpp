// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * Suppose the values given for ‘p’ and ‘q’ are 10 and 15 respectively. *
 * Then the output of the code shown below is 15. Since the condition   *
 * given for #elif is true, the value stored in ‘q’ will be printed,    *
 * that is 15.                                                          *                                                   *
 ************************************************************************/ 
int main()
{
    int p,q;
    cout << "Enter two numbers\n";
    cin >> p >> q;
    #if(4<2)
        cout << p << endl;
    //#elif(2>-1)
    //    cout << q << endl;
    #else
        cout << "bye" << endl;
    #endif
}
