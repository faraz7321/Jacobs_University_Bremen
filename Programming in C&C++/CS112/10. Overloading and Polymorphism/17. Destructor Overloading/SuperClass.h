/****************************************************************
 This file contains the definition of the Student Class. It     *
 contains all the public and private attributes and function    *
 definitions.                                                   *
 ***************************************************************/

#include<iostream>
#include<string>

using namespace std;

class SuperClass {
    private:
        //Private attributes
        int privatesupervar1;
        
        //Private Behavior
        void privatesuperfunc();
    
    protected:
        //Private attributes
        int protectedsupervar1;
        
        //Private Behavior
        void protectedsuperfunc();

    public:
        //Public Attributes
        int publicsupervar1;

        // Public Constructors
        SuperClass();
        
        // Public Destructor
        ~SuperClass();

        //Public Behavior
        void publicsuperfunc();

        void setprivatesupervar(int privatesupervar);
        void setprotectedsupervar(int protectedsupervar);
        void setpublicsupervar(int publicsupervar);

        int getprivatesupervar();
        int getprotectedsupervar();
        int getpublicsupervar();     
};
