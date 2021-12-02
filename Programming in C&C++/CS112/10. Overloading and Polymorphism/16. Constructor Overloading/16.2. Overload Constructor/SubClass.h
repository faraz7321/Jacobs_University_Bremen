/****************************************************************
 This file contains the definition of the Student Class. It     *
 contains all the public and private attributes and function    *
 definitions.                                                   *
 ***************************************************************/

#include <iostream>
#include <string>
#include "SuperClass.cpp"

using namespace std;

class SubClass : public SuperClass {
    private:
        //Private attributes
        int privatesubvar1;
        
        //Private Behavior
        void privatesubfunc();
    
    protected:
        //Private attributes
        int protectedsubvar1;
        
        //Private Behavior
        void protectedsubfunc();

    public:
        //Public Attributes
        int publicsubvar1;

        // Public Constructors
        SubClass();
        
        // Public Destructor

        //Public Behavior
        void publicsubfunc();

        void setprivatesubvar(int privatesubvar);
        void setprotectedsubvar(int protectedsubvar);
        void setpublicsubvar(int publicsubvar);

        int getprivatesubvar();
        int getprotectedsubvar();
        int getpublicsubvar();        
};
