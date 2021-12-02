// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The output of the code shown below is Dollar. Since the macro CC is  *
 * defined as US at the beginning of the code, it satisfies the         *
 * condition #elif(CC==US). Hence “Dollar” is printed.                  *                                                   *
 ************************************************************************/ 
#define PAKISTAN 1
#define US 2
#define CC US
int main()
{
    #if CC==PAKISTAN
        cout << "Rupee" << endl;
    #elif CC==US
        cout << "Dollar" << endl;
    #else
        cout << "Euro" << endl;
    #endif 
    return 0;
}