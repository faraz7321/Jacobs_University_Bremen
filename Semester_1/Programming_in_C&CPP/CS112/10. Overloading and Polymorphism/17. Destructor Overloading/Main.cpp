/****************************************************************
  The main class definition for this project.                   *
*****************************************************************/

#include "SubClass.cpp"

using namespace std;

int main() {
    /******************************************************************
     * Note that when the object is created for subClass, first the   *
     * constructor of Base class is called followed by the constructor*
     * of derived class. Order is important to remember.              *
     *                                                                *
     * Note that when the object is destroyed for subClass, first the *
     * destructor of Derived class is called followed by destructor   *
     * of Super/Base class. Order is important to remember.           *
     ******************************************************************/
    cout << "Creating objects. Constructors will be called. " << endl << endl;

    SubClass a;
    
    cout << "Object created. Constructors called. " << endl << endl;
    cout << "Program ending. Destructors of objects will be called. " << endl << endl;    
    return 0;
}
