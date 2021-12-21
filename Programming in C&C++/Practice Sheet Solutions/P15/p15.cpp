#include <iostream>
#include <string.h>

using namespace std;

class Car
{
    protected:
    //protected properties
        std::string brand;
        std::string model;
        double price;

    public:
        //parametric constructor
        Car(std::string nbrand, std::string nmodel,
            double nprice) { model = nmodel; brand = nbrand;
            price = nprice;}

        //destructor
        ~Car() { cout << "Deconstructor was called!\n"; }

        //setter for model name
        void setModel(std::string xmodel) { model = xmodel;}

        //extra : print method
        void print(){cout << "Car is " << brand << " and " << model << " and has a price of " << price <<".\n"; }
};
int main()
{
    Car A("brand 1", "model 23", 2345.789);
    A.setModel("model 23+");

    A.print();

    return 0;
}
