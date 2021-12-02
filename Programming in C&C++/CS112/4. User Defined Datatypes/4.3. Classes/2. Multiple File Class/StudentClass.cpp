/***************************************************************
 This file contains the description of the behavior for Student*
 Class. Contains all the function definitions.                 *
 ***************************************************************/

#include "StudentClass.h"

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