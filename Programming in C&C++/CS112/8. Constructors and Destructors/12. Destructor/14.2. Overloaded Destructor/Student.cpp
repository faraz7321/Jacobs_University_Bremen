/****************************************************************
  The main class definition for this project. Shows that the    *
  default builtin destructor can be overloaded to "destroy"     *
  objects in the desired manner instead of doing nothing when   *
  an object goes out of scope.                                  *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
// The default destructor has been overridden in the class Student
// and the new destructor sets GPA to 0 whenever an object Student
// is destroyed.
// A cout command in Destructor function shows that the default
// destructor has been overridden and in fact the new function 
// written by us in the class will be called when the object gets
// out of scope.

//Other functions and behavior of Student remain the same as shown below.
    Student ahtasham;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl;
}
