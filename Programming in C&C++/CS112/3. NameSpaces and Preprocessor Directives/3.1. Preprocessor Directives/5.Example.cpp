// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The output to the above code will be no. Since we have used the      *
 * preprocessor directive, #ifndef and defined the identifier san, “yes”*
 * is not printed. Hence only “no” is printed as output.                *                                                   *
 ************************************************************************/ 
#define san 557
int main()
{
    #ifndef san
      cout << "yes" << endl;
    #endif
    cout << "no" << endl;
    return 1;
}
