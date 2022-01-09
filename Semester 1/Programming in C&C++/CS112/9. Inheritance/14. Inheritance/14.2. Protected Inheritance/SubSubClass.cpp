/***************************************************************
 This file contains the description of the behavior for Student*
 Class. Contains all the function definitions.                 *
 ***************************************************************/

#include "SubSubClass.h"

/*****************************************************************
    These are constructor functions needed for object declaration*
******************************************************************/

/*****************************************************************
    This is destructor function needed for memory deallocation   *
    for the object                                               *
******************************************************************/

/*****************************************************************
    These are all functions needed for public definition         *
******************************************************************/
void SubSubClass::privatesubsubfunc() {
    cout << "Private SubSubClass Function Called" << endl;
}

void SubSubClass::protectedsubsubfunc() {
    cout << "Protected SubSubClass Function Called" << endl;
}

void SubSubClass::publicsubsubfunc() {
    cout << "Public SubSubClass Function Called" << endl;
}

void SubSubClass::setprivatesubsubvar(int privatesubsubvar) {
    privatesubsubvar1 = privatesubsubvar;
}

void SubSubClass::setprotectedsubsubvar(int protectedsubsubvar) {
    protectedsubsubvar1 = protectedsubsubvar;
}

void SubSubClass::setpublicsubsubvar(int publicsubsubvar) {
    publicsubsubvar1 = publicsubsubvar;
}

int SubSubClass::getprivatesubsubvar() {
    return privatesubsubvar1;
}

int SubSubClass::getprotectedsubsubvar() {
    return protectedsubsubvar1;
}

int SubSubClass::getpublicsubsubvar() {
    return publicsubsubvar1;
}        

/* Notice that I am accessing protected members of the SubClass and 
   of the SuperClass in the following functions, which I can not
   access outside of the class in which they are defined or without 
   inheriting them with public or protected inheritance through to
   the Base Class (SuperClass). The level at which the first private
   inheritance is encountered, access to even public or protected 
   functions and attributes will also be lost beyond that level. */

int SubSubClass::checkingAccesstoPublicSubvar() {
    cout << "Accessing Public SubClass Variable from within SubSubClass. " << endl;
    return publicsubvar1;
}

int SubSubClass::checkingAccesstoProtectedSubvar() {
    cout << "Accessing Protected SubClass Variable from within SubSubClass. " << endl;
    return protectedsubvar1;
}

int SubSubClass::checkingAccesstoPublicSupervar() {
    cout << "Accessing Public SuperClass Variable from within SubSubClass. " << endl;
    return publicsupervar1;
}

int SubSubClass::checkingAccesstoProtectedSupervar() {
    cout << "Accessing Protected SuperClass Variable from within SubSubClass. " << endl;
    return protectedsupervar1;
}