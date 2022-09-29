#include<iostream>

using namespace std;
/*********************************************************************************
 * Note that only the salary is displayed correctly and the rest are all incorrect
 * (junk or not exactly as intended).
 * Because Union only stores the last variable changed in the code correctly, and
 * for the earlier initialized variables inside a Union, the value MAY not be 
 * necessarily correct. 
 * 
 * In the example, we can see that values of Id, Name and Age members of 
 * union got corrupted because final value assigned to the variable has occupied 
 * the memory location and this is the reason that the value of salary member is 
 * getting printed very well. 
 *********************************************************************************/
union Employee
{
    int Id;
    char Name[25];
    int Age;
    long Salary;
};

int main()
{
    Employee E;

    cout << "\nEnter Employee Id : ";
    cin >> E.Id;

    cout << "\nEnter Employee Name : ";
    cin >> E.Name;

    cout << "\nEnter Employee Age : ";
    cin >> E.Age;

    cout << "\nEnter Employee Salary : ";
    cin >> E.Salary;

    cout << "\n\nEmployee Id : " << E.Id;
    cout << "\nEmployee Name : " << E.Name;
    cout << "\nEmployee Age : " << E.Age;
    cout << "\nEmployee Salary : " << E.Salary;

    return 0;
}

/*
    Output :

        Enter Employee Id : 1
        Enter Employee Name : Hashim
        Enter Employee Age : 29
        Enter Employee Salary : 45000

        Employee Id : -20536
        Employee Name : ?$?$  ?
        Employee Age : -20536
        Employee Salary : 45000
*/