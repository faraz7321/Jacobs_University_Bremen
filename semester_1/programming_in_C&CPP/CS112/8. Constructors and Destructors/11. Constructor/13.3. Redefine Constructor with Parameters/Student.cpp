/****************************************************************
  The main class definition for this project. Shows that the    *
  default builtin constructor when overridden by another        *
  will not work anymore once there is another constructor that  *
  has been declared with or without parameters.                 *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
// This example gives an error as there is only one constructor that
// requires providing three parameters. So, constructor with no parameters 
// can no longer be used when an object is made without giving any parameters 

    Student ahtasham;

    Student afraz(2020041, "Afraz", 3.2);

    cout << "GPA of Afraz is " << afraz.getGPA() << endl << endl;
    cout << "Name of Afraz is " << afraz.getName() << endl << endl;

    cout << "GPA of student is " << ahtasham.getGPA() << endl;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl;
}
