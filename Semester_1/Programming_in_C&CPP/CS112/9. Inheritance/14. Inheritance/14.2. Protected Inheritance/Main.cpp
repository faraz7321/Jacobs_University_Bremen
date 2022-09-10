/****************************************************************
  The main class definition for this project.                   *
*****************************************************************/

#include "SubSubClass.cpp"

using namespace std;

int main() {
    SubSubClass a;

    a.publicsubsubfunc();

    /* Since all functions given below are either private or protected
       in the SubSubClass, hence they can not be accessed from main function.
       Uncommenting any of the two lines will give error. */

//    a.protectedsubsubfunc();
//    a.privatesubsubfunc();

    /* Note that protected and pubic functions inherited in protected mode can be accessed
       from within the derived classes as the following functions of SubSubClass can
       access the protected and private members. */

       a.checkingAccesstoProtectedSubvar();
       a.checkingAccesstoProtectedSupervar();
       a.checkingAccesstoPublicSubvar();
       a.checkingAccesstoPublicSupervar();

    /* Since all functions given below are inherited as protected functions
       in the SubSubClass, hence they can not be accessed from outside the SubClass.
       Uncommenting any of the six lines (including the public function of SuperClass
       and/or SubClass) will give error. */
       
//    a.publicsuperfunc();
//    a.protectedsuperfunc();
//    a.privatesuperfunc();
//    a.publicsubfunc();
//    a.protectedsubfunc();
//    a.privatesubfunc();

    return 0;
}
