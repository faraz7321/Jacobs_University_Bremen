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
     ******************************************************************/
    SubClass a(1,2);

    return 0;
}
