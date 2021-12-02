/**********************************************************************
 * Structure is a collection of variables of different data types     *
 * under a single name. It is similar to a class in that, both hold a * 
 * collecion of data of different data types.                         *
 *                                                                    *
 **********************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
 * For example: You want to store some information about a person:    *
 * his/her name, citizenship number and salary. You can easily create *
 * different variables name, citNo, salary to store these information *
 * separately.                                                        *
 *                                                                    *
 * However, in the future, you would want to store information about  *
 * multiple persons. Now, you'd need to create different variables for*
 *  each information per person: name1, citNo1, salary1, name2,       *
 * citNo2, salary2.                                                   *
 *                                                                    *
 * You can easily visualize how big and messy the code would look.    *
 * Also, since no relation between the variables (information) would  *
 * exist, it's going to be a daunting task.                           *
 *                                                                    *
 * A better approach will be to have a collection of all related      *
 * information under a single name Person, and use it for every       *
 * person. Now, the code looks much cleaner, readable and efficient as*
 * well.                                                              *
 *                                                                    *
 * This collection of all related information under a single name     *
 * Person is a structure.                                             *
 **********************************************************************/

/**********************************************************************
 * The struct keyword defines a structure type followed by an         *
 * identifier (name of the structure).                                *
 * Then inside the curly braces, you can declare one or more members  *
 * (declare variables inside curly braces) of that structure.         *
 **********************************************************************/

/**********************************************************************
 * Here a structure person is defined which has three members: name,  *
 * age and salary.                                                    *
 *                                                                    *
 * When a structure is created, no memory is allocated.               *
 *                                                                    *
 * The structure definition is only the blueprint for the creating of *
 * variables. You can imagine it as a datatype. When you define an    *
 * integer as below:                                                  *
 * int foo;                                                           *
 * The int specifies that, variable foo can hold integer element only.*
 *  Similarly, structure definition only specifies that, what property*
 *  a structure variable holds when it is defined.                    *
 *                                                                    *
 * Note: Remember to end the declaration with a semicolon (;).        *
 **********************************************************************/

struct Person
{
  char name[50];
  int age;
  float salary;
};
