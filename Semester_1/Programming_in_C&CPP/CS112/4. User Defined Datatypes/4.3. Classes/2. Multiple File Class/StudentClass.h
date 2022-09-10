/****************************************************************
 This file contains the definition of the Student Class. It     *
 contains all the public and private attributes and function    *
 definitions.                                                   *
 ***************************************************************/

#include<iostream>
#include<string>

using namespace std;

class Student {
    private:
        //Private attributes
        int regno, age;
        string name;
        double gpa;
        
        //Private Behavior
    public:
        //Public Attributes

        //Public get value methods
        int getRegNo();
        int getAge();
        string getName();
        double getGPA();
        
        //Public set value methods
        void setRegNo(int);
        void setAge(int);
        void setName(string);
        void setGPA(double);
};
