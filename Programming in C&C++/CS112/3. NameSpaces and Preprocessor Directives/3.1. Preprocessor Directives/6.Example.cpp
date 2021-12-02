// standard macro names
#include <iostream>
using namespace std;

/************************************************************************ 
 * The code shown below is an illustration of the preprocessor directive*
 * #if. The value of the defined identifier max is 100. On checking the *
 * condition (100%10==1), which is false, the statements after #if are  *
 * not executed till #endif is encountered. Hence the output is foundry.*                                                   *
 ************************************************************************/ 
#define max 100
int main()
{
    #if(max%10)
      cout << "san" << endl;
    #endif
    cout << "foundry" << endl;
    return 1;
}
