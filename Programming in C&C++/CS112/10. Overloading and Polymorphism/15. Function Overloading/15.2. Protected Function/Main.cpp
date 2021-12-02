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

    /* Note that protected and public functions inherited in protected mode can be accessed
       from within the derived classes as the following functions of SubSubClass can
       access the protected and private members. */

       a.checkingAccesstoProtectedSubvar();
       a.checkingAccesstoProtectedSupervar();
       a.checkingAccesstoPublicSubvar();
       a.checkingAccesstoPublicSupervar();

    /*********************************************************************************************
     * Since all functions given below are inherited as protected functions in the SubSubClass,  *
     * hence they can not be accessed from outside the SubClass directly as shown previously.    *
     * However, we have overloaded these functions and placed the overloaded functions as public *
     * functions. Hence, even the protected function of superclass becomes accessible here and   *
     * does not give error.                                                                      *
     *                                                                                           * 
     * Note that overloaded functions actually run the code given in the body of overloaded      *
     * function and not of the base/super class. Hence, the hierarchy is checked whenever a      *
     * function call is made. If the function with exact function signature is present in the    *
     * derived class (as is the case of overloaded functions), it will be used, and only if it is*
     * not found in derived class will the compiler then look for in the base/super class.       *
     *********************************************************************************************/
       
    a.publicsuperfunc();
    a.protectedsuperfunc();
    
    /* Uncommenting private or public non-overloaded functions will give error. */
//    a.privatesuperfunc();
//    a.publicsubfunc();
//    a.protectedsubfunc();
//    a.privatesubfunc();

    return 0;
}
