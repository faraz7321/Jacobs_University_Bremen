/****************************************************************
  The main class definition for this project. Shows that the    *
  default builtin constructor can be overridden with multiple   *
  constructors, as many as one can come up with, and the        *
  constructor called depends on the way the object is declared. *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
    cout << "******** The Student with the overridden constructor without parameters ********" << endl;
    Student ahtasham;
    cout << "GPA of student is " << ahtasham.getGPA() << endl;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl << endl << endl;

    cout << "******** The Student with the overridden constructor with three parameters ********" << endl;
    Student afraz(2020041, "Afraz", 3.2);
    cout << "GPA of Afraz is " << afraz.getGPA() << endl;
    cout << "Name of Afraz is " << afraz.getName() << endl;
}
