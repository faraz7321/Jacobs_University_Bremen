/****************************************************************
  The main class definition for this project.                   *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
    Student ahtasham;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl;

    ahtasham.setAge(25);
    cout << "Age of Ahtasham after update is " << ahtasham.getAge() << endl;

    ahtasham.setName("Ahtasham");
    cout << "Name of student is " << ahtasham.getName() << endl;

    ahtasham.setGPA(3.521);
    cout << "GPA of student is " << ahtasham.getGPA() << endl;
}
