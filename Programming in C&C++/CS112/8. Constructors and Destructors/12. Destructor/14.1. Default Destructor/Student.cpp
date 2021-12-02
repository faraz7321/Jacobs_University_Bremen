/****************************************************************
  The main class definition for this project. Shows that the    *
  default builtin destructor that does nothing for the objects  *
  is always called whenever the object gets out of scope even if*
  an explicit call to the destructor is not made.               *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
// When an object is finished or gets out of scope (e.g., function ends or goes out of braces 
// in loops), the default destructor is called. It is defined as ~ClassName(), and
// does not do anything in reality. Hence, although it did execute at the end of main function
// it does not show any lines.
    Student ahtasham;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl;
}
