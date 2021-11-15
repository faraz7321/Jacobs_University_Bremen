/*
CH-230-A
Critter.h
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <string> // defines standard C++ string class

/* First C++ class */
class Critter
{
private: // data members are private
    std::string name;
    float hunger{};
    int boredom{};
    double height{};
    //scale the value
    float to_float(int newhunger);
    //scales back the value
    int to_int(float newhunger);

public: // business logic methods are public
    // setter methods
    void setName(std::string &newname);
    void setHunger(int newhunger);
    void setBoredom(int newboredom);
    // getter method
    int getHunger();
    // service method
    void print();
};