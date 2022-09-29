#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Object3D
{
    private :
        string name;
    public :
        Object3D();
        Object3D(string &);
        virtual void volume() = 0;
};

Object3D :: Object3D(string &n)
{
    name = n;
}

class Sphere : public Object3D
{
    private :
        double radius;
    public :
        Sphere();
        Sphere(string&, double);
        void volume();
};

Sphere :: Sphere(string&n, double r) : Object3D(n) {radius = r;}

void Sphere :: volume()
{
    cout << "Volume of sphere is: " << 4/3 * M_PI * radius * radius *radius << endl;
}

class Cylinder : public Object3D
{
    private :
        double height;
        double radius;
    public :
        Cylinder();
        Cylinder(string&, double, double);
        void volume();
};

Cylinder :: Cylinder(string& n, double h, double r) : Object3D(n)
{
    height = h;
    radius = r;
}

void Cylinder :: volume()
{
    cout << "Volume of cylinder is: " << M_PI * radius* radius * height << endl;
}

class RectPrism : public Object3D
{
    private :
        double width;
        double length;
        double height;
    public :
        RectPrism();
        RectPrism(string&, double, double, double);
        void volume();

};

RectPrism :: RectPrism(string &n, double w, double l, double h) : Object3D(n)
        { width = w; length = l; height = h;}

void RectPrism :: volume()
{
    cout << "Volume of rectprism is: "<< width*length*height << endl;
}

class Cube : public Object3D
{
    private :
        double side;
    public :
        Cube();
        Cube(string&, double);
        void volume();

};

Cube :: Cube(string& n, double s) : Object3D(n)
{
    side = s;
}

void Cube :: volume()
{
    cout<<"Volume of cube is: " << side*side*side << endl;
}

int main(int argc, char *argv[])
{
    Object3D *arr[5];
    string n="sphere";
    arr[0] = new Sphere(n, 1.3);
    n = "rectprism";
    arr[1] = new RectPrism(n, 2.0, 3.0, 4.0);
    n = "cylinder";
    arr[2] = new Cylinder(n, 2.0, 1.3);
    n  ="cube";
    arr[3] = new Cube(n, 2.0);
    n = "rectprism2";
    arr[4] = new RectPrism(n, 1.0, 2.0, 3.5);

    int i;
    for(i=0; i<5; i++)
        arr[i]->volume();

    for(i=0; i<5; i++)
        delete arr[i];
    return 0;
}
