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
    double *arr;

public:
    //constructors
    Vector();
    Vector(int, double *);
    Vector(const Vector &);
    //destructors
    ~Vector();

    // getters and setters
    int getSize();
    double *getVector();
    void setSize(int size);
    void setVector(double *);

    // calculations methods
    double norm();
    /**
     * @brief add 2 vectors
     * 
     * @return Vector 
     */
    Vector add(const Vector) const;
    /**
     * @brief subtract vectors
     * 
     * @return Vector 
     */
    Vector sub(const Vector) const;
    /**
     * @brief calculates scalar product
     * 
     * @return double 
     */
    double scalarProd(const Vector) const;

    //service method
    void toString();
};
