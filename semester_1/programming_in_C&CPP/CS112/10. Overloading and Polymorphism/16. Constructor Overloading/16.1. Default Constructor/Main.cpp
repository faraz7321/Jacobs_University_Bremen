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

    /* Since all functions given below are inherited as public functions
       in the SubClass, hence the public functions declared in SuperClass
       can be accessed publicly using the SubClass object. However, private
       functions and attributes of SuperClass can not be accessed from outside
       the SuperClass and protected functions and attributes from outside the
       SuperClass and from outside the SubClass. */
       
       
    a.publicsuperfunc();

    /* Uncommenting any of the two lines will give error. */

//    a.protectedsuperfunc();
//    a.privatesuperfunc();
    return 0;
}
