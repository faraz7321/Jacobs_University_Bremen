#include <iostream>

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

class Taxi : public Car
{
    private:
        int passengers_nr;
    public:
        //parametric constructor
        Taxi(std::string nbrand, std::string nmodel, double nprice,
             int pas) : Car(nbrand, nmodel, nprice){ passengers_nr = pas;}

        //destructor
        ~Taxi() {cout << "Destructor for Taxi was called!\n"; }

        //print method
        void print() const{ cout << "Taxi is "
        << model << " and " << brand << " and costs " << price << " and has a limit of "
        << passengers_nr << endl; }

};
int main()
{
    Taxi t("model 1", "brand 23", 3484.44, 4);

    t.print();

    return 0;
}
