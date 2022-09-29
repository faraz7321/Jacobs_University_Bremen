/**********************************************************************
 * The meaning of Encapsulation, is to make sure that "sensitive" data*
 * is hidden from users. To achieve this, you must declare class      *
 * variables/attributes as private (cannot be accessed from outside   *
 * the class). If you want others to read or modify the value of a    *
 * private member, you can provide public get and set methods.        *
 *                                                                    *
 * Why is Encapsulation considered good?                              *
 * It is considered good practice to declare your class attributes as *
 * private (as often as you can). Encapsulation ensures better        *
 * control of your data, because you (or others) can change one part  *
 * of the code without affecting other parts.                         *
 * Because Encapsulation provides increased security of data          *
 **********************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
 * The salary attribute is private, which have restricted access.     *
 *                                                                    *
 * The public setSalary() method takes a parameter (s) and assigns it *
 * to the salary attribute (salary = s).                              *
 *                                                                    *
 * The public getSalary() method returns the value of the private     *
 * salary attribute.                                                  *
 *                                                                    *
 * Inside main(), we create an object of the Employee class. Now we   *
 * can use the setSalary() method to set the value of the private     *
 * attribute to 50000. Then we call the getSalary() method on the     *
 * object to return the value.                                        *
 **********************************************************************/

class Employee {
  private:
    // Private attribute
    int salary;

  public:
    // Setter
    void setSalary(int s) {
      salary = s;
    }
    // Getter
    int getSalary() {
      return salary;
    }
};

int main() {
  Employee myObj;
  myObj.setSalary(50000);
  cout << myObj.getSalary();
  return 0;
}
