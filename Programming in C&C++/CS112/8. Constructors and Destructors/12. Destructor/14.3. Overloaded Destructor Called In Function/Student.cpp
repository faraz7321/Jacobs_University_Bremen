/****************************************************************
  The main class definition for this project. Shows that the    *
  destructor can be called by the coder to "destroy" objects    *
  in the desired manner even when the object is within scope.   *
  However, note that things that have been mentioned in         *
  destructor are only assigned new values.                      *
  
  The object is not    *
  destroyed by the destructor really. Instead only the pointer  *
  pointing to the memory location of the object is removed from *
  the table as an object gets out of scope. So if the object is *
  within scope, a destructor does not delete it.                *       
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
  // Please note that exactly only one destructor can be created with no parameters
  // as opposed to as many constructors as possible.

  // Hence, a destructor can not have any parameters.
  cout << "We are going to create a object in the following scope. " << endl;
  cout << "****************************************************************" << endl;
  {
    Student ahtasham;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham before destructor is " << ahtasham.getAge() << endl;
    
    ahtasham.~Student();
    cout << "Age of Ahtasham after destructor is " << ahtasham.getAge() << endl;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham after destructor but setting it is " << ahtasham.getAge() << endl;

    cout << "Ahtasham is now going to be out of scope" << endl;
  }
  cout << "****************************************************************" << endl;
  cout << "We are working in main function now. " << endl;
}
