/***************************************************************
 This file contains the description of the behavior for Student*
 Class. Contains all the function definitions.                 *
 ***************************************************************/

#include "StudentClass.h"

/*****************************************************************
    These are constructor functions needed for object declaration*
******************************************************************/
Student::Student(int regno1, string nameOfStudent, double gpaOfStudent) {
    regno = regno1;
    name = nameOfStudent;
    gpa = gpaOfStudent;
    cout << "Our constructor with three parameters has been called" << endl;
}

/*****************************************************************
    This is destructor function needed for memory deallocation   *
    for the object                                               *
******************************************************************/

/*****************************************************************
    These are all functions needed for public definition         *
******************************************************************/
void Student::setRegNo(int reg) {
    regno = reg;
}

void Student::setAge(int ageOfStudent) {
    age = ageOfStudent;
}

void Student::setName(string nameOfStudent) {
    name = nameOfStudent;
}

void Student::setGPA(double cgpa){
    gpa = cgpa;
}

int Student::getRegNo() {
    return regno;
}

int Student::getAge() {
    return age;
}

string Student::getName() {
    return name;
}

double Student::getGPA(){
    return gpa;
}