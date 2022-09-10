/***************************************************************
 This file contains the description of the behavior for Student*
 Class. Contains all the function definitions.                 *
 ***************************************************************/

#include "SuperClass.h"

/*****************************************************************
    These are constructor functions needed for object declaration*
******************************************************************/
SuperClass::SuperClass(int a, int b) {
    cout << "Overriding Constructor for SuperClass. Constructor of SuperClass with parameters called." << endl;
}

SuperClass::SuperClass() {
    cout << "Overriding Constructor for SuperClass. Constructor of SuperClass without parameters called." << endl;
}

/*****************************************************************
    This is destructor function needed for memory deallocation   *
    for the object                                               *
******************************************************************/

/*****************************************************************
    These are all functions needed for public definition         *
******************************************************************/
void SuperClass::privatesuperfunc() {
    cout << "Private SuperClass Function Called" << endl;
}

void SuperClass::protectedsuperfunc() {
    cout << "Protected SuperClass Function Called" << endl;
}

void SuperClass::publicsuperfunc() {
    cout << "Public SuperClass Function Called" << endl;
}

void SuperClass::setprivatesupervar(int privatesupervar) {
    privatesupervar1 = privatesupervar;
}

void SuperClass::setprotectedsupervar(int protectedsupervar) {
    protectedsupervar1 = protectedsupervar;
}

void SuperClass::setpublicsupervar(int publicsupervar) {
    publicsupervar1 = publicsupervar;
}

int SuperClass::getprivatesupervar() {
    return privatesupervar1;
}

int SuperClass::getprotectedsupervar() {
    return protectedsupervar1;
}

int SuperClass::getpublicsupervar() {   
    return publicsupervar1;
}        
