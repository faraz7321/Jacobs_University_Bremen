/****************************************************************
  The main class definition for this project. Shows that the    *
  default builtin constructor that does nothing for the objects *
  is always called whenever a new object is made.               *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
//When an object is created, the default constructor is called first. It is defined as
//ClassName(), and does not set or get any parameter. Hence, the result of accessing
//a variable GPA without setting it is a junk value and only after setting it can you
//get the correct value.

//An object Student is created here with the default builtin constructor that does not
//initialize any variable. Only after age has been set can its stored value be retrieved.
    Student ahtasham;

    cout << "GPA of student is " << ahtasham.getGPA() << endl;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl;
}
