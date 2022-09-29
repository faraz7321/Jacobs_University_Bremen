/***************************************************************
 This file contains the description of the behavior for Student*
 Class. Contains all the function definitions.                 *
 ***************************************************************/

#include "SubClass.h"

/*****************************************************************
    These are constructor functions needed for object declaration*
******************************************************************/
SubClass::SubClass() {
    cout << "Overriding Constructor for SubClass. Constructor of SubClass without parameters called." << endl;
}

SubClass::SubClass(int a, int b) {
    cout << "Overriding Constructor for SubClass. Constructor of SubClass with parameters called." << endl;
}

/*****************************************************************
    This is destructor function needed for memory deallocation   *
    for the object                                               *
******************************************************************/

/*****************************************************************
    These are all functions needed for public definition         *
******************************************************************/
void SubClass::privatesubfunc() {
    cout << "Private SubClass Function Called" << endl;
}

void SubClass::protectedsubfunc() {
    cout << "Protected SubClass Function Called" << endl;
}

void SubClass::publicsubfunc() {
    cout << "Public SubClass Function Called" << endl;
}

void SubClass::setprivatesubvar(int privatesubvar) {
    privatesubvar1 = privatesubvar;
}

void SubClass::setprotectedsubvar(int protectedsubvar) {
    protectedsubvar1 = protectedsubvar;
}

void SubClass::setpublicsubvar(int publicsubvar) {
    publicsubvar1 = publicsubvar;
}

int SubClass::getprivatesubvar() {
    return privatesubvar1;
}

int SubClass::getprotectedsubvar() {
    return protectedsubvar1;
}

int SubClass::getpublicsubvar() {
    return publicsubvar1;
}        
