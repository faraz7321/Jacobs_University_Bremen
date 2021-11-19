/*
CH-230-A
Vector.h
Faraz Ahmad
fahmad@jacobs.university.de
 */

class Vector
{
private:
    int size;
    double element;
    double *ptr;

public:
    //constructors
    Vector();
    Vector(Vector &v);
    //destructor
    ~Vector();
    //getter and setter methods
    int getSize();
    //service method
    void toString();
};

Vector::Vector()
{
}

Vector::~Vector()
{
}
