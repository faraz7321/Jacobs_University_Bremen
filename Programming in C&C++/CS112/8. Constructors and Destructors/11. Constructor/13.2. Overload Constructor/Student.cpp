/****************************************************************
  The main class definition for this project. Shows that the    *
  default builtin constructor can be overloaded to initialize   *
  objects in the desired manner instead of doing nothing when   *
  a new object is made.                                         *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
// The default constructor has been overridden in the class Student
// and the new constructor sets GPA to 0 whenever an object Student
// is created.
// A cout command in Constructor function shows that the default
// constructor has been overridden and in fact the new function 
// written by us in the class will be called.

//Other functions and behavior of Student remain the same as shown below.
    Student ahtasham;

    cout << "GPA of student is " << ahtasham.getGPA() << endl;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl;
}
