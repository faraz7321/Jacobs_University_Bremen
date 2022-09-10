/****************************************************************
 This file contains the definition of the SubSubClass Class. It *
 contains all the public and private attributes and function    *
 definitions.                                                   *
 ***************************************************************/

#include <iostream>
#include <string>
#include "SubClass.cpp"

using namespace std;

class SubSubClass : public SubClass {
    private:
        //Private attributes
        int privatesubsubvar1;
        
        //Private Behavior
        void privatesubsubfunc();
    
    protected:
        //Private attributes
        int protectedsubsubvar1;
        
        //Private Behavior
        void protectedsubsubfunc();

    public:
        //Public Attributes
        int publicsubsubvar1;

        // Public Constructors

        // Public Destructor

        //Public Behavior
        void publicsubsubfunc();

        void setprivatesubsubvar(int privatesubsubvar);
        void setprotectedsubsubvar(int protectedsubsubvar);
        void setpublicsubsubvar(int publicsubsubvar);

        int getprivatesubsubvar();
        int getprotectedsubsubvar();
        int getpublicsubsubvar();   

        int checkingAccesstoPublicSubvar();
        int checkingAccesstoProtectedSubvar();
        int checkingAccesstoPublicSupervar();
        int checkingAccesstoProtectedSupervar();     
};
