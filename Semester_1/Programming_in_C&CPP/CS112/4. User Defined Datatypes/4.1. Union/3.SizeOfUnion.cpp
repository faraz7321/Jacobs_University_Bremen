#include<iostream>

using namespace std;

/*********************************************************************************
 * Example for comparing size of Union and Structure. 
 * long = 8 bytes. 
 * int = 4 bytes
 * char = 1 byte each
 *********************************************************************************/

struct Employee1
{
    int Id;
    char Name[25];
    int Age;
    long Salary;
};

union Employee
{
    int Id;
    char Name[25];
    int Age;
    long Salary;
};

int main()
{
    cout << "Size of Structure Employee1 is : " << sizeof(Employee1) << endl;
    cout << "Size of Union Employee is : " << sizeof(Employee) << endl;
    
    return 0;
}

/*
    Output :
        Size of Structure Employee1 is : 48
        Size of Union Employee is : 32
*/