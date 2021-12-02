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
       
    /* Uncommenting the following line will give error. */
//    a.privatesuperfunc();
    return 0;
}
