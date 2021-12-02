/****************************************************************
  The main class definition for this project.                   *
*****************************************************************/

#include "StudentClass.cpp"

using namespace std;

int main() {
  cout << "We are going to create an object Ahtasham in the following scope. " << endl;
  cout << "****************************************************************" << endl;
  {
    Student ahtasham;

    cout << "GPA of student is " << ahtasham.getGPA() << endl;

    ahtasham.setAge(20);
    cout << "Age of Ahtasham is " << ahtasham.getAge() << endl;

    ahtasham.setAge(25);
    cout << "Age of Ahtasham after update is " << ahtasham.getAge() << endl;

    ahtasham.setName("Ahtasham");
    cout << "Name of student is " << ahtasham.getName() << endl;

    ahtasham.setGPA(3.521);
    cout << "GPA of student is " << ahtasham.getGPA() << endl;
  }

  cout << "****************************************************************" << endl;
  cout << "We are working in main function now. " << endl;
  
  cout << "We are going to create an object Afraz in the following scope. " << endl;
  cout << "****************************************************************" << endl;
  Student afraz(2020041, "Afraz", 3.2);
  
  cout << "GPA of Afraz is " << afraz.getGPA() << endl << endl;
  cout << "Name of Afraz is " << afraz.getName() << endl;
  afraz.~Student();
  
  cout << "GPA of Afraz is " << afraz.getGPA() << endl;
  cout << endl << endl;
  cout << "Name of Afraz is " << afraz.getName() << endl;
  cout << "****************************************************************" << endl;

}
