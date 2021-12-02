/****************************************************************
  The main class definition for this project.                   *
*****************************************************************/

#include "SubClass.cpp"

using namespace std;

int main() {
    SubClass a;

    a.publicsubfunc();

    /* Since all functions given below are either private or protected
       in the SubClass, hence they can not be accessed from main function.
       Uncommenting any of the two lines will give error. */

//    a.protectedsubfunc();
//    a.privatesubfunc();

    /* Since all functions given below are inherited as private functions
       in the SubClass, hence they can not be accessed from outside the SubClass.
       Uncommenting any of the three lines (including the public function of 
       SuperClass) will give error. */
       
//    a.publicsuperfunc();
//    a.protectedsuperfunc();
//    a.privatesuperfunc();

    return 0;
}
