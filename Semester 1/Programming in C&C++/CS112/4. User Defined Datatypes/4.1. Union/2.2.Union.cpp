#include<iostream>

using namespace std;

/*********************************************************************************
 * Note that every attribute is displayed correctly.
 * Because Union only stores the last variable changed in the code correctly, and
 * for the earlier initialized variables inside a Union, the value MAY not be 
 * necessarily correct. But you initialize and use the same variable at the same
 * time, so all values are now displayed correctly. 
 * 
 * Here, all the members are getting printed very well because one member is being
 * used at a time.
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
    cout << "\n\nEmployee Id : " << E.Id;

    cout << "\nEnter Employee Name : ";
    cin >> E.Name;
    cout << "\nEmployee Name : " << E.Name;

    cout << "\nEnter Employee Age : ";
    cin >> E.Age;
    cout << "\nEmployee Age : " << E.Age;

    cout << "\nEnter Employee Salary : ";
    cin >> E.Salary;
    cout << "\nEmployee Salary : " << E.Salary<<endl;
    cout<<sizeof(Employee)<<endl;
    
    return 0;
}

/*
    Output :

        Enter Employee Id : 1
        Employee Id : 1
        
        Enter Employee Name : Hashim
        Employee Name : Hashim
        
        Enter Employee Age : 29
        Employee Age : 29
        
        Enter Employee Salary : 45000
        Employee Salary : 45000
*/
