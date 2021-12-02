/***************************************************************
 This file contains the description of the behavior for Student*
 Class. Contains all the function definitions.                 *
 ***************************************************************/

#include "StudentClass.h"

/*****************************************************************
    These are constructor functions needed for object declaration*
******************************************************************/

/*****************************************************************
    This is destructor function needed for memory deallocation   *
    for the object                                               *
******************************************************************/
Student::~Student() {
    name = "";
    gpa = 0;
    regno = 0;
    cout << "Our overloaded destructor has been called" << endl;
}

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