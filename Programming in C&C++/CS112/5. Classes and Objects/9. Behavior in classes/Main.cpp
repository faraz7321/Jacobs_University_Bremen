/****************************************************************
  The main class definition for this project. Shows that only   *
  the public functions are accessible to the function in which  *
  the object was created.               *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {

    Student ahtasham;

    // Accessing a variable without setting it. The call is successful but the result is a junk value!
    cout << "GPA of student is " << ahtasham.getGPA() << endl; 

    // Accessing a variable after setting it. The call is successful and the result is the set value!
    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl;

    // Accessing a variable after updating it. The call is successful and the result is the updated set value!
    ahtasham.setAge(25);
    cout << "Age of Ahtasham after update is " << ahtasham.getAge() << endl;

    // Accessing another variable after setting it. The call is successful and the result is the set value!
    ahtasham.setName("Ahtasham");
    cout << "Name of student is " << ahtasham.getName() << endl;

    // Accessing another variable after setting it. The call is successful and the result is the set value!
    ahtasham.setGPA(3.521);
    cout << "GPA of student is " << ahtasham.getGPA() << endl;
}
